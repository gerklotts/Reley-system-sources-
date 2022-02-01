#if !defined(AFX_LISTENINGSOCKET_H__88722063_F749_46AC_B12B_BEDF9CF454E9__INCLUDED_)
#define AFX_LISTENINGSOCKET_H__88722063_F749_46AC_B12B_BEDF9CF454E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListeningSocket.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListeningSocket command target

class CListeningSocket : public CAsyncSocket {
// Attributes
public:
	DWORD m_IP_Port;

// Operations
public:
	CListeningSocket();
	virtual ~CListeningSocket();
	void Create();

// Overrides
public:
	void GetLastError(char *Caption);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListeningSocket)
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListeningSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////
// CServIP_PortDlg dialog

class CServIP_PortDlg : public CDialog {
// Construction
public:
	CServIP_PortDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CServIP_PortDlg)
	enum { IDD = IDD_SERV_IP_PORT_DLG };
	DWORD	m_Port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServIP_PortDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServIP_PortDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENINGSOCKET_H__88722063_F749_46AC_B12B_BEDF9CF454E9__INCLUDED_)
