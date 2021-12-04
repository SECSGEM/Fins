#pragma once
#include "Export/InterfaceExport.h"
#include "FinsHandle.h"

class CFinsReadWrite : public CInterfaceExport
{
public:

	// ����
	virtual CResult SetParament(const char* pName, const char* pValue); 

	// ��ʼ��ģ��
	virtual CResult Connect(); 
	virtual CResult Disconnect(); 

	// �ͷ�
	virtual void Release(); 

public:	

	// ����
	virtual CResult Read(const char* pAddr, char* pData, __int32 size, char* pCtrlData); 
	virtual CResult Read(const char* pAddr, __int16* pData, __int32 size, char* pCtrlData); 
	virtual CResult Read(const char* pAddr, __int32* pData, __int32 size, char* pCtrlData); 
	virtual CResult Read(const char* pAddr, __int64* pData, __int32 size, char* pCtrlData); 

	// д��
	virtual CResult Write(const char* pAddr, char* pData, __int32 size, char* pCtrlData); 
	virtual CResult Write(const char* pAddr, __int16* pData, __int32 size, char* pCtrlData); 
	virtual CResult Write(const char* pAddr, __int32* pData, __int32 size, char* pCtrlData); 
	virtual CResult Write(const char* pAddr, __int64* pData, __int32 size, char* pCtrlData); 												

private:
	long ReadData(int nAddr, __int16* pData, int nSize, int nDataType);		// ��ȡ2�ֽ�һ��	
	long WriteData(int nAddr, __int16* pData, int nSize, int nDataType);	// ��ȡ2�ֽ�һ��
	void GetDataTypeAndAddr(string pAddr, int& nDataType, int& nAddr);		// ��ȡ���ݵ�ַ
	int GetDataArea(string pArea);		// ��ȡ������

private:
	CFinsHandle m_pHandle;

};












































