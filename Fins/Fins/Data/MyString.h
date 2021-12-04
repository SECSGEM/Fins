#pragma once


class CMyString
{

public:
	CMyString();
	CMyString(int size);
	CMyString(const char* pStr);
	CMyString(const char* pStr, int size);
	CMyString(const CMyString& dst);
	~CMyString();


	CMyString& operator = (const CMyString& dst);

	// �����ַ���
	char Append(const char* str);
	
	char Append(const char* str, int length);
	
	char Append(const char* str, int offset, int slen);		// offsetΪ�����ַ�����ʼλ��
	
	// ��ȡ�ַ���
	char* GetString();
	
	// ����
	int Size();

	// ���ô�С
	// ͬʱ����ʹ�ó��ȵ������ó���
	void SetSize(int nSize);

private:
	char* MallocMemory(int nSize);
	void FreeMemory(char* pObject);

private:
	// �ַ���
	char* m_pBuff;

	// ��ǰ����
	int m_nLength;
	
	// �ܳ���
	int m_nSpaceAvl;

};

















