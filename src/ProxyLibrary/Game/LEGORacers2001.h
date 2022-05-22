#pragma once

#include <Windows.h>

typedef BYTE _BYTE;
typedef WORD _WORD;
typedef DWORD _DWORD;

#define __cppobj
#define this self
#define HWND RACERS_HWND
#define HWND__ RACERS_HWND__

#include "LEGORacers2001.inc"

#undef __cppobj
#undef this
#undef HWND
#undef HWND__