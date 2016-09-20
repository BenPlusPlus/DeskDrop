// DeskDrop.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

HWND GetTargetWindow_Notepad()
{
	HWND hWnd = FindWindowW(L"Notepad", NULL);
	if (hWnd)
	{
		hWnd = FindWindowExW(hWnd, NULL, L"Edit", NULL);
		return hWnd;
	}
	return 0;
}

HWND GetTargetWindow_Desktop()
{
	return GetDesktopWindow();
}

HWND GetTargetWindow()
{
	return GetTargetWindow_Notepad();
}

