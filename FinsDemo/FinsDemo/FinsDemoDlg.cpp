
// FinsDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinsDemo.h"
#include "FinsDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFinsDemoDlg �Ի���




CFinsDemoDlg::CFinsDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFinsDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFinsDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editIP);
	DDX_Control(pDX, IDC_EDIT2, m_editPort);
	DDX_Control(pDX, IDC_EDIT3, m_editTimeout);
	DDX_Control(pDX, IDC_EDIT_READ_ADDR, m_editReadAddr);
	DDX_Control(pDX, IDC_EDIT_READ_DATA, m_editReadData);
	DDX_Control(pDX, IDC_EDIT_WRITE_ADDR, m_editWriteAddr);
	DDX_Control(pDX, IDC_EDIT_WRITE_DATA, m_editWriteData);
}

BEGIN_MESSAGE_MAP(CFinsDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SET_PARAM, OnBtnSetParam)
	ON_BN_CLICKED(IDC_BTN_READ_CHAR, OnBtnReadChar)
	ON_BN_CLICKED(IDC_BTN_READ_SHORT, OnBtnReadShort)
	ON_BN_CLICKED(IDC_BTN_READ_INT, OnBtnReadInt)
	ON_BN_CLICKED(IDC_BTN_WRITE_CHAR, OnBtnWriteChar)
	ON_BN_CLICKED(IDC_BTN_WRITE_SHORT, OnBtnWriteShort)
	ON_BN_CLICKED(IDC_BTN_WRITE_INT, OnBtnWriteInt)
	ON_BN_CLICKED(IDC_BTN_READ_COUNT, &CFinsDemoDlg::OnBnClickedBtnReadCount)
END_MESSAGE_MAP()


// CFinsDemoDlg ��Ϣ�������

BOOL CFinsDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_editIP.SetWindowText("192.168.1.50");
	m_editPort.SetWindowText("9600");
	m_editTimeout.SetWindowText("2000");
	m_editReadAddr.SetWindowText("DM102");
	m_editWriteAddr.SetWindowText("DM102");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFinsDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFinsDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFinsDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFinsDemoDlg::OnBtnSetParam()
{
	
	CString pIP;
	CString pPort;
	CString pTimeout;

	m_editIP.GetWindowText(pIP);
	m_editPort.GetWindowText(pPort);
	m_editTimeout.GetWindowText(pTimeout);
	
	m_pFins.SetIP((LPCSTR)pIP);
	m_pFins.SetPort(::atoi(pPort));
	m_pFins.SetTimeout(::atoi(pTimeout));
}




void CFinsDemoDlg::OnBtnReadChar()
{
	CString pAddr;
	m_editReadAddr.GetWindowText(pAddr);

	// ��ȡ����
	char nData;
	CResult rc = m_pFins.Read((LPCSTR)pAddr, nData);
	if (rc.nCode != 0)
	{
		CString pErr;
		pErr.Format("%d:%s", rc.nCode, rc.pText);
		MessageBox(pErr);
	}
	else
	{
		CString pData;
		pData.Format("%d", nData);
		m_editReadData.SetWindowText(pData);
	}	
}


void CFinsDemoDlg::OnBtnReadShort()
{
	CString pAddr;
	m_editReadAddr.GetWindowText(pAddr);

	// ��ȡ����
	__int16 nData;
	CResult rc = m_pFins.Read((LPCSTR)pAddr, nData);
	if (rc.nCode != 0)
	{
		CString pErr;
		pErr.Format("%d:%s", rc.nCode, rc.pText);
		MessageBox(pErr);
	}
	else
	{
		CString pData;
		pData.Format("%d", nData);
		m_editReadData.SetWindowText(pData);
	}		
}


void CFinsDemoDlg::OnBtnReadInt()
{
	CString pAddr;
	m_editReadAddr.GetWindowText(pAddr);

	// ��ȡ����
	__int32 nData;
	CResult rc = m_pFins.Read((LPCSTR)pAddr, nData);
	if (rc.nCode != 0)
	{
		CString pErr;
		pErr.Format("%d:%s", rc.nCode, rc.pText);
		MessageBox(pErr);
	}
	else
	{
		CString pData;
		pData.Format("%d", nData);
		m_editReadData.SetWindowText(pData);
	}		
}


void CFinsDemoDlg::OnBtnWriteChar()
{
	CString pAddr;
	CString pData;
	m_editWriteAddr.GetWindowText(pAddr);
	m_editWriteData.GetWindowText(pData);

	// ��ȡ����
	char nData = atoi(pData);
	CResult rc = m_pFins.Write((LPCSTR)pAddr, nData);
	if (rc.nCode != 0)
	{
		CString pErr;
		pErr.Format("%d:%s", rc.nCode, rc.pText);
		MessageBox(pErr);
	}
}


void CFinsDemoDlg::OnBtnWriteShort()
{
	CString pAddr;
	CString pData;
	m_editWriteAddr.GetWindowText(pAddr);
	m_editWriteData.GetWindowText(pData);

	// ��ȡ����
	__int16 nData = atoi(pData);
	CResult rc = m_pFins.Write((LPCSTR)pAddr, nData);
	if (rc.nCode != 0)
	{
		CString pErr;
		pErr.Format("%d:%s", rc.nCode, rc.pText);
		MessageBox(pErr);
	}
}


void CFinsDemoDlg::OnBtnWriteInt()
{
	CString pAddr;
	CString pData;
	m_editWriteAddr.GetWindowText(pAddr);
	m_editWriteData.GetWindowText(pData);

	// ��ȡ����
	__int32 nData = atoi(pData);
	CResult rc = m_pFins.Write((LPCSTR)pAddr, nData);
	if (rc.nCode != 0)
	{
		CString pErr;
		pErr.Format("%d:%s", rc.nCode, rc.pText);
		MessageBox(pErr);
	}
}




void CFinsDemoDlg::OnBnClickedBtnReadCount()
{
	SYSTEMTIME pBeginTime;
	SYSTEMTIME pEndTime;
	GetLocalTime(&pBeginTime);

	__int16 pData[100] = {0};
	for (int i = 0; i < 10000000; i++)
	{
		m_pFins.Read("DM10", pData, 100);
	}
	GetLocalTime(&pEndTime);
	
	CString pSubTime;
	pSubTime.Format("ʱ��Ϊ��ţ������%d, �������%d", pEndTime.wSecond - pBeginTime.wSecond, pEndTime.wMilliseconds - pBeginTime.wMilliseconds);
	MessageBox(pSubTime);
}











