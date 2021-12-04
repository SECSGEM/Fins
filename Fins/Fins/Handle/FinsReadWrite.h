#pragma once
#include "Export/InterfaceExport.h"
#include "FinsHandle.h"

class CFinsReadWrite : public CInterfaceExport
{
public:

	// 参数
	virtual CResult SetParament(const char* pName, const char* pValue); 

	// 初始化模块
	virtual CResult Connect(); 
	virtual CResult Disconnect(); 

	// 释放
	virtual void Release(); 

public:	

	// 读出
	virtual CResult Read(const char* pAddr, char* pData, __int32 size, char* pCtrlData); 
	virtual CResult Read(const char* pAddr, __int16* pData, __int32 size, char* pCtrlData); 
	virtual CResult Read(const char* pAddr, __int32* pData, __int32 size, char* pCtrlData); 
	virtual CResult Read(const char* pAddr, __int64* pData, __int32 size, char* pCtrlData); 

	// 写入
	virtual CResult Write(const char* pAddr, char* pData, __int32 size, char* pCtrlData); 
	virtual CResult Write(const char* pAddr, __int16* pData, __int32 size, char* pCtrlData); 
	virtual CResult Write(const char* pAddr, __int32* pData, __int32 size, char* pCtrlData); 
	virtual CResult Write(const char* pAddr, __int64* pData, __int32 size, char* pCtrlData); 												

private:
	long ReadData(int nAddr, __int16* pData, int nSize, int nDataType);		// 读取2字节一次	
	long WriteData(int nAddr, __int16* pData, int nSize, int nDataType);	// 读取2字节一次
	void GetDataTypeAndAddr(string pAddr, int& nDataType, int& nAddr);		// 获取数据地址
	int GetDataArea(string pArea);		// 获取数据区

private:
	CFinsHandle m_pHandle;

};












































