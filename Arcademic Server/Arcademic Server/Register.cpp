#include "Main.h"

int Register(Player_Data Player, SOCKET s)
{
	char count[SIZE];
	char account_Query[SIZE];
	char user_Query[SIZE];

	int account_count = 0;
	int user_count = 0;

	MYSQL conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	//int retval;

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
		sprintf(count, "select * from account_list");
		
		mysql_query(&conn, count);
		res = mysql_store_result(&conn);

		while ((row = mysql_fetch_row(res)) != NULL)
		{
			account_count++;
		}

		sprintf(count, "select * from user_info");

		mysql_query(&conn, count);
		res = mysql_store_result(&conn);

		while ((row = mysql_fetch_row(res)) != NULL)
		{
			user_count++;
		}

		sprintf(account_Query, "insert into account_list (number, id, pw) values (%d, '%s', '%s')", account_count + 1, Player.ID, Player.PW);
		sprintf(user_Query, "insert into user_info (number, id, name, email, cellnum) values (%d, '%s', '%s', '%s', '%s')", user_count + 1, Player.ID, Player.NAME, Player.EMAIL, Player.CELLNUM);

		mysql_query(&conn, account_Query);
		
		mysql_query(&conn, user_Query);

		return SUCCESS_REGIT;
	}
}