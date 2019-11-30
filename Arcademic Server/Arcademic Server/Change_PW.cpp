#include "Main.h"

int Change_PW(Change_Pw Player, SOCKET s)
{
	char Query[SIZE]; //update account_list set pw='' where id=''

	int retval;
	//int len;

	Player_Data Send_Player;

	memset(&Send_Player, 0x0, sizeof(Player_Data));

	sprintf(Query, "update account_list set pw='%s' where id='%s'", Player.PW1, Player.ID);

	MYSQL conn;
	//MYSQL_RES* res;
	//MYSQL_ROW row;

	Player_Data Return_Player;

	memset(&Return_Player, 0x0, sizeof(Player_Data));
	
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
		mysql_query(&conn, Query);

		Return_Player.Check = O_CHGPW;

		//--------------------------------- Encrypt
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
		//---------------------------------

		return SUCCESS_CHGPW;
	}
}