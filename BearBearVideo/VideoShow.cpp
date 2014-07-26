// VideoShow.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "VideoShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoShow dialog



CVideoShow::CVideoShow(CWnd* pParent /*=NULL*/)
	: CDarwDialog(CVideoShow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoShow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_Captured=FALSE;
	isW=FALSE;
}


void CVideoShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoShow)
	DDX_Control(pDX, IDC_PANEL, m_panel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoShow, CDarwDialog)
	//{{AFX_MSG_MAP(CVideoShow)
	ON_WM_CREATE()
	ON_WM_NCCALCSIZE()
//	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoShow message handlers

void CVideoShow::OnOK() 
{

}



BOOL CVideoShow::OnInitDialog() 
{
	CDarwDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//创建预览窗口
	m_hWndVideo = capCreateCaptureWindow(NULL,WS_POPUP,1,1,10,10,m_hWnd,0);

	//连接驱动程序
	if (capDriverConnect(m_hWndVideo,0))
	{	
		::SetParent(m_hWndVideo,*this);
		::SetWindowLong(m_hWndVideo,GWL_STYLE,WS_CHILD);

		CRect wndRC;
		m_panel.GetClientRect(wndRC);
		m_panel.MapWindowPoints(this,wndRC);
		wndRC.DeflateRect(1,1,1,1);

		::SetWindowPos(m_hWndVideo,NULL,wndRC.left,wndRC.top,wndRC.Width(),wndRC.Height(),SWP_NOZORDER);
		::ShowWindow(m_hWndVideo,SW_SHOW);


	}	else
	{
		MessageBox("没有找到摄像头驱动");
		OnCancel ();
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVideoShow::OnCancel ()
{
	capDriverDisconnect(m_hWndVideo);
	::AfxGetMainWnd ()->ShowWindow (SW_SHOW);
	CDarwDialog::OnCancel ();
}




int CVideoShow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	DWORD dwStyle   =  GetWindowLong(m_hWnd,GWL_STYLE);   
	SetWindowLong(m_hWnd,GWL_STYLE,dwStyle|WS_THICKFRAME );   
	
	if (CDarwDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	return 0;
}



void CVideoShow::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	lpncsp->rgrc ->left -=2;
	lpncsp->rgrc ->right +=1;
	
	CDarwDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}





HWND CVideoShow::GethWnd()
{
	return m_hWndVideo;
}
