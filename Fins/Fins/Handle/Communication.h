#pragma once

// 用于TCP/IP通讯

class CCommunication
{
public:
	CCommunication();
	virtual ~CCommunication();

	// 释放
	void Release();	
	void SetTimeout(int nMs);					// 设置超时
	void SetMode(bool bLongConnect);			// 长连接或者短连接模式
	void SetTcpIP(const char* pIP);				// socket参数
	void SetTcpPort(int nPort);					// socket参数
	int GetTimeout();
	
	long SendSyncData(CMyString pSendData, CMyString& pRecvData);	// 数据发读
	void Disconnect();	// 断开通讯

protected:

	// 数据接收
	void SetRecvComplete(int nSize);	// 告诉通讯，数据接收完成
	virtual void OnBeginRecv();								// 重写数据接收,开始接收数据，用于协议识别
	virtual void OnDataRecv(char* pData, int nSize) = 0;	// 重写数据接收,用于协议识别
	virtual void OnCloseConnect();							// 通讯关闭

private:
		
	long Connect();			// TCP连接
	void CloseConnect();	// TCP关闭连接

	void InitSockWSA();
	void ReleaseSockWSA();

	// 接收数据线程
	void CreateRecvThread();		// 创建接收线程
	void ExitRecvThread();			// 退出接收线程
	static void RunRecvThread(void* lp);
	void RecvHandle();
	bool IsExitThread();
	void OneRecvData();				// 一次接收数据
	void StartRecvData();			// 开始接收数据
	void StopRecvData();			

	// 数据读取,从缓存内读取
	long RecvData(CMyString& pRecvData);	
	

private:
	
	bool m_bLongConnect;		// 长连接		
	int m_nRecvTimeout;			// 接收超时

	// socket
	SOCKET m_hSock; 
	struct sockaddr_in m_pSA;
	vCritical m_syncLock;		// 每次只能单个tcp读写
	vCritical m_syncLockTcp;	// soekct操作

	HANDLE m_hRecvTimeoutEvent;		// 接收线程超时
	HANDLE m_hRecvExitFinish;		// 定时器线程退出完毕
	HANDLE m_hRecvExit;				// 接收退出
	HANDLE m_hRecvStartData;		// 开始接收数据

	CMyString m_pRecvData;		// 接收到的数据
	long m_nRecvCode;			// 读取错误代码

	// 临时缓
	int m_nSize;
	int m_nRecvSize;
	char m_pBuff[200];

};













