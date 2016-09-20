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

	if (targetWnd == NULL)
	{
		return TRUE;
	}

	BOOL success;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		success = SubclassWindow(targetWnd);
		helloStr = L"subclass success: %d";
		swprintf_s(buf, helloStr, success);
		MessageBox(NULL, buf, NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		if (lpReserved != NULL) // only clean up if process is terminating.
		{
			helloStr = L"Goodbye, lpReserved: %d";
			swprintf_s(buf, helloStr, lpReserved);
			MessageBox(NULL, buf, NULL, NULL);
			//UnsubclassWindow(targetWnd);
		}
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

