// SuccessLogin.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC Client.h"
#include "SuccessLogin.h"
#include "afxdialogex.h"
#include "MFC ClientDlg.h"
#include "CheckingInfo.h"


// SuccessLogin 대화 상자

IMPLEMENT_DYNAMIC(SuccessLogin, CDialogEx)

SuccessLogin::SuccessLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
}

SuccessLogin::~SuccessLogin()
{
}

void SuccessLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SuccessLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &SuccessLogin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &SuccessLogin::OnBnClickedButton1)
END_MESSAGE_MAP()


// SuccessLogin 메시지 처리기


void SuccessLogin::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CheckingInfo dlg;
	
	dlg.Player = Player__;

	dlg.DoModal();
}


BOOL SuccessLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef UNICODE
	USES_CONVERSION;
#endif
	CString toolTip;
	toolTip.Format(_T("%s (%s) 님 환영합니다."), A2W(Player__.NAME), A2W(Player__.ID));
	GetDlgItem(IDTEXT)->SetWindowText(toolTip);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SuccessLogin::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMFCClientDlg dlg;

	memset(&Player__, 0, sizeof(Player_Data));

	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

	dlg.DoModal();
}
