#ifndef INCLUDE_HEADER
#define INCLUDE_HEADER

#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>

#pragma comment(lib,"ws2_32")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
using std::cout;
using std::endl;

#include <thread>
#include <chrono>

#include <string>
#include <stdexcept>
#include <stdlib.h>

#include <regex> // Á¤±Ô½Ä

#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

#endif