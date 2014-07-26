// beautifulcanlendaryearcombox.cpp : implementation file
//

#include "stdafx.h"
#include "..\BearBearVideo.h"
#include "beautifulcanlendaryearcombox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBeautifulCanlendarYearCombox

static WNDPROC m_pWndProc = 0; //���ڹ��ӹ�ȡCComboBox�������б�ĵ���¼�
static CBeautifulCanlendarYearCombox *m_pComboBox = 0; //���ڴ洢��ǰ�����ӹ�ס��
                                                       //����ĵ�ַ

CBeautifulCanlendarYearCombox::CBeautifulCanlendarYearCombox()
{
	m_isDec = 0;
	m_hListBox = NULL;
}

CBeautifulCanlendarYearCombox::~CBeautifulCanlendarYearCombox()
{
}


BEGIN_MESSAGE_MAP(CBeautifulCanlendarYearCombox, CComboBox)
	//{{AFX_MSG_MAP(CBeautifulCanlendarYearCombox)
	ON_WM_CANCELMODE()
	ON_CBN_SELENDOK(CBN_SELENDCANCEL, OnSelendcancel)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropDown)
	ON_MESSAGE(WM_CTLCOLORLISTBOX, OnCtlColorListBox)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelendok)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeautifulCanlendarYearCombox message handlers

void CBeautifulCanlendarYearCombox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	
	if (!IsWindowEnabled())
	{
        CBrush brDisabled(RGB(192,192,192)); // light gray
		CBrush* pOldBrush = pDC->SelectObject(&brDisabled);
		CPen penDisabled(PS_SOLID, 1, RGB(192,192,192));
        CPen* pOldPen = pDC->SelectObject(&penDisabled);

		
        //�����ǻ����ı��Ĳ���
		CRect textRect = lpDrawItemStruct->rcItem;
        textRect.left = textRect.left + 6;  
		

		CString strText;
	    if(lpDrawItemStruct->itemID != LB_ERR)
		{
		   GetLBText( lpDrawItemStruct->itemID,strText);
        }

		pDC->SetTextColor(RGB(160,160,160));
    
		CFont newFont,*oldFont;
		newFont.CreatePointFont(90,"����");
		oldFont = (CFont *)pDC->SelectObject(&newFont);
		pDC->DrawText(strText,&textRect,DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS);
		pDC->SelectObject(oldFont); 
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
		return;
	}


	CString strText;
	if(lpDrawItemStruct->itemID != LB_ERR)
	{
		   GetLBText( lpDrawItemStruct->itemID,strText);
    }


	if(strText == "-" || strText == "+")//����ı���- ���ʾҪ�������������İ�ť
	{
		 
		CBrush brHighlight(RGB(231,241,245)); 
		CBrush* pOldBrush = pDC->SelectObject(&brHighlight);
		CPen penHighlight(PS_SOLID, 1, RGB(107,141,162));
		CPen* pOldPen = pDC->SelectObject(&penHighlight);
		 
		CRect rcBackground;
        rcBackground.left = lpDrawItemStruct->rcItem.left + 2;
		rcBackground.right = lpDrawItemStruct->rcItem.right - 2;
		rcBackground.top = lpDrawItemStruct->rcItem.top + 2;
        rcBackground.bottom = lpDrawItemStruct->rcItem.bottom - 2;

	 	pDC->Rectangle(&rcBackground);
		pDC->SetBkMode(TRANSPARENT);
       	pDC->SetTextColor(RGB(255,0,0));
		
		//�����ǻ����ı��Ĳ���


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
		
		//�����ǻ����ı��Ĳ���
		CRect textRect = lpDrawItemStruct->rcItem;
        textRect.left = textRect.left + 6;  
		
		CString strText;
	    if(lpDrawItemStruct->itemID != LB_ERR)
		{
		   GetLBText( lpDrawItemStruct->itemID,strText);
        }
    
		CFont newFont,*oldFont;
		newFont.CreatePointFont(90,"����");
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

		//�����ǻ����ı��Ĳ���
		CRect textRect = lpDrawItemStruct->rcItem;
        textRect.left = textRect.left + 6;  
		
		CString strText;
	    if(lpDrawItemStruct->itemID != LB_ERR)
		{
		   GetLBText( lpDrawItemStruct->itemID,strText);
        }

		CFont newFont,*oldFont;
		newFont.CreatePointFont(90,"����");
		oldFont = (CFont *)pDC->SelectObject(&newFont);
		pDC->DrawText(strText,&textRect,DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS);
        pDC->SelectObject(oldFont);

		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}
	
}

BOOL CBeautifulCanlendarYearCombox::Create(DWORD dwStyle,const RECT &rect,CWnd *pParentWnd,UINT nID)
{
	return CComboBox::Create(dwStyle | CBS_OWNERDRAWFIXED | 
		                     CBS_HASSTRINGS, rect, 
							 pParentWnd, nID
							 );
}

void CBeautifulCanlendarYearCombox::MeasureItem(LPMEASUREITEMSTRUCT lpDrawItemStruct)
{

}

void CBeautifulCanlendarYearCombox::OnCancelMode() 
{
	CComboBox::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CBeautifulCanlendarYearCombox::OnSelendcancel() 
{
	
	
}


void CBeautifulCanlendarYearCombox::OnDropDown() 
{
	//���������ñ���ס�Ķ����Ա�Ȼṳ������Ϣ
	//��ΪCComboBox�ǵ���ȥ �ŵ����б�
	//�����������Ȼ�ȡ��Ҫ����List

	m_pComboBox = this;
	
}


/**
 * ����:
 *    ���ڴ��������б����Ϣ�Ļص�����.
 * ����:
 *    (��)
 * ����ֵ:
 *    (��)
 **/
extern "C" LRESULT FAR PASCAL ComboBoxListBoxProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{

	switch (nMsg) 
	{

		
		case WM_RBUTTONDOWN: 
		{
		

			break;
		}

		
		case LB_GETCURSEL: 
		{
			return m_pComboBox->GetCurSel();
			break;
		}


		case WM_CHAR: 
		{
			if (wParam == VK_SPACE) //����û����¿ո����δ���
			{
				INT nIndex = CallWindowProcA(m_pWndProc, hWnd, LB_GETCURSEL, wParam, lParam);

				CRect rcItem;
				SendMessage(hWnd, LB_GETITEMRECT, nIndex, (LONG)(VOID *)&rcItem);
				InvalidateRect(hWnd, rcItem, FALSE);
				 
				//m_pComboBox->SetCheck(nIndex, !m_pComboBox->GetCheck(nIndex));
			 
				m_pComboBox->GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetWindowLong(m_pComboBox->m_hWnd, GWL_ID), CBN_SELCHANGE), (LPARAM)m_pComboBox->m_hWnd);
				return 0;
			}

			break;
		}


		case WM_LBUTTONDOWN: 
		{

			CRect rcClient;
			GetClientRect(hWnd, rcClient);

			CPoint pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);


			if (PtInRect(rcClient, pt)) 
			{
				//��ȡһ�еĸ߶�
				INT nItemHeight = SendMessage(hWnd, LB_GETITEMHEIGHT, 0, 0);
                //��ȡ���������
				INT nTopIndex   = SendMessage(hWnd, LB_GETTOPINDEX, 0, 0);
                //�����ǰ����
				INT nIndex = nTopIndex + pt.y / nItemHeight;

				//��ȡ���еķ�Χ
				CRect rcItem;
				SendMessage(hWnd, LB_GETITEMRECT, nIndex, (LONG)(VOID *)&rcItem);
                
				CString strText;
                m_pComboBox->GetLBText(nIndex,strText);
				
				if(strText == "-")//������Ӧ�����Ϲ�����Ϣ
				{
					m_pComboBox->BeginRollBack();
					return 0;
				}

				if(strText == "+")
				{
                    m_pComboBox->BeginRollToFuture();
					return 0;
				}
                 
			}

			break;
		}

		case WM_LBUTTONUP: 
		{

			//���´��������ڽ�ֹ�˳����������˵���
			//һ��CComboBox�������б�ֻҪһ��ͻ�
			//��ʧ������������������Ϣ�����䲻��ʧ.
		    CRect rcClient;
			GetClientRect(hWnd, rcClient);

			CPoint pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);


			if (PtInRect(rcClient, pt)) 
			{
				//��ȡһ�еĸ߶�
				INT nItemHeight = SendMessage(hWnd, LB_GETITEMHEIGHT, 0, 0);
                //��ȡ���������
				INT nTopIndex   = SendMessage(hWnd, LB_GETTOPINDEX, 0, 0);
                //�����ǰ����
				INT nIndex = nTopIndex + pt.y / nItemHeight;

				//��ȡ���еķ�Χ
				CRect rcItem;
				SendMessage(hWnd, LB_GETITEMRECT, nIndex, (LONG)(VOID *)&rcItem);
                
				CString strText;
                m_pComboBox->GetLBText(nIndex,strText);
				if(strText == "-" || strText == "+")
				{
					m_pComboBox->StopRoll();
                    return 0;  
				}

				m_pComboBox->SetCurSel(nIndex);

				//DWORD year = atoi(strText);
             
				//m_pComboBox->GetParent()->SendMessage(UM_YEAR_SELCHANGE,year);
		
			}


			
		}
		
	}

	return CallWindowProc(m_pWndProc, hWnd, nMsg, wParam, lParam);
}


LRESULT CBeautifulCanlendarYearCombox::OnCtlColorListBox(WPARAM wParam, LPARAM lParam) 
{
	//����ÿؼ�����Ϣû�б���������m_hListBoxΪ��
	//�������Ϊ��������ؼ�����Ϣ��
	if (m_hListBox == NULL) 
	{
		HWND hWnd = (HWND)lParam;

		if (hWnd != 0 && hWnd != m_hWnd) {
			
			m_hListBox = hWnd;//����ÿؼ��ľ���������������ʾ�Ѿ�������

			//��ʼ�޸�����ؼ�����Ϣ�ص�Ϊ�Լ��ĺ���
			m_pWndProc = (WNDPROC)GetWindowLong(m_hListBox, GWL_WNDPROC);
			SetWindowLong(m_hListBox, GWL_WNDPROC, (LONG)ComboBoxListBoxProc);
		}
	}

	
	return DefWindowProc(WM_CTLCOLORLISTBOX, wParam, lParam);
}

void CBeautifulCanlendarYearCombox::OnTimer(UINT nIDEvent) 
{

	if(m_isDec == 0)
	{
		KillTimer(201);
		return;
	}

	if(m_isDec == 1)
	{
        CString strText;
		m_pComboBox->GetLBText(1,strText);
		int year = atoi(strText);
		if(year <= 1970)
		{
			return ;
		}

		for(int i = 0; i < 6; i++)
		{
			CString strText;
			m_pComboBox->GetLBText(i+1,strText);
            m_pComboBox->DeleteString(i+1); 
			int year = atoi(strText);
			year = year - 1;
			strText.Format("%d",year);
            m_pComboBox->InsertString(i+1,strText);
			
		}
	}

	if(m_isDec == -1)
	{
		CString strText;
		m_pComboBox->GetLBText(6,strText);
		int year = atoi(strText);
		if(year >= 2037)
		{
			return ;
		}

		for(int i = 0; i < 6; i++)
		{
			CString strText;
			m_pComboBox->GetLBText(i+1,strText);
            m_pComboBox->DeleteString(i+1); 
			int year = atoi(strText);
			year = year + 1;
			strText.Format("%d",year);
            m_pComboBox->InsertString(i+1,strText);
			
		}

	}
	
	CComboBox::OnTimer(nIDEvent);
}

void CBeautifulCanlendarYearCombox::BeginRollBack()
{
	m_isDec = 1;
    SetTimer(201,1,NULL);
}

void CBeautifulCanlendarYearCombox::BeginRollToFuture()
{
    m_isDec = -1;
    SetTimer(201,1,NULL);
}

void CBeautifulCanlendarYearCombox::StopRoll()
{
    m_isDec = 0;
}

int CBeautifulCanlendarYearCombox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	CRect clientRect;
//	GetClientRect(&clientRect);
   // m_FlatEdit.Create(WS_CHILD|WS_VISIBLE, CRect(5,5,clientRect.Width()-22,clientRect.Height()-2),this,200);
	//m_FlatEdit.SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	return 0;
}

void CBeautifulCanlendarYearCombox::OnSelendok() 
{
	 
	
}

int CBeautifulCanlendarYearCombox::SetCurSel(int cursel)
{
    m_CurSel = cursel;
	return CComboBox::SetCurSel(cursel);
}

int CBeautifulCanlendarYearCombox::GetCurSel()
{
    return m_CurSel;
}
