// DrawEdit.cpp : implementation file
//

#include "stdafx.h"
#include "BearBearVideo.h"
#include "DrawEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawEdit

CDrawEdit::CDrawEdit()
{
}

CDrawEdit::~CDrawEdit()
{
}


BEGIN_MESSAGE_MAP(CDrawEdit, CEdit)
	//{{AFX_MSG_MAP(CDrawEdit)
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawEdit message handlers



void CDrawEdit::OnNcPaint() 
{

	CDC *pDC=GetWindowDC();
	CBrush brush;
	CRect winRect;
	GetWindowRect(&winRect);
	CRect rect;
//����
	rect.left =0;
	rect.right =winRect.Width  ();
	rect.top =winRect.Height ()-1;
	rect.bottom =winRect.Height ();
	brush.CreateSolidBrush (RGB(94,179,227));

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();
//����
	rect.left =0;
	rect.right =winRect.Width  ();
	rect.top =0;
	rect.bottom =1;
	brush.CreateSolidBrush (RGB(94,179,227));

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();


//left��
	rect.left =0;
	rect.right =1;
	rect.top =0;
	rect.bottom =winRect.Height ();
	brush.CreateSolidBrush (RGB(94,179,227));

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();

//right��
	rect.left =winRect.Width ()-1;
	rect.right =winRect.Width(),
	rect.top =0;
	rect.bottom =winRect.Height ();
	brush.CreateSolidBrush (RGB(94,179,227));

	pDC->FillRect (&rect,&brush);
	pDC->DeleteDC ();

	brush.DeleteObject ();	
}
