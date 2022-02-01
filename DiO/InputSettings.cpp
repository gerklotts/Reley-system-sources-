// InputSettings.cpp : implementation file

#include "stdafx.h"
#include "Define.h"
#include "dio.h"
#include "InputSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CDC dcMemory;

/////////////////////////////////////////////////////////////////////////////
// CInputSettings dialog

CInputSettings::CInputSettings(CWnd* pParent /*=NULL*/) : CDialog(CInputSettings::IDD, pParent){
	//{{AFX_DATA_INIT(CInputSettings)
	m_inputNo = _T("");
	m_byteClrHiR = _T("x!x!x");
	m_byteClrHiG = _T("x!x!x");
	m_byteClrHiB = _T("x!x!x");
	m_byteClrLoR = _T("x!x!x");
	m_byteClrLoG = _T("x!x!x");
	m_byteClrLoB = _T("x!x!x");
	m_byteBkgHiR = _T("x!x!x");
	m_byteBkgHiG = _T("x!x!x");
	m_byteBkgHiB = _T("x!x!x");
	m_byteBkgLoR = _T("x!x!x");
	m_byteBkgLoG = _T("x!x!x");
	m_byteBkgLoB = _T("x!x!x");
	//}}AFX_DATA_INIT
	m_Text[1] = _T("--- 1 ---");
	m_Text[0] = _T("--- 0 ---");
	m_TextColour[1][0] =   0;
	m_TextColour[1][1] =   0;
	m_TextColour[1][2] =   0;
	m_TextColour[0][0] =   0;
	m_TextColour[0][1] =   0;
	m_TextColour[0][2] =   0;
	m_BackGround[1][0] = 200;
	m_BackGround[1][1] = 200;
	m_BackGround[1][2] = 200;
	m_BackGround[0][0] = 200;
	m_BackGround[0][1] = 200;
	m_BackGround[0][2] = 200;
}

void CInputSettings::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputSettings)
	DDX_Control(pDX, IDC_1_CLR_R, m_SliderClrHiR);
	DDX_Control(pDX, IDC_1_CLR_G, m_SliderClrHiG);
	DDX_Control(pDX, IDC_1_CLR_B, m_SliderClrHiB);
	DDX_Control(pDX, IDC_0_CLR_R, m_SliderClrLoR);
	DDX_Control(pDX, IDC_0_CLR_G, m_SliderClrLoG);
	DDX_Control(pDX, IDC_0_CLR_B, m_SliderClrLoB);
	DDX_Control(pDX, IDC_1_BKG_R, m_SliderBkgHiR);
	DDX_Control(pDX, IDC_1_BKG_G, m_SliderBkgHiG);
	DDX_Control(pDX, IDC_1_BKG_B, m_SliderBkgHiB);
	DDX_Control(pDX, IDC_0_BKG_R, m_SliderBkgLoR);
	DDX_Control(pDX, IDC_0_BKG_G, m_SliderBkgLoG);
	DDX_Control(pDX, IDC_0_BKG_B, m_SliderBkgLoB);
	DDX_Text(pDX, IDC_N_INPUT, m_inputNo);
	DDX_Text(pDX, IDC_1_BYTE_CLR_R, m_byteClrHiR);
	DDX_Text(pDX, IDC_1_BYTE_CLR_G, m_byteClrHiG);
	DDX_Text(pDX, IDC_1_BYTE_CLR_B, m_byteClrHiB);
	DDX_Text(pDX, IDC_0_BYTE_CLR_R, m_byteClrLoR);
	DDX_Text(pDX, IDC_0_BYTE_CLR_G, m_byteClrLoG);
	DDX_Text(pDX, IDC_0_BYTE_CLR_B, m_byteClrLoB);
	DDX_Text(pDX, IDC_1_BYTE_BKG_R, m_byteBkgHiR);
	DDX_Text(pDX, IDC_1_BYTE_BKG_G, m_byteBkgHiG);
	DDX_Text(pDX, IDC_1_BYTE_BKG_B, m_byteBkgHiB);
	DDX_Text(pDX, IDC_0_BYTE_BKG_R, m_byteBkgLoR);
	DDX_Text(pDX, IDC_0_BYTE_BKG_G, m_byteBkgLoG);
	DDX_Text(pDX, IDC_0_BYTE_BKG_B, m_byteBkgLoB);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_1, m_btn[1]);
	DDX_Control(pDX, IDC_BUTTON_0, m_btn[0]);
	DDX_Text(pDX, IDC_TEXT_1, m_Text[1]);
	DDX_Text(pDX, IDC_TEXT_0, m_Text[0]);
}

BEGIN_MESSAGE_MAP(CInputSettings, CDialog)
	//{{AFX_MSG_MAP(CInputSettings)
	ON_WM_HSCROLL()
	ON_EN_UPDATE(IDC_TEXT_1, OnUpdateText_1)
	ON_EN_UPDATE(IDC_TEXT_0, OnUpdateText_0)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputSettings message handlers

BOOL CInputSettings::OnInitDialog() {
	CDialog::OnInitDialog();
	m_SliderClrHiR.SetRange(0, 255, false);
	m_SliderClrHiG.SetRange(0, 255, false);
	m_SliderClrHiB.SetRange(0, 255, false);
	m_SliderClrLoR.SetRange(0, 255, false);
	m_SliderClrLoG.SetRange(0, 255, false);
	m_SliderClrLoB.SetRange(0, 255, false);
	m_SliderBkgHiR.SetRange(0, 255, false);
	m_SliderBkgHiG.SetRange(0, 255, false);
	m_SliderBkgHiB.SetRange(0, 255, false);
	m_SliderBkgLoR.SetRange(0, 255, false);
	m_SliderBkgLoG.SetRange(0, 255, false);
	m_SliderBkgLoB.SetRange(0, 255, false);
	m_SliderClrHiR.SetPos(m_TextColour[1][0]);
	m_SliderClrHiG.SetPos(m_TextColour[1][1]);
	m_SliderClrHiB.SetPos(m_TextColour[1][2]);
	m_SliderClrLoR.SetPos(m_TextColour[0][0]);
	m_SliderClrLoG.SetPos(m_TextColour[0][1]);
	m_SliderClrLoB.SetPos(m_TextColour[0][2]);
	m_SliderBkgHiR.SetPos(m_BackGround[1][0]);
	m_SliderBkgHiG.SetPos(m_BackGround[1][1]);
	m_SliderBkgHiB.SetPos(m_BackGround[1][2]);
	m_SliderBkgLoR.SetPos(m_BackGround[0][0]);
	m_SliderBkgLoG.SetPos(m_BackGround[0][1]);
	m_SliderBkgLoB.SetPos(m_BackGround[0][2]);
	m_byteClrHiR.Format("%u", m_TextColour[1][0]);
	m_byteClrHiG.Format("%u", m_TextColour[1][1]);
	m_byteClrHiB.Format("%u", m_TextColour[1][2]);
	m_byteClrLoR.Format("%u", m_TextColour[0][0]);
	m_byteClrLoG.Format("%u", m_TextColour[0][1]);
	m_byteClrLoB.Format("%u", m_TextColour[0][2]);
	m_byteBkgHiR.Format("%u", m_BackGround[1][0]);
	m_byteBkgHiG.Format("%u", m_BackGround[1][1]);
	m_byteBkgHiB.Format("%u", m_BackGround[1][2]);
	m_byteBkgLoR.Format("%u", m_BackGround[0][0]);
	m_byteBkgLoG.Format("%u", m_BackGround[0][1]);
	m_byteBkgLoB.Format("%u", m_BackGround[0][2]);
	UpdateData(SET_TO_DLG);
	PrepareBMP(1);
	m_btn[1].SetBitmap(m_bmp[1]);
	PrepareBMP(0);
	m_btn[0].SetBitmap(m_bmp[0]);
	return(true); // return TRUE unless you set the focus to a control
}	              // EXCEPTION: OCX Property Pages should return FALSE
void CInputSettings::PrepareBMP(int NoBMP) {
	CBrush Brush(RGB(m_BackGround[NoBMP][0], m_BackGround[NoBMP][1], m_BackGround[NoBMP][2]));
	CBitmap * oldBMP = dcMemory.SelectObject(&m_bmp[NoBMP]);
	CBrush * oldBrush = dcMemory.SelectObject(&Brush);
	dcMemory.SetBkMode(TRANSPARENT);
	dcMemory.SetTextColor(RGB(m_TextColour[NoBMP][0],  m_TextColour[NoBMP][1], m_TextColour[NoBMP][2]));
	CRect MyRect(0, 0, BUTTON_X_SIZE-1, BUTTON_Y_SIZE-1);
	dcMemory.FillRect(&MyRect, &Brush);
	MyRect.top = BUTTON_TOP;
	dcMemory.DrawText(m_Text[NoBMP], &MyRect, DT_CENTER | DT_VCENTER);
	dcMemory.SelectObject(oldBMP);
	dcMemory.SelectObject(oldBrush);
}
void CInputSettings::OnOK() {
	UpdateData(GET_FROM_DLG);
	m_TextColour[1][0] = m_SliderClrHiR.GetPos();
	m_TextColour[1][1] = m_SliderClrHiG.GetPos();
	m_TextColour[1][2] = m_SliderClrHiB.GetPos();
	m_TextColour[0][0] = m_SliderClrLoR.GetPos();
	m_TextColour[0][1] = m_SliderClrLoG.GetPos();
	m_TextColour[0][2] = m_SliderClrLoB.GetPos();
	m_BackGround[1][0] = m_SliderBkgHiR.GetPos();
	m_BackGround[1][1] = m_SliderBkgHiG.GetPos();
	m_BackGround[1][2] = m_SliderBkgHiB.GetPos();
	m_BackGround[0][0] = m_SliderBkgLoR.GetPos();
	m_BackGround[0][1] = m_SliderBkgLoG.GetPos();
	m_BackGround[0][2] = m_SliderBkgLoB.GetPos();
	CDialog::OnOK();
}
void CInputSettings::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	bool flgHi, flgLo;
	flgHi = flgLo = false;
	if(       (void *)&m_SliderClrHiR == (void *)pScrollBar) {
		m_TextColour[1][0] = m_SliderClrHiR.GetPos();
		m_byteClrHiR.Format("%u", m_TextColour[1][0]);
		UpdateData(SET_TO_DLG);
		flgHi = true;
	} else if((void *)&m_SliderClrHiG == (void *)pScrollBar) {
		m_TextColour[1][1] = m_SliderClrHiG.GetPos();
		m_byteClrHiG.Format("%u", m_TextColour[1][1]);
		UpdateData(SET_TO_DLG);
		flgHi = true;
	} else if((void *)&m_SliderClrHiB == (void *)pScrollBar) {
		m_TextColour[1][2] = m_SliderClrHiB.GetPos();
		m_byteClrHiB.Format("%u", m_TextColour[1][2]);
		UpdateData(SET_TO_DLG);
		flgHi = true;
	} else if((void *)&m_SliderClrLoR == (void *)pScrollBar) {
		m_TextColour[0][0] = m_SliderClrLoR.GetPos();
		m_byteClrLoR.Format("%u", m_TextColour[0][0]);
		UpdateData(SET_TO_DLG);
		flgLo = true;
	} else if((void *)&m_SliderClrLoG == (void *)pScrollBar) {
		m_TextColour[0][1] = m_SliderClrLoG.GetPos();
		m_byteClrLoG.Format("%u", m_TextColour[0][1]);
		UpdateData(SET_TO_DLG);
		flgLo = true;
	} else if((void *)&m_SliderClrLoB == (void *)pScrollBar) {
		m_TextColour[0][2] = m_SliderClrLoB.GetPos();
		m_byteClrLoB.Format("%u", m_TextColour[0][2]);
		UpdateData(SET_TO_DLG);
		flgLo = true;
	} else 	if((void *)&m_SliderBkgHiR == (void *)pScrollBar) {
		m_BackGround[1][0] = m_SliderBkgHiR.GetPos();
		m_byteBkgHiR.Format("%u", m_BackGround[1][0]);
		UpdateData(SET_TO_DLG);
		flgHi = true;
	} else if((void *)&m_SliderBkgHiG == (void *)pScrollBar) {
		m_BackGround[1][1] = m_SliderBkgHiG.GetPos();
		m_byteBkgHiG.Format("%u", m_BackGround[1][1]);
		UpdateData(SET_TO_DLG);
		flgHi = true;
	} else if((void *)&m_SliderBkgHiB == (void *)pScrollBar) {
		m_BackGround[1][2] = m_SliderBkgHiB.GetPos();
		m_byteBkgHiB.Format("%u", m_BackGround[1][2]);
		UpdateData(SET_TO_DLG);
		flgHi = true;
	} else if((void *)&m_SliderBkgLoR == (void *)pScrollBar) {
		m_BackGround[0][0] = m_SliderBkgLoR.GetPos();
		m_byteBkgLoR.Format("%u", m_BackGround[0][0]);
		UpdateData(SET_TO_DLG);
		flgLo = true;
	} else if((void *)&m_SliderBkgLoG == (void *)pScrollBar) {
		m_BackGround[0][1] = m_SliderBkgLoG.GetPos();
		m_byteBkgLoG.Format("%u", m_BackGround[0][1]);
		UpdateData(SET_TO_DLG);
		flgLo = true;
	} else if((void *)&m_SliderBkgLoB == (void *)pScrollBar) {
		m_BackGround[0][2] = m_SliderBkgLoB.GetPos();
		m_byteBkgLoB.Format("%u", m_BackGround[0][2]);
		UpdateData(SET_TO_DLG);
		flgLo = true;
	}
	if(flgHi) {
		PrepareBMP(1);
		m_btn[1].SetBitmap(m_bmp[1]);
	} else if(flgLo) {
		PrepareBMP(0);
		m_btn[0].SetBitmap(m_bmp[0]);
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CInputSettings::OnUpdateText_1() {
	UpdateData(GET_FROM_DLG);
	PrepareBMP(1);
	m_btn[1].SetBitmap(m_bmp[1]);
	UpdateData(SET_TO_DLG);
}

void CInputSettings::OnUpdateText_0() {
	UpdateData(GET_FROM_DLG);
	PrepareBMP(0);
	m_btn[0].SetBitmap(m_bmp[0]);
	UpdateData(SET_TO_DLG);
}
