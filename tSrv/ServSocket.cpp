// ServSocket.cpp : implementation file

#include "stdafx.h"
#include "srv.h"
#include "tSrvDlg.h"
#include "ServSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CTSrvDlg *pTSrvDlg;

/////////////////////////////////////////////////////////////////////////////
// CServSocket

CServSocket::CServSocket() {
	m_Accepted = false;
	memset(m_Buffer, 0, SERV_BUFFER_LENGHT);
	m_UserIP = "---.---.---.---";
}

CServSocket::~CServSocket() {
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CServSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServSocket member functions

void CServSocket::GetLastError(char *Caption) {
	char String[200];
	strcpy(String, Caption); strcat(String, "\r\n");
	int LastError = CAsyncSocket::GetLastError();
	if( 	LastError == WSANOTINITIALISED)  strcat(String, "A successful AfxSocketInit must occur before using this API.");
	else if(LastError == WSAEINPROGRESS)	 strcat(String, "A blocking Windows Sockets operation is in progress.");
	else if(LastError == WSAEINPROGRESS)	 strcat(String, "A blocking Windows Sockets call is in progress.");
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

// extern char BoardTime[10][15];

void CServSocket::OnReceive(int nErrorCode) {
	memset(m_Buffer, 0, SERV_BUFFER_LENGHT);
	if(Receive(m_Buffer, SERV_BUFFER_LENGHT) == SOCKET_ERROR) {
		GetLastError("Receive");
	} else
		pTSrvDlg->Receive(m_Buffer);
	CAsyncSocket::OnReceive(nErrorCode);
}

void CServSocket::OnClose(int nErrorCode) {
	m_Accepted = false;
	CAsyncSocket::OnClose(nErrorCode);
	Close();
	m_UserIP = "---.---.---.---";
	pTSrvDlg->UpdateData(false);
}

void CServSocket::OnSend(int nErrorCode) {
	CAsyncSocket::OnSend(nErrorCode);
}
