// ShowWindow.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "ShowWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowWindow dialog


CShowWindow::CShowWindow(CWnd* pParent /*=NULL*/)
	: CDarwDialog(CShowWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowWindow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_b=NULL;
}


void CShowWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowWindow)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowWindow, CDarwDialog)
	//{{AFX_MSG_MAP(CShowWindow)
	ON_WM_CREATE()
	ON_WM_NCCALCSIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowWindow message handlers

void CShowWindow::OnOK() 
{

	
//	CDialog::OnOK();WS_THICKFRAME 
}

void CShowWindow::OnCancel() 
{
	
	CDialog::OnCancel();
}



int CShowWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	DWORD dwStyle   =  GetWindowLong(m_hWnd,GWL_STYLE);   
	SetWindowLong(m_hWnd,GWL_STYLE,dwStyle|WS_THICKFRAME );   
	
	if (CDarwDialog::OnCreate(lpCreateStruct) == -1)
		return -1;



	return 0;
}



void CShowWindow::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	lpncsp->rgrc ->left -=2;
	lpncsp->rgrc ->right +=1;

	CDarwDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CShowWindow::DrawPic(HBITMAP bit)
{
	//获取图片信息


/**/CDC *pDC;
	pDC=GetDC ();
	CDC memoryDC;
	CBitmap newBitmap,*oldBitmap;
	memoryDC.CreateCompatibleDC (pDC);
//加载位图

//	newBitmap.CreateCompatibleBitmap (pDC,bitinfo.bmWidth  ,bitinfo.bmHeight  );
	oldBitmap=newBitmap.FromHandle (bit );
	oldBitmap=(CBitmap *)memoryDC.SelectObject (oldBitmap);

	CRect r;
	GetWindowRect(&r);
	pDC->StretchBlt (0,5,r.Width (),r.Height (),
		&memoryDC,0,0,r.Width (),r.Height() ,SRCCOPY);
//清除内存
	memoryDC.SelectObject (oldBitmap);
	oldBitmap->DeleteObject ();
	newBitmap.DeleteObject ();
	memoryDC.DeleteDC ();
	pDC->DeleteDC ();

	m_b=bit;
//	DeleteObject(bit);
}



void CShowWindow::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	DrawPic(m_b);		
	// Do not call CDarwDialog::OnPaint() for painting messages
}







