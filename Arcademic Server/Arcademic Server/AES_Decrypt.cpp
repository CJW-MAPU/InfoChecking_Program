#include "Main.h"

void AES_Decrypt(IN unsigned char* Enc_OUT, OUT unsigned char* Player, unsigned char* DEC_IV, unsigned char* Aes_KEY)
{
	AES_KEY Dec_KEY;
	
	AES_set_decrypt_key(Aes_KEY, 128, &Dec_KEY);

	AES_cbc_encrypt(Enc_OUT, Player, (sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1, &Dec_KEY, DEC_IV, AES_DECRYPT);
}
