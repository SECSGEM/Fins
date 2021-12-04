#pragma once



// 转换数据。Low在低、Hight在高
unsigned int GetShortLH(const unsigned char* pData);
unsigned int GetIntLH(const unsigned char* pData);

void SetShortLH(__int64 nNum, unsigned char* pData);
void SetIntLH(__int64 nNum, unsigned char* pData);

// 转换数据。Low在高、Hight在低
unsigned int GetShortHL(const unsigned char* pData);
unsigned int GetIntHL(const unsigned char* pData);

void SetShortHL(__int64 nNum, unsigned char* pData);
void SetIntHL(__int64 nNum, unsigned char* pData);


// 开辟和释放内存
char* vMalloc(__int64 nSize);
void vFree(char* pData);






