#pragma once

// ����TCP/IPͨѶ

class CCommunication
{
public:
	CCommunication();
	virtual ~CCommunication();

	// �ͷ�
	void Release();	
	void SetTimeout(int nMs);					// ���ó�ʱ
	void SetMode(bool bLongConnect);			// �����ӻ��߶�����ģʽ
	void SetTcpIP(const char* pIP);				// socket����
	void SetTcpPort(int nPort);					// socket����
	int GetTimeout();
	
	long SendSyncData(CMyString pSendData, CMyString& pRecvData);	// ���ݷ���
	void Disconnect();	// �Ͽ�ͨѶ

protected:

	// ���ݽ���
	void SetRecvComplete(int nSize);	// ����ͨѶ�����ݽ������
	virtual void OnBeginRecv();								// ��д���ݽ���,��ʼ�������ݣ�����Э��ʶ��
	virtual void OnDataRecv(char* pData, int nSize) = 0;	// ��д���ݽ���,����Э��ʶ��
	virtual void OnCloseConnect();							// ͨѶ�ر�

private:
		
	long Connect();			// TCP����
	void CloseConnect();	// TCP�ر�����

	void InitSockWSA();
	void ReleaseSockWSA();

	// ���������߳�
	void CreateRecvThread();		// ���������߳�
	void ExitRecvThread();			// �˳������߳�
	static void RunRecvThread(void* lp);
	void RecvHandle();
	bool IsExitThread();
	void OneRecvData();				// һ�ν�������
	void StartRecvData();			// ��ʼ��������
	void StopRecvData();			

	// ���ݶ�ȡ,�ӻ����ڶ�ȡ
	long RecvData(CMyString& pRecvData);	
	

private:
	
	bool m_bLongConnect;		// ������		
	int m_nRecvTimeout;			// ���ճ�ʱ

	// socket
	SOCKET m_hSock; 
	struct sockaddr_in m_pSA;
	vCritical m_syncLock;		// ÿ��ֻ�ܵ���tcp��д
	vCritical m_syncLockTcp;	// soekct����

	HANDLE m_hRecvTimeoutEvent;		// �����̳߳�ʱ
	HANDLE m_hRecvExitFinish;		// ��ʱ���߳��˳����
	HANDLE m_hRecvExit;				// �����˳�
	HANDLE m_hRecvStartData;		// ��ʼ��������

	CMyString m_pRecvData;		// ���յ�������
	long m_nRecvCode;			// ��ȡ�������

	// ��ʱ��
	int m_nSize;
	int m_nRecvSize;
	char m_pBuff[200];

};













