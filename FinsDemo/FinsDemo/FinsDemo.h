
// FinsDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFinsDemoApp:
// �йش����ʵ�֣������ FinsDemo.cpp
//

class CFinsDemoApp : public CWinApp
{
public:
	CFinsDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFinsDemoApp theApp;