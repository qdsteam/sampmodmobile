#pragma once

#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <unistd.h>
#include <jni.h>

#include "vendor/RakNet/SAMP/samp_netencr.h"
#include "vendor/RakNet/SAMP/SAMPRPC.h"
#include "util/util.h"

#define SAMP_VERSION	"0.3.7"
#define MODSA_VERSION	"0.0.0.3"

#define ADDRZERO "93.170.76.34"
#define ADDRONE "37.143.12.132"
#define ADDRTWO "37.230.139.49"

#define MAX_PLAYERS		1004
#define MAX_VEHICLES	2000
#define MAX_PLAYER_NAME	24

#define RAKSAMP_CLIENT
#define NETCODE_CONNCOOKIELULZ 0x6969

extern uintptr_t g_libGTASA;
extern const char* g_pszStorage;

void Log(const char *fmt, ...);
uint32_t GetTickCount();