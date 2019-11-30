
// MFC ClientDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC Client.h"
#include "MFC ClientDlg.h"
#include "afxdialogex.h"
#include "SuccessLogin.h"
#include "CheckingInfo.h"
#include "Main.h"
#include "Register.h"
#include "FoundAccount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCClientDlg 대화 상자



CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
	, Login_ID(_T(""))
	, Login_PW(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, Login_ID);
	DDX_Text(pDX, IDC_EDIT3, Login_PW);
	DDV_MaxChars(pDX, Login_PW, 20);
}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCClientDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCClientDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCClientDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCClientDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCClientDlg 메시지 처리기

BOOL CMFCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCClientDlg::OnBnClickedButton2() // Register
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	Register dlg;

	dlg.DoModal();
}

void CMFCClientDlg::OnBnClickedButton1() // Login
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// CheckingInfo dlg1;
	SuccessLogin dlg2;

	// dlg1.DoModal();
	// dlg2.DoModal();


	UpdateData(TRUE);

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

	Player_Data Player;
	Player_Data Success_Login;

	static char buffer[SIZE / 5];
	char temp11[SIZE];
	unsigned char Dec_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

	memset(&Player, 0x0, sizeof(Player));
	memset(buffer, 0x0, sizeof(SIZE / 5));
	memset(temp11, 0x0, sizeof(SIZE));
	memset(&Success_Login, 0x0, sizeof(Player_Data));

	strcpy(temp11, (CStringA)Login_PW);
	strcat(temp11, (CStringA)Login_ID);

	sha256(temp11, buffer);

	Player.Check = T_LOGIN;
	strcpy(Player.ID, (CStringA)Login_ID);
	strcpy(Player.PW, buffer);

	//----------------------------- Encrypt
	
	unsigned char AES_Key[128 / 8];
	ZeroMemory(AES_Key, 128 / 8);

	Create_AES_KEY(AES_Key);

	unsigned char ENC_IV[AES_BLOCK_SIZE], DEC_IV[AES_BLOCK_SIZE];
	ZeroMemory(ENC_IV, AES_BLOCK_SIZE);
	ZeroMemory(DEC_IV, AES_BLOCK_SIZE);

	Create_AES_IV(ENC_IV, DEC_IV);

	unsigned char Enc_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

	AES_Encrypt(Player, Enc_OUT, ENC_IV, AES_Key);

	ENC_Data Data;
	memset(&Data, 0x0, sizeof(ENC_Data));

	memcpy(Data.ENC, Enc_OUT, (sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1);
	memcpy(Data.IV, DEC_IV, AES_BLOCK_SIZE);
	memcpy(Data.KEY, AES_Key, 128 / 8);
	
	//------------------------------




	int retval;
	
	retval = send(s, (char *)&Data, sizeof(ENC_Data), 0);
	//retval = send(s, (char *)&Player, sizeof(Player_Data), 0);

	memset(&Data, 0x0, sizeof(ENC_Data));

	std::this_thread::sleep_for(std::chrono::seconds(1));

	//memcpy(&Success_Login, recv_Player(s), sizeof(Player_Data));



	
	//------------------------------- Decrypt
	
	memcpy(&Data, recv_Player(s), sizeof(ENC_Data));

	AES_Decrypt(Data.ENC, Dec_OUT, Data.IV, Data.KEY);

	memcpy(&Success_Login, Dec_OUT, sizeof(Player_Data));

	//-------------------------------


	CString temp;
	char aaaa[SIZE] = "로그인이 성공적으로 진행되었습니다!";
	char bbbb[SIZE] = "아이디 혹은 비밀번호가 잘못되었습니다!";
	

	if (Success_Login.Check == SUCCESS_LOGIN)
	{
		temp = aaaa;
		AfxMessageBox(temp);

		::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

		dlg2.Player__ = Success_Login;

		closesocket(s);
		WSACleanup();

		dlg2.DoModal();
	}
	else if (Success_Login.Check == WRONGID || Success_Login.Check == WRONGPW)
	{
		temp = bbbb;
		AfxMessageBox(temp);

		closesocket(s);
		WSACleanup();
	}
}


void CMFCClientDlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCClientDlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCClientDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	FoundAccount dlg;

	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);

	dlg.DoModal();

	
}

