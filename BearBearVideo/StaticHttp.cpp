// StaticHttp.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "StaticHttp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticHttp

CStaticHttp::CStaticHttp()
{
	m_big=FALSE;
}

CStaticHttp::~CStaticHttp()
{
}


BEGIN_MESSAGE_MAP(CStaticHttp, CStatic)
	//{{AFX_MSG_MAP(CStaticHttp)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticHttp message handlers

void CStaticHttp::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CString str,s;
	s="403275198";
	str.Format ( "Tencent://Message/?menu=no&exe=qq&uin=%s&websiteName=??&info=",s);

	ShellExecute(GetSafeHwnd(),   NULL,   
			str,   NULL,   NULL,   SW_SHOWNORMAL);


	CStatic::OnLButtonDown(nFlags, point);
}








void CStaticHttp::OnMouseMove(UINT nFlags, CPoint point) 
{


	::SetCursor(AfxGetApp() ->LoadCursor(IDC_HAND));//
	CStatic::OnMouseMove(nFlags, point);
}

void CStaticHttp::OnTimer(UINT nIDEvent) 
{
	if(m_big)
	{
		CFont font;
		font.CreatePointFont (110,"ËÎÌו");
		
		SetFont(&font);
		font.DeleteObject ();

		m_big=FALSE;
	}
	else
	{

		CFont font;
		font.CreatePointFont (90,"ËÎÌו");
		SetFont(&font);
		font.DeleteObject ();
		m_big=TRUE;
	}
	CStatic::OnTimer(nIDEvent);
}








void CStaticHttp::Dong()
{
	SetTimer(1,1000,NULL);
}
