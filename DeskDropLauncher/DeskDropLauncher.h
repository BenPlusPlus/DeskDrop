#pragma once

#include <Windows.h>
#include <strsafe.h>
#include "resource.h"

#define INJECT_FAILURE 501

int print_log(const wchar_t* format, ...)
{
	static wchar_t w_printf_buf[1024] = { 0 };
	va_list args;
	va_start(args, format);
	StringCchVPrintf(w_printf_buf, sizeof(w_printf_buf), format, args);
	va_end(args);
	OutputDebugString(w_printf_buf);
	return 0;
}


