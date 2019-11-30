#include "Main.h"
/*
int Login_Test(Player_Data Player, SOCKET s)
{
	
	char ID_Query[SIZE];
	//int retval;
	//int len;

	memset(ID_Query, 0x0, SIZE);

	snprintf(ID_Query,SIZE, "select pw from account_list where id ='%s'", Player.ID);

	MYSQL conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	mysql_init(&conn);
	mysql_set_character_set(&conn, "euckr");

	
	if (!mysql_real_connect(&conn, MYSQLHOST, MYSQLUSERID, MYSQLUSERPW, MYSQLDBNAME, 3306, (char *)NULL, 0))
	{
		const char * aaa = mysql_error(&conn);
		printf("%s\n", aaa);
		
		return DB_CONN_ERROR;
	}
	else 
	{
		mysql_real_query(&conn, ID_Query, strlen(ID_Query));
		printf("%s\n", mysql_error(&conn));
		cout << "!@$!@$!@" << endl;
	}
	mysql_close(&conn);

	return SUCCESS_LOGIN;
}*/