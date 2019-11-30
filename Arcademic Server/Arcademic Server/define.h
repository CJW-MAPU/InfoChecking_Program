#ifndef DEFINE_HEADER
#define DEFINE_HEADER

#define SERVER_PORT 11235
#define BUF_SIZE 4096
#define QUEUE_SIZE 10
#define IPAddress "127.0.0.1"
#define SIZE 10000
#define SMALLSIZE 200

#define MYSQLUSERID "arcademic"	
#define MYSQLUSERPW "root" // locs@1035
#define MYSQLHOST "127.0.0.1"			
#define MYSQLDBNAME "privacy_db"

#define DB_CONN_ERROR 50000
#define DB_READ_ERROR 50001

#define T_LOGIN 1000 // �α��� �õ�
#define WRONGID 1001 // �α��� ���
#define WRONGPW 1002
#define SUCCESS_LOGIN 1003

#define T_REGIT 2000 // ȸ������ �õ�
#define P_REGIT 2001 // ȸ������ ���
#define SUCCESS_REGIT 2003

#define T_UPDAT 3000 // ������Ʈ �õ�
#define P_UPDAT 3001 // ������Ʈ ���
#define SUCCESS_UPDAT 3003

#define T_OVLAP 4000 // �ߺ�Ȯ�� �õ�
#define X_OVLAP 4001 // �ߺ� X
#define O_OVLAP	4002 // �ߺ� O 
#define SUCCESS_CHECKING 4003 

#define T_CNTCK 5000 // �̸�, ����ȣ �� ���� ���� ���� �õ�
#define X_CNTCK 5001
#define O_CNTCK 5002
#define SUCCESS_CNTCK 5003

#define T_FNDID 6000 // IDã�� �õ�
#define X_FNDID 6001
#define O_FNDID 6002
#define SUCCESS_FNDID 6003

#define T_CHKPW 7000
#define X_CHKPW 7001
#define O_CHKPW 7002
#define SUCCESS_CHKPW 7003
#define NO_ID__CHKPW 7004

#define T_FNDPW 8000
#define X_FNDPW 8001
#define O_FNDPW 8002
#define SUCCESS_FNDPW 8003

#define T_CHGPW 9000
#define X_CHGPW 9001
#define O_CHGPW 9002
#define SUCCESS_CHGPW 9003

#define AES_BLOCK_SIZE 16

#endif