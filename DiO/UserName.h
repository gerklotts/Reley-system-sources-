#if !defined(AFX_USERNAME_H__BC10BABD_6B3C_4052_97A4_0A81C27BA994__INCLUDED_)
#define AFX_UserNAME_H__BC10BABD_6B3C_4052_97A4_0A81C27BA994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserName.h : header file
//

#define START_USER_NAME ("&User Name")

/////////////////////////////////////////////////////////////////////////////
// CUserName dialog

class CUserName : public CDialog {
// Construction
public:
	CUserName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserName)
	enum { IDD = IDD_USER_NAME };
	CString	m_UserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserName)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERNAME_H__BC10BABD_6B3C_4052_97A4_0A81C27BA994__INCLUDED_)
