#if !defined(AFX_MYSOCKET_H__7944C74E_5A38_4E88_97DF_FF38D1956065__INCLUDED_)
#define AFX_MYSOCKET_H__7944C74E_5A38_4E88_97DF_FF38D1956065__INCLUDED_

#include <afxsock.h>		// MFC socket extensions

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file

#include "resource.h"		// main symbols

class CDiODlg;
/////////////////////////////////////////////////////////////////////////////
// CMySocket command target

class CMySocket : public CAsyncSocket {
// Attributes
public:

// Operations
public:
	CMySocket();
	virtual ~CMySocket();

// Overrides
public:
	CDiODlg *m_pDiODlg;
	CString m_Status;
	bool    m_flgConnected;
	BYTE    m_IP_Address[4];
	UINT    m_IP_Port;
	char    m_Buffer[2000];

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
	void CreateMySocket();
	void Connecttt();
	void SaveINI();
	void Close();
protected:
	void GetLastError(char *Caption);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__7944C74E_5A38_4E88_97DF_FF38D1956065__INCLUDED_)
