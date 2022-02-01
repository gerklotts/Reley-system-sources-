// ListeningSocket.cpp : implementation file
//

#include "stdafx.h"
#include "srv.h"
#include "tSrvDlg.h"
#include "ListeningSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CTSrvDlg *pTSrvDlg;

/////////////////////////////////////////////////////////////////////////////
// CListeningSocket

CListeningSocket::CListeningSocket() {
	m_IP_Port = 22022;
}

CListeningSocket::~CListeningSocket() {
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListeningSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CListeningSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListeningSocket member functions

void CListeningSocket::GetLastError(char *Caption) {
	char String[200];
	strcpy(String, Caption); strcat(String, "\n\r");
	int LastError = CAsyncSocket::GetLastError();
	if( 	LastError == WSANOTINITIALISED)  strcat(String, "A successful AfxSocketInit must occur before using this API.");
	else if(LastError == WSAEINPROGRESS)	 strcat(String, "A blocking Windows Sockets operation is in progress.");
	else if(LastError == WSAEDESTADDRREQ)	 strcat(String, "A destination address is required.");
	else if(LastError == WSAEADDRINUSE) 	 strcat(String, "An attempt has been made to listen on an address in use.");
	else if(LastError == WSAEAFNOSUPPORT)	 strcat(String, "Addresses in the specified family cannot be used with this socket.");
	else if(LastError == WSAETIMEDOUT)		 strcat(String, "Attempt to connect timed out without establishing a connection.");
	else if(LastError == WSAENOTSOCK)		 strcat(String, "The descriptor is not a socket.");
	else if(LastError == WSAEOPNOTSUPP) 	 strcat(String, "The referenced socket is not of a type that supports the Listen operation.");
	else if(LastError == WSAEPROTONOSUPPORT) strcat(String, "The specified port is not supported.");
	else if(LastError == WSAEPROTOTYPE) 	 strcat(String, "The specified port is the wrong type for this socket.");
	else if(LastError == WSAEADDRINUSE) 	 strcat(String, "The specified address is already in use.");
	else if(LastError == WSAEADDRNOTAVAIL)	 strcat(String, "The specified address is not available from the local machine.");
	else if(LastError == WSAEAFNOSUPPORT)	 strcat(String, "The specified address family is not supported.");
	else if(LastError == WSAESOCKTNOSUPPORT) strcat(String, "The specified socket type is not supported in this address family.");
	else if(LastError == WSAENETDOWN)		 strcat(String, "The Windows Sockets implementation detected that the network subsystem failed.");
	else if(LastError == WSAEINVAL) 		 strcat(String, "The socket has not been bound with Bind or is already connected.");
	else if(LastError == WSAEISCONN)		 strcat(String, "The socket is already connected.");
	else if(LastError == WSAEWOULDBLOCK)	 strcat(String, "The socket is marked as nonblocking and the connection cannot be completed immediately.");
	else if(LastError == WSAECONNREFUSED)	 strcat(String, "The attempt to connect was rejected.");
	else if(LastError == WSAEFAULT) 		 strcat(String, "The nSockAddrLen argument is incorrect.");
	else if(LastError == WSAENETUNREACH)	 strcat(String, "The network cannot be reached from this host at this time.");
	else if(LastError == WSAEMFILE) 		 strcat(String, "No more file descriptors are available.");
	else if(LastError == WSAENOBUFS)		 strcat(String, "No buffer space is available. The socket cannot be created.");
	else if(LastError == WSAEMFILE) 		 strcat(String, "No more file descriptors are available.");
	else if(LastError == WSAEINVAL) 		 strcat(String, "Invalid host address.");
	else									 strcat(String, "Unknown ERROR");
	AfxMessageBox(String, MB_OK);
}

void CListeningSocket::OnAccept(int nErrorCode) {
	CAsyncSocket::OnAccept(nErrorCode);
	pTSrvDlg->OnAccept();
}

void CListeningSocket::Create() {
	if(!CAsyncSocket::Create(m_IP_Port))
		GetLastError("Listening Socket");
}

/////////////////////////////////////////////////////////////////////////////
// CServIP_PortDlg dialog

CServIP_PortDlg::CServIP_PortDlg(CWnd* pParent /*=NULL*/) : CDialog(CServIP_PortDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CServIP_PortDlg)
	//}}AFX_DATA_INIT
}

void CServIP_PortDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServIP_PortDlg)
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDV_MinMaxDWord(pDX, m_Port, 1025, 65535);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServIP_PortDlg, CDialog)
	//{{AFX_MSG_MAP(CServIP_PortDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServIP_PortDlg message handlers
