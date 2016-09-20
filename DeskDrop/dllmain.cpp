#include "stdafx.h"
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include "deskdrop.h"
#include "Subclass.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	wchar_t* helloStr;
	wchar_t buf[250];
	DWORD pid = GetCurrentProcessId();
	HWND targetWnd = GetTargetWindow();

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		helloStr = L"Target window: %d";
		swprintf_s(buf, helloStr, targetWnd);
		MessageBox(NULL, buf, NULL, NULL);
		SubclassWindow(targetWnd);
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		//helloStr = L"Goodbye from: %d";
		//swprintf_s(buf, helloStr, pid);
		//MessageBox(NULL, buf, NULL, NULL);
		UnsubclassWindow(targetWnd);
		break;
	}
	return TRUE;
}


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

