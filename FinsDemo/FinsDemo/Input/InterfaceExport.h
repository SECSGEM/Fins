#pragma once

#ifndef __FINS_MEMEORY_DATA__
#define __FINS_MEMEORY_DATA__

// 内存数据类型:软元件
namespace FINS_DATA_TYPE
{
	enum ENUM
	{
		ERR = 0x00,		// 错误
		DM = 0x82,		// 数据寄存器	
	};
}

#define OCA_PARAM_FINS_IP				"IP"				// 统一API：fins的IP地址
#define OCA_PARAM_FINS_PORT				"PORT"				// 统一API：fins的IP地址
#define OCA_PARAM_FINS_TIMEOUT			"TIMEOUT"			// 统一API：fins的IP地址

#endif

struct CResult;

// 欧姆龙Fins协议
class CInterfaceExport
{
public:

	// 参数
	virtual CResult SetParament(const char* pName, const char* pValue) = 0; 

	// 初始化模块
	virtual CResult Connect() = 0; 
	virtual CResult Disconnect() = 0; 

	// 释放
	virtual void Release() = 0; 

	// 读出
	virtual CResult Read(const char* pAddr, char* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Read(const char* pAddr, __int16* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Read(const char* pAddr, __int32* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Read(const char* pAddr, __int64* pData, __int32 nSize, char* pCtrlData) = 0; 

	// 写入
	virtual CResult Write(const char* pAddr, char* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Write(const char* pAddr,  __int16* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Write(const char* pAddr,  __int32* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Write(const char* pAddr,  __int64* pData, __int32 nSize, char* pCtrlData) = 0; 

};




#ifndef __RESULT_CODE__
#define __RESULT_CODE__

// 返回值结果
struct CResult
{
	__int32 nCode;		// 错误代码
	char pText[200];	// 错误信息	

	CResult()
	{
		nCode = 0;
		memset(pText, 0, 200);
	}
	CResult(__int32 nCode)
	{
		SetData(nCode, "");
	}
	CResult(__int32 nCode, char* pText)
	{
		SetData(nCode, pText);
	}
	void SetData(__int32 nCode, char* pText)
	{
		this->nCode = nCode;
		memset(this->pText, 0, 200);
		if (pText != NULL)
		{
			strncpy_s(this->pText, 200, pText, 200);
		}		
	}
};
#endif



























