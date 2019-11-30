// CheckingInfo.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC Client.h"
#include "CheckingInfo.h"
#include "afxdialogex.h"
#include "Main.h"


// CheckingInfo 대화 상자

IMPLEMENT_DYNAMIC(CheckingInfo, CDialogEx)

CheckingInfo::CheckingInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, Info_Name(_T(""))
	, Info_Email(_T(""))
	, Info_CellNum(_T(""))
{

}

CheckingInfo::~CheckingInfo()
{
}

void CheckingInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, Info_Name);
	DDX_Text(pDX, IDC_EDIT4, Info_Email);
	DDX_Text(pDX, IDC_EDIT5, Info_CellNum);
}


BEGIN_MESSAGE_MAP(CheckingInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CheckingInfo::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT3, &CheckingInfo::OnEnChangeEdit3)
	ON_STN_CLICKED(INFOTEXT, &CheckingInfo::OnStnClickedInfotext)
	ON_BN_CLICKED(IDC_BUTTON2, &CheckingInfo::OnBnClickedButton2)
END_MESSAGE_MAP()


// CheckingInfo 메시지 처리기


void CheckingInfo::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Player_Data Send_Player;

#ifdef UNICODE
	USES_CONVERSION;
#endif

	char aaaa[SIZE] = "오류";
	char bbbb[SIZE] = "정보 수정이 완료되었습니다!";
	char cccc[SIZE] = "정보 수정이 실패하였습니다!";
	char dddd[SIZE] = "모든 정보를 입력해 주시기 바랍니다.";
	char eeee[SIZE] = "이메일 형식을 맞춰주세요.";
	char ffff[SIZE] = "전화번호 형식을 맞춰주세요.";
	CString temp;

	std::regex email("[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*@[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*.[a-zA-Z]{2,3}");
	std::regex phone("[0-9]{3}-[0-9]{3,4}-[0-9]{4}");


	memset(&Send_Player, 0x0, sizeof(Send_Player));

	int retval;
	unsigned char Dec_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

	if (Update_Count == 0)
	{
		GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);

		Update_Count = 1;
	}
	else if (Update_Count == 1)
	{
		UpdateData(TRUE);

		if (strcmp((CStringA)Info_Name, "") == 0 || strcmp((CStringA)Info_Email, "") == 0 || strcmp((CStringA)Info_CellNum, "") == 0)
		{
			temp = dddd;
			AfxMessageBox(temp);
		}
		else
		{
			if (std::regex_match(W2A(Info_Email), email) != false)
			{
				if (std::regex_match(W2A(Info_CellNum), phone) != false)
				{
					Send_Player.Check = T_UPDAT;
					strcpy(Send_Player.ID, Player.ID);
					strcpy(Send_Player.NAME, (CStringA)Info_Name);
					strcpy(Send_Player.EMAIL, (CStringA)Info_Email);
					strcpy(Send_Player.CELLNUM, (CStringA)Info_CellNum);

					WORD wVersionRequested;
					WSADATA wsaData;
					SOCKADDR_IN target;
					SOCKET s;

					int err;

					wVersionRequested = MAKEWORD(1, 1);
					err = WSAStartup(wVersionRequested, &wsaData);

					if (err != 0)
					{
						cout << "WSAStartup error: " << WSAGetLastError() << endl;
						WSACleanup();
						return;
					}

					target.sin_family = AF_INET;
					target.sin_port = htons(SERVER_PORT);
					target.sin_addr.s_addr = inet_addr(IPAddress);

					s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

					if (s == INVALID_SOCKET)
					{
						cout << "socket()error : " << WSAGetLastError() << endl;
						WSACleanup();
						return;
					}

					if (connect(s, reinterpret_cast<SOCKADDR *>(&target), sizeof(target)) == SOCKET_ERROR)
					{
						cout << "connect() error : " << WSAGetLastError() << endl;
						cout << "서버 먼저 실행해주세요." << endl;
						WSACleanup();
						return;
					}

					//------------------------------- Encrypt
					unsigned char AES_Key[128 / 8];
					ZeroMemory(AES_Key, 128 / 8);

					Create_AES_KEY(AES_Key);

					unsigned char ENC_IV[AES_BLOCK_SIZE], DEC_IV[AES_BLOCK_SIZE];
					ZeroMemory(ENC_IV, AES_BLOCK_SIZE);
					ZeroMemory(DEC_IV, AES_BLOCK_SIZE);

					Create_AES_IV(ENC_IV, DEC_IV);

					unsigned char Enc_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

					AES_Encrypt(Send_Player, Enc_OUT, ENC_IV, AES_Key);

					ENC_Data Data;
					memset(&Data, 0x0, sizeof(ENC_Data));

					memcpy(Data.ENC, Enc_OUT, (sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1);
					memcpy(Data.IV, DEC_IV, AES_BLOCK_SIZE);
					memcpy(Data.KEY, AES_Key, 128 / 8);

					retval = send(s, (char *)&Data, sizeof(ENC_Data), 0);

					memset(&Data, 0x0, sizeof(ENC_Data));
					//-------------------------------

					//------------------------------- Decrypt
					memcpy(&Data, recv_Player(s), sizeof(ENC_Data));
					
					AES_Decrypt(Data.ENC, Dec_OUT, Data.IV, Data.KEY);

					memcpy(&Player, Dec_OUT, sizeof(Player_Data));
					//-------------------------------

					if (Player.Check == P_UPDAT)
					{
						CString toolTip;

						toolTip.Format(_T("%s (%s) 님 정보"), A2W(Player.ID), A2W(Player.NAME));
						GetDlgItem(INFOTEXT)->SetWindowText(toolTip);

						closesocket(s);
						WSACleanup();

						GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
						GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
						GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);

						Update_Count = 0;
					}
					else
					{
						temp = cccc;

						AfxMessageBox(temp);

						closesocket(s);
						WSACleanup();
					}
				}
				else
				{
					temp = ffff;
					AfxMessageBox(temp);
				}
				
			}
			else
			{
				temp = eeee;
				AfxMessageBox(temp);
			}
		}
	}
	else
	{
		temp = aaaa;
		AfxMessageBox(temp);
	}
}


void CheckingInfo::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CheckingInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

#ifdef UNICODE
	USES_CONVERSION;
#endif
	
	
	CEdit *pEdit;
	CString toolTip;
	toolTip.Format(_T("%s (%s) 님 정보"), A2W(Player.ID), A2W(Player.NAME));
	GetDlgItem(INFOTEXT)->SetWindowText(toolTip);

	pEdit = (CEdit *)GetDlgItem(IDC_EDIT3);

	if (pEdit)
	{
		pEdit->SetWindowText((CString)Player.NAME);
	}

	pEdit = (CEdit *)GetDlgItem(IDC_EDIT4);

	if (pEdit)
	{
		pEdit->SetWindowText((CString)Player.EMAIL);
	}

	pEdit = (CEdit *)GetDlgItem(IDC_EDIT5);

	if (pEdit)
	{
		pEdit->SetWindowText((CString)Player.CELLNUM);
	}

	Update_Count = 0;
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CheckingInfo::OnStnClickedInfotext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CheckingInfo::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

}
