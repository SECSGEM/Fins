#pragma once
#include "Communication.h"


class CFinsHandle : public CCommunication
{
public:
	CFinsHandle();
		
	long ReadMemoryData(int nAddr, int nSize, FINS_DATA_TYPE::ENUM nType, __int16* pData);
	long WriteMemoryData(int nAddr, int nSize, FINS_DATA_TYPE::ENUM nType, __int16* pData);
	
private:
	
	virtual void OnBeginRecv();							// ��д���ݽ���,��ʼ��������
	virtual void OnDataRecv(char* pData, int nSize);	// ��д���ݽ���,����Э��ʶ��
	virtual void OnCloseConnect();						// ͨѶ�ر�

	// ���������Ƿ����
	long CheckReplyDataIsError(char* pData, int nSize);		// ���������Ƿ����

	long GetFinsNodeAddress();	// ��ȡfins�ڵ��ַ		
	long EstablishCommunicationByFins();	// ����FinsͨѶ
	
private:

	CMyString m_pRecvData;
	bool m_bEstablishCommunicationByFins;	// ��Fins����ͨѶ
	int m_nIpNode;	// IP�ڵ�

};
























