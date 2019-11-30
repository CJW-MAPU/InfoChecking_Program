#ifndef SERVER_MAIN_H
#define SERVER_MAIN_H

#include "include.h"
#include "struct.h"
#include "define.h"


ENC_Data *recv_Player(SOCKET s);
int Login_Check(Player_Data Player, SOCKET s);
int Login_Test(Player_Data Player, SOCKET s);
int Overlap_Check(Player_Data Player, SOCKET s);
int Register(Player_Data Player, SOCKET s);
int Update(Player_Data Player, SOCKET s);
int Count_Check(Player_Data Player, SOCKET s);
int Found_ID(Player_Data Player, SOCKET s);
int Found_PW(Player_Data Player, SOCKET s);
int Change_PW(Change_Pw Player, SOCKET s);
void sha256(char * string, char outputBuffer[SIZE / 5]);
void AES_Encrypt(IN Player_Data Player, OUT unsigned char* Enc_OUT, unsigned char* ENC_IV, unsigned char* Aes_KEY);
void AES_Encrypt(IN Found_IDList Player, OUT unsigned char* Enc_OUT, unsigned char* ENC_IV, unsigned char* Aes_KEY);
void AES_Decrypt(IN unsigned char* Enc_OUT, OUT unsigned char* Player, unsigned char* DEC_IV, unsigned char* Dec_KEY);
void Create_AES_KEY(unsigned char AES_Key[128 / 8]);
void Create_AES_IV(unsigned char ENC_IV[AES_BLOCK_SIZE], unsigned char DEC_IV[AES_BLOCK_SIZE]);

#endif