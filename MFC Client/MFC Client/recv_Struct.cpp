#include "Main.h"

ENC_Data* recv_Player(SOCKET s)
{
	int len;

	int GetSize;
	char suBuffer[sizeof(ENC_Data) + 1];
	memset(suBuffer, 0x0, SIZE);

	ENC_Data *Data;

	GetSize = recv(s, suBuffer, sizeof(ENC_Data), 0);

	Data = (ENC_Data *)suBuffer;

	return Data;
}