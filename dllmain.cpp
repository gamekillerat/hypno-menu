// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

DWORD WINAPI ControlThread(LPVOID lpParam) {

	if (AllocConsole()) {
		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		SetConsoleTitleW(L"HypnoV2 > Thank iAmSpace for this madness x)");
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
	}

	Log::Msg("Start Up > Starting Hooking for Hypno Menu...");
	Log::Msg("Start Up > LOG Console");

	Hooking::Start((HMODULE)lpParam);
	while (!Unload::do_it) {
		if (GetAsyncKeyState(VK_DELETE)) {
			Unload::do_it = true;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::this_thread::yield();
	}
	Features::niggerHotkey = false;
	FreeConsole();
	//fclose(stdout);
	Shutdown();
	Hooking::Cleanup();
	FreeLibraryAndExitThread((HMODULE)lpParam, 0);
	return 0;
}

class VTable { public: virtual void VFunction(HMODULE hModule); };
void VTable::VFunction(HMODULE hModule)
{
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ControlThread, hModule, NULL, NULL);
}

typedef void(__thiscall* VFunction_t)(void* ptr);
VFunction_t OG_VFunction;
void __fastcall HK_VFunction(void* p) { OG_VFunction(p); }

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved ) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {		
		VTable* vtable = new VTable();
		void** vtable2 = *(void***)vtable;

		DWORD protection;

		VirtualProtect(&vtable2[0], 4, PAGE_EXECUTE_READWRITE, &protection);
		OG_VFunction = (VFunction_t)vtable2[0];
		vtable2[0] = &HK_VFunction;
		VirtualProtect(&vtable2[0], 4, protection, 0);
		vtable->VFunction(hModule);
	}
	return TRUE;
}