#include "stdafx.h"
#include "FinsReadWrite.h"



// ����
CResult CFinsReadWrite::SetParament(const char* pName, const char* pValue)
{
	if(pName == nullptr ||
		pValue == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS ����ָ��Ϊ��");
	}

	string pNameString = pName;

	if (pNameString == "IP")
	{
		m_pHandle.SetTcpIP(pValue);
	}
	else if (pNameString == "PORT")
	{
		int nPort = ::atoi(pValue);
		m_pHandle.SetTcpPort(nPort);
	}
	else if (pNameString == "TIMEOUT")
	{
		int nTimerOut = ::atoi(pValue);
		m_pHandle.SetTimeout(nTimerOut);
	}

	return CResult(0);
}

// ��ʼ��ģ��
CResult CFinsReadWrite::Connect()
{
	return CResult(0);
}

CResult CFinsReadWrite::Disconnect()
{
	return CResult(0);
}


// �ͷ�
void CFinsReadWrite::Release()
{
	delete this;
}



// 1�ֽ�			
CResult CFinsReadWrite::Read(const char* pAddr, char* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS ����ָ��Ϊ��");
	}
		
	int nDataType;		// ��������
	int nAddr;			// ���ݵ�ַ
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);	
	
	long nCode = 0;
	if(nSize % 2)
	{
		// ��������
		int nReadSize = nSize;
		nReadSize++;

		__int16* pReadData = (__int16*)malloc(nReadSize);
		if (pReadData == nullptr)
		{
			return FINS_MALLOC_FAIL;
		}

		// ��ȡ����
		nCode = ReadData(nAddr, pReadData, nReadSize / 2, nDataType);
		if(nCode == 0)
		{
			memcpy(pData, pReadData, nSize);
		}
		free(pReadData);
	}
	else
	{
		nCode = ReadData(nAddr, (__int16*)pData, nSize / 2, nDataType);
	}
	return nCode;
}

// 2�ֽ�			
CResult CFinsReadWrite::Read(const char* pAddr, __int16* pData, __int32 nSize, char* pCtrlData)
{
	long nCode = 0;
	int nDataType;		// ��������
	int nAddr;			// ���ݵ�ַ

	GetDataTypeAndAddr(pAddr, nDataType, nAddr);		
	nCode = ReadData(nAddr, pData, nSize, nDataType);
	return CResult(nCode);
}

// 4�ֽ�
CResult CFinsReadWrite::Read(const char* pAddr, __int32* pData, __int32 nSize, char* pCtrlData)
{
	long nCode = 0;
	int nDataType;		// ��������
	int nAddr;			// ���ݵ�ַ

	GetDataTypeAndAddr(pAddr, nDataType, nAddr);		
	nCode = ReadData(nAddr, (__int16*)pData, nSize * 2, nDataType);
	return CResult(nCode);
}

// 8�ֽ�
CResult CFinsReadWrite::Read(const char* pAddr, __int64* pData, __int32 nSize, char* pCtrlData)
{
	long nCode = 0;
	int nDataType;		// ��������
	int nAddr;			// ���ݵ�ַ

	GetDataTypeAndAddr(pAddr, nDataType, nAddr);		
	nCode = ReadData(nAddr, (__int16*)pData, nSize * 2, nDataType);
	return CResult(nCode);
}

// ��ȡ2�ֽ�һ��	
long CFinsReadWrite::ReadData(int nAddr, __int16* pData, int nSize, int nDataType)
{
	FINS_DATA_TYPE::ENUM nType = (FINS_DATA_TYPE::ENUM)nDataType;
	switch(nType)
	{
	case FINS_DATA_TYPE::DM:
		{
			return m_pHandle.ReadMemoryData(nAddr, nSize, nType, pData);
		}
		break;
	}

	return FINS_NOT_DATA_AREA;
}



// 1�ֽ�
CResult CFinsReadWrite::Write(const char* pAddr, char* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS ����ָ��Ϊ��");
	}

	long nCode = 0;
	int nDataType;		// ��������
	int nAddr;			// ���ݵ�ַ

	// ��ȡPLC����͵�ַ
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);

	if(nSize % 2)
	{
		// ��������
		int nReadSize = nSize;
		nReadSize++;

		__int8* pReadData = (__int8*)malloc(nReadSize);
		if (pReadData == nullptr)
		{
			return FINS_MALLOC_FAIL;
		}

		memset(pReadData, 0, nReadSize);
		memcpy(pReadData, pData, nSize);

		// ��ȡ����
		nCode = WriteData(nAddr, (__int16*)pReadData, nReadSize / 2, nDataType);		
		free(pReadData);
	}
	else
	{
		nCode = WriteData(nAddr, (__int16*)pData, nSize / 2, nDataType);
	}
	return nCode;
}	

// 2�ֽ�
CResult CFinsReadWrite::Write(const char* pAddr, __int16* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS ����ָ��Ϊ��");
	}

	long nCode = 0;
	int nDataType;		// ��������
	int nAddr;			// ���ݵ�ַ

	// ��ȡPLC����͵�ַ
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);	
	nCode = WriteData(nAddr, pData, nSize, nDataType);
	return nCode;
}	

// 4�ֽ�	
CResult CFinsReadWrite::Write(const char* pAddr, __int32* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS ����ָ��Ϊ��");
	}

	long nCode = 0;
	int nDataType;		// ��������
	int nAddr;			// ���ݵ�ַ

	// ��ȡPLC����͵�ַ
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);	
	nCode = WriteData(nAddr, (__int16*)pData, nSize * 2, nDataType);
	return nCode;
}									

// 8�ֽ�	
CResult CFinsReadWrite::Write(const char* pAddr, __int64* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS ����ָ��Ϊ��");
	}

	long nCode = 0;
	int nDataType;		// ��������
	int nAddr;			// ���ݵ�ַ

	// ��ȡPLC����͵�ַ
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);
	nCode = WriteData(nAddr, (__int16*)pData, nSize * 4, nDataType);
	return nCode;
}									



// ��ȡ2�ֽ�һ��	
long CFinsReadWrite::WriteData(int nAddr, __int16* pData, int nSize, int nDataType)
{
	FINS_DATA_TYPE::ENUM nType = (FINS_DATA_TYPE::ENUM)nDataType;
	switch(nType)
	{
	case FINS_DATA_TYPE::DM:
		{
			return m_pHandle.WriteMemoryData(nAddr, nSize, nType, pData);
		}
		break;
	}

	return FINS_NOT_DATA_AREA;
}


// ��ȡ���ݵ�ַ
void CFinsReadWrite::GetDataTypeAndAddr(string pAddr, int& nDataType, int& nAddr)
{
	unsigned int i = 0;
	for (; i < pAddr.size(); i++)
	{
		if(pAddr[i] >= '0' && pAddr[i] <= '9')
		{
			break;
		}
	}

	// ��������
	string pType = pAddr.substr(0, i);
	nDataType = GetDataArea(pType);

	// ���ݵ�ַ
	string pStartAddr = pAddr.substr(i, pAddr.size() - i);
	nAddr = ::atol(pStartAddr.c_str());
}


// ��ȡ������
int CFinsReadWrite::GetDataArea(string pArea)
{
	int nDataType = 0;

	if (pArea == "DM") { nDataType = FINS_DATA_TYPE::DM; }
	else if (pArea == "dm") { nDataType = FINS_DATA_TYPE::DM; }
	else { nDataType = FINS_DATA_TYPE::ERR; }

	return nDataType;
}




























