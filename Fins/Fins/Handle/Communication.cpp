#include "stdafx.h"
#include "Communication.h"


CCommunication::CCommunication()
{
	m_nRecvTimeout = 5000;
	m_bLongConnect = true;
	m_hSock = INVALID_SOCKET;
	InitSockWSA();

	memset(&m_pSA, 0, sizeof(struct sockaddr_in));
	
	m_hRecvExit = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hRecvExitFinish = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hRecvTimeoutEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hRecvStartData = CreateEvent(NULL, TRUE, FALSE, NULL);

	CreateRecvThread();
}


CCommunication::~CCommunication()
{
	ExitRecvThread();
	ReleaseSockWSA();

	CloseHandle(m_hRecvExit);
	CloseHandle(m_hRecvExitFinish);
	CloseHandle(m_hRecvTimeoutEvent);
	CloseHandle(m_hRecvStartData);
}



void CCommunication::InitSockWSA()
{
	// �����
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{		
	}
}


void CCommunication::ReleaseSockWSA()
{
	// �����
	if(WSACleanup() != 0)
	{		
	}
}

// �ͷ�
void CCommunication::Release()
{

}

// TCP����
long CCommunication::Connect()
{
	if(m_hSock == INVALID_SOCKET)
	{
		m_hSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(m_hSock != INVALID_SOCKET)
		{		
			if(connect(m_hSock, (struct sockaddr*)&m_pSA, sizeof(m_pSA)) < 0)
			{					
				closesocket(m_hSock);
				m_hSock = INVALID_SOCKET;	
				return FINS_SOCKET_CONNECT_FAIL;
			}	
		}
		else
		{
			return FINS_SOCKET_CREATE_FAIL;
		}
	}

	return 0;
}

// TCP�ر�����
void CCommunication::CloseConnect()
{
	vLocker lock(&m_syncLockTcp);
	if (m_hSock != INVALID_SOCKET)
	{
		shutdown(m_hSock, 2);
		closesocket(m_hSock);
		m_hSock = INVALID_SOCKET;

		OnCloseConnect();
	}	
}


// ���ó�ʱ
void CCommunication::SetTimeout(__int32 nMs)
{
	if(nMs < 100)
	{
		nMs = 100;
	}
	m_nRecvTimeout = nMs;
}

int CCommunication::GetTimeout()
{
	return m_nRecvTimeout;
}


// �����ӻ��߶�����ģʽ
void CCommunication::SetMode(bool bLongConnect)
{
	m_bLongConnect = bLongConnect;
}

// socket����
void CCommunication::SetTcpIP(const char* pIP)
{	
	m_pSA.sin_family = AF_INET;	
	m_pSA.sin_addr.s_addr = inet_addr(pIP);	
}

// socket����
void CCommunication::SetTcpPort(__int32 nPort)
{	
	m_pSA.sin_family = AF_INET;
	m_pSA.sin_port = htons(nPort);
}




// ���ݷ���
long CCommunication::SendSyncData(CMyString pSendData, CMyString& pRecvData)
{
	vLocker lock(&m_syncLock);

	long nCode = Connect();
	if(nCode != 0)
	{
		return nCode;
	}

	// ���ԭ��������
	m_pRecvData.SetSize(0);

	// ��������
	int res = send(m_hSock, pSendData.GetString(), pSendData.Size(), 0);
	if(res == SOCKET_ERROR)
	{
		CloseConnect();
		return FINS_SEND_FAIL;
	}
	
	// ���ݶ�ȡ
	nCode = RecvData(pRecvData);

	// ������ÿ�ζ��ر�
	if(!m_bLongConnect)
	{
		CloseConnect();
	}

	return nCode;
}



// ���ݶ�ȡ
// ����ʱ����
long CCommunication::RecvData(CMyString& pRecvData)
{		
	long nCode = 0;
	StartRecvData();

	// �ȴ�����
	ResetEvent(m_hRecvTimeoutEvent);
	DWORD rs = WaitForSingleObject(m_hRecvTimeoutEvent, m_nRecvTimeout);
	
	// �ɹ�����ֵ
	if (rs == WAIT_OBJECT_0)
	{
		pRecvData = m_pRecvData;
	}

	// ��ʱ����������
	else
	{
		StopRecvData();
		CloseConnect();
		nCode = FINS_RECV_WAIT_TIMEOUT;
	}
	
	return nCode;	
}


// ���������߳�
// 
void CCommunication::CreateRecvThread()
{
	ResetEvent(m_hRecvExitFinish);
	_beginthread(RunRecvThread, 0, this);
}

// �˳������߳�
// 
void CCommunication::ExitRecvThread()
{
	CloseConnect();
	SetEvent(m_hRecvExit);	
	SetEvent(m_hRecvStartData);
	WaitForSingleObject(m_hRecvExitFinish, INFINITE);
}



// ��ʱ���߳�
void CCommunication::RunRecvThread(void* lp)
{
	CCommunication* pMC = (CCommunication*)lp;
	pMC->RecvHandle();
	SetEvent(pMC->m_hRecvExitFinish);	// �������
}

// ��ʱ��
void CCommunication::RecvHandle()
{
	while (!IsExitThread())
	{
		WaitForSingleObject(m_hRecvStartData, INFINITE);
		if (IsExitThread())
		{
			break;
		}		

		OneRecvData();
	}
}

// һ�ν�������
void CCommunication::OneRecvData()
{
	m_nSize = 200;
	m_nRecvSize = recv(m_hSock, m_pBuff, m_nSize, 0);
	if(m_nRecvSize == SOCKET_ERROR)
	{
		CloseConnect();
		m_nRecvCode = FINS_SOCKET_CONNECT_ERR;
	}
	else
	{			
		m_pRecvData.Append(m_pBuff, m_nRecvSize);			
		m_nRecvCode = 0;	
		OnDataRecv(m_pBuff, m_nRecvSize);	
	}
}

// ����ͨѶ�����ݽ������
void CCommunication::SetRecvComplete(int nSize)
{
	ResetEvent(m_hRecvStartData);			// ��λ����
	SetEvent(m_hRecvTimeoutEvent);			// ���ճɹ�	
}

// ��д���ݽ���,��ʼ�������ݣ�����Э��ʶ��
void CCommunication::OnBeginRecv()
{
}

// ͨѶ�ر�
void CCommunication::OnCloseConnect()
{

}

bool CCommunication::IsExitThread()
{
	if(WaitForSingleObject(m_hRecvExit, 0) == WAIT_OBJECT_0)
	{
		return true;
	}
	return false;
}



// ��ʼ��������
void CCommunication::StartRecvData()
{
	OnBeginRecv();
	SetEvent(m_hRecvStartData);
}

// ֹͣ��������
void CCommunication::StopRecvData()
{
	ResetEvent(m_hRecvStartData);
}

// �Ͽ�ͨѶ
void CCommunication::Disconnect()
{

}
















