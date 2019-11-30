#include "Main.h"

void AES_Encrypt(IN Player_Data Player, OUT unsigned char* Enc_OUT, unsigned char* ENC_IV, unsigned char* Aes_KEY)
{
	AES_KEY Enc_KEY;

	AES_set_encrypt_key(Aes_KEY, 128, &Enc_KEY);

	AES_cbc_encrypt((unsigned char *)&Player, Enc_OUT, sizeof(Player_Data), &Enc_KEY, ENC_IV, AES_ENCRYPT);
}

void AES_Encrypt(IN Found_IDList Player, OUT unsigned char* Enc_OUT, unsigned char* ENC_IV, unsigned char* Aes_KEY)
{
	AES_KEY Enc_KEY;

	AES_set_encrypt_key(Aes_KEY, 128, &Enc_KEY);

	AES_cbc_encrypt((unsigned char *)&Player, Enc_OUT, sizeof(Player_Data), &Enc_KEY, ENC_IV, AES_ENCRYPT);
}