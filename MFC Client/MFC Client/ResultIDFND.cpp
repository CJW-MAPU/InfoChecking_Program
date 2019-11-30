// ResultIDFND.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC Client.h"
#include "ResultIDFND.h"
#include "afxdialogex.h"
#include "Main.h"
#include "FoundAccount.h"
#include "MFC ClientDlg.h"


// ResultIDFND 대화 상자

IMPLEMENT_DYNAMIC(ResultIDFND, CDialogEx)

ResultIDFND::ResultIDFND(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

ResultIDFND::~ResultIDFND()
{
}

void ResultIDFND::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ResultIDFND, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ResultIDFND::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ResultIDFND::OnBnClickedButton2)
END_MESSAGE_MAP()


// ResultIDFND 메시지 처리기


BOOL ResultIDFND::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CFont font;

	font.CreateFont(16, 9, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, (LPCTSTR)"Arial");

#ifdef UNICODE
	USES_CONVERSION;
#endif

	CString toolTip;
	toolTip.Format(_T("%s 님의 이름으로 생성된 계정은 다음과 같습니다."), A2W(Player.NAME));
	GetDlgItem(IDNOTICE)->SetWindowText(toolTip);
	
	switch (FND_Player.Count)
	{
		case 1:
		{
			GetDlgItem(IDLIST1)->ShowWindow(TRUE);
			toolTip.Format(_T("%s"), A2W(FND_Player.ID1));
			GetDlgItem(IDLIST1)->SetWindowText(toolTip);
			break;
		}
		case 2:
		{
			GetDlgItem(IDLIST1)->ShowWindow(TRUE);
			GetDlgItem(IDLIST2)->ShowWindow(TRUE);
			toolTip.Format(_T("%s"), A2W(FND_Player.ID1));
			GetDlgItem(IDLIST1)->SetWindowText(toolTip);
			toolTip.Format(_T("%s"), A2W(FND_Player.ID2));
			GetDlgItem(IDLIST2)->SetWindowText(toolTip);
			break;
		}
		case 3:
		{
			GetDlgItem(IDLIST1)->ShowWindow(TRUE);
			GetDlgItem(IDLIST2)->ShowWindow(TRUE);
			GetDlgItem(IDLIST3)->ShowWindow(TRUE);
			toolTip.Format(_T("%s"), A2W(FND_Player.ID1));
			GetDlgItem(IDLIST1)->SetWindowText(toolTip);
			toolTip.Format(_T("%s"), A2W(FND_Player.ID2));
			GetDlgItem(IDLIST2)->SetWindowText(toolTip);
			toolTip.Format(_T("%s"), A2W(FND_Player.ID3));
			GetDlgItem(IDLIST3)->SetWindowText(toolTip);
			break;
		}
		default:
		{
			//GetDlgItem(IDLIST2)->ShowWindow(TRUE);
			toolTip.Format(_T("%s 님의 이름으로 생성된 계정이 존재하지 않습니다."), A2W(Player.NAME));
			GetDlgItem(IDNOTICE)->SetWindowTextW(toolTip);
			break;
		}
	}
	

	//GetDlgItem(IDNOTICE)->SetFont(&font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ResultIDFND::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	FoundAccount dlg;

	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

	dlg.DoModal();
}


void ResultIDFND::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMFCClientDlg dlg;

	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

	dlg.DoModal();
}
