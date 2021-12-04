#include "stdafx.h"
#include "FinsHandle.h"

CFinsHandle::CFinsHandle()
{
	m_bEstablishCommunicationByFins = false;
	m_nIpNode = 0;
}

// 重写数据接收,用于协议识别
void CFinsHandle::OnDataRecv(char* pData, int nSize)
{
	if (nSize > 0)
	{	
		m_pRecvData.Append(pData, nSize);
		if (m_pRecvData.Size() >= FINS_TCP_HEAD_SIZE)
		{
			FINS_TCP_HEAD pHead;
			pHead.SetData(m_pRecvData.GetString());
			int nAllSize = pHead.GetLength();

			if (m_pRecvData.Size() >= nAllSize)
			{
				SetRecvComplete(nAllSize);
			}
		}
	}
}


// 重写数据接收,开始接收数据，用于协议识别
void CFinsHandle::OnBeginRecv()
{
	m_pRecvData.SetSize(0);
}

// 通讯关闭
void CFinsHandle::OnCloseConnect()
{
	m_bEstablishCommunicationByFins = false;
}


long CFinsHandle::ReadMemoryData(int nAddr, int nSize, FINS_DATA_TYPE::ENUM nType, __int16* pData)
{
	long nCode = 0;
	if(nCode = EstablishCommunicationByFins())
	{
		return nCode;
	}

	CMyString pSendData;

	// 获取发送内存
	int nAllSize;
	nAllSize  = FINS_TCP_HEAD_SIZE;
	nAllSize += FINS_CONTROL_HEAD_SIZE;
	nAllSize += FINS_MEMORY_AREA_READ_SIZE; 
	pSendData.SetSize(nAllSize);
	char* pBuff = pSendData.GetString();
	
	// 头部信息
	FINS_TCP_HEAD pHead;	
	pHead.nCommand = FINS_TCP_CMD_DATA;
	pHead.SetLength(nAllSize);		//长度
	pHead.GetData(pBuff);

	// control部分
	FINS_CONTROL_HEAD pControlHead;
	pControlHead.nDA1 = 0; 
	pControlHead.nSA1 = m_nIpNode;
	pControlHead.nCmd1 = 0x01;
	pControlHead.nCmd2 = 0x01;
	pControlHead.GetData(pBuff + FINS_TCP_HEAD_SIZE);

	// 数据部分
	FINS_MEMORY_AREA_READ pMemory;
	pMemory.nAreaCode = nType;
	pMemory.nAddr = nAddr;
	pMemory.nBitNo = 0;
	pMemory.nLength = nSize;
	pMemory.GetData(pBuff + FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE);
	
	//	// 发送数据
	CMyString pRecvData;
	nCode = SendSyncData(pSendData, pRecvData);
	if (nCode == 0)
	{
		// 先判断答复数据的头数据是否正确	
		if(nCode = CheckReplyDataIsError(pRecvData.GetString(), pRecvData.Size()))
		{
			return nCode;
		}

		// 数据头
		FINS_TCP_HEAD pHeadReply;
		pHeadReply.SetData(pRecvData.GetString());

		// 答复长度要求
		int nMinSize = FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE + FINS_MEMORY_AREA_READ_FIX_R_SIZE + nSize * 2;
		if(pHeadReply.GetLength() < nMinSize)
		{
			return FINS_REPLY_READ_DATA_TOO_SHORT;
		}
		else
		{
			// FINS协议部分
			FINS_CONTROL_HEAD pControlHeadReply;
			pControlHeadReply.SetData(pRecvData.GetString());
		
			if (pControlHeadReply.nCmd1 != pControlHead.nCmd1 ||
				pControlHeadReply.nCmd2 != pControlHead.nCmd2)
			{
				// 命令不一致
				return FINS_REPLY_CMD_NO_IS_REQUST_CMD;
			}

			// 答复数据
			FINS_MEMORY_AREA_READ_REPLY pReplyData;
			pReplyData.SetData(pRecvData.GetString(), pRecvData.Size());	
			if(pReplyData.nEndCode != 0)
			{
				return FINS_REPLY_READ_DATA_FAIL;	
			}

			// 拷贝数据
			int nReadByte = nSize * 2;
			if (pReplyData.GetDataBytsSize() == nReadByte)
			{
				memcpy(pData, pReplyData.GetData(), nReadByte);
			}
			else
			{				
				return FINS_REPLY_READ_DATA_TOO_SHORT;				
			}
		}
	}
	return nCode;
}



long CFinsHandle::WriteMemoryData(int nAddr, int nSize, FINS_DATA_TYPE::ENUM nType, __int16* pData)
{
	long nCode = 0;
	if(nCode = EstablishCommunicationByFins())
	{
		return nCode;
	}

	CMyString pSendData;
	int nBytsSize = nSize * 2;

	// 获取发送内存
	int nAllSize;
	nAllSize  = FINS_TCP_HEAD_SIZE;
	nAllSize += FINS_CONTROL_HEAD_SIZE;
	nAllSize += FINS_MEMORY_AREA_READ_SIZE; 
	nAllSize += nBytsSize;
	pSendData.SetSize(nAllSize);
	char* pBuff = pSendData.GetString();


	// 头部信息
	FINS_TCP_HEAD pHead;	
	pHead.nCommand = FINS_TCP_CMD_DATA;
	pHead.SetLength(nAllSize);		//长度
	pHead.GetData(pBuff);

	// control部分
	FINS_CONTROL_HEAD pControlHead;
	pControlHead.nDA1 = 0; 
	pControlHead.nSA1 = m_nIpNode;
	pControlHead.nCmd1 = 0x01;
	pControlHead.nCmd2 = 0x02;
	pControlHead.GetData(pBuff + FINS_TCP_HEAD_SIZE);

	// 数据部分
	FINS_MEMORY_AREA_WRITE pMemory;
	pMemory.nAreaCode = nType;
	pMemory.nAddr = nAddr;
	pMemory.nBitNo = 0;
	pMemory.nLength = nSize;
	pMemory.pData.Append((char*)pData, nBytsSize);
	pMemory.GetData(pBuff + FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE);

	//	// 发送数据
	CMyString pRecvData;
	nCode = SendSyncData(pSendData, pRecvData);
	if (nCode == 0)
	{
		// 先判断答复数据的头数据是否正确			
		if(nCode = CheckReplyDataIsError(pRecvData.GetString(), pRecvData.Size()))
		{
			return nCode;
		}
		
		// 数据头
		FINS_TCP_HEAD pHeadReply;
		pHeadReply.SetData(pRecvData.GetString());

		// 答复长度要求
		int nMinSize = FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE + FINS_MEMORY_AREA_WRITE_R_SIZE;
		if(pHeadReply.GetLength() < nMinSize)
		{
			return FINS_REPLY_READ_DATA_TOO_SHORT;
		}
		else
		{
			// FINS协议部分
			FINS_CONTROL_HEAD pControlHeadReply;
			pControlHeadReply.SetData(pRecvData.GetString());
			if (pControlHeadReply.nCmd1 != pControlHead.nCmd1 ||
				pControlHeadReply.nCmd2 != pControlHead.nCmd2)
			{
				// 命令不一致
				return FINS_REPLY_CMD_NO_IS_REQUST_CMD;
			}
						
			// 答复数据
			FINS_MEMORY_AREA_WRITE_REPLY pReplyData;
			pReplyData.SetData(pRecvData.GetString());				
			if(pReplyData.nEndCode != 0)
			{
				return FINS_REPLY_WRITE_DATA_FAIL;	
			}
		}
		
	}
	return nCode;
}


	// 获取fins节点地址
long CFinsHandle::GetFinsNodeAddress()
{
	return 0;
}


// 检查答复数据是否错误
long CFinsHandle::CheckReplyDataIsError(char* pData, int nSize)
{
	if (nSize < FINS_TCP_HEAD_SIZE)
	{
		// 小于最小要求数据
		return FINS_REPLY_DATA_TOO_SHORT;
	}
	
	// 消息错误
	FINS_TCP_HEAD pHeadReply;
	pHeadReply.SetData(pData);
	if (pHeadReply.nErrorCode)
	{
		return FINS_REPLY_ERROR_BY_MESSAGE;
	}
		
	return 0;
}


// 建立通讯
long CFinsHandle::EstablishCommunicationByFins()
{
	if (m_bEstablishCommunicationByFins)
	{
		// 已经建立通讯连接了
		return 0;
	}
	
	long nCode = 0;
	CMyString pSendData;

	// 获取发送内存
	int nAllSize;
	nAllSize  = FINS_TCP_HEAD_SIZE;
	nAllSize += FINS_CONNECT_REQUST_SIZE;
	pSendData.SetSize(nAllSize);	
	char* pBuff = pSendData.GetString();

	// 头部信息
	FINS_TCP_HEAD pHead;	
	pHead.nCommand = FINS_TCP_CMD_CONNECT_REQUST;
	pHead.SetLength(nAllSize);		//长度
	pHead.GetData(pBuff);
	
	// IP地址
	FINS_CONNECT_REQUST pConnectRequst;	
	pConnectRequst.GetData(pBuff + FINS_TCP_HEAD_SIZE);
		
// 发送数据
	CMyString pRecvData;
	if(nCode = SendSyncData(pSendData, pRecvData))
	{
		return nCode;
	}

	// 处理返回值
	FINS_TCP_HEAD pHeadReply;
	pHeadReply.SetData(pRecvData.GetString());
	
	// 检查头信息
	if (pHeadReply.nErrorCode == 0 &&
		pHeadReply.nCommand == FINS_TCP_CMD_CONNECT_RESPONSE)
	{

		// 提取 IP Node信息
		if (pHeadReply.GetLength() == FINS_TCP_HEAD_SIZE + FINS_CONNECT_RESPONS_SIZE)
		{
			// 提取
			FINS_CONNECT_RESPONSE pConnectResponse;
			pConnectResponse.SetData(pRecvData.GetString());
			m_nIpNode = pConnectResponse.pClientAddrss[3];
			
			// 建立通讯成功
			m_bEstablishCommunicationByFins = true;

			return 0;
		}					
	}	

	return FINS_REQUST_CONNECT_FAIL;
}










