#include "stdafx.h"
#include <Windows.h>
#include <CommCtrl.h>
#include "Subclass.h"

#define SUBCLASSID 90909

WNDPROC OrigWndProc = 0;

LRESULT CALLBACK DeskDropWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
		return 0;
	}
	break;
	}

	return CallWindowProc(OrigWndProc, hWnd, message, wParam, lParam);
}

LRESULT CALLBACK DeskDropWndProcSafe(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
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
		return 0;
	}
	break;
	case WM_NCDESTROY:
	{
		UnsubclassWindow(hWnd);
	}
	break;
	}

	return DefSubclassProc(hWnd, message, wParam, lParam);
}


BOOL SubclassWindow(HWND hWnd)
{
	if (OrigWndProc != 0)
	{
		return TRUE;
	}

	OrigWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC);
	SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)DeskDropWndProc);

	return TRUE;

	//return SetWindowSubclass(hWnd, DeskDropWndProcSafe, SUBCLASSID, 0);
}


BOOL UnsubclassWindow(HWND hWnd)
{
	if (OrigWndProc == 0)
	{
		return TRUE; // not subclassed
	}

	SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)OrigWndProc);

	return TRUE;

	//return RemoveWindowSubclass(hWnd, DeskDropWndProcSafe, SUBCLASSID);
}

