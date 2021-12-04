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
	// 必须的
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{		
	}
}


void CCommunication::ReleaseSockWSA()
{
	// 必须的
	if(WSACleanup() != 0)
	{		
	}
}

// 释放
void CCommunication::Release()
{

}

// TCP连接
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

// TCP关闭连接
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


// 设置超时
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


// 长连接或者短连接模式
void CCommunication::SetMode(bool bLongConnect)
{
	m_bLongConnect = bLongConnect;
}

// socket参数
void CCommunication::SetTcpIP(const char* pIP)
{	
	m_pSA.sin_family = AF_INET;	
	m_pSA.sin_addr.s_addr = inet_addr(pIP);	
}

// socket参数
void CCommunication::SetTcpPort(__int32 nPort)
{	
	m_pSA.sin_family = AF_INET;
	m_pSA.sin_port = htons(nPort);
}




// 数据发读
long CCommunication::SendSyncData(CMyString pSendData, CMyString& pRecvData)
{
	vLocker lock(&m_syncLock);

	long nCode = Connect();
	if(nCode != 0)
	{
		return nCode;
	}

	// 清空原来的数据
	m_pRecvData.SetSize(0);

	// 发送数据
	int res = send(m_hSock, pSendData.GetString(), pSendData.Size(), 0);
	if(res == SOCKET_ERROR)
	{
		CloseConnect();
		return FINS_SEND_FAIL;
	}
	
	// 数据读取
	nCode = RecvData(pRecvData);

	// 短连接每次都关闭
	if(!m_bLongConnect)
	{
		CloseConnect();
	}

	return nCode;
}



// 数据读取
// 带超时处理
long CCommunication::RecvData(CMyString& pRecvData)
{		
	long nCode = 0;
	StartRecvData();

	// 等待接收
	ResetEvent(m_hRecvTimeoutEvent);
	DWORD rs = WaitForSingleObject(m_hRecvTimeoutEvent, m_nRecvTimeout);
	
	// 成功返回值
	if (rs == WAIT_OBJECT_0)
	{
		pRecvData = m_pRecvData;
	}

	// 超时等其他错误
	else
	{
		StopRecvData();
		CloseConnect();
		nCode = FINS_RECV_WAIT_TIMEOUT;
	}
	
	return nCode;	
}


// 创建接收线程
// 
void CCommunication::CreateRecvThread()
{
	ResetEvent(m_hRecvExitFinish);
	_beginthread(RunRecvThread, 0, this);
}

// 退出接收线程
// 
void CCommunication::ExitRecvThread()
{
	CloseConnect();
	SetEvent(m_hRecvExit);	
	SetEvent(m_hRecvStartData);
	WaitForSingleObject(m_hRecvExitFinish, INFINITE);
}



// 定时器线程
void CCommunication::RunRecvThread(void* lp)
{
	CCommunication* pMC = (CCommunication*)lp;
	pMC->RecvHandle();
	SetEvent(pMC->m_hRecvExitFinish);	// 处理完毕
}

// 定时器
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

// 一次接收数据
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

// 告诉通讯，数据接收完成
void CCommunication::SetRecvComplete(int nSize)
{
	ResetEvent(m_hRecvStartData);			// 复位接收
	SetEvent(m_hRecvTimeoutEvent);			// 接收成功	
}

// 重写数据接收,开始接收数据，用于协议识别
void CCommunication::OnBeginRecv()
{
}

// 通讯关闭
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



// 开始接收数据
void CCommunication::StartRecvData()
{
	OnBeginRecv();
	SetEvent(m_hRecvStartData);
}

// 停止接收数据
void CCommunication::StopRecvData()
{
	ResetEvent(m_hRecvStartData);
}

// 断开通讯
void CCommunication::Disconnect()
{

}
















