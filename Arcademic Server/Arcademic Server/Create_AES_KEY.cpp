#include "Main.h"

void Create_AES_KEY(unsigned char AES_Key[128 / 8])
{	
	memset(AES_Key, 0x0, 128 / 8);

	RAND_bytes(AES_Key, 128 / 8);
}
