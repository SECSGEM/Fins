#include "stdafx.h"
#include "FinsReadWrite.h"



// 参数
CResult CFinsReadWrite::SetParament(const char* pName, const char* pValue)
{
	if(pName == nullptr ||
		pValue == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS 参数指针为空");
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

// 初始化模块
CResult CFinsReadWrite::Connect()
{
	return CResult(0);
}

CResult CFinsReadWrite::Disconnect()
{
	return CResult(0);
}


// 释放
void CFinsReadWrite::Release()
{
	delete this;
}



// 1字节			
CResult CFinsReadWrite::Read(const char* pAddr, char* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS 参数指针为空");
	}
		
	int nDataType;		// 数据类型
	int nAddr;			// 数据地址
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);	
	
	long nCode = 0;
	if(nSize % 2)
	{
		// 奇数处理
		int nReadSize = nSize;
		nReadSize++;

		__int16* pReadData = (__int16*)malloc(nReadSize);
		if (pReadData == nullptr)
		{
			return FINS_MALLOC_FAIL;
		}

		// 读取数据
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

// 2字节			
CResult CFinsReadWrite::Read(const char* pAddr, __int16* pData, __int32 nSize, char* pCtrlData)
{
	long nCode = 0;
	int nDataType;		// 数据类型
	int nAddr;			// 数据地址

	GetDataTypeAndAddr(pAddr, nDataType, nAddr);		
	nCode = ReadData(nAddr, pData, nSize, nDataType);
	return CResult(nCode);
}

// 4字节
CResult CFinsReadWrite::Read(const char* pAddr, __int32* pData, __int32 nSize, char* pCtrlData)
{
	long nCode = 0;
	int nDataType;		// 数据类型
	int nAddr;			// 数据地址

	GetDataTypeAndAddr(pAddr, nDataType, nAddr);		
	nCode = ReadData(nAddr, (__int16*)pData, nSize * 2, nDataType);
	return CResult(nCode);
}

// 8字节
CResult CFinsReadWrite::Read(const char* pAddr, __int64* pData, __int32 nSize, char* pCtrlData)
{
	long nCode = 0;
	int nDataType;		// 数据类型
	int nAddr;			// 数据地址

	GetDataTypeAndAddr(pAddr, nDataType, nAddr);		
	nCode = ReadData(nAddr, (__int16*)pData, nSize * 2, nDataType);
	return CResult(nCode);
}

// 读取2字节一次	
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



// 1字节
CResult CFinsReadWrite::Write(const char* pAddr, char* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS 参数指针为空");
	}

	long nCode = 0;
	int nDataType;		// 数据类型
	int nAddr;			// 数据地址

	// 获取PLC区域和地址
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);

	if(nSize % 2)
	{
		// 奇数处理
		int nReadSize = nSize;
		nReadSize++;

		__int8* pReadData = (__int8*)malloc(nReadSize);
		if (pReadData == nullptr)
		{
			return FINS_MALLOC_FAIL;
		}

		memset(pReadData, 0, nReadSize);
		memcpy(pReadData, pData, nSize);

		// 读取数据
		nCode = WriteData(nAddr, (__int16*)pReadData, nReadSize / 2, nDataType);		
		free(pReadData);
	}
	else
	{
		nCode = WriteData(nAddr, (__int16*)pData, nSize / 2, nDataType);
	}
	return nCode;
}	

// 2字节
CResult CFinsReadWrite::Write(const char* pAddr, __int16* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS 参数指针为空");
	}

	long nCode = 0;
	int nDataType;		// 数据类型
	int nAddr;			// 数据地址

	// 获取PLC区域和地址
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);	
	nCode = WriteData(nAddr, pData, nSize, nDataType);
	return nCode;
}	

// 4字节	
CResult CFinsReadWrite::Write(const char* pAddr, __int32* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS 参数指针为空");
	}

	long nCode = 0;
	int nDataType;		// 数据类型
	int nAddr;			// 数据地址

	// 获取PLC区域和地址
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);	
	nCode = WriteData(nAddr, (__int16*)pData, nSize * 2, nDataType);
	return nCode;
}									

// 8字节	
CResult CFinsReadWrite::Write(const char* pAddr, __int64* pData, __int32 nSize, char* pCtrlData)
{
	if (pAddr == nullptr ||
		pData == nullptr ||
		pCtrlData == nullptr)
	{
		return CResult(FINS_PARAM_POINT_ENTPY, "FINS 参数指针为空");
	}

	long nCode = 0;
	int nDataType;		// 数据类型
	int nAddr;			// 数据地址

	// 获取PLC区域和地址
	GetDataTypeAndAddr(pAddr, nDataType, nAddr);
	nCode = WriteData(nAddr, (__int16*)pData, nSize * 4, nDataType);
	return nCode;
}									



// 读取2字节一次	
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


// 获取数据地址
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

	// 数据类型
	string pType = pAddr.substr(0, i);
	nDataType = GetDataArea(pType);

	// 数据地址
	string pStartAddr = pAddr.substr(i, pAddr.size() - i);
	nAddr = ::atol(pStartAddr.c_str());
}


// 获取数据区
int CFinsReadWrite::GetDataArea(string pArea)
{
	int nDataType = 0;

	if (pArea == "DM") { nDataType = FINS_DATA_TYPE::DM; }
	else if (pArea == "dm") { nDataType = FINS_DATA_TYPE::DM; }
	else { nDataType = FINS_DATA_TYPE::ERR; }

	return nDataType;
}




























