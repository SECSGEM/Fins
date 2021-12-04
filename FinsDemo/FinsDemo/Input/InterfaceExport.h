#pragma once

#ifndef __FINS_MEMEORY_DATA__
#define __FINS_MEMEORY_DATA__

// �ڴ���������:��Ԫ��
namespace FINS_DATA_TYPE
{
	enum ENUM
	{
		ERR = 0x00,		// ����
		DM = 0x82,		// ���ݼĴ���	
	};
}

#define OCA_PARAM_FINS_IP				"IP"				// ͳһAPI��fins��IP��ַ
#define OCA_PARAM_FINS_PORT				"PORT"				// ͳһAPI��fins��IP��ַ
#define OCA_PARAM_FINS_TIMEOUT			"TIMEOUT"			// ͳһAPI��fins��IP��ַ

#endif

struct CResult;

// ŷķ��FinsЭ��
class CInterfaceExport
{
public:

	// ����
	virtual CResult SetParament(const char* pName, const char* pValue) = 0; 

	// ��ʼ��ģ��
	virtual CResult Connect() = 0; 
	virtual CResult Disconnect() = 0; 

	// �ͷ�
	virtual void Release() = 0; 

	// ����
	virtual CResult Read(const char* pAddr, char* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Read(const char* pAddr, __int16* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Read(const char* pAddr, __int32* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Read(const char* pAddr, __int64* pData, __int32 nSize, char* pCtrlData) = 0; 

	// д��
	virtual CResult Write(const char* pAddr, char* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Write(const char* pAddr,  __int16* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Write(const char* pAddr,  __int32* pData, __int32 nSize, char* pCtrlData) = 0; 
	virtual CResult Write(const char* pAddr,  __int64* pData, __int32 nSize, char* pCtrlData) = 0; 

};




#ifndef __RESULT_CODE__
#define __RESULT_CODE__

// ����ֵ���
struct CResult
{
	__int32 nCode;		// �������
	char pText[200];	// ������Ϣ	

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



























