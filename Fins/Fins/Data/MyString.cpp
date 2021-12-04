#include "stdafx.h"
#include "MyString.h"




CMyString::CMyString()
{
	m_pBuff = (char*)MallocMemory(200);		
	m_nLength = 0;
	m_nSpaceAvl = 200;
}

CMyString::CMyString(int size)
{
	if (size <= 0)
	{
		size = 200;
	}

	m_pBuff = (char*)MallocMemory(size);		
	m_nLength = 0;
	m_nSpaceAvl = size;
}

CMyString::CMyString(const char* pStr)
{		
	int size = (int)strlen(pStr);
	m_nSpaceAvl = 3 * size;
	if (m_nSpaceAvl < 200)
	{
		m_nSpaceAvl = 200;
	}
	m_pBuff =  (char*)MallocMemory(m_nSpaceAvl);
	memcpy(m_pBuff, pStr, size);
	m_nLength = size;		
}


CMyString::CMyString(const char* pStr, int size)
{	
	m_nSpaceAvl = 3 * size;
	if (m_nSpaceAvl < 200)
	{
		m_nSpaceAvl = 200;
	}
	m_pBuff = (char*)MallocMemory(m_nSpaceAvl);
	memcpy(m_pBuff, pStr, size);
	m_nLength = size;
}

CMyString::CMyString(const CMyString& dst)
{	
	this->m_nLength = dst.m_nLength;
	this->m_nSpaceAvl = dst.m_nSpaceAvl;
	this->m_pBuff = (char*)MallocMemory(this->m_nSpaceAvl);
	memcpy(m_pBuff, dst.m_pBuff, this->m_nLength);	
}

CMyString::~CMyString()
{
	if(m_pBuff != nullptr)
	{
		FreeMemory(m_pBuff);
	}
}

char CMyString::Append(const char* str)
{
	return Append(str, -1);
}


char CMyString::Append(const char* str, int length)
{
	return Append(str, 0, length);
}

char CMyString::Append(const char* str, int offset, int slen)
{
	if (slen < 0)
	{
		slen = (int)strlen((char*)str);
	}
	int num = m_nLength + slen;
	if (num > m_nSpaceAvl)
	{
		m_nSpaceAvl = 2 * num;
		char* numArray = (char*)MallocMemory(m_nSpaceAvl);
		memcpy(numArray, m_pBuff, m_nLength);		
		// 先释放
		FreeMemory(m_pBuff);
		m_pBuff = numArray;
	}
	for (int index = 0; index < slen; ++index)
	{
		m_pBuff[m_nLength + index] = str[offset + index];
	}
	m_nLength += slen;
	return m_nLength;
}

// 获取字符串
char* CMyString::GetString()
{
	return m_pBuff;
}

// 长度
int CMyString::Size()
{
	return m_nLength;
}

// 设置大小
// 同时，已使用长度等于设置长度
void CMyString::SetSize(int nSize)
{
	if (nSize < 0)
	{
		nSize = 0;
	}

	if (nSize > m_nLength)
	{
		m_nSpaceAvl = nSize;
		char* mTmpBuff =  (char*)MallocMemory(m_nSpaceAvl);
		memcpy(mTmpBuff, m_pBuff, m_nLength);
		FreeMemory(m_pBuff);
		m_pBuff = (char*)mTmpBuff;
	}
	m_nLength = nSize;	
}


CMyString& CMyString::operator = (const CMyString& dst)
{	
	if(m_pBuff != nullptr)
	{
		FreeMemory(m_pBuff);
	}
	this->m_nLength = dst.m_nLength;
	this->m_nSpaceAvl = dst.m_nSpaceAvl;
	this->m_pBuff = (char*)MallocMemory(this->m_nSpaceAvl);
	memcpy(m_pBuff, dst.m_pBuff, this->m_nLength);	
	return* this;
}


char* CMyString::MallocMemory(int nSize)
{
	char* pData = (char*)malloc(nSize+5);
	memset(pData, 0, nSize+5);
	return pData;
}

void CMyString::FreeMemory(char* pObject)
{
	free(pObject);
}













