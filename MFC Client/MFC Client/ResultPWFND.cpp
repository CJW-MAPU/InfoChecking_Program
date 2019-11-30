// ResultPWFND.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC Client.h"
#include "ResultPWFND.h"
#include "afxdialogex.h"
#include "Main.h"
#include "MFC ClientDlg.h"


// ResultPWFND 대화 상자

IMPLEMENT_DYNAMIC(ResultPWFND, CDialogEx)

ResultPWFND::ResultPWFND(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, New_PW(_T(""))
	, Check_PW(_T(""))
{

}

ResultPWFND::~ResultPWFND()
{
}

void ResultPWFND::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, New_PW);
	DDX_Text(pDX, IDC_EDIT2, Check_PW);
}


BEGIN_MESSAGE_MAP(ResultPWFND, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ResultPWFND::OnBnClickedButton1)
END_MESSAGE_MAP()


// ResultPWFND 메시지 처리기


void ResultPWFND::OnBnClickedButton1() // New_PW, Check_PW
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	Change_PW Send_Player;
	Player_Data Receive_Player;
	CMFCClientDlg dlg;

	memset(&Send_Player, 0x0, sizeof(Change_PW));
	memset(&Receive_Player, 0x0, sizeof(Player_Data));
	
	int retval;

	CString temp;
	char aaaa[SIZE] = "모든 정보를 입력해 주시기 바랍니다.";
	char bbbb[SIZE] = "두 개의 비밀번호가 일치하지 않습니다.";
	char cccc[SIZE] = "비밀번호 변경이 완료되었습니다.";

	static char PW_hash1[SIZE / 5];
	static char PW_hash2[SIZE / 5];
	char temp11[SIZE];

	memset(PW_hash1, 0x0, sizeof(SIZE / 5));
	memset(PW_hash2, 0x0, sizeof(SIZE / 5));
	memset(temp11, 0x0, sizeof(SIZE));

	strcpy(temp11, (CStringA)New_PW);
	strcat(temp11, Player.ID);

	sha256(temp11, PW_hash1);

	strcpy(temp11, (CStringA)Check_PW);
	strcat(temp11, Player.ID);

	sha256(temp11, PW_hash2);
	

	if (strcmp((CStringA)New_PW, "") == 0 || strcmp((CStringA)Check_PW, "") == 0)
	{
		temp = aaaa;

		AfxMessageBox(temp);
	}
	else
	{
		if (stricmp(PW_hash1, PW_hash2) == 0)
		{
			Send_Player.Check = T_CHGPW;
			strcpy(Send_Player.ID, Player.ID);
			strcpy(Send_Player.PW1, PW_hash1);
			strcpy(Send_Player.PW2, PW_hash2);

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
			

			if (Receive_Player.Check == O_CHGPW)
			{
				temp = cccc;

				AfxMessageBox(temp);

				::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

				dlg.DoModal();
			}
			else
			{
			}

			closesocket(s);
			WSACleanup(); 
		}
		else
		{
			temp = bbbb;
			
			AfxMessageBox(temp);
		}
	}
}
