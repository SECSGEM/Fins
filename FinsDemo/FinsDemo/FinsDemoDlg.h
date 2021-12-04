
// FinsDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "Input/Fins.h"
#include "afxwin.h"

// CFinsDemoDlg �Ի���
class CFinsDemoDlg : public CDialogEx
{
// ����
public:
	CFinsDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FINSDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CFins m_pFins;	// ŷķ��ͨѶ����

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
