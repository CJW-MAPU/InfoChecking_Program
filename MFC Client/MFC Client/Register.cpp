// Register.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC Client.h"
#include "Register.h"
#include "afxdialogex.h"
#include "Main.h"

// Register 대화 상자

IMPLEMENT_DYNAMIC(Register, CDialogEx)

Register::Register(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, Register_ID(_T(""))
	, Register_PW(_T(""))
	, Register_PW2(_T(""))
	, Register_Name(_T(""))
	, Register_Email(_T(""))
	, Register_Cellnum(_T(""))
{

}

Register::~Register()
{
}

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Register_ID);
	DDX_Text(pDX, IDC_EDIT5, Register_PW);
	DDX_Text(pDX, IDC_EDIT6, Register_PW2);
	DDX_Text(pDX, IDC_EDIT7, Register_Name);
	DDX_Text(pDX, IDC_EDIT8, Register_Email);
	DDX_Text(pDX, IDC_EDIT9, Register_Cellnum);
}


BEGIN_MESSAGE_MAP(Register, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &Register::OnBnClickedButton2)	
	ON_BN_CLICKED(IDC_BUTTON3, &Register::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &Register::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT6, &Register::OnEnChangeEdit6)
END_MESSAGE_MAP()


// Register 메시지 처리기


void Register::OnBnClickedButton2() // confirm
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	USES_CONVERSION;

	int retval;
	Player_Data Send_Player;
	Player_Data Success_Check;

	memset(&Send_Player, 0x0, sizeof(Send_Player));
	memset(&Success_Check, 0x0, sizeof(Success_Check));

	std::regex email("[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*@[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*.[a-zA-Z]{2,3}");
	std::regex phone("[0-9]{3}-[0-9]{3,4}-[0-9]{4}");


	CString temp;
	char aaaa[SIZE] = "모든 정보를 입력해 주시기 바랍니다.";
	char bbbb[SIZE] = "두 개의 비밀번호가 일치하지 않습니다.";
	char cccc[SIZE] = "이메일 형식을 맞춰주세요.";
	char dddd[SIZE] = "전화번호 형식을 맞춰주세요.";
	char eeee[SIZE] = "회원가입이 완료되었습니다!";
	char ffff[SIZE] = "만들 수 있는 계정의 수가 가득찼습니다.\n기존 아이디를 찾아주세요.";
	char zzzz[SIZE] = "qweqwe";

	static char PW_hash1[SIZE / 5];
	static char PW_hash2[SIZE / 5];
	char temp11[SIZE];

	memset(PW_hash1, 0x0, sizeof(SIZE / 5));
	memset(PW_hash2, 0x0, sizeof(SIZE / 5));
	memset(temp11, 0x0, sizeof(SIZE));

	strcpy(temp11, (CStringA)Register_PW);
	strcat(temp11, (CStringA)Register_ID);

	sha256(temp11, PW_hash1);

	strcpy(temp11, (CStringA)Register_PW2);
	strcat(temp11, (CStringA)Register_ID);
	
	sha256(temp11, PW_hash2);

//	if (Success_Check.Check == O_CNTCK)
//	{
	if (strcmp((CStringA)Register_PW, "") == 0 || strcmp((CStringA)Register_PW2, "") == 0 || strcmp((CStringA)Register_Name, "") == 0 || strcmp((CStringA)Register_Email, "") == 0 || strcmp((CStringA)Register_Cellnum, "") == 0)
	{
		temp = aaaa;

		AfxMessageBox(temp);

//		closesocket(s);
//		WSACleanup();
	}
	else
	{
		if (stricmp(PW_hash1, PW_hash2) == 0) // 비밀번호 일치 ( 코드 작성 )
		{
			if (std::regex_match(W2A(Register_Email), email) != false)
			{
				if (std::regex_match(W2A(Register_Cellnum), phone) != false)
				{
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

					Send_Player.Check = T_CNTCK;
					strcpy(Send_Player.ID, (CStringA)Register_ID);
					strcpy(Send_Player.PW, PW_hash1);
					strcpy(Send_Player.NAME, (CStringA)Register_Name);
					strcpy(Send_Player.EMAIL, (CStringA)Register_Email);
					strcpy(Send_Player.CELLNUM, (CStringA)Register_Cellnum);

					//--------------------------------- Encrypt
					unsigned char AES_Key[128 / 8];
					ZeroMemory(AES_Key, 128 / 8);

					Create_AES_KEY(AES_Key);

					unsigned char ENC_IV[AES_BLOCK_SIZE], DEC_IV[AES_BLOCK_SIZE];
					ZeroMemory(ENC_IV, AES_BLOCK_SIZE);
					ZeroMemory(DEC_IV, AES_BLOCK_SIZE);

					Create_AES_IV(ENC_IV, DEC_IV);

					unsigned char Enc_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];
					unsigned char Dec_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

					AES_Encrypt(Send_Player, Enc_OUT, ENC_IV, AES_Key);

					ENC_Data Data;
					memset(&Data, 0x0, sizeof(ENC_Data));

					memcpy(Data.ENC, Enc_OUT, (sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1);
					memcpy(Data.IV, DEC_IV, AES_BLOCK_SIZE);
					memcpy(Data.KEY, AES_Key, 128 / 8);

					retval = send(s, (char *)&Data, sizeof(ENC_Data), 0);
					//---------------------------------

					//--------------------------------- Decrypt
					memcpy(&Data, recv_Player(s), sizeof(ENC_Data));

					AES_Decrypt(Data.ENC, Dec_OUT, Data.IV, Data.KEY);

					memcpy(&Success_Check, Dec_OUT, sizeof(Player_Data));
					//---------------------------------

					if (Success_Check.Check == O_CNTCK)
					{
						temp = eeee;
						AfxMessageBox(temp);

						::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

						closesocket(s);
						WSACleanup();
					}
					else
					{
						temp = ffff;

						AfxMessageBox(temp);

		     			closesocket(s);
						WSACleanup();
					}

//					closesocket(s);
//					WSACleanup();
				}
				else
				{
					temp = dddd;
					AfxMessageBox(temp);

//					closesocket(s);
//					WSACleanup();
				}
			}
			else
			{
				temp = cccc;
				AfxMessageBox(temp);

//				closesocket(s);
//				WSACleanup();
			}
		}
		else // 비밀번호 다름
		{
			temp = bbbb;

			AfxMessageBox(temp);

//			closesocket(s);
//			WSACleanup();
		}
	}
/*	}
	else
	{
		temp = ffff;
		
		AfxMessageBox(temp);

		closesocket(s);
		WSACleanup();
	}*/
}


void Register::OnBnClickedButton3() // 중복 확인
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	UpdateData(TRUE);

	// GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);

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

	Player_Data Send_Player;


	Player_Data Success_Check;
	int retval;
	int len;

	memset(&Send_Player, 0x0, sizeof(Send_Player));


	Send_Player.Check = T_OVLAP;
	strcpy(Send_Player.ID, (CStringA)Register_ID);

	
	char aaaa[SIZE] = "사용이 가능한 ID입니다.";
	char bbbb[SIZE] = "이미 사용중인 ID입니다.";
	char cccc[SIZE] = "수신 오류";
	char dddd[SIZE] = "ID를 입력해주세요.";

	CString temp;

	if (strcmp((CStringA)Register_ID, "") == 0)
	{
		temp = dddd;

		AfxMessageBox(temp);
	}
	else
	{
		//--------------------------------- Encrypt
		unsigned char AES_Key[128 / 8];
		ZeroMemory(AES_Key, 128 / 8);

		Create_AES_KEY(AES_Key);

		unsigned char ENC_IV[AES_BLOCK_SIZE], DEC_IV[AES_BLOCK_SIZE];
		ZeroMemory(ENC_IV, AES_BLOCK_SIZE);
		ZeroMemory(DEC_IV, AES_BLOCK_SIZE);

		Create_AES_IV(ENC_IV, DEC_IV);

		unsigned char Enc_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];
		unsigned char Dec_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

		AES_Encrypt(Send_Player, Enc_OUT, ENC_IV, AES_Key);

		ENC_Data Data;
		memset(&Data, 0x0, sizeof(ENC_Data));

		memcpy(Data.ENC, Enc_OUT, (sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1);
		memcpy(Data.IV, DEC_IV, AES_BLOCK_SIZE);
		memcpy(Data.KEY, AES_Key, 128 / 8);

		retval = send(s, (char *)&Data, sizeof(ENC_Data), 0);
		//---------------------------------

		//--------------------------------- Decrypt
		memcpy(&Data, recv_Player(s), sizeof(ENC_Data));

		AES_Decrypt(Data.ENC, Dec_OUT, Data.IV, Data.KEY);

		memcpy(&Success_Check, Dec_OUT, sizeof(Player_Data));
		//---------------------------------

		

		if (Success_Check.Check == X_OVLAP) // 중복 없음
		{
			temp = aaaa;
			AfxMessageBox(temp);

			GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);

			closesocket(s);
			WSACleanup();
		}
		else if (Success_Check.Check == O_OVLAP) // 중복 있음
		{
			temp = bbbb;
			AfxMessageBox(temp);

			Register_ID = "";

			UpdateData(FALSE);

			closesocket(s);
			WSACleanup();
		}
		else
		{
			temp = cccc;
			AfxMessageBox(temp);

			closesocket(s);
			WSACleanup();
		}
	}
}


void Register::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}


void Register::OnEnChangeEdit6()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Register::OnLbnSelchangeList2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Register::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


