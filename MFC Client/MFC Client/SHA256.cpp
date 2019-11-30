#include "Main.h"

void sha256(char * string, char outputBuffer[SIZE / 5])
{
	unsigned char hash[SHA256_DIGEST_LENGTH];

	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, string, strlen(string));
	SHA256_Final(hash, &sha256);

	int i = 0;

	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}

	outputBuffer[SIZE / 5 - 1] = 0;
}