#include "stdafx.h"
#include "Injector.h"
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <conio.h>
#include <stdio.h> 

Injector::Injector(void)
{
}


Injector::~Injector(void)
{
}

bool Injector::Inject(wchar_t* procName, wchar_t* dllName)
{
	DWORD pID = GetTargetThreadIDFromProcName(procName);
	wprintf(L"Process ID: %d\n", pID);

	wchar_t DLL_NAME[MAX_PATH] = { 0 };
	GetFullPathName(dllName, MAX_PATH, DLL_NAME, NULL);
	wprintf(L"DLL to inject: %s\n", DLL_NAME);

	HANDLE Proc = 0;
	HMODULE hLib = 0;
	wchar_t buf[50] = { 0 };
	LPVOID RemoteString, LoadLibAddr;

	if (!pID)
		return false;

	Proc = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ, FALSE, pID);
	if (!Proc)
	{
		wprintf(L"OpenProcess() failed: %d", GetLastError());
		//MessageBox(NULL, buf, "Loader", MB_OK); 
		wprintf(buf);
		return false;
	}
	wprintf(L"OpenProcess() result: %d\n", Proc);

	LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");
	wprintf(L"LoadLibAddr: %d\n", LoadLibAddr);

	// Allocate space in the process for our DLL
	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, (wcslen(DLL_NAME)+1)*sizeof(wchar_t), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	wprintf(L"RemoteString: %d\n", RemoteString);

	// Write the string name of our DLL in the memory allocated
	bool writeResult = WriteProcessMemory(Proc, (LPVOID)RemoteString, DLL_NAME, (wcslen(DLL_NAME) + 1) * sizeof(wchar_t), NULL);
	wprintf(L"WriteProcessMemory result: %d\n", writeResult);

	// Load our DLL
	HANDLE hThread = CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, (LPVOID)RemoteString, NULL, NULL);
	wprintf(L"Thread handle: %d\n", hThread);

	CloseHandle(Proc);
	return true;
}

bool Injector::Inject(DWORD pID, wchar_t* dllName)
{
	wchar_t DLL_NAME[MAX_PATH] = { 0 };
	GetFullPathName(dllName, MAX_PATH, DLL_NAME, NULL);
	wprintf(DLL_NAME);
	wprintf(L"\n");

	HANDLE Proc = 0;
	HMODULE hLib = 0;
	wchar_t buf[50] = { 0 };
	LPVOID RemoteString, LoadLibAddr;

	if (!pID)
		return false;

	Proc = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, pID);
	if (!Proc)
	{
		wprintf(buf, "OpenProcess() failed: %d", GetLastError());
		//MessageBox(NULL, buf, L"Loader", MB_OK);
		wprintf(buf);
		return false;
	}

	LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");

	// Allocate space in the process for our DLL
	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, (wcslen(DLL_NAME) + 1) * sizeof(wchar_t), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	// Write the string name of our DLL in the memory allocated
	WriteProcessMemory(Proc, (LPVOID)RemoteString, DLL_NAME, (wcslen(DLL_NAME) + 1) * sizeof(wchar_t), NULL);

	// Load our DLL
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, (LPVOID)RemoteString, NULL, NULL);

	CloseHandle(Proc);
	return true;
}

DWORD Injector::GetTargetThreadIDFromProcName(const wchar_t * ProcName)
{
	PROCESSENTRY32 pe;
	HANDLE thSnapShot;
	BOOL retval, ProcFound = false;

	thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (thSnapShot == INVALID_HANDLE_VALUE)
	{
		//MessageBox(NULL, "Error: Unable to create toolhelp snapshot!", "2MLoader", MB_OK);
		wprintf(L"Error: Unable to create toolhelp snapshot!");
		return false;
	}

	pe.dwSize = sizeof(PROCESSENTRY32);

	retval = Process32First(thSnapShot, &pe);
	while (retval)
	{
		if (!wcscmp(pe.szExeFile, ProcName))
		{
			return pe.th32ProcessID;
		}
		retval = Process32Next(thSnapShot, &pe);
	}
	return 0;
}

