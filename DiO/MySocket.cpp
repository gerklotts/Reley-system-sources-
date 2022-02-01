// MySocket.cpp : implementation file

#include "stdafx.h"
#include "DiODlg.h"
#include "MySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL flgAddressData;

/////////////////////////////////////////////////////////////////////////////
// CMySocket

CMySocket::CMySocket() {
	m_Status = "NOT CONNECTED";
	m_flgConnected = false;
	m_IP_Address[0] = 192;
	m_IP_Address[1] = 168;
	m_IP_Address[2] =   0;
	m_IP_Address[3] = 104;
	m_IP_Port = 33033;
}

CMySocket::~CMySocket() {
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMySocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CMySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMySocket member functions

void CMySocket::GetLastError(char *Caption) {
	char String[500];
	strcpy(String, Caption); strcat(String, "\n\r");
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
//	else if(LastError == WSAEWOULDBLOCK)	 strcat(String, "The socket is marked as nonblocking and the connection cannot be completed immediately.");
	else if(LastError == WSAECONNREFUSED)	 strcat(String, "The attempt to connect was rejected.");
	else if(LastError == WSAEFAULT) 		 strcat(String, "The nSockAddrLen argument is incorrect.");
	else if(LastError == WSAENETUNREACH)	 strcat(String, "The network cannot be reached from this host at this time.");
	else if(LastError == WSAEMFILE) 		 strcat(String, "No more file descriptors are available.");
	else if(LastError == WSAENOBUFS)		 strcat(String, "No buffer space is available. The socket cannot be created.");
	else if(LastError == WSAEMFILE) 		 strcat(String, "No more file descriptors are available.");
	else if(LastError == WSAEINVAL) 		 strcat(String, "Invalid host address.");
	else									 strcat(String, "Unknown ERROR");
	m_pDiODlg->m_Answer.SetWindowText(String);
}

void CMySocket::CreateMySocket() {
	if(!CAsyncSocket::Create())
		GetLastError("Create : ");
	m_pDiODlg->m_SocketStatus.SetWindowText(m_Status);
}

void CMySocket::Connecttt() {
	m_Status = "CONNECTING. Wait ...";
	m_pDiODlg->m_SocketStatus.SetWindowText(m_Status);
	char String[50];
	sprintf(String, "%u.%u.%u.%u", m_IP_Address[0], m_IP_Address[1], m_IP_Address[2], m_IP_Address[3]);
	if(!CAsyncSocket::Connect(String, m_IP_Port))
		GetLastError("Connect : ");
	else
		m_flgConnected = true;
	m_pDiODlg->m_SocketStatus.SetWindowText(m_Status);
}

void CMySocket::OnReceive(int nErrorCode) {
	int i;
	if((i = Receive(m_Buffer, 1999)) == SOCKET_ERROR) {
		GetLastError("Receive : ");
	} else {
		m_Buffer[i] = 0;
		m_pDiODlg->Receive(m_Buffer);
	}
	m_pDiODlg->m_SocketStatus.SetWindowText(m_Status);
	CAsyncSocket::OnReceive(nErrorCode);
}

void CMySocket::Close() {
	m_flgConnected = false;
	m_Status = "NOT CONNECTED";
	m_pDiODlg->ServerOnClose();
	CAsyncSocket::Close();
}

void CMySocket::OnClose(int nErrorCode) {
	if(nErrorCode)
		GetLastError("Close : ");
	m_flgConnected = false;
	m_Status = "NOT CONNECTED";
	m_pDiODlg->ServerOnClose();
	CAsyncSocket::OnClose(nErrorCode);
}

void CMySocket::OnSend(int nErrorCode) {
	if(nErrorCode)
		GetLastError("Send : ");
	else
		m_Status = "CONNECTED";
	m_pDiODlg->m_SocketStatus.SetWindowText(m_Status);
	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnConnect(int nErrorCode) {
	if(nErrorCode) {
		m_flgConnected = false;
		m_Status = "NOT CONNECTED 10";
		m_pDiODlg->m_ConnectTimer = 20;
		GetLastError("OnConnect : ");
		m_pDiODlg->m_SocketStatus.SetWindowText(m_Status);
	} else {
		m_Status = "CONNECTED";
		m_flgConnected = true;
		m_pDiODlg->ServerOnConnect();
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
