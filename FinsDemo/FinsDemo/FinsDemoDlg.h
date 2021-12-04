
// FinsDemoDlg.h : 头文件
//

#pragma once
#include "Input/Fins.h"
#include "afxwin.h"

// CFinsDemoDlg 对话框
class CFinsDemoDlg : public CDialogEx
{
// 构造
public:
	CFinsDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FINSDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnSetParam();
	afx_msg void OnBtnReadChar();
	afx_msg void OnBtnReadShort();
	afx_msg void OnBtnReadInt();
	afx_msg void OnBtnWriteChar();
	afx_msg void OnBtnWriteShort();
	afx_msg void OnBtnWriteInt();

private:
	CFins m_pFins;	// 欧姆龙通讯对象

	CEdit m_editIP;
	CEdit m_editPort;
	CEdit m_editTimeout;
	CEdit m_editReadAddr;
	CEdit m_editReadData;
	CEdit m_editWriteAddr;
	CEdit m_editWriteData;

public:
	afx_msg void OnBnClickedBtnReadCount();
};
