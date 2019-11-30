// FoundAccount.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC Client.h"
#include "FoundAccount.h"
#include "afxdialogex.h"
#include "Main.h"
#include "ResultIDFND.h"
#include "ResultPWFND.h"



// FoundAccount 대화 상자

IMPLEMENT_DYNAMIC(FoundAccount, CDialogEx)

FoundAccount::FoundAccount(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, FNDID_Name(_T(""))
	, FNDID_PN(_T(""))
	, FNDPW_Name(_T(""))
	, FNDPW_ID(_T(""))
{

}

FoundAccount::~FoundAccount()
{
}

void FoundAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, FNDID_Name);
	DDX_Text(pDX, IDC_EDIT5, FNDID_PN);
	DDX_Text(pDX, IDC_EDIT8, FNDPW_Name);
	DDX_Text(pDX, IDC_EDIT9, FNDPW_ID);
}


BEGIN_MESSAGE_MAP(FoundAccount, CDialogEx)
	ON_STN_CLICKED(FOUNDID2, &FoundAccount::OnStnClickedFoundid2)
	ON_BN_CLICKED(IDC_BUTTON2, &FoundAccount::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &FoundAccount::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON4, &FoundAccount::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT8, &FoundAccount::OnEnChangeEdit8)
END_MESSAGE_MAP()


// FoundAccount 메시지 처리기


BOOL FoundAccount::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CFont font;

	//font.CreateFont(16, 9, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, (LPCTSTR)"Arial");

	//GetDlgItem(FOUNDID)->SetFont(&font);
	//GetDlgItem(FOUNDID2)->SetFont(&font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

// IDC_EDIT1 = ID찾기 이름, IDC_EDIT5 = ID찾기 휴대폰번호
// IDC_EDIT8 = PW찾기 이름, IDC_EDIT9 = PW찾기 아이디

void FoundAccount::OnStnClickedFoundid2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void FoundAccount::OnBnClickedButton2() // ID 찾기 cummit
{	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	USES_CONVERSION;

	ResultIDFND dlg1;
	Player_Data FoundID;
	Found_IDList ReceiveIDData;
	Player_Data SendToDlg;

	int retval;

	std::regex phone("[0-9]{3}-[0-9]{3,4}-[0-9]{4}");

	CString temp;

	char aaaa[SIZE] = "모든 정보를 입력해 주시기 바랍니다.";
	char dddd[SIZE] = "전화번호 형식을 맞춰주세요.";

	memset(&FoundID, 0x0, sizeof(Player_Data));
	memset(&ReceiveIDData, 0x0, sizeof(Found_IDList));
	memset(&SendToDlg, 0x0, sizeof(Player_Data));

	UpdateData(TRUE);

	if (strcmp((CStringA)FNDID_Name, "") == 0 || strcmp((CStringA)FNDID_PN, "") == 0)
	{
		temp = aaaa;

		AfxMessageBox(temp);
	}
	else
	{
		if (std::regex_match(W2A(FNDID_PN), phone) != false)
		{
			FoundID.Check = T_FNDID;
			strcpy(FoundID.NAME, (CStringA)FNDID_Name);
			strcpy(FoundID.CELLNUM, (CStringA)FNDID_PN);
			strcpy(SendToDlg.NAME, (CStringA)FNDID_Name);

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

			AES_Encrypt(FoundID, Enc_OUT, ENC_IV, AES_Key);

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

			memcpy(&ReceiveIDData, Dec_OUT, sizeof(Player_Data));
			//---------------------------------



			memcpy(&dlg1.FND_Player, &ReceiveIDData, sizeof(Found_IDList));

			memcpy(&dlg1.Player, &SendToDlg, sizeof(Player_Data));

			closesocket(s);
			WSACleanup();

			::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

			dlg1.DoModal();
		}
		else
		{
			temp = dddd;

			AfxMessageBox(temp);
		}
	}
}


void FoundAccount::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void FoundAccount::OnBnClickedButton4() // FNDPW_Name, FNDPW_ID
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	USES_CONVERSION;

	UpdateData(TRUE);

	Player_Data Send_Player;
	Player_Data Receive_Player;

	ResultPWFND dlg;

	int retval;

	memset(&Send_Player, 0x0, sizeof(Player_Data));
	memset(&Receive_Player, 0x0, sizeof(Player_Data));

	CString temp;
	char aaaa[SIZE] = "모든 정보를 입력해 주시기 바랍니다.";
	char bbbb[SIZE] = "입력한 정보와 일치하는 정보가 존재하지 않습니다.";


	if (strcmp((CStringA)FNDPW_Name, "") == 0 || strcmp((CStringA)FNDPW_ID, "") == 0)
	{
		temp = aaaa;

		AfxMessageBox(temp);
	}
	else
	{
		Send_Player.Check = T_CHKPW;
		strcpy(Send_Player.NAME, (CStringA)FNDPW_Name);
		strcpy(Send_Player.ID, (CStringA)FNDPW_ID);

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

		memcpy(&Receive_Player, Dec_OUT, sizeof(Player_Data));
		//---------------------------------

		if (Receive_Player.Check == O_CHKPW)
		{
			strcpy(Receive_Player.ID, (CStringA)FNDPW_ID);
			
			memcpy(&dlg.Player, &Receive_Player, sizeof(Player_Data));

			::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

			dlg.DoModal();
		}
		else if (Receive_Player.Check == X_CHKPW)
		{
			temp = bbbb;

			AfxMessageBox(temp);
		}
		else
		{
		}
	}
}


void FoundAccount::OnEnChangeEdit8()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
