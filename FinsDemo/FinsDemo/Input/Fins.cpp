#include "stdafx.h"
#include "Fins.h"
#include "ModuleDevelopH.h"
#pragma warning(disable:4996) 

// ŷķ��FinsЭ��
CFins::CFins() :
	m_pLoadInterface("Fins.dll")
{	
	m_pFins = NULL;
	m_pLoadInterface.DllCreateInterface((void**)&m_pFins);	
}


CFins::~CFins()
{

}




// ���õ�ַ
CResult CFins::SetIP(std::string pIP)
{
	return SetParament(OCA_PARAM_FINS_IP, pIP);
}

// ���ö˿ں�
CResult CFins::SetPort(int nPort)
{
	return SetParament(OCA_PARAM_FINS_PORT, nPort);
}

// ���ó�ʱ
CResult CFins::SetTimeout(int nTimeMs)
{
	return SetParament(OCA_PARAM_FINS_TIMEOUT, nTimeMs);
}


// ����
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



// ����
CResult CFins::Read(std::string pAddr, char* pData, int nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll����ʧ�ܣ����ܲ����ڻ��߳���");
	}
	return m_pFins->Read(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Read(std::string pAddr, __int16* pData, int nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll����ʧ�ܣ����ܲ����ڻ��߳���");
	}
	return m_pFins->Read(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Read(std::string pAddr, __int32* pData, int nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll����ʧ�ܣ����ܲ����ڻ��߳���");
	}
	return m_pFins->Read(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Read(std::string pAddr, __int64* pData, int nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll����ʧ�ܣ����ܲ����ڻ��߳���");
	}
	return m_pFins->Read(pAddr.c_str(), pData, nSize, "");
}
 



// д��
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


// д��
CResult CFins::Write(std::string pAddr, char* pData, __int32 nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll����ʧ�ܣ����ܲ����ڻ��߳���");
	}
	return m_pFins->Write(pAddr.c_str(), pData, nSize, "");
}
 
CResult CFins::Write(std::string pAddr,  __int16* pData, __int32 nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll����ʧ�ܣ����ܲ����ڻ��߳���");
	}
	return m_pFins->Write(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Write(std::string pAddr,  __int32* pData, __int32 nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll����ʧ�ܣ����ܲ����ڻ��߳���");
	}
	return m_pFins->Write(pAddr.c_str(), pData, nSize, "");
}

CResult CFins::Write(std::string pAddr,  __int64* pData, __int32 nSize)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll����ʧ�ܣ����ܲ����ڻ��߳���");
	}
	return m_pFins->Write(pAddr.c_str(), pData, nSize, "");
}


CResult CFins::SetParament(std::string pName, std::string pValue)
{
	if (m_pFins == NULL)
	{
		return CResult(1, "fins.dll����ʧ�ܣ����ܲ����ڻ��߳���");
	}
	return m_pFins->SetParament(pName.c_str(), pValue.c_str());
}
 
CResult CFins::SetParament(std::string pName, int nValue)
{
	char pTmp[200] = {0};
	sprintf(pTmp, "%d", nValue);
	return SetParament(pName, pTmp);
}




















