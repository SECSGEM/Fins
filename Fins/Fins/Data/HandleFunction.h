#pragma once



// ת�����ݡ�Low�ڵ͡�Hight�ڸ�
unsigned int GetShortLH(const unsigned char* pData);
unsigned int GetIntLH(const unsigned char* pData);

void SetShortLH(__int64 nNum, unsigned char* pData);
void SetIntLH(__int64 nNum, unsigned char* pData);

// ת�����ݡ�Low�ڸߡ�Hight�ڵ�
unsigned int GetShortHL(const unsigned char* pData);
unsigned int GetIntHL(const unsigned char* pData);

void SetShortHL(__int64 nNum, unsigned char* pData);
void SetIntHL(__int64 nNum, unsigned char* pData);


// ���ٺ��ͷ��ڴ�
char* vMalloc(__int64 nSize);
void vFree(char* pData);






