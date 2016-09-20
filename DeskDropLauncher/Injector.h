#pragma once
#include <Windows.h>

class Injector
{
public:
	Injector(void);
	~Injector(void);

	bool Inject(wchar_t* procName, wchar_t* dllName);
	bool Inject(DWORD pID, wchar_t* dllName);

private:
	DWORD GetTargetThreadIDFromProcName(const wchar_t * ProcName);
};

