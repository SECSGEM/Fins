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

	// 附加字符串
	char Append(const char* str);
	
	char Append(const char* str, int length);
	
	char Append(const char* str, int offset, int slen);		// offset为传入字符串开始位置
	
	// 获取字符串
	char* GetString();
	
	// 长度
	int Size();

	// 设置大小
	// 同时，已使用长度等于设置长度
	void SetSize(int nSize);

private:
	char* MallocMemory(int nSize);
	void FreeMemory(char* pObject);

private:
	// 字符串
	char* m_pBuff;

	// 当前长度
	int m_nLength;
	
	// 总长度
	int m_nSpaceAvl;

};

















