#if !defined(AFX_AD_H__E59CA1EB_BF38_4A44_98A0_F42454DED128__INCLUDED_)
#define AFX_AD_H__E59CA1EB_BF38_4A44_98A0_F42454DED128__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAD dialog
#include "StaticHttp.h"

class CAD : public CDialog
{
// Construction
public:
	void DrawDialog();
	CAD(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CAD)
	enum { IDD = IDD_OLE_PROPPAGE_SMALL };
	CStaticHttp	m_qq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAD)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AD_H__E59CA1EB_BF38_4A44_98A0_F42454DED128__INCLUDED_)
