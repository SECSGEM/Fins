#pragma once
#include "Communication.h"


class CFinsHandle : public CCommunication
{
public:
	CFinsHandle();
		
	long ReadMemoryData(int nAddr, int nSize, FINS_DATA_TYPE::ENUM nType, __int16* pData);
	long WriteMemoryData(int nAddr, int nSize, FINS_DATA_TYPE::ENUM nType, __int16* pData);
	
private:
	
	virtual void OnBeginRecv();							// 重写数据接收,开始接收数据
	virtual void OnDataRecv(char* pData, int nSize);	// 重写数据接收,用于协议识别
	virtual void OnCloseConnect();						// 通讯关闭

	// 检查答复数据是否错误
	long CheckReplyDataIsError(char* pData, int nSize);		// 检查答复数据是否错误

	long GetFinsNodeAddress();	// 获取fins节点地址		
	long EstablishCommunicationByFins();	// 建立Fins通讯
	
private:

	CMyString m_pRecvData;
	bool m_bEstablishCommunicationByFins;	// 与Fins建立通讯
	int m_nIpNode;	// IP节点

};
























