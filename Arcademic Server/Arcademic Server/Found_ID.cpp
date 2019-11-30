#include "Main.h"

int Found_ID(Player_Data Player, SOCKET s)
{
	char Query[SIZE]; 

	int retval;
	int count = 0;
	int len;

	Found_IDList IDList;
	
	memset(&IDList, 0x0, sizeof(Found_IDList));

	sprintf(Query, "select id from user_info where name='%s' and cellnum='%s' order by number asc", Player.NAME, Player.CELLNUM);

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
		len = mysql_real_query(&conn, Query, strlen(Query));

		res = mysql_store_result(&conn);

		while ((row = mysql_fetch_row(res)) != NULL)
		{
			count++;

			switch (count)
			{
				case 1:
				{
					strcpy(IDList.ID1, row[0]);
					IDList.Count = count;
					IDList.Check = O_FNDID;
					break;
				}
				case 2:
				{
					strcpy(IDList.ID2, row[0]);
					IDList.Count = count;
					break;
				}
				case 3:
				{
					strcpy(IDList.ID3, row[0]);
					IDList.Count = count;
					break;
				}
				default:
				{
					IDList.Check = X_FNDID;
					break;
				}
			}
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

		AES_Encrypt(IDList, Enc_OUT, ENC_IV, AES_Key);

		ENC_Data Data;
		memset(&Data, 0x0, sizeof(ENC_Data));

		memcpy(Data.ENC, Enc_OUT, (sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1);
		memcpy(Data.IV, DEC_IV, AES_BLOCK_SIZE);
		memcpy(Data.KEY, AES_Key, 128 / 8);

		retval = send(s, (char *)&Data, sizeof(ENC_Data), 0);
		//---------------------------------

		return SUCCESS_FNDID;
	}
}