#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include <iostream>
#include <chrono>
#include <thread>

// GUARD
#define WIN32_LEAN_AND_MEAN
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#define _WINSOCKAPI_

// WINDOWS API
#include <Windows.h>
// WINSOCK
#include <Ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")

#endif //PCH_H
