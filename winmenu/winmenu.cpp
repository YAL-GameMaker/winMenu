/// @author YellowAfterlife

#include "stdafx.h"
#include "winmenu.h"
#include <Windows.h>
#include "winapi_hook.h"
#include <intrin.h>

#ifdef wm_hook_adj

// ideally should be doing bMenu = GetMenu(hwnd) != NULL in the runner,
// but it doesn't, so let's install a little hook function

static HMODULE hmGame = 0;
static HWND main_hwnd = NULL;

HookPairDecl(BOOL, AdjustWindowRectEx, 
	_Inout_ LPRECT lpRect,
	_In_ DWORD dwStyle,
	_In_ BOOL bMenu,
	_In_ DWORD dwExStyle
) {
	auto hm = hmFromAddress(_ReturnAddress());

	#if 0
	char hmn[128] = "";
	GetModuleFileNameA(hm, hmn, std::size(hmn));
	trace("Is AdjustWindowRectEx being called from runner?: %d (%s)", hm == hmGame, hmn);
	#endif

	if (!bMenu && hmGame && hm == hmGame) {
		bMenu = GetMenu(main_hwnd) != NULL;
	}
	return AdjustWindowRectEx_base(lpRect, dwStyle, bMenu, dwExStyle);
}

#endif

dllx double winmenu_preinit_raw(void* pHwnd, double nHwnd) {
	#ifdef wm_hook_adj
	static bool hooked = false;
	if (hooked) return 1;
	//
	hmGame = hmFromAddress(_ReturnAddress());
	hooked = InstallHookPlus("User32.dll", "AdjustWindowRectEx", AdjustWindowRectEx, AdjustWindowRectEx_hook, &AdjustWindowRectEx_base);
	//
	if (nHwnd != 0) {
		main_hwnd = (HWND)(int32_t)nHwnd;
	} else {
		main_hwnd = (HWND)pHwnd;
	}
	#endif
	return 1;
}