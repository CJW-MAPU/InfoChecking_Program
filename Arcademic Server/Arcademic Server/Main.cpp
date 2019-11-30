#include "Main.h"

int Initial_Value = 1;

int main(void)
{
	
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKADDR_IN servAddr, cliAddr;

	char buf[SIZE];
	char buf2[SIZE];

	unsigned char Dec_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

	int err;
	int db_return;

	ENC_Data Data;
	Player_Data Player;
	Change_Pw Player1;

	memset(buf, 0x0, SIZE);
	memset(buf2, 0x0, SIZE);
	memset(&Player, 0, sizeof(Player_Data));
	memset(&Player1, 0x0, sizeof(Change_Pw));
	memset(&Data, 0x0, sizeof(ENC_Data));

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0)
	{
		cout << "WSAStartup error " << WSAGetLastError() << endl;
		WSACleanup();
			
		return 0;
	}

	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(SERVER_PORT);
	servAddr.sin_addr.s_addr = inet_addr(IPAddress);

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET)
	{
		cout << "Socket error " << WSAGetLastError() << endl;
		WSACleanup();

		return 0;
	}

	int x = bind(s, reinterpret_cast<SOCKADDR *>(&servAddr), sizeof(servAddr));

	if (x == SOCKET_ERROR)
	{
		cout << "Binding failed. Error code : " << WSAGetLastError << endl;
		WSACleanup();

		return 0;
	}
	cout << "Waiting for client ... " << endl;

	while (1)
	{
		listen(s, 5);

		int xx = sizeof(cliAddr);

		SOCKET s2 = accept(s, reinterpret_cast <SOCKADDR *>(&cliAddr), &xx);

		if (Initial_Value == 0)
		{
			Initial_Value++;
			//memcpy(&Player1, recv_Player(s2), sizeof(Player_Data));
			//------------------------- Decrypt

			memcpy(&Data, recv_Player(s2), sizeof(ENC_Data));

			AES_Decrypt(Data.ENC, Dec_OUT, Data.IV, Data.KEY);

			memcpy(&Player1, Dec_OUT, sizeof(Dec_OUT));
			
			//------------------------- Decrypt

			cout << endl;
			cout << "──── Receive Data from Client ────" << endl;
			cout << "Check   Number  : " << Player1.Check << endl;
			cout << "Player  ID      : " << Player1.ID << endl;
			cout << "Player  PW1     : " << Player1.PW1<< endl;
			cout << "Player  PW2     : " << Player1.PW2 << endl;
			cout << "──────────────────────────────────" << endl;

			if (Player1.Check == T_CHGPW)
			{
				cout << endl << endl << endl << endl << endl << endl << "Starting Change PW Logic.." << endl;

				db_return = Change_PW(Player1, s2);

				cout << db_return << endl;
			}
			else
			{
				cout << "수신 오류" << endl;
			}

		}
		else if (Initial_Value >= 1)
		{
			Initial_Value++;
			//memcpy(&Player, recv_Player(s2), sizeof(Player_Data));
			//------------------------- Decrypt
			
			memcpy(&Data, recv_Player(s2), sizeof(ENC_Data));

			AES_Decrypt(Data.ENC, Dec_OUT, Data.IV, Data.KEY);

			memcpy(&Player, Dec_OUT, sizeof(Player_Data));
			
			//------------------------- Decrypt

			cout << endl;
			cout << "──── Receive Data from Client ────" << endl;
			cout << "Check   Number  : " << Player.Check << endl;
			cout << "Player  ID      : " << Player.ID << endl;
			cout << "Player  PW      : " << Player.PW << endl;
			cout << "Player  Name    : " << Player.NAME << endl;
			cout << "Player  E MAIL  : " << Player.EMAIL << endl;
			cout << "Player  CellNum : " << Player.CELLNUM << endl;
			cout << "──────────────────────────────────" << endl;

			if (Player.Check == T_LOGIN)
			{

				cout << endl << endl << endl << endl << endl << endl << "Starting Login Logic.." << endl;

				db_return = Login_Check(Player, s2);

				cout << db_return << endl;

			}
			else if (Player.Check == T_UPDAT)
			{

				cout << endl << endl << endl << endl << endl << endl << "Starting Update Logic.." << endl;

				db_return = Update(Player, s2);

				cout << db_return << endl;

			}
			else if (Player.Check == T_OVLAP)
			{

				cout << endl << endl << endl << endl << endl << endl << "Starting Check Overlap Logic.." << endl;

				db_return = Overlap_Check(Player, s2);

				cout << db_return << endl;


			}
			else if (Player.Check == T_CNTCK)
			{

				cout << endl << endl << endl << endl << endl << endl << "Starting Count Check Logic.." << endl;

				db_return = Count_Check(Player, s2);

				cout << db_return << endl;

			}
			else if (Player.Check == T_FNDID)
			{

				cout << endl << endl << endl << endl << endl << endl << "Starting Found ID Logic.." << endl;

				db_return = Found_ID(Player, s2);

				cout << db_return << endl;

			}
			else if (Player.Check == T_CHKPW)
			{

				cout << endl << endl << endl << endl << endl << endl << "Starting Check ID List Logic.." << endl;

				db_return = Found_PW(Player, s2);

				cout << db_return << endl;

			}
			else
			{
				cout << "수신 오류" << endl;
			}
		}
		else
		{
		}

	}

	getchar();
	getchar();
	getchar();

	closesocket(s);
	WSACleanup();

	return 0;
}


//#include "Main.h"
/*
int main()
{
	//size_t Enc_OUT_Size = ;

	unsigned char Enc_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];
	unsigned char Dec_OUT[sizeof(Player_Data) * 2 + 1];

	Player_Data Player;
	memset(&Player, 0x0, sizeof(Player_Data));


	Player.Check = 1;
	strcpy(Player.ID, "ID");
	strcpy(Player.PW, "PW");
	strcpy(Player.NAME, "NAME");
	strcpy(Player.EMAIL, "EMAIL");
	strcpy(Player.CELLNUM, "CELLNUM");

	cout << Player.Check << endl;
	cout << Player.ID << endl;
	cout << Player.PW << endl;
	cout << Player.NAME << endl;
	cout << Player.EMAIL << endl;
	cout << Player.CELLNUM << endl << endl << endl;

	unsigned char AES_Key[128 / 8];
	ZeroMemory(AES_Key, 128 / 8);

	Create_AES_KEY(AES_Key);

	unsigned char ENC_IV[AES_BLOCK_SIZE], DEC_IV[AES_BLOCK_SIZE];
	ZeroMemory(ENC_IV, AES_BLOCK_SIZE);
	ZeroMemory(DEC_IV, AES_BLOCK_SIZE);	

	Create_AES_IV(ENC_IV, DEC_IV);

	AES_Encrypt(Player, Enc_OUT, ENC_IV, AES_Key);

	AES_Decrypt(Enc_OUT, Dec_OUT, DEC_IV, AES_Key);


	Player_Data Out;
	memset(&Out, 0x0, sizeof(Player_Data));

	//memcpy(&Out, Dec_OUT, sizeof(Player_Data));

	//Out = (Player_Data&)*Dec_OUT;
	memcpy(&Out, Dec_OUT, sizeof(Dec_OUT));

	cout << Out.NAME << endl;
	cout << Out.EMAIL << endl;

	getchar();
	getchar();
}
*/