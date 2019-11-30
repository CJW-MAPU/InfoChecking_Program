#include "Main.h"

int Login_Check(Player_Data Player, SOCKET s)
{
	char ID_Query[SIZE];
	char RecvData_Query[SIZE];
	int retval;
	Player_Data Return_Player;

	memset(ID_Query, 0x0, SIZE);
	memset(&Return_Player, 0x0, sizeof(Player_Data));

	sprintf(ID_Query, "select pw from account_list where id='%s'", Player.ID);
	sprintf(RecvData_Query, "select * from user_info where id='%s'", Player.ID);

	int len;
	int struct_len;

	MYSQL conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	mysql_init(&conn);
	mysql_set_character_set(&conn, "euckr");

	//if (!mysql_real_connect(&conn, MYSQLHOST, MYSQLUSERID, MYSQLUSERPW, MYSQLDBNAME, 3308, (char *)NULL, 0))
	if (!mysql_real_connect(&conn, MYSQLHOST, MYSQLUSERID, MYSQLUSERPW, MYSQLDBNAME, 3306, (char *)NULL, 0))
	{
		const char * aaa = mysql_error(&conn);
		printf("%s\n", aaa);

		return DB_CONN_ERROR;
	}
	else
	{
		len = mysql_real_query(&conn, ID_Query, strlen(ID_Query));
		res = mysql_store_result(&conn);

		row = mysql_fetch_row(res);

		if (row == NULL)
		{
			
			mysql_free_result(res);
			mysql_close(&conn);

			// 존재하지 않는 아이디

			Return_Player.Check = WRONGID;
			
			unsigned char AES_Key[128 / 8];
			ZeroMemory(AES_Key, 128 / 8);

			Create_AES_KEY(AES_Key);

			unsigned char ENC_IV[AES_BLOCK_SIZE], DEC_IV[AES_BLOCK_SIZE];
			ZeroMemory(ENC_IV, AES_BLOCK_SIZE);
			ZeroMemory(DEC_IV, AES_BLOCK_SIZE);

			Create_AES_IV(ENC_IV, DEC_IV);

			unsigned char Enc_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

			AES_Encrypt(Return_Player, Enc_OUT, ENC_IV, AES_Key);

			ENC_Data Data;
			memset(&Data, 0x0, sizeof(ENC_Data));

			memcpy(Data.ENC, Enc_OUT, (sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1);
			memcpy(Data.IV, DEC_IV, AES_BLOCK_SIZE);
			memcpy(Data.KEY, AES_Key, 128 / 8);

			retval = send(s, (char *)&Data, sizeof(ENC_Data), 0);

			return WRONGID;
		}

		if (strcmp(row[0], Player.PW) == 0)
		{
			/*
				Client에 P_LOGIN 전송
			*/
			cout << endl << endl << "Send SUCCESS_LOGIN(1003) to Client " << endl << endl << endl;
			struct_len = sizeof(Return_Player);

			mysql_real_query(&conn, RecvData_Query, strlen(RecvData_Query));

			res = mysql_store_result(&conn);

			row = mysql_fetch_row(res);

			if (row == NULL)
			{
				mysql_free_result(res);
				mysql_close(&conn);

				return DB_READ_ERROR;
			}
			
			Return_Player.Check = SUCCESS_LOGIN;
			strcpy(Return_Player.ID, Player.ID);
			strcpy(Return_Player.NAME, row[2]);
			strcpy(Return_Player.EMAIL, row[3]);
			strcpy(Return_Player.CELLNUM, row[4]);

			unsigned char AES_Key[128 / 8];
			ZeroMemory(AES_Key, 128 / 8);

			Create_AES_KEY(AES_Key);

			unsigned char ENC_IV[AES_BLOCK_SIZE], DEC_IV[AES_BLOCK_SIZE];
			ZeroMemory(ENC_IV, AES_BLOCK_SIZE);
			ZeroMemory(DEC_IV, AES_BLOCK_SIZE);

			Create_AES_IV(ENC_IV, DEC_IV);

			unsigned char Enc_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

			AES_Encrypt(Return_Player, Enc_OUT, ENC_IV, AES_Key);

			ENC_Data Data;
			memset(&Data, 0x0, sizeof(ENC_Data));

			memcpy(Data.ENC, Enc_OUT, (sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1);
			memcpy(Data.IV, DEC_IV, AES_BLOCK_SIZE);
			memcpy(Data.KEY, AES_Key, 128 / 8);

			retval = send(s, (char *)&Data, sizeof(ENC_Data), 0);
		}
		else
		{
			//free(ID_Query);
			mysql_free_result(res);
			mysql_close(&conn);

			// 잘못된 비밀번호

			Return_Player.Check = WRONGPW;

			unsigned char AES_Key[128 / 8];
			ZeroMemory(AES_Key, 128 / 8);

			Create_AES_KEY(AES_Key);

			unsigned char ENC_IV[AES_BLOCK_SIZE], DEC_IV[AES_BLOCK_SIZE];
			ZeroMemory(ENC_IV, AES_BLOCK_SIZE);
			ZeroMemory(DEC_IV, AES_BLOCK_SIZE);

			Create_AES_IV(ENC_IV, DEC_IV);

			unsigned char Enc_OUT[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];

			AES_Encrypt(Return_Player, Enc_OUT, ENC_IV, AES_Key);

			ENC_Data Data;
			memset(&Data, 0x0, sizeof(ENC_Data));

			memcpy(Data.ENC, Enc_OUT, (sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1);
			memcpy(Data.IV, DEC_IV, AES_BLOCK_SIZE);
			memcpy(Data.KEY, AES_Key, 128 / 8);

			retval = send(s, (char *)&Data, sizeof(ENC_Data), 0);

			return WRONGPW;
		}
	}

	mysql_free_result(res);
	mysql_close(&conn);
	return SUCCESS_LOGIN;
}