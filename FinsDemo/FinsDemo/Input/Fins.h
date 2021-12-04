#pragma once
#include <string>
#include "InterfaceExport.h"
#include "ModuleDevelopH.h"

// 欧姆龙Fins协议
class CFins
{
public:
	CFins();
	virtual ~CFins();
		
	// 参数
	CResult SetIP(std::string pIP);				// 设置地址
	CResult SetPort(int nPort);				// 设置端口号
	CResult SetTimeout(int nTimeMs);		// 设置超时
	
// 读出
	CResult Read(std::string pAddr, char& pData); 
	CResult Read(std::string pAddr, __int16& pData); 
	CResult Read(std::string pAddr, __int32& pData); 
	CResult Read(std::string pAddr, __int64& pData);
	
	CResult Read(std::string pAddr, char* pData, int nSize); 
	CResult Read(std::string pAddr, __int16* pData, int nSize); 
	CResult Read(std::string pAddr, __int32* pData, int nSize); 
	CResult Read(std::string pAddr, __int64* pData, int nSize); 


	
// 写入	
	CResult Write(std::string pAddr, char& pData); 
	CResult Write(std::string pAddr,  __int16& pData); 
	CResult Write(std::string pAddr,  __int32& pData); 
	CResult Write(std::string pAddr,  __int64& pData); 

	CResult Write(std::string pAddr, char* pData, __int32 nSize); 
	CResult Write(std::string pAddr,  __int16* pData, __int32 nSize); 
	CResult Write(std::string pAddr,  __int32* pData, __int32 nSize); 
	CResult Write(std::string pAddr,  __int64* pData, __int32 nSize); 



private:
		
	CResult SetParament(std::string pName, std::string pValue); 
	CResult SetParament(std::string pName, int nValue); 

private:

	CInterfaceExport* m_pFins;
	CMgrDllDelegate m_pLoadInterface;

};















