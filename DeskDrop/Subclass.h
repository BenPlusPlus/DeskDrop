#pragma once

#include "stdafx.h"
#include <Windows.h>

LRESULT CALLBACK DeskDropWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DeskDropWndProcSafe(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
BOOL SubclassWindow(HWND hWnd);
BOOL UnsubclassWindow(HWND hWnd);

