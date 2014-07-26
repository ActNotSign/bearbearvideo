// DrawTab.cpp : implementation file
//

#include "stdafx.h"
#include "BearBearVideo.h"
#include "DrawTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawTab property page

IMPLEMENT_DYNCREATE(CDrawTab, CPropertyPage)

CDrawTab::CDrawTab() : CPropertyPage(CDrawTab::IDD)
{
	//{{AFX_DATA_INIT(CDrawTab)
	//}}AFX_DATA_INIT
}

CDrawTab::~CDrawTab()
{
}

void CDrawTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawTab)
	DDX_Control(pDX, IDC_WAVE, m_wave);
	DDX_Control(pDX, IDC_SOFT, m_soft);
	DDX_Control(pDX, IDC_TIMERS, m_timer);
	DDX_Control(pDX, IDC_AD, m_ad);
	DDX_Control(pDX, IDC_LZ, m_lz);
	DDX_Control(pDX, IDC_SET, m_set);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDrawTab, CPropertyPage)
	//{{AFX_MSG_MAP(CDrawTab)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_LZ, OnLz)
	ON_BN_CLICKED(IDC_WAVE, OnWave)
	ON_BN_CLICKED(IDC_TIMERS, OnTimers)
	ON_BN_CLICKED(IDC_SOFT, OnSoft)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_AD, OnAd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawTab message handlers

HBRUSH CDrawTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = ::CreateSolidBrush (RGB(22,76,121));
	
	// TODO: Return a different brush if the default is not desired
	
	return hbr;
	// TODO: Return a different brush if the default is not desired

}


void CDrawTab::OnSet() 
{
	m_iwho=1;
	ShowDialog();
}

void CDrawTab::OnLz() 
{
	m_iwho=2;
	ShowDialog();
}

void CDrawTab::OnWave() 
{
	m_iwho=3;
	ShowDialog();
}

void CDrawTab::OnTimers() 
{
	m_iwho=4;
	ShowDialog();
}
void CDrawTab::OnSoft() 
{
	m_iwho=5;
	ShowDialog();

}

void CDrawTab::OnAd() 
{
	m_iwho=6;
	ShowDialog();	
}

BOOL CDrawTab::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	SetDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDrawTab::SetDialog()
{

	/**/
	m_dset.Create (IDD_OLE_PROPPAGE_SET);
	//获取矩形的大小，因为所有属性页都是一样大的。所以取一个代表，这里取得是m_dset;
	m_dset.GetWindowRect  (&r);
	//初始化第一个页面
	m_set.EnableWindow (FALSE);
	m_dset.MoveWindow (1,30,r.Width (),r.Height ());
	m_dset.ShowWindow (SW_SHOW);
//录制
	m_dlz.Create (IDD_OLE_PROPPAGE_MB);
	m_dlz.MoveWindow (1,30,0,0);
	m_dlz.ShowWindow (SW_SHOW);
//声音
	m_dwav.Create (IDD_OLE_PROPPAGE_WAVA);
	m_dwav.MoveWindow (1,30,0,0);
	m_dwav.ShowWindow (SW_SHOW);
//定时器
	m_dtimer.Create (IDD_OLE_PROPPAGE_TIMER);
	m_dtimer.MoveWindow (1,30,0,0);
	m_dtimer.ShowWindow (SW_SHOW);
//辅助软件
	m_dSoft.Create (IDD_OLE_PROPPAGE_SOFT);
	m_dSoft.MoveWindow (1,30,0,0);
	m_dSoft.ShowWindow (SW_SHOW);
//关于
	m_dad.Create (IDD_OLE_PROPPAGE_SMALL);
	m_dad.MoveWindow (1,30,0,0);
	m_dad.ShowWindow (SW_SHOW);

}

void CDrawTab::ShowDialog()
{

	switch (m_iwho)
	{
	case 1:
		m_set.EnableWindow (FALSE);
		m_lz.EnableWindow ();
		m_wave.EnableWindow ();
		m_timer.EnableWindow ();
		m_soft.EnableWindow ();
		m_ad.EnableWindow ();

		m_dset.MoveWindow (1,30,r.Width (),r.Height ());
		m_dlz.MoveWindow (1,30,0,0);
		m_dwav.MoveWindow (1,30,0,0);
		m_dtimer.MoveWindow (1,30,0,0);
		m_dSoft.MoveWindow (1,30,0,0);
		m_dad.MoveWindow (1,30,0,0);


		break;
	case 2:
		m_lz.EnableWindow (FALSE);
		m_set.EnableWindow ();
		m_wave.EnableWindow ();
		m_soft.EnableWindow ();
		m_ad.EnableWindow ();

		m_dlz.MoveWindow (1,30,r.Width (),r.Height ());
		m_dset.MoveWindow (1,30,0,0);
		m_dwav.MoveWindow (1,30,0,0);
		m_dtimer.MoveWindow (1,30,0,0);
		m_timer.EnableWindow ();
		m_dSoft.MoveWindow (1,30,0,0);
		m_dad.MoveWindow (1,30,0,0);

		break;
	case 3:
		m_wave.EnableWindow (FALSE);
		m_set.EnableWindow ();
		m_lz.EnableWindow ();
		m_timer.EnableWindow ();
		m_soft.EnableWindow ();
		m_ad.EnableWindow ();

		m_dwav.MoveWindow (1,30,r.Width (),r.Height ());
		m_dset.MoveWindow (1,30,0,0);
		m_dlz.MoveWindow (1,30,0,0);
		m_dtimer.MoveWindow (1,30,0,0);
		m_dSoft.MoveWindow (1,30,0,0);
		m_dad.MoveWindow (1,30,0,0);

		break;
	case 4:
		m_timer.EnableWindow (FALSE);
		m_set.EnableWindow ();
		m_lz.EnableWindow ();
		m_wave.EnableWindow ();
		m_soft.EnableWindow ();
		m_ad.EnableWindow ();

		m_dtimer.MoveWindow (1,30,r.Width (),r.Height ());
		m_dset.MoveWindow (1,30,0,0);
		m_dlz.MoveWindow (1,30,0,0);
		m_dwav.MoveWindow (1,30,0,0);
		m_dSoft.MoveWindow (1,30,0,0);
		m_dad.MoveWindow (1,30,0,0);


		break;
	case 5:
		m_soft.EnableWindow (FALSE);
		m_timer.EnableWindow ();
		m_set.EnableWindow ();
		m_lz.EnableWindow ();
		m_wave.EnableWindow ();
		m_ad.EnableWindow ();


		m_dSoft.MoveWindow (1,30,r.Width (),r.Height ());
		m_dset.MoveWindow (1,30,0,0);
		m_dlz.MoveWindow (1,30,0,0);
		m_dwav.MoveWindow (1,30,0,0);
		m_dtimer.MoveWindow (1,30,0,0);
		m_dad.MoveWindow (1,30,0,0);

		break;
	case 6:
		m_ad.EnableWindow (FALSE);
		m_timer.EnableWindow ();
		m_set.EnableWindow ();
		m_lz.EnableWindow ();
		m_wave.EnableWindow ();
		m_soft.EnableWindow ();

		m_dad.MoveWindow (1,30,r.Width (),r.Height ());
		m_dset.MoveWindow (1,30,0,0);
		m_dlz.MoveWindow (1,30,0,0);
		m_dwav.MoveWindow (1,30,0,0);
		m_dtimer.MoveWindow (1,30,0,0);
		m_dSoft.MoveWindow (1,30,0,0);


		break;
	}
}






