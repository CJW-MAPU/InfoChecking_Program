#ifndef STRUCT_HEADER
#define STRUCT_HEADER

#include "define.h"

#pragma pack(push,1)
typedef struct Player_Data {
	char ID[SIZE / 5 - sizeof(int)];
	char PW[SIZE / 5];
	char NAME[SIZE / 5];
	char EMAIL[SIZE / 5];
	char CELLNUM[SIZE / 5];
	int Check;
} Player_Data;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct Found_IDList {
	char ID1[SIZE / 3 - sizeof(int)];
	char ID2[SIZE / 3 - sizeof(int)];
	char ID3[SIZE / 3];
	int Count; 
	int Check;
} Found_IDList;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct Change_PW {
	char PW1[SIZE / 3];
	char PW2[SIZE / 3];
	char ID[SIZE / 3 - sizeof(int)];
	int Check;
} Change_Pw;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct ENC_Data {
	unsigned char ENC[(sizeof(Player_Data) + AES_BLOCK_SIZE) * 2 + 1];
	unsigned char IV[AES_BLOCK_SIZE];
	unsigned char KEY[128 / 8];
} ENC_Data;
#pragma pack(pop)

#endif