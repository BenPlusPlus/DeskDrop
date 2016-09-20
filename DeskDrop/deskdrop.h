#pragma once
#include <windows.h>
#include <strsafe.h>

int print_log(const wchar_t* format, ...);

HWND GetTargetWindow();

