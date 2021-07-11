#undef max
#include <cstdint>

#include "Patch.h"
#include <dinput.h>
#include <fstream>
#include <string>
#include <iostream>
#include <d3d9/d3d9.h>
#include <d3d9/d3dx9.h>


HMODULE base_address;

FARPROC p;
HINSTANCE hL = 0;
Patch *P;


BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason,LPVOID v)
{
	
	base_address = GetModuleHandle(NULL);
	FILE* f = new FILE();
	if (reason == DLL_PROCESS_ATTACH)
	{
		WCHAR szPath[MAX_PATH];

		if (!GetSystemDirectory(szPath, sizeof(szPath) - 20))
			return FALSE;
		wcscat_s(szPath, L"\\dinput8.dll");
		
		hL = LoadLibrary(szPath);

		if (!hL) 
			return FALSE;

		p = GetProcAddress(hL,"DirectInput8Create");

		DWORD DirectX_ver = 8;

		DWORD PID = GetCurrentProcessId();
		HMODULE hMods[1024];
		DWORD cbNeeded;
		int i;
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, PID);

		HMODULE hD3D8Dll = GetModuleHandle(L"d3d8.dll");
		if (!hD3D8Dll) DirectX_ver = 9;


		config parameters(false, false, 1);
		bool result = LoadConfig(parameters);
		if (parameters.texture_mod && DirectX_ver == 8) {
			MessageBox(NULL, L"L'injection de texture ne fonctionne pas avec la version DirectX8 (lancez la DX9 !)", L"Error!", MB_ICONWARNING | MB_OK);
			exit(EXIT_FAILURE);
		}
		else {
			char name[MAX_PATH + 1];
			GetModuleFileNameA(base_address, name, MAX_PATH);
			P = new Patch(base_address, name, parameters);
			P->Patching();
		}
		
		
	}

	if (reason == DLL_PROCESS_DETACH)
	{
		
		delete P;
		FreeLibrary(hL);
	}
	FreeConsole();
	return TRUE;
}

// DirectInput8Create
HRESULT __stdcall  __E__0__(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter)
{

	typedef HRESULT(__stdcall* pCreate)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
	pCreate ppC = (pCreate)p;
	
	HRESULT ret = ppC(hinst, dwVersion, riidltf, ppvOut, punkOuter);

	
	return ret; /* */
}