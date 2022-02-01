#if !defined(AFX_SERVSOCKET_H__1DD1024B_FDC7_4311_997B_395A5C8E1A37__INCLUDED_)
#define AFX_SERVSOCKET_H__1DD1024B_FDC7_4311_997B_395A5C8E1A37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServSocket.h : header file
//

#define SERV_BUFFER_LENGHT 4000
/////////////////////////////////////////////////////////////////////////////
// CServSocket command target

class CServSocket : public CAsyncSocket {
// Attributes
public:
	CString	m_UserIP;
	char m_Buffer[SERV_BUFFER_LENGHT];
	bool m_Accepted;

// Operations
public:
	CServSocket();
	virtual ~CServSocket();

// Overrides
public:
	void GetLastError(char *Caption);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL
	// Generated message map functions
	//{{AFX_MSG(CServSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVSOCKET_H__1DD1024B_FDC7_4311_997B_395A5C8E1A37__INCLUDED_)
