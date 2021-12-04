#pragma once



struct FINS_TCP_HEAD
{
	char pMagic[4];					// 协议ID	FINS
	unsigned int nLength;			// 长度,需要设置
	char pReserved[3];				// 保留
	int nCommand;					// 数据帧类型
	unsigned int nErrorCode;		// 错误代码


	FINS_TCP_HEAD();
	void GetData(char* pData);		// 转成二进制数据	
	void SetData(char* pData);		// 从二进制数据获取	

	void SetLength(int nLength);	// 设置数据长度大小
	int GetLength();				// 获取数据长度大小
	
};


struct FINS_CONTROL_HEAD 
{
	int nICF;		// 信息控制码
	int nRev;		// 保留
	int nGCT;		// 网关数据量
	int nDNA;		// 目标网络地址
	int nDA1;		// 目标节点号
	int nDA2;		// 源单元号
	int nSNA;		// 源网络地址
	int nSA1;		// 源节点
	int nSA2;		// 源单元地址
	int nSID;		// 序列号
	int nCmd1;		// 命令1
	int nCmd2;		// 命令2

	FINS_CONTROL_HEAD();
	void GetData(char* pData);		// 转成二进制数据	
	void SetData(char* pData);		// 从二进制数据获取	

};


// FINS请求连接
struct FINS_CONNECT_REQUST
{
	char pClientAddrss[4];			// 客户端地址,一般为0x0000000

	FINS_CONNECT_REQUST();
	void GetData(char* pData);		// 转成二进制数据	
	void SetIp(string pIP);
};

// FINS请求连接答复
struct FINS_CONNECT_RESPONSE 
{
	char pClientAddrss[4];			// PC	
	char pServerAddrss[4];			// PLC CPU

	FINS_CONNECT_RESPONSE();
	void SetData(char* pData);		// 转成二进制数据	
};

// 内存区读取
struct FINS_MEMORY_AREA_READ
{
	int nAreaCode;		// 区域代码
	int nAddr;			// 开始地址
	int nBitNo;			// 位号
	int nLength;		// 长度

	FINS_MEMORY_AREA_READ();
	void GetData(char* pData);		// 转成二进制数据	
};

// 内存区读取答复
struct FINS_MEMORY_AREA_READ_REPLY
{
	int nEndCode;
	CMyString pData;		// 数据

	void SetData(char* pData, int nSize);		// 转成二进制数据
	int GetDataSize();							// fins长度
	int GetDataBytsSize();						// 实际byte长度
	char* GetData();
};



// 内存区写入
struct FINS_MEMORY_AREA_WRITE
{
	int nAreaCode;		// 区域代码
	int nAddr;			// 开始地址
	int nBitNo;			// 位号
	int nLength;		// 长度
	CMyString pData;	// 数据

	FINS_MEMORY_AREA_WRITE();
	void GetData(char* pData);		// 转成二进制数据	
};

// 内存区读取答复
struct FINS_MEMORY_AREA_WRITE_REPLY
{
	int nEndCode;

	FINS_MEMORY_AREA_WRITE_REPLY();
	void SetData(char* pData);		// 转成二进制数据	
};











