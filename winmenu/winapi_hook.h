#pragma once
#include "winmenu.h"
#include <Dbghelp.h>

#ifdef wm_hook_adj
BOOL InstallHook(LPCSTR module, LPCSTR function, void* hook, void** original);

template<typename T>
BOOL InstallHookPlus(LPCSTR module, LPCSTR function, T proto, T hook, T* out_orig) {
	return InstallHook(module, function, hook, (void**)out_orig);
}
#define HookPairDecl(ret, name, ...)\
	ret(__stdcall* name##_base)(##__VA_ARGS__);\
	__declspec(noinline) ret __stdcall  name##_hook(##__VA_ARGS__)

HMODULE hmFromAddress(void* addr);
#endif