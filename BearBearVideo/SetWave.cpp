// SetWave.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "SetWave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetWave property page

IMPLEMENT_DYNCREATE(CSetWave, CPropertyPage)

LONG CALLBACK WaveIOProc(LPMMIOINFO lpmmioInfo, UINT uMsg, 
                         LPARAM lParam1, LPARAM lParam2);

CSetWave::CSetWave() : CPropertyPage(CSetWave::IDD)
{
	//{{AFX_DATA_INIT(CSetWave)
	m_wSize = -1;
	m_cl = -1;
	//}}AFX_DATA_INIT
}

CSetWave::~CSetWave()
{
}

void CSetWave::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetWave)
	DDX_Control(pDX, IDC_SLIDER1, m_volumeSize);
	DDX_Radio(pDX, IDC_WEISHU_8, m_wSize);
	DDX_Radio(pDX, IDC_CI_8000, m_cl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetWave, CPropertyPage)
	//{{AFX_MSG_MAP(CSetWave)
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetWave message handlers

void CSetWave::DrawDialog()
{
	CDC *pDC=GetWindowDC();
	CBrush brush;
	CRect winRect;
	GetWindowRect(&winRect);
	CRect rect;	
	brush.CreateSolidBrush (RGB(94,179,227));
//底线
	rect.left =0;
	rect.right =winRect.Width  ();
	rect.top =winRect.Height ()-1;
	rect.bottom =winRect.Height ();


	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();
//上线
	rect.left =0;
	rect.right =winRect.Width  ();
	rect.top =0;
	rect.bottom =1;

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();


//left线
	rect.left =0;
	rect.right =1;
	rect.top =0;
	rect.bottom =winRect.Height ();

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();

//right线
	rect.left =winRect.Width ()-1;
	rect.right =winRect.Width(),
	rect.top =0;
	rect.bottom =winRect.Height ();

	pDC->FillRect (&rect,&brush);
	pDC->DeleteDC ();

	brush.DeleteObject ();	
}

HBRUSH CSetWave::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = ::CreateSolidBrush (RGB(243,245,247));
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor(RGB(22,76,121));	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

LRESULT CSetWave::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT callBack = CDialog::DefWindowProc(message, wParam, lParam);
	if(!::IsWindow(m_hWnd))
    {
       return callBack ;
    }	
   if(message == WM_PAINT || message == WM_NCACTIVATE || message == WM_NOTIFY)
	{   
           DrawDialog();
    }	
	return callBack;
}








BOOL CSetWave::OnInitDialog() 
{	


	CPropertyPage::OnInitDialog();
	//初始化选中
	((CButton*)GetDlgItem(IDC_WEISHU_16))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CI_11025))->SetCheck(1);

	//声音控制
	m_volumeSize.SetRange(0,200);
	m_volumeSize.SetPos (100);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CSetWave::GetSampsize()
{
	//获取位
	UpdateData ();
	if(m_wSize==0)
	{
		return 8;
	}else
		if(m_wSize==1)
	{
		return 16;
	}

	return 1;
}

int CSetWave::GetFreq()
{
	//获取Hz
	UpdateData ();
	switch (m_cl)
	{
	case 0:
		return 8000;
	case 1:
		return 11025;
	case 2:
		return 22050;
	case 3:
		return 44100;
	}
	return 1;
}

void CSetWave::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	DWORD pos;
	int scrollpos;
	scrollpos=m_volumeSize.GetPos ();
	if(scrollpos<100)
	{
		::waveOutGetVolume (0,&pos);
		pos=pos & 0x0000ffff | ((scrollpos+50) << 8); 
		::waveOutSetVolume (0,pos);
	}

	if(scrollpos>100)
	{
		::waveOutGetVolume (0,&pos);
		pos=pos & 0xffff0000 | ((scrollpos-50) << 24); 
		::waveOutSetVolume (0,pos);
	}
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
