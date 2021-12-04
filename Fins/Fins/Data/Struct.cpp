#include "stdafx.h"
#include "Sturct.h"


FINS_TCP_HEAD::FINS_TCP_HEAD()
{
	memset(this, 0, sizeof(FINS_TCP_HEAD));
	memcpy(pMagic, "FINS", 4);
}

void FINS_TCP_HEAD::GetData(char* pData)
{
	unsigned char* pBuff = (unsigned char*)pData;
	memcpy(pBuff, pMagic, 4);
	SetIntHL(nLength, pBuff+4);
	memcpy(pBuff+8, pReserved, 3);
	pBuff[11] = (unsigned char)nCommand;
	SetIntHL(nErrorCode, pBuff+12);
}

// 从二进制数据获取
void FINS_TCP_HEAD::SetData(char* pData)
{
	unsigned char* pBuff = (unsigned char*)pData;
	memcpy(pMagic, pBuff, 4);
	nLength = GetIntHL(pBuff+4);
	memcpy(pReserved, pBuff+8, 3);
	nCommand = pBuff[11];
	nErrorCode = GetIntHL(pBuff+12);
}

// 获取数据长度大小
int FINS_TCP_HEAD::GetLength()
{
	int nLength = this->nLength + 8;
	return nLength;
}

// 设置数据长度大小
void FINS_TCP_HEAD::SetLength(int nLength)
{
	this->nLength = nLength - 8;
}

FINS_CONTROL_HEAD::FINS_CONTROL_HEAD()
{
	memset(this, 0, sizeof(FINS_CONTROL_HEAD));

	nICF = 0x80;		// 信息控制码,需要答复
	nRev = 0;			// 保留
	nGCT = 0x02;		// 网关数据量
	nDNA = 0;			// 目标网络地址
	nDA1 = 1;			// 目标节点号
	nDA2 = 0;			// 源单元号
	nSNA = 0;			// 源网络地址
	nSA1 = 1;			// 源节点
	nSA2 = 0;			// 源单元地址
	nSID = 0xFF;		// 序列号
	nCmd1;				// 命令1
	nCmd2;				// 命令2
}


// 转成二进制数据
void FINS_CONTROL_HEAD::GetData(char* pData)
{
	unsigned char* pBuff = (unsigned char*)pData;
	pBuff[0] = nICF;
	pBuff[1] = nRev;
	pBuff[2] = nGCT;
	pBuff[3] = nDNA;
	pBuff[4] = nDA1;
	pBuff[5] = nDA2;
	pBuff[6] = nSNA;
	pBuff[7] = nSA1;
	pBuff[8] = nSA2;
	pBuff[9] = nSID;
	pBuff[10] = nCmd1;
	pBuff[11] = nCmd2;
}


// 从二进制数据获取	
void FINS_CONTROL_HEAD::SetData(char* pData)
{
	unsigned char* pBuff = (unsigned char*)pData;
	pBuff = pBuff + FINS_TCP_HEAD_SIZE;
		
	nICF = pBuff[0];
	nRev = pBuff[1];
	nGCT = pBuff[2];
	nDNA = pBuff[3];
	nDA1 = pBuff[4];
	nDA2 = pBuff[5];
	nSNA = pBuff[6];
	nSA1 = pBuff[7];
	nSA2 = pBuff[8];
	nSID = pBuff[9];
	nCmd1 = pBuff[10];
	nCmd2 = pBuff[11];
}


FINS_CONNECT_REQUST::FINS_CONNECT_REQUST()
{
	memset(this, 0, sizeof(FINS_CONNECT_REQUST));
}

// 转成二进制数据	
void FINS_CONNECT_REQUST::GetData(char* pData)
{
	memcpy(pData, pClientAddrss, 4);
}

void FINS_CONNECT_REQUST::SetIp(string pIP)
{
	*((unsigned __int32*)pClientAddrss) = inet_addr(pIP.c_str());	
}

FINS_CONNECT_RESPONSE::FINS_CONNECT_RESPONSE()
{
	memset(this, 0, sizeof(FINS_CONNECT_RESPONSE));
}

// 二进制数据	
void FINS_CONNECT_RESPONSE::SetData(char* pData)
{
	int nDataOffset = FINS_TCP_HEAD_SIZE;		// 偏移
	char* pBuff = pData + nDataOffset;

	memcpy(pClientAddrss, pBuff, 4);
	memcpy(pServerAddrss, pBuff + 4, 4);
}


FINS_MEMORY_AREA_READ::FINS_MEMORY_AREA_READ()
{
	nAddr = 0;
	nAreaCode = 0;
	nBitNo = 0;
	nLength = 0;
}


// 转成二进制数据	
void FINS_MEMORY_AREA_READ::GetData(char* pData)
{
	unsigned char* pBuff = (unsigned char*)pData;
	pBuff[0] = nAreaCode;
	SetShortHL(nAddr, pBuff + 1);
	pData[3] = nBitNo;	
	SetShortHL(nLength, pBuff + 4);
}




// 转成二进制数据
void FINS_MEMORY_AREA_READ_REPLY::SetData(char* pData, int nSize)
{	
	int nDataOffset = FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE;
	unsigned char* pBuff = (unsigned char*)pData;

	nEndCode = GetShortHL(pBuff + nDataOffset);
		
	// 计算实际数据
	nDataOffset += 2;	// EndCode偏移
	int nDataSize = nSize - nDataOffset;

	// 拷贝数据
	if (nDataSize > 0)
	{
		this->pData.SetSize(nDataSize);
		memcpy(this->pData.GetString(), pBuff + nDataOffset, nDataSize);
	}
}


int FINS_MEMORY_AREA_READ_REPLY::GetDataSize()
{
	return pData.Size() / 2;
}

// 实际byte长度
int FINS_MEMORY_AREA_READ_REPLY::GetDataBytsSize()
{
	return pData.Size();
}

char* FINS_MEMORY_AREA_READ_REPLY::GetData()
{
	return pData.GetString();
}


FINS_MEMORY_AREA_WRITE::FINS_MEMORY_AREA_WRITE()
{
	nAddr = 0;
	nAreaCode = 0;
	nBitNo = 0;
	nLength = 0;
}

// 转成二进制数据	
void FINS_MEMORY_AREA_WRITE::GetData(char* pData)
{
	unsigned char* pBuff = (unsigned char*)pData;
	pBuff[0] = nAreaCode;
	SetShortHL(nAddr, pBuff + 1);
	pData[3] = nBitNo;	
	SetShortHL(nLength, pBuff + 4);	
	memcpy(pData + 6, (this->pData).GetString(), (this->pData).Size());
}

FINS_MEMORY_AREA_WRITE_REPLY::FINS_MEMORY_AREA_WRITE_REPLY()
{
	nEndCode = 0;
}


// 从二进制数据获取	
void FINS_MEMORY_AREA_WRITE_REPLY::SetData(char* pData)
{
	unsigned char* pBuff = (unsigned char*)pData;
	pBuff = pBuff + FINS_TCP_HEAD_SIZE + FINS_CONTROL_HEAD_SIZE;

	nEndCode = GetShortHL(pBuff);
}










