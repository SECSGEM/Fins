#include "stdafx.h"
#include "Fins.h"
#include "ModuleDevelopH.h"
#pragma warning(disable:4996) 

// 欧姆龙Fins协议
CFins::CFins() :
	m_pLoadInterface("Fins.dll")
{	
	m_pFins = NULL;
	m_pLoadInterface.DllCreateInterface((void**)&m_pFins);	
}


CFins::~CFins()
{

}




// 设置地址
CResult CFins::SetIP(std::string pIP)
{
	return SetParament(OCA_PARAM_FINS_IP, pIP);
}

// 设置端口号
CResult CFins::SetPort(int nPort)
{
	return SetParament(OCA_PARAM_FINS_PORT, nPort);
}

// 设置超时
CResult CFins::SetTimeout(int nTimeMs)
{
	return SetParament(OCA_PARAM_FINS_TIMEOUT, nTimeMs);
}


// 读出
CResult CFins::Read(std::string pAddr, char& pData)
{
	return Read(pAddr.c_str(), &pData, 1);
}

CResult CFins::Read(std::string pAddr, __int16& pData)
{
	return Read(pAddr.c_str(), &pData, 1);
}

CResult CFins::Read(std::string pAddr, __int32& pData)
{
	return Read(pAddr.c_str(), &pData, 1);
}

CResult CFins::Read(std::string pAddr, __int64& pData)
{	
	return Read(pAddr.c_str(), &pData, 1);
}



// 读出
CResult CFins::Read(std::string pAddr, char* pData, int nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll加载失败，可能不存在或者出错");
	}
	return m_pFins->Read(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Read(std::string pAddr, __int16* pData, int nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll加载失败，可能不存在或者出错");
	}
	return m_pFins->Read(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Read(std::string pAddr, __int32* pData, int nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll加载失败，可能不存在或者出错");
	}
	return m_pFins->Read(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Read(std::string pAddr, __int64* pData, int nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll加载失败，可能不存在或者出错");
	}
	return m_pFins->Read(pAddr.c_str(), pData, nSize, "");
}
 



// 写入
CResult CFins::Write(std::string pAddr, char& pData)
{
	return Write(pAddr.c_str(), &pData, 1);
}

CResult CFins::Write(std::string pAddr,  __int16& pData)
{
	return Write(pAddr.c_str(), &pData, 1);
}

CResult CFins::Write(std::string pAddr,  __int32& pData)
{
	return Write(pAddr.c_str(), &pData, 1);
}

CResult CFins::Write(std::string pAddr,  __int64& pData)
{	
	return Write(pAddr.c_str(), &pData, 1);
}


// 写入
CResult CFins::Write(std::string pAddr, char* pData, __int32 nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll加载失败，可能不存在或者出错");
	}
	return m_pFins->Write(pAddr.c_str(), pData, nSize, "");
}
 
CResult CFins::Write(std::string pAddr,  __int16* pData, __int32 nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll加载失败，可能不存在或者出错");
	}
	return m_pFins->Write(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Write(std::string pAddr,  __int32* pData, __int32 nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll加载失败，可能不存在或者出错");
	}
	return m_pFins->Write(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Write(std::string pAddr,  __int64* pData, __int32 nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll加载失败，可能不存在或者出错");
	}
	return m_pFins->Write(pAddr.c_str(), pData, nSize, "");
}


CResult CFins::SetParament(std::string pName, std::string pValue)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll加载失败，可能不存在或者出错");
	}
	return m_pFins->SetParament(pName.c_str(), pValue.c_str());
}
 
CResult CFins::SetParament(std::string pName, int nValue)
{
	char pTmp[200] = {0};
	sprintf(pTmp, "%d", nValue);
	return SetParament(pName, pTmp);
}




















