#pragma once



struct FINS_TCP_HEAD
{
	char pMagic[4];					// Э��ID	FINS
	unsigned int nLength;			// ����,��Ҫ����
	char pReserved[3];				// ����
	int nCommand;					// ����֡����
	unsigned int nErrorCode;		// �������


	FINS_TCP_HEAD();
	void GetData(char* pData);		// ת�ɶ���������	
	void SetData(char* pData);		// �Ӷ��������ݻ�ȡ	

	void SetLength(int nLength);	// �������ݳ��ȴ�С
	int GetLength();				// ��ȡ���ݳ��ȴ�С
	
};


struct FINS_CONTROL_HEAD 
{
	int nICF;		// ��Ϣ������
	int nRev;		// ����
	int nGCT;		// ����������
	int nDNA;		// Ŀ�������ַ
	int nDA1;		// Ŀ��ڵ��
	int nDA2;		// Դ��Ԫ��
	int nSNA;		// Դ�����ַ
	int nSA1;		// Դ�ڵ�
	int nSA2;		// Դ��Ԫ��ַ
	int nSID;		// ���к�
	int nCmd1;		// ����1
	int nCmd2;		// ����2

	FINS_CONTROL_HEAD();
	void GetData(char* pData);		// ת�ɶ���������	
	void SetData(char* pData);		// �Ӷ��������ݻ�ȡ	

};


// FINS��������
struct FINS_CONNECT_REQUST
{
	char pClientAddrss[4];			// �ͻ��˵�ַ,һ��Ϊ0x0000000

	FINS_CONNECT_REQUST();
	void GetData(char* pData);		// ת�ɶ���������	
	void SetIp(string pIP);
};

// FINS�������Ӵ�
struct FINS_CONNECT_RESPONSE 
{
	char pClientAddrss[4];			// PC	
	char pServerAddrss[4];			// PLC CPU

	FINS_CONNECT_RESPONSE();
	void SetData(char* pData);		// ת�ɶ���������	
};

// �ڴ�����ȡ
struct FINS_MEMORY_AREA_READ
{
	int nAreaCode;		// �������
	int nAddr;			// ��ʼ��ַ
	int nBitNo;			// λ��
	int nLength;		// ����

	FINS_MEMORY_AREA_READ();
	void GetData(char* pData);		// ת�ɶ���������	
};

// �ڴ�����ȡ��
struct FINS_MEMORY_AREA_READ_REPLY
{
	int nEndCode;
	CMyString pData;		// ����

	void SetData(char* pData, int nSize);		// ת�ɶ���������
	int GetDataSize();							// fins����
	int GetDataBytsSize();						// ʵ��byte����
	char* GetData();
};



// �ڴ���д��
struct FINS_MEMORY_AREA_WRITE
{
	int nAreaCode;		// �������
	int nAddr;			// ��ʼ��ַ
	int nBitNo;			// λ��
	int nLength;		// ����
	CMyString pData;	// ����

	FINS_MEMORY_AREA_WRITE();
	void GetData(char* pData);		// ת�ɶ���������	
};

// �ڴ�����ȡ��
struct FINS_MEMORY_AREA_WRITE_REPLY
{
	int nEndCode;

	FINS_MEMORY_AREA_WRITE_REPLY();
	void SetData(char* pData);		// ת�ɶ���������	
};











