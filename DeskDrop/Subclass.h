#pragma once

#include "stdafx.h"
#include <Windows.h>

LRESULT CALLBACK DeskDropWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void SubclassWindow(HWND hWnd);
void UnsubclassWindow(HWND hWnd);

