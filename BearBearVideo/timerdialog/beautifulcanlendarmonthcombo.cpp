// beautifulcanlendarmonthcombo.cpp : implementation file
//

#include "stdafx.h"
#include "..\BearBearVideo.h"
#include "beautifulcanlendarmonthcombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBeautifulCanlendarMonthCombo

CBeautifulCanlendarMonthCombo::CBeautifulCanlendarMonthCombo()
{
	
}

CBeautifulCanlendarMonthCombo::~CBeautifulCanlendarMonthCombo()
{

	
}



BEGIN_MESSAGE_MAP(CBeautifulCanlendarMonthCombo, CComboBox)
	//{{AFX_MSG_MAP(CBeautifulCanlendarMonthCombo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeautifulCanlendarMonthCombo message handlers

void CBeautifulCanlendarMonthCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	
	if (!IsWindowEnabled())
	{
        CBrush brDisabled(RGB(192,192,192)); // light gray
		CBrush* pOldBrush = pDC->SelectObject(&brDisabled);
		CPen penDisabled(PS_SOLID, 1, RGB(192,192,192));
        CPen* pOldPen = pDC->SelectObject(&penDisabled);

		
        //以下是绘制文本的部分
		CRect textRect = lpDrawItemStruct->rcItem;
        textRect.left = textRect.left + 6;  
		
		CString strText;
	    if(lpDrawItemStruct->itemID != LB_ERR)
		{
		   GetLBText( lpDrawItemStruct->itemID,strText);
        }

		pDC->SetTextColor(RGB(160,160,160));
    
		CFont newFont,*oldFont;
		newFont.CreatePointFont(85,"宋体");
		oldFont = (CFont *)pDC->SelectObject(&newFont);
		pDC->DrawText(strText,&textRect,DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS);
		pDC->SelectObject(oldFont); 
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
		return;
	}

	// Selected
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) 
		&& (lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE))) 
	{
		CBrush brHighlight(RGB(231,241,245)); 
		CBrush* pOldBrush = pDC->SelectObject(&brHighlight);
		CPen penHighlight(PS_SOLID, 1, RGB(107,141,162));
		CPen* pOldPen = pDC->SelectObject(&penHighlight);
		 
	 	pDC->Rectangle(&lpDrawItemStruct->rcItem);
		pDC->SetBkMode(TRANSPARENT);
       	pDC->SetTextColor(RGB(255,0,0));
		
		//以下是绘制文本的部分
		CRect textRect = lpDrawItemStruct->rcItem;
        textRect.left = textRect.left + 6;  
		
		CString strText;
	    if(lpDrawItemStruct->itemID != LB_ERR)
		{
		   GetLBText( lpDrawItemStruct->itemID,strText);
        }
    
		CFont newFont,*oldFont;
		newFont.CreatePointFont(85,"宋体");
		oldFont = (CFont *)pDC->SelectObject(&newFont);
		pDC->DrawText(strText,&textRect,DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS);
        pDC->SelectObject(oldFont);
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}

	// De-Selected
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) 
		&& (lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE))) 
	{
		CBrush brWindow(::GetSysColor(COLOR_WINDOW)); 
		CBrush* pOldBrush = pDC->SelectObject(&brWindow);
		CPen penHighlight(PS_SOLID, 1, ::GetSysColor(COLOR_WINDOW));
		CPen* pOldPen = pDC->SelectObject(&penHighlight);
		pDC->Rectangle(&lpDrawItemStruct->rcItem);
		pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
       	pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));

		//以下是绘制文本的部分
		CRect textRect = lpDrawItemStruct->rcItem;
        textRect.left = textRect.left + 6;  
		
		CString strText;
	    if(lpDrawItemStruct->itemID != LB_ERR)
		{
		   GetLBText( lpDrawItemStruct->itemID,strText);
        }
    
		CFont newFont,*oldFont;
		newFont.CreatePointFont(85,"宋体");
		oldFont = (CFont *)pDC->SelectObject(&newFont);
		pDC->DrawText(strText,&textRect,DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS);
        pDC->SelectObject(oldFont);

		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}

	
}


void CBeautifulCanlendarMonthCombo::MeasureItem(LPMEASUREITEMSTRUCT lpDrawItemStruct)
{

}

BOOL CBeautifulCanlendarMonthCombo::Create(DWORD dwStyle,const RECT &rect,CWnd *pParentWnd,UINT nID)
{
	return CComboBox::Create(dwStyle | CBS_OWNERDRAWVARIABLE | 
		                     CBS_HASSTRINGS, rect, 
							 pParentWnd, nID
							 );
}