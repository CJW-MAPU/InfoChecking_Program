#include "Main.h"

void Create_AES_IV(unsigned char ENC_IV[AES_BLOCK_SIZE], unsigned char DEC_IV[AES_BLOCK_SIZE])
{
	RAND_bytes(ENC_IV, AES_BLOCK_SIZE);
	memcpy(DEC_IV, ENC_IV, AES_BLOCK_SIZE);
}