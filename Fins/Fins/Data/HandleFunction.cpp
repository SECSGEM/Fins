#include "stdafx.h"
#include "HandleFunction.h"

// ת�����ݡ�Low�ڵ͡�Hight�ڸ�
unsigned int GetShortLH(const unsigned char* pData)
{
	__int64 nNum = 0;
	nNum = pData[0];
	nNum += (((int)pData[1]) << 8) & 0xFF00;
	return (unsigned int)nNum;
}


unsigned int GetIntLH(const unsigned char* pData)
{
	__int64 nNum = 0;
	nNum = pData[0];
	nNum += (((int)pData[1]) << 8) & 0xFF00;
	nNum += (((int)pData[2]) << 16) & 0xFF0000;
	nNum += (((int)pData[3]) << 24) & 0xFF000000;
	return (unsigned int)nNum;
}



void SetShortLH(__int64 nNum, unsigned char* pData)
{	
	pData[0] = nNum & 0xFF;
	pData[1] = (nNum >> 8) & 0xFF;
}


void SetIntLH(__int64 nNum, unsigned char* pData)
{	
	pData[0] = nNum & 0xFF;
	pData[1] = (nNum >> 8) & 0xFF;
	pData[2] = (nNum >> 16) & 0xFF;
	pData[3] = (nNum >> 24) & 0xFF;
}

// ת�����ݡ�Low�ڸߡ�Hight�ڵ�
unsigned int GetShortHL(const unsigned char* pData)
{
	__int64 nNum = 0;
	nNum = (((int)pData[0]) << 8) & 0xFF00;
	nNum += pData[1];	
	return (unsigned int)nNum;
}


unsigned int GetIntHL(const unsigned char* pData)
{
	__int64 nNum = 0;

	nNum  = (((int)pData[0]) << 24) & 0xFF000000;
	nNum += (((int)pData[1]) << 16) & 0xFF0000;
	nNum += (((int)pData[2]) << 8) & 0xFF00;
	nNum += pData[3];
		
	return (unsigned int)nNum;
}



void SetShortHL(__int64 nNum, unsigned char* pData)
{	
	pData[0] = (nNum >> 8) & 0xFF;
	pData[1] = nNum & 0xFF;	
}


void SetIntHL(__int64 nNum, unsigned char* pData)
{	
	pData[0] = (nNum >> 24) & 0xFF;
	pData[1] = (nNum >> 16) & 0xFF;
	pData[2] = (nNum >> 8) & 0xFF;
	pData[3] = nNum & 0xFF;	
}


// ���ٺ��ͷ��ڴ�
char* vMalloc(__int64 nSize)
{
	int nRealSize = (int)(nSize+2);
	char* pBuff = (char*)malloc(nRealSize);
	if (pBuff !=nullptr)
	{
		memset(pBuff, 0, nRealSize);
	}
	return pBuff;
}

// ���ٺ��ͷ��ڴ�
void vFree(char* pData)
{
	free(pData);
}











