#include "stdafx.h"
#include <Windows.h>

#define CUSTOMPROPERTY L"DeskDropOldProc"

LRESULT CALLBACK DeskDropWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WNDPROC OrigWndProc = (WNDPROC)GetProp(hWnd, CUSTOMPROPERTY);
	if (OrigWndProc == NULL)
	{
		return 0;
	}

	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		wchar_t* testmsg = L"Hi there!!!";
		TextOut(hdc, 8, 8, testmsg, wcslen(testmsg));
		EndPaint(hWnd, &ps);
	}
	break;
	default:
		return CallWindowProc(OrigWndProc, hWnd, message, wParam, lParam);
	}
	return 0;
}


void SubclassWindow(HWND hWnd)
{
	WNDPROC OrigWndProc = (WNDPROC)GetProp(hWnd, CUSTOMPROPERTY);
	if (OrigWndProc)
	{
		return; // already subclassed
	}

	OrigWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC);
	SetProp(hWnd, CUSTOMPROPERTY, OrigWndProc);
	SetWindowLongPtr(hWnd, GWLP_WNDPROC, (long)DeskDropWndProc);
}


void UnsubclassWindow(HWND hWnd)
{
	WNDPROC OrigWndProc = (WNDPROC)GetProp(hWnd, CUSTOMPROPERTY);
	if (OrigWndProc == NULL)
	{
		return; // not subclassed
	}

	SetWindowLongPtr(hWnd, GWLP_WNDPROC, (long)OrigWndProc);
	RemoveProp(hWnd, CUSTOMPROPERTY);
}

