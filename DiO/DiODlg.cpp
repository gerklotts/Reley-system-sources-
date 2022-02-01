// DiODlg.cpp : implementation file

#include "stdafx.h"
#include "Define.h"
#include "DiO.h"
#include "UserName.h"
#include "DiODlg.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define INI_FILE ".\\DiO.ini"

unsigned char Delays[4][6];
CDC dcMemory;

/////////////////////////////////////////////////////////////////////////////
// CDiODlg dialog

CDiODlg::CDiODlg(CWnd* pParent /*=NULL*/) : CDialog(CDiODlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CDiODlg)
	m_Inputs = _T("");
	m_ConnectTimer = 0;
	//}}AFX_DATA_INIT
	m_flgSaveRX = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_UserName = "qwqw"; //START_USER_NAME;
	m_InputsDWORD = 0ul;
	m_RelaysWORD = m_OutputsWORD = 0;
	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 3; j++) {
			m_InBackGround[1][i][j] = 200;
			m_InBackGround[0][i][j] = 200;
			m_InTextColour[1][i][j] = 0;
			m_InTextColour[0][i][j] = 0;
		}
	}
}

void CDiODlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiODlg)
	DDX_Control(pDX, IDC_ANSWER, m_Answer);
	DDX_Control(pDX, IDC_CONNECTED, m_SocketStatus);
	DDX_Control(pDX, IDC_SET_IP, m_btnSetIP);
	DDX_Control(pDX, IDC_SAVE_RX, m_checkSaveRX);
	//}}AFX_DATA_MAP
	for(int i = 0; i < 32; i++) {
		DDX_Control(pDX, IDC_IN_00 + i, m_btnInputs[i]);
	}
	for(i = 0; i < 16; i++) {
		DDX_Control(pDX, IDC_OUT_00 + i, m_btnOutputs[i]);
//		DDX_Control(pDX, IDC_RELAY_ON_00 + i, m_btnRelaysOn[i]);
//		DDX_Control(pDX, IDC_RELAY_OFF_00 + i, m_btnRelaysOff[i]);
	}
	if(pDX->m_bSaveAndValidate) { // GET controls
	} else { // SET controls
	}
}

BEGIN_MESSAGE_MAP(CDiODlg, CDialog)
	//{{AFX_MSG_MAP(CDiODlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE_RX, OnSaveRx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SET_IP, OnSetIP)
	ON_BN_CLICKED(IDC_OUT_00, OnOutput00)
	ON_BN_CLICKED(IDC_OUT_01, OnOutput01)
	ON_BN_CLICKED(IDC_OUT_02, OnOutput02)
	ON_BN_CLICKED(IDC_OUT_03, OnOutput03)
	ON_BN_CLICKED(IDC_OUT_04, OnOutput04)
	ON_BN_CLICKED(IDC_OUT_05, OnOutput05)
	ON_BN_CLICKED(IDC_OUT_06, OnOutput06)
	ON_BN_CLICKED(IDC_OUT_07, OnOutput07)
	ON_BN_CLICKED(IDC_OUT_08, OnOutput08)
	ON_BN_CLICKED(IDC_OUT_09, OnOutput09)
	ON_BN_CLICKED(IDC_OUT_10, OnOutput10)
	ON_BN_CLICKED(IDC_OUT_11, OnOutput11)
	ON_BN_CLICKED(IDC_OUT_12, OnOutput12)
	ON_BN_CLICKED(IDC_OUT_13, OnOutput13)
	ON_BN_CLICKED(IDC_OUT_14, OnOutput14)
	ON_BN_CLICKED(IDC_OUT_15, OnOutput15)

	ON_BN_CLICKED(IDC_RELAY_ON_00, OnRelayOn00)
	ON_BN_CLICKED(IDC_RELAY_ON_01, OnRelayOn01)
	ON_BN_CLICKED(IDC_RELAY_ON_02, OnRelayOn02)
	ON_BN_CLICKED(IDC_RELAY_ON_03, OnRelayOn03)
	ON_BN_CLICKED(IDC_RELAY_ON_04, OnRelayOn04)
	ON_BN_CLICKED(IDC_RELAY_ON_05, OnRelayOn05)
	ON_BN_CLICKED(IDC_RELAY_ON_06, OnRelayOn06)
	ON_BN_CLICKED(IDC_RELAY_ON_07, OnRelayOn07)
	ON_BN_CLICKED(IDC_RELAY_ON_08, OnRelayOn08)
	ON_BN_CLICKED(IDC_RELAY_ON_09, OnRelayOn09)
	ON_BN_CLICKED(IDC_RELAY_ON_10, OnRelayOn10)
	ON_BN_CLICKED(IDC_RELAY_ON_11, OnRelayOn11)
	ON_BN_CLICKED(IDC_RELAY_ON_12, OnRelayOn12)
	ON_BN_CLICKED(IDC_RELAY_ON_13, OnRelayOn13)
	ON_BN_CLICKED(IDC_RELAY_ON_14, OnRelayOn14)
	ON_BN_CLICKED(IDC_RELAY_ON_15, OnRelayOn15)

	ON_BN_CLICKED(IDC_RELAY_OFF_00, OnRelayOff00)
	ON_BN_CLICKED(IDC_RELAY_OFF_01, OnRelayOff01)
	ON_BN_CLICKED(IDC_RELAY_OFF_02, OnRelayOff02)
	ON_BN_CLICKED(IDC_RELAY_OFF_03, OnRelayOff03)
	ON_BN_CLICKED(IDC_RELAY_OFF_04, OnRelayOff04)
	ON_BN_CLICKED(IDC_RELAY_OFF_05, OnRelayOff05)
	ON_BN_CLICKED(IDC_RELAY_OFF_06, OnRelayOff06)
	ON_BN_CLICKED(IDC_RELAY_OFF_07, OnRelayOff07)
	ON_BN_CLICKED(IDC_RELAY_OFF_08, OnRelayOff08)
	ON_BN_CLICKED(IDC_RELAY_OFF_09, OnRelayOff09)
	ON_BN_CLICKED(IDC_RELAY_OFF_10, OnRelayOff10)
	ON_BN_CLICKED(IDC_RELAY_OFF_11, OnRelayOff11)
	ON_BN_CLICKED(IDC_RELAY_OFF_12, OnRelayOff12)
	ON_BN_CLICKED(IDC_RELAY_OFF_13, OnRelayOff13)
	ON_BN_CLICKED(IDC_RELAY_OFF_14, OnRelayOff14)
	ON_BN_CLICKED(IDC_RELAY_OFF_15, OnRelayOff15)

	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_IN_00, OnIn00)
	ON_BN_CLICKED(IDC_IN_01, OnIn01)
	ON_BN_CLICKED(IDC_IN_02, OnIn02)
	ON_BN_CLICKED(IDC_IN_03, OnIn03)
	ON_BN_CLICKED(IDC_IN_04, OnIn04)
	ON_BN_CLICKED(IDC_IN_05, OnIn05)
	ON_BN_CLICKED(IDC_IN_06, OnIn06)
	ON_BN_CLICKED(IDC_IN_07, OnIn07)
	ON_BN_CLICKED(IDC_IN_08, OnIn08)
	ON_BN_CLICKED(IDC_IN_09, OnIn09)
	ON_BN_CLICKED(IDC_IN_10, OnIn10)
	ON_BN_CLICKED(IDC_IN_11, OnIn11)
	ON_BN_CLICKED(IDC_IN_12, OnIn12)
	ON_BN_CLICKED(IDC_IN_13, OnIn13)
	ON_BN_CLICKED(IDC_IN_14, OnIn14)
	ON_BN_CLICKED(IDC_IN_15, OnIn15)
	ON_BN_CLICKED(IDC_IN_16, OnIn16)
	ON_BN_CLICKED(IDC_IN_17, OnIn17)
	ON_BN_CLICKED(IDC_IN_18, OnIn18)
	ON_BN_CLICKED(IDC_IN_19, OnIn19)
	ON_BN_CLICKED(IDC_IN_20, OnIn20)
	ON_BN_CLICKED(IDC_IN_21, OnIn21)
	ON_BN_CLICKED(IDC_IN_22, OnIn22)
	ON_BN_CLICKED(IDC_IN_23, OnIn23)
	ON_BN_CLICKED(IDC_IN_24, OnIn24)
	ON_BN_CLICKED(IDC_IN_25, OnIn25)
	ON_BN_CLICKED(IDC_IN_26, OnIn26)
	ON_BN_CLICKED(IDC_IN_27, OnIn27)
	ON_BN_CLICKED(IDC_IN_28, OnIn28)
	ON_BN_CLICKED(IDC_IN_29, OnIn29)
	ON_BN_CLICKED(IDC_IN_30, OnIn30)
	ON_BN_CLICKED(IDC_IN_31, OnIn31)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiODlg message handlers

void CDiODlg::SetInBMP(int HiLo, int No) {
	CRect MyRect(0, 0, BUTTON_X_SIZE-1, BUTTON_Y_SIZE-1);
	CBrush Brush(RGB(m_InBackGround[HiLo][No][0], m_InBackGround[HiLo][No][1], m_InBackGround[HiLo][No][2]));
	CBrush * oldBrush = dcMemory.SelectObject(&Brush);
	CBitmap * oldBMP = dcMemory.SelectObject(&m_bmpIn[HiLo][No]);
	dcMemory.FillRect(&MyRect, &Brush);
	MyRect.top = BUTTON_TOP;
	dcMemory.SetBkMode(TRANSPARENT);
	dcMemory.SetTextColor(RGB(m_InTextColour[HiLo][No][0], m_InTextColour[HiLo][No][1], m_InTextColour[HiLo][No][2]));
	dcMemory.DrawText(m_InText[HiLo][No], &MyRect, DT_CENTER | DT_VCENTER);
	dcMemory.SelectObject(oldBrush);
	dcMemory.SelectObject(oldBMP);
}

BOOL CDiODlg::OnInitDialog() {
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	ReadINI();
	if(m_flgSaveRX)
		FPrintfSaveRx("----------------------- Start ---------------------------\n");
	m_checkSaveRX.SetCheck(m_flgSaveRX);
	SaveINI();
	m_MySocket.m_pDiODlg = this;
	m_MySocket.CreateMySocket();
	m_MySocket.Connecttt();
	Set_btnSetIP();
	SetTimer(0x12349876, 500, NULL);
	m_SocketOnTimer = 20; // x 500 mSec = 10.0 Sec
	FPrintfConect();
	m_bmpHi.LoadBitmap(IDB_ON);
	m_bmpLo.LoadBitmap(IDB_OFF);
	m_bmpX.LoadBitmap(IDB_X);
	CDC * pDcDlg = GetDC();
	dcMemory.CreateCompatibleDC(pDcDlg);
	for(int i = 0; i < 32; i++) {
		m_bmpIn[1][i].CreateCompatibleBitmap(pDcDlg, BUTTON_X_SIZE, BUTTON_Y_SIZE);
		m_bmpIn[0][i].CreateCompatibleBitmap(pDcDlg, BUTTON_X_SIZE, BUTTON_Y_SIZE);
		SetInBMP(1, i);
		SetInBMP(0, i);
	}
	m_InputSettings.m_bmp[0].CreateCompatibleBitmap(pDcDlg, BUTTON_X_SIZE, BUTTON_Y_SIZE);
	m_InputSettings.m_bmp[1].CreateCompatibleBitmap(pDcDlg, BUTTON_X_SIZE, BUTTON_Y_SIZE);
	Set_btnHiLo();
	return(true);  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDiODlg::OnPaint() {
	if(IsIconic()) {
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDiODlg::OnQueryDragIcon() {
	return (HCURSOR) m_hIcon;
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/*void CDiODlg::Set_btnRequest() {
	if(!m_flgGranted)
		m_Request.SetWindowText("&Request");
	else
		m_Request.SetWindowText("Send info");
}*/
char BackgruondKey[2][3][25]= {
	{ "HiBackground_RED", "HiBackground_GREEN", "HiBackground_BLUE" },
	{ "LoBackground_RED", "LoBackground_GREEN", "LoBackground_BLUE" },
};
char TextColourKey[2][3][25]= {
	{ "HiTextColour_RED", "HiTextColour_GREEN", "HiTextColour_BLUE" },
	{ "LoTextColour_RED", "LoTextColour_GREEN", "LoTextColour_BLUE" },
};
void CDiODlg::ReadINI() {
	m_MySocket.m_IP_Address[0] = GetPrivateProfileInt("DiO", "IP_Address1", 169, INI_FILE);
	m_MySocket.m_IP_Address[1] = GetPrivateProfileInt("DiO", "IP_Address2", 254, INI_FILE);
	m_MySocket.m_IP_Address[2] = GetPrivateProfileInt("DiO", "IP_Address3", 243, INI_FILE);
	m_MySocket.m_IP_Address[3] = GetPrivateProfileInt("DiO", "IP_Address4", 237, INI_FILE);
	m_MySocket.m_IP_Port       = GetPrivateProfileInt("DiO", "IP_Port",    8080, INI_FILE);
	m_flgSaveRX   = GetPrivateProfileInt("DiO", "SaveRX", 0, INI_FILE);
	if(m_flgSaveRX < 0 || m_flgSaveRX > 1)
		m_flgSaveRX = 1;
	char SectionName[100];
	for(int i = 0; i < 32; i++) {
		sprintf(SectionName, "Input_%02u", i+1);
		for(int j = 0; j < 3; j++) {
			m_InTextColour[1][i][j] = GetPrivateProfileInt(SectionName, TextColourKey[0][j], 255, INI_FILE);
			m_InTextColour[0][i][j] = GetPrivateProfileInt(SectionName, TextColourKey[1][j],   0, INI_FILE);
			m_InBackGround[1][i][j] = GetPrivateProfileInt(SectionName, BackgruondKey[0][j], 127, INI_FILE);
			m_InBackGround[0][i][j] = GetPrivateProfileInt(SectionName, BackgruondKey[1][j], 127, INI_FILE);
		}
		GetPrivateProfileString(SectionName, "HiText", "--Hi--", m_InText[1][i], 20, INI_FILE);
		GetPrivateProfileString(SectionName, "LoText", "__Lo__", m_InText[0][i], 20, INI_FILE);
	}
}
void CDiODlg::SaveINI() {
	char String[200];
	sprintf(String, "%d", m_flgSaveRX);                WritePrivateProfileString("DiO", "SaveRX",      String, INI_FILE);
	sprintf(String, "%d", m_MySocket.m_IP_Address[0]); WritePrivateProfileString("DiO", "IP_Address1", String, INI_FILE);
	sprintf(String, "%d", m_MySocket.m_IP_Address[1]); WritePrivateProfileString("DiO", "IP_Address2", String, INI_FILE);
	sprintf(String, "%d", m_MySocket.m_IP_Address[2]); WritePrivateProfileString("DiO", "IP_Address3", String, INI_FILE);
	sprintf(String, "%d", m_MySocket.m_IP_Address[3]); WritePrivateProfileString("DiO", "IP_Address4", String, INI_FILE);
	sprintf(String, "%d", m_MySocket.m_IP_Port);       WritePrivateProfileString("DiO", "IP_Port",     String, INI_FILE);
	WritePrivateProfileString("DiO", "######", "###############", INI_FILE);
	char SectionName[100];
	for(int i = 0; i < 32; i++) {
		sprintf(SectionName, "Input_%02u", i+1);
		for(int j = 0; j < 3; j++) {
			sprintf(String, "%d", m_InTextColour[1][i][j]); WritePrivateProfileString(SectionName, TextColourKey[0][j], String, INI_FILE);
			sprintf(String, "%d", m_InTextColour[0][i][j]); WritePrivateProfileString(SectionName, TextColourKey[1][j], String, INI_FILE);
			sprintf(String, "%d", m_InBackGround[1][i][j]); WritePrivateProfileString(SectionName, BackgruondKey[0][j], String, INI_FILE);
			sprintf(String, "%d", m_InBackGround[0][i][j]); WritePrivateProfileString(SectionName, BackgruondKey[1][j], String, INI_FILE);
		}
		WritePrivateProfileString(SectionName, "HiText", m_InText[1][i], INI_FILE);
		WritePrivateProfileString(SectionName, "LoText", m_InText[0][i], INI_FILE);
		WritePrivateProfileString(SectionName, "------", "---------------", INI_FILE);
	}
}

void CDiODlg::Set_btnSetIP() {
	char String[200];
	sprintf(String, "IP = %u.%u.%u.%u   Port = %u", m_MySocket.m_IP_Address[0], m_MySocket.m_IP_Address[1], m_MySocket.m_IP_Address[2], m_MySocket.m_IP_Address[3], m_MySocket.m_IP_Port);
	m_btnSetIP.SetWindowText(String);
}

void CDiODlg::FPrintfSaveRx(char * String) {
	if(m_flgSaveRX) {
		FILE *fp;
		if((fp = fopen("DiO.SQL", "a")) != NULL) {
			CTime CurrTime = CTime::GetCurrentTime();
			CString s = CurrTime.Format("%Y.%m.%d %H:%M:%S = ");
			fprintf(fp, s);
			fprintf(fp, String);
			fclose(fp);
		}
	}
}

void CDiODlg::FPrintfConect() {
	char String[200];
	if(m_MySocket.m_flgConnected)
		sprintf(String, "%u.%u.%u.%u : %u  Connected\n", m_MySocket.m_IP_Address[0], m_MySocket.m_IP_Address[1], m_MySocket.m_IP_Address[2], m_MySocket.m_IP_Address[3], m_MySocket.m_IP_Port);
	else
		sprintf(String, "%u.%u.%u.%u : %u  NOT Connected\n", m_MySocket.m_IP_Address[0], m_MySocket.m_IP_Address[1], m_MySocket.m_IP_Address[2], m_MySocket.m_IP_Address[3], m_MySocket.m_IP_Port);
	FPrintfSaveRx(String);
}

void CDiODlg::OnTimer(UINT nIDEvent) { // x 500 mSec
	if(m_ConnectTimer) {
		m_ConnectTimer--;
		if(!(m_ConnectTimer % 2)) {
			if(!m_ConnectTimer) {
				m_MySocket.Connecttt();
				FPrintfConect();
			} else
				m_MySocket.m_Status.Format("NOT CONNECTED %u", m_ConnectTimer / 2);
			m_SocketStatus.SetWindowText(m_MySocket.m_Status);
		}
	}
	if(!m_SocketOnTimer) {
		if(m_MySocket.m_flgConnected) {
			m_SocketOnTimer = 20; // x 500 mSec = 10.0 Sec
//			m_MySocket.Send("S", 1);
		}
	} else
		m_SocketOnTimer--;
	CDialog::OnTimer(nIDEvent);
}

void CDiODlg::OnSaveRx() {
	if(!UpdateData(GET_FROM_DLG))
		return;
	char String[20];
	m_flgSaveRX = m_checkSaveRX.GetCheck();
	sprintf(String, "%d", m_flgSaveRX);
	WritePrivateProfileString("DiO", "SaveRX", String, INI_FILE);
}

void CDiODlg::OnSetIP() {
	m_ConnectTimer = 0;
	m_SetIP.m_Address[0] = m_MySocket.m_IP_Address[0];
	m_SetIP.m_Address[1] = m_MySocket.m_IP_Address[1];
	m_SetIP.m_Address[2] = m_MySocket.m_IP_Address[2];
	m_SetIP.m_Address[3] = m_MySocket.m_IP_Address[3];
	m_SetIP.m_IP_Port    = m_MySocket.m_IP_Port;
	if((m_SetIP.DoModal() == IDOK) && (!m_MySocket.m_flgConnected || memcmp(m_MySocket.m_IP_Address, m_SetIP.m_Address, 4) || m_MySocket.m_IP_Port != m_SetIP.m_IP_Port)) {
		m_MySocket.Close();
		memcpy(m_MySocket.m_IP_Address, m_SetIP.m_Address, 4);
		m_MySocket.m_IP_Port = m_SetIP.m_IP_Port;
		SaveINI();
		Set_btnSetIP();
		m_MySocket.CreateMySocket();
		m_MySocket.Connecttt();
		FPrintfConect();
		UpdateData(SET_TO_DLG);
	}
}

void CDiODlg::OnCancel() {
	if(MessageBox("EXIT ?", "EXIT ?", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES) {
		m_MySocket.Close();
		FPrintfSaveRx("---------------- exit ------------------\n\n");
		CDialog::OnCancel();
	}
}

void CDiODlg::ServerOnConnect() {
	m_Answer.SetWindowText(".");
	UpdateData(SET_TO_DLG);
}

void CDiODlg::ServerOnClose() {
	m_Answer.SetWindowText("Rejected");
	UpdateData(SET_TO_DLG);
}

DWORD CheckDWORD[32] = {
	0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080,
	0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000,
	0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,
	0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
};
void CDiODlg::Set_btnHiLo(void) {
	for(int i = 0; i < 32; i++) {
		if(!m_MySocket.m_flgConnected)
			m_btnInputs[i].SetBitmap(m_bmpX);
		else if(m_InputsDWORD & CheckDWORD[i])
			m_btnInputs[i].SetBitmap(m_bmpIn[1][i]);
		else
			m_btnInputs[i].SetBitmap(m_bmpIn[0][i]);
	}
	for(i = 0; i < 16; i++) {
		if(!m_MySocket.m_flgConnected) {
			m_btnOutputs[i].SetBitmap(m_bmpX);
//			m_btnRelaysOn[i].SetBitmap(m_bmpX);
//			m_btnRelaysOff[i].SetBitmap(m_bmpX);
		} else {
			if(m_OutputsWORD & (WORD)CheckDWORD[i])
				m_btnOutputs[i].SetBitmap(m_bmpHi);
			else
				m_btnOutputs[i].SetBitmap(m_bmpLo);
//			if(m_RelaysWORD & (WORD)CheckDWORD[i])
//				m_btnRelaysOn[i].SetBitmap(m_bmpHi);
//			else
//				m_btnRelaysOn[i].SetBitmap(m_bmpLo);
		}
	}
}

void CDiODlg::Receive(char *pBuffer) {
	char String[200];
	m_Inputs = pBuffer;
	sprintf(String, "receive: \"%s\"\n", pBuffer);
	FPrintfSaveRx(String);
	if(*pBuffer == '!') {
		MessageBox(pBuffer, "MESSAGE :", MB_OK);
	} else {
		DWORD inDWORD;
		sscanf(pBuffer, "%08X", &inDWORD);
		for(int i = 0; i < 32; i++) {
			if((inDWORD ^ m_InputsDWORD) & CheckDWORD[i]) {
				char String[150];
				if(inDWORD & CheckDWORD[i])
					sprintf(String, "On%02d.wav", i + 1);
				else
					sprintf(String, "Off%02d.wav", i + 1);
				PlaySound(String, NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		m_InputsDWORD = inDWORD;
		sscanf(&pBuffer[9], "%04X", &inDWORD);
		m_OutputsWORD = (WORD)inDWORD;
		sscanf(&pBuffer[14], "%x04X", &inDWORD);
		m_RelaysWORD = (WORD)inDWORD;
		Set_btnHiLo();
	}
	UpdateData(SET_TO_DLG);
}

void CDiODlg::OnOutput(unsigned int No) {
	if(!strcmp(m_UserName, START_USER_NAME)) {
		MessageBox("First enter \"User Name\"\nthen \"Request\"", "----------------", MB_OK);
	} else if(m_MySocket.m_flgConnected) {
		char Buffer[200];
		sprintf(Buffer, "o%u", No);
		int SendNumb = m_MySocket.Send(Buffer, strlen(Buffer));
		sprintf(Buffer, "SENT : 552 %u\n", SendNumb);
		FPrintfSaveRx(Buffer);
	} else
		MessageBox("NOT connected.\nTo connect check server\nor press \"IP xxx.xxx.xxx.xxx Port yyyy\"\nselect IP & Port and then OK.", "NOT CONNECTED", MB_OK);
}

void CDiODlg::OnOutput00() { OnOutput( 0); }
void CDiODlg::OnOutput01() { OnOutput( 1); }
void CDiODlg::OnOutput02() { OnOutput( 2); }
void CDiODlg::OnOutput03() { OnOutput( 3); }
void CDiODlg::OnOutput04() { OnOutput( 4); }
void CDiODlg::OnOutput05() { OnOutput( 5); }
void CDiODlg::OnOutput06() { OnOutput( 6); }
void CDiODlg::OnOutput07() { OnOutput( 7); }
void CDiODlg::OnOutput08() { OnOutput( 8); }
void CDiODlg::OnOutput09() { OnOutput( 9); }
void CDiODlg::OnOutput10() { OnOutput(10); }
void CDiODlg::OnOutput11() { OnOutput(11); }
void CDiODlg::OnOutput12() { OnOutput(12); }
void CDiODlg::OnOutput13() { OnOutput(13); }
void CDiODlg::OnOutput14() { OnOutput(14); }
void CDiODlg::OnOutput15() { OnOutput(15); }

void CDiODlg::OnRelayOn(unsigned int No) {
	if(!strcmp(m_UserName, START_USER_NAME)) {
		MessageBox("First enter \"User Name\"\nthen \"Request\"", "----------------", MB_OK);
	} else if(m_MySocket.m_flgConnected) {
		char String[1000], Buffer[200];
		sprintf(Buffer, "R%u", No);
		int SendNumb = m_MySocket.Send(Buffer, strlen(Buffer));
		sprintf(String, "SENT : \"%s\" = %u\n", Buffer, SendNumb);
		FPrintfSaveRx(String);
	} else
		MessageBox("NOT connected.\nTo connect check server\nor press \"IP xxx.xxx.xxx.xxx Port yyyy\"\nselect IP & Port and then OK.", "NOT CONNECTED", MB_OK);
}

void CDiODlg::OnRelayOn00() { OnRelayOn( 0); }
void CDiODlg::OnRelayOn01() { OnRelayOn( 1); }
void CDiODlg::OnRelayOn02() { OnRelayOn( 2); }
void CDiODlg::OnRelayOn03() { OnRelayOn( 3); }
void CDiODlg::OnRelayOn04() { OnRelayOn( 4); }
void CDiODlg::OnRelayOn05() { OnRelayOn( 5); }
void CDiODlg::OnRelayOn06() { OnRelayOn( 6); }
void CDiODlg::OnRelayOn07() { OnRelayOn( 7); }
void CDiODlg::OnRelayOn08() { OnRelayOn( 8); }
void CDiODlg::OnRelayOn09() { OnRelayOn( 9); }
void CDiODlg::OnRelayOn10() { OnRelayOn(10); }
void CDiODlg::OnRelayOn11() { OnRelayOn(11); }
void CDiODlg::OnRelayOn12() { OnRelayOn(12); }
void CDiODlg::OnRelayOn13() { OnRelayOn(13); }
void CDiODlg::OnRelayOn14() { OnRelayOn(14); }
void CDiODlg::OnRelayOn15() { OnRelayOn(15); }

void CDiODlg::OnRelayOff(unsigned int No) {
	if(!strcmp(m_UserName, START_USER_NAME)) {
		MessageBox("First enter \"User Name\"\nthen \"Request\"", "----------------", MB_OK);
	} else if(m_MySocket.m_flgConnected) {
		char String[1000], Buffer[200];
		sprintf(Buffer, "r%u", No);
		int SendNumb = m_MySocket.Send(Buffer, strlen(Buffer));
		sprintf(String, "SENT : \"%s\" = %u\n", Buffer, SendNumb);
		FPrintfSaveRx(String);
	} else
		MessageBox("NOT connected.\nTo connect check server\nor press \"IP xxx.xxx.xxx.xxx Port yyyy\"\nselect IP & Port and then OK.", "NOT CONNECTED", MB_OK);
}

void CDiODlg::OnRelayOff00() { OnRelayOff( 0); }
void CDiODlg::OnRelayOff01() { OnRelayOff( 1); }
void CDiODlg::OnRelayOff02() { OnRelayOff( 2); }
void CDiODlg::OnRelayOff03() { OnRelayOff( 3); }
void CDiODlg::OnRelayOff04() { OnRelayOff( 4); }
void CDiODlg::OnRelayOff05() { OnRelayOff( 5); }
void CDiODlg::OnRelayOff06() { OnRelayOff( 6); }
void CDiODlg::OnRelayOff07() { OnRelayOff( 7); }
void CDiODlg::OnRelayOff08() { OnRelayOff( 8); }
void CDiODlg::OnRelayOff09() { OnRelayOff( 9); }
void CDiODlg::OnRelayOff10() { OnRelayOff(10); }
void CDiODlg::OnRelayOff11() { OnRelayOff(11); }
void CDiODlg::OnRelayOff12() { OnRelayOff(12); }
void CDiODlg::OnRelayOff13() { OnRelayOff(13); }
void CDiODlg::OnRelayOff14() { OnRelayOff(14); }
void CDiODlg::OnRelayOff15() { OnRelayOff(15); }

void CDiODlg::OnIn(unsigned int No) {
	m_InputSettings.m_inputNo.Format("Input #%u", No+1);
	m_InputSettings.m_Text[1] = m_InText[1][No];
	m_InputSettings.m_Text[0] = m_InText[0][No];
	m_InputSettings.m_TextColour[1][0] = m_InTextColour[1][No][0];
	m_InputSettings.m_TextColour[1][1] = m_InTextColour[1][No][1];
	m_InputSettings.m_TextColour[1][2] = m_InTextColour[1][No][2];
	m_InputSettings.m_TextColour[0][0] = m_InTextColour[0][No][0];
	m_InputSettings.m_TextColour[0][1] = m_InTextColour[0][No][1];
	m_InputSettings.m_TextColour[0][2] = m_InTextColour[0][No][2];
	m_InputSettings.m_BackGround[1][0] = m_InBackGround[1][No][0];
	m_InputSettings.m_BackGround[1][1] = m_InBackGround[1][No][1];
	m_InputSettings.m_BackGround[1][2] = m_InBackGround[1][No][2];
	m_InputSettings.m_BackGround[0][0] = m_InBackGround[0][No][0];
	m_InputSettings.m_BackGround[0][1] = m_InBackGround[0][No][1];
	m_InputSettings.m_BackGround[0][2] = m_InBackGround[0][No][2];
	if(m_InputSettings.DoModal() == IDOK) {
		m_InTextColour[1][No][0] = m_InputSettings.m_TextColour[1][0];
		m_InTextColour[1][No][1] = m_InputSettings.m_TextColour[1][1];
		m_InTextColour[1][No][2] = m_InputSettings.m_TextColour[1][2];
		m_InTextColour[0][No][0] = m_InputSettings.m_TextColour[0][0];
		m_InTextColour[0][No][1] = m_InputSettings.m_TextColour[0][1];
		m_InTextColour[0][No][2] = m_InputSettings.m_TextColour[0][2];
		m_InBackGround[1][No][0] = m_InputSettings.m_BackGround[1][0];
		m_InBackGround[1][No][1] = m_InputSettings.m_BackGround[1][1];
		m_InBackGround[1][No][2] = m_InputSettings.m_BackGround[1][2];
		m_InBackGround[0][No][0] = m_InputSettings.m_BackGround[0][0];
		m_InBackGround[0][No][1] = m_InputSettings.m_BackGround[0][1];
		m_InBackGround[0][No][2] = m_InputSettings.m_BackGround[0][2];
		strncpy(m_InText[1][No], m_InputSettings.m_Text[1], 25);
		strncpy(m_InText[0][No], m_InputSettings.m_Text[0], 25);
		SaveINI();
		SetInBMP(1, No);
		SetInBMP(0, No);
		Set_btnHiLo();
		UpdateData(SET_TO_DLG);
	}
}

void CDiODlg::OnIn00() { OnIn( 0); }
void CDiODlg::OnIn01() { OnIn( 1); }
void CDiODlg::OnIn02() { OnIn( 2); }
void CDiODlg::OnIn03() { OnIn( 3); }
void CDiODlg::OnIn04() { OnIn( 4); }
void CDiODlg::OnIn05() { OnIn( 5); }
void CDiODlg::OnIn06() { OnIn( 6); }
void CDiODlg::OnIn07() { OnIn( 7); }
void CDiODlg::OnIn08() { OnIn( 8); }
void CDiODlg::OnIn09() { OnIn( 9); }
void CDiODlg::OnIn10() { OnIn(10); }
void CDiODlg::OnIn11() { OnIn(11); }
void CDiODlg::OnIn12() { OnIn(12); }
void CDiODlg::OnIn13() { OnIn(13); }
void CDiODlg::OnIn14() { OnIn(14); }
void CDiODlg::OnIn15() { OnIn(15); }
void CDiODlg::OnIn16() { OnIn(16); }
void CDiODlg::OnIn17() { OnIn(17); }
void CDiODlg::OnIn18() { OnIn(18); }
void CDiODlg::OnIn19() { OnIn(19); }
void CDiODlg::OnIn20() { OnIn(20); }
void CDiODlg::OnIn21() { OnIn(21); }
void CDiODlg::OnIn22() { OnIn(22); }
void CDiODlg::OnIn23() { OnIn(23); }
void CDiODlg::OnIn24() { OnIn(24); }
void CDiODlg::OnIn25() { OnIn(25); }
void CDiODlg::OnIn26() { OnIn(26); }
void CDiODlg::OnIn27() { OnIn(27); }
void CDiODlg::OnIn28() { OnIn(28); }
void CDiODlg::OnIn29() { OnIn(29); }
void CDiODlg::OnIn30() { OnIn(30); }
void CDiODlg::OnIn31() { OnIn(31); }
