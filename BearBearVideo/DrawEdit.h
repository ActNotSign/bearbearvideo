#if !defined(AFX_DRAWEDIT_H__A28A6A91_8053_42CA_A3F7_3653B261C09C__INCLUDED_)
#define AFX_DRAWEDIT_H__A28A6A91_8053_42CA_A3F7_3653B261C09C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawEdit window

class CDrawEdit : public CEdit
{
// Construction
public:
	CDrawEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawEdit)
	afx_msg void OnNcPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWEDIT_H__A28A6A91_8053_42CA_A3F7_3653B261C09C__INCLUDED_)
