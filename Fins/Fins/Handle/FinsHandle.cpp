#include "stdafx.h"
#include "FinsHandle.h"

CFinsHandle::CFinsHandle()
{
	m_bEstablishCommunicationByFins = false;
	m_nIpNode = 0;
}

// ��д���ݽ���,����Э��ʶ��
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


// ��д���ݽ���,��ʼ�������ݣ�����Э��ʶ��
void CFinsHandle::OnBeginRecv()
{
	m_pRecvData.SetSize(0);
}

// ͨѶ�ر�
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

	// ��ȡ�����ڴ�
	int nAllSize;
	nAllSize  = FINS_TCP_HEAD_SIZE;
	nAllSize += FINS_CONTROL_HEAD_SIZE;
	nAllSize += FINS_MEMORY_AREA_READ_SIZE; 
	pSendData.SetSize(nAllSize);
	char* pBuff = pSendData.GetString();
	
	// ͷ����Ϣ
	FINS_TCP_HEAD pHead;	
	pHead.nCommand = FINS_TCP_CMD_DATA;
	pHead.SetLength(nAllSize);		//����
	pHead.GetData(pBuff);

	// control����
	FINS_CONTROL_HEAD pControlHead;
	pControlHead.nDA1 = 0; 
	pControlHead.nSA1 = m_nIpNode;
	pControlHead.nCmd1 = 0x01;
	pControlHead.nCmd2 = 0x01;
	pControlHead.GetData(pBuff + FINS_TCP_HEAD_SIZE);

	// ���ݲ���
	FINS_MEMORY_AREA_READ pMemory;
	pMemory.nAreaCode = nType;
	pMemory.nAddr = nAddr;
	pMemory.nBitNo = 0;
	pMemory.nLength = nSize;
	pMemory.GetData(pBuff + FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE);
	
	//	// ��������
	CMyString pRecvData;
	nCode = SendSyncData(pSendData, pRecvData);
	if (nCode == 0)
	{
		// ���жϴ����ݵ�ͷ�����Ƿ���ȷ	
		if(nCode = CheckReplyDataIsError(pRecvData.GetString(), pRecvData.Size()))
		{
			return nCode;
		}

		// ����ͷ
		FINS_TCP_HEAD pHeadReply;
		pHeadReply.SetData(pRecvData.GetString());

		// �𸴳���Ҫ��
		int nMinSize = FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE + FINS_MEMORY_AREA_READ_FIX_R_SIZE + nSize * 2;
		if(pHeadReply.GetLength() < nMinSize)
		{
			return FINS_REPLY_READ_DATA_TOO_SHORT;
		}
		else
		{
			// FINSЭ�鲿��
			FINS_CONTROL_HEAD pControlHeadReply;
			pControlHeadReply.SetData(pRecvData.GetString());
		
			if (pControlHeadReply.nCmd1 != pControlHead.nCmd1 ||
				pControlHeadReply.nCmd2 != pControlHead.nCmd2)
			{
				// ���һ��
				return FINS_REPLY_CMD_NO_IS_REQUST_CMD;
			}

			// ������
			FINS_MEMORY_AREA_READ_REPLY pReplyData;
			pReplyData.SetData(pRecvData.GetString(), pRecvData.Size());	
			if(pReplyData.nEndCode != 0)
			{
				return FINS_REPLY_READ_DATA_FAIL;	
			}

			// ��������
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

	// ��ȡ�����ڴ�
	int nAllSize;
	nAllSize  = FINS_TCP_HEAD_SIZE;
	nAllSize += FINS_CONTROL_HEAD_SIZE;
	nAllSize += FINS_MEMORY_AREA_READ_SIZE; 
	nAllSize += nBytsSize;
	pSendData.SetSize(nAllSize);
	char* pBuff = pSendData.GetString();


	// ͷ����Ϣ
	FINS_TCP_HEAD pHead;	
	pHead.nCommand = FINS_TCP_CMD_DATA;
	pHead.SetLength(nAllSize);		//����
	pHead.GetData(pBuff);

	// control����
	FINS_CONTROL_HEAD pControlHead;
	pControlHead.nDA1 = 0; 
	pControlHead.nSA1 = m_nIpNode;
	pControlHead.nCmd1 = 0x01;
	pControlHead.nCmd2 = 0x02;
	pControlHead.GetData(pBuff + FINS_TCP_HEAD_SIZE);

	// ���ݲ���
	FINS_MEMORY_AREA_WRITE pMemory;
	pMemory.nAreaCode = nType;
	pMemory.nAddr = nAddr;
	pMemory.nBitNo = 0;
	pMemory.nLength = nSize;
	pMemory.pData.Append((char*)pData, nBytsSize);
	pMemory.GetData(pBuff + FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE);

	//	// ��������
	CMyString pRecvData;
	nCode = SendSyncData(pSendData, pRecvData);
	if (nCode == 0)
	{
		// ���жϴ����ݵ�ͷ�����Ƿ���ȷ			
		if(nCode = CheckReplyDataIsError(pRecvData.GetString(), pRecvData.Size()))
		{
			return nCode;
		}
		
		// ����ͷ
		FINS_TCP_HEAD pHeadReply;
		pHeadReply.SetData(pRecvData.GetString());

		// �𸴳���Ҫ��
		int nMinSize = FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE + FINS_MEMORY_AREA_WRITE_R_SIZE;
		if(pHeadReply.GetLength() < nMinSize)
		{
			return FINS_REPLY_READ_DATA_TOO_SHORT;
		}
		else
		{
			// FINSЭ�鲿��
			FINS_CONTROL_HEAD pControlHeadReply;
			pControlHeadReply.SetData(pRecvData.GetString());
			if (pControlHeadReply.nCmd1 != pControlHead.nCmd1 ||
				pControlHeadReply.nCmd2 != pControlHead.nCmd2)
			{
				// ���һ��
				return FINS_REPLY_CMD_NO_IS_REQUST_CMD;
			}
						
			// ������
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


	// ��ȡfins�ڵ��ַ
long CFinsHandle::GetFinsNodeAddress()
{
	return 0;
}


// ���������Ƿ����
long CFinsHandle::CheckReplyDataIsError(char* pData, int nSize)
{
	if (nSize < FINS_TCP_HEAD_SIZE)
	{
		// С����СҪ������
		return FINS_REPLY_DATA_TOO_SHORT;
	}
	
	// ��Ϣ����
	FINS_TCP_HEAD pHeadReply;
	pHeadReply.SetData(pData);
	if (pHeadReply.nErrorCode)
	{
		return FINS_REPLY_ERROR_BY_MESSAGE;
	}
		
	return 0;
}


// ����ͨѶ
long CFinsHandle::EstablishCommunicationByFins()
{
	if (m_bEstablishCommunicationByFins)
	{
		// �Ѿ�����ͨѶ������
		return 0;
	}
	
	long nCode = 0;
	CMyString pSendData;

	// ��ȡ�����ڴ�
	int nAllSize;
	nAllSize  = FINS_TCP_HEAD_SIZE;
	nAllSize += FINS_CONNECT_REQUST_SIZE;
	pSendData.SetSize(nAllSize);	
	char* pBuff = pSendData.GetString();

	// ͷ����Ϣ
	FINS_TCP_HEAD pHead;	
	pHead.nCommand = FINS_TCP_CMD_CONNECT_REQUST;
	pHead.SetLength(nAllSize);		//����
	pHead.GetData(pBuff);
	
	// IP��ַ
	FINS_CONNECT_REQUST pConnectRequst;	
	pConnectRequst.GetData(pBuff + FINS_TCP_HEAD_SIZE);
		
// ��������
	CMyString pRecvData;
	if(nCode = SendSyncData(pSendData, pRecvData))
	{
		return nCode;
	}

	// ������ֵ
	FINS_TCP_HEAD pHeadReply;
	pHeadReply.SetData(pRecvData.GetString());
	
	// ���ͷ��Ϣ
	if (pHeadReply.nErrorCode == 0 &&
		pHeadReply.nCommand == FINS_TCP_CMD_CONNECT_RESPONSE)
	{

		// ��ȡ IP Node��Ϣ
		if (pHeadReply.GetLength() == FINS_TCP_HEAD_SIZE + FINS_CONNECT_RESPONS_SIZE)
		{
			// ��ȡ
			FINS_CONNECT_RESPONSE pConnectResponse;
			pConnectResponse.SetData(pRecvData.GetString());
			m_nIpNode = pConnectResponse.pClientAddrss[3];
			
			// ����ͨѶ�ɹ�
			m_bEstablishCommunicationByFins = true;

			return 0;
		}					
	}	

	return FINS_REQUST_CONNECT_FAIL;
}










