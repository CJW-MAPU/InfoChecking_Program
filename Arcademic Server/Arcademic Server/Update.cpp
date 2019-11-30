#include "Main.h"

int Update(Player_Data Player, SOCKET s)
{
	char Update_Query[SIZE];
	char Recv_Query[SIZE];

	sprintf(Update_Query, "update user_info set name='%s', email='%s', cellnum='%s' where id='%s'", Player.NAME, Player.EMAIL, Player.CELLNUM, Player.ID);
	sprintf(Recv_Query, "select name, email, cellnum from user_info where id='%s'", Player.ID);

	MYSQL conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	int retval;

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
		mysql_query(&conn, Update_Query);

		mysql_query(&conn, Recv_Query);

		res = mysql_store_result(&conn);

		if ((row = mysql_fetch_row(res)) != NULL)
		{
			Return_Player.Check = P_UPDAT;
			strcpy(Return_Player.ID, Player.ID);
			strcpy(Return_Player.NAME, row[0]);
			strcpy(Return_Player.EMAIL, row[1]);
			strcpy(Return_Player.CELLNUM, row[2]);

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

			return SUCCESS_UPDAT;
		}
		else
		{
			return DB_CONN_ERROR;
		}
	}
}