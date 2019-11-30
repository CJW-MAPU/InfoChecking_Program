#ifndef INCLUDE_HEADER
#define INCLUDE_HEADER

#define _CRT_SECURE_NO_WARNINGS

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

#include <mysql.h>

#pragma comment(lib, "libmysql")

#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

#include <thread>
#include <chrono>

#include <string>
using std::string;

#include <stdexcept>
#include <cstdlib>
#include <ctime>

#include <Windows.h>

#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#endif