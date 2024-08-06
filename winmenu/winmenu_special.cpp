#include "stdafx.h"
#include "winmenu.h"
#include <queue>

std::queue<uint32_t> wndmenu_queue{};
std::queue<uint32_t> wndmenu_sysqueue{};

WNDPROC wndproc_base;
LRESULT wndproc_hook(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_COMMAND) {
        switch (HIWORD(wParam)) {
            case 0: case 1: // menu, accelerator
                wndmenu_queue.push(LOWORD(wParam));
                break;
        }
    } else if (msg == WM_SYSCOMMAND) {
        auto cmd = (uint32_t)wParam;
        if (cmd < 0xF000) wndmenu_sysqueue.push(cmd);
    }
    return CallWindowProc(wndproc_base, hwnd, msg, wParam, lParam);
}
void wndproc_ensure(HWND hwnd) {
    if (wndproc_base != nullptr) return;
    wndproc_base = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)wndproc_hook);
}

dllx double winmenu_queue_size(double _kind) {
    if ((int)_kind > 0) {
        return (double)wndmenu_sysqueue.size();
    } else return (double)wndmenu_queue.size();
}
dllx double winmenu_queue_pop(double _kind) {
    auto& q = (int)_kind > 0 ? wndmenu_sysqueue : wndmenu_queue;
    if (q.empty()) return -1;
    int result = q.front();
    q.pop();
    return result;
}

/// ~
dllg bool winmenu_bar_set_raw(GAME_HWND hwnd, wm_menu menu) {
    wndproc_ensure(hwnd);
    return SetMenu(hwnd, menu);
}
/// ~
dllg bool winmenu_bar_reset_raw(GAME_HWND hwnd) {
    return SetMenu(hwnd, NULL);
}
dllg bool winmenu_bar_redraw(GAME_HWND hwnd) {
    return DrawMenuBar(hwnd);
}
struct wm_bar_info {
    int x, y, width, height;
    int flags;
};
static std::optional<wm_bar_info> winmenu_bar_get_info_impl(HWND hwnd, int kind, std::optional<wm_index> index) {
    MENUBARINFO inf{};
    inf.cbSize = sizeof(inf);
    if (!GetMenuBarInfo(hwnd, kind, index.has_value() ? index.value() + 1 : 0, &inf)) return {};
    wm_bar_info result{};
    result.x = inf.rcBar.left;
    result.width = inf.rcBar.right - inf.rcBar.left + 1;
    result.y = inf.rcBar.top;
    result.height = inf.rcBar.bottom - inf.rcBar.top + 1;
    auto flags = 0;
    if (inf.fBarFocused) flags |= 1;
    if (inf.fFocused) flags |= 2;
    result.flags = flags;
    return result;
}
dllg std::optional<wm_bar_info> winmenu_bar_get_info(GAME_HWND hwnd, std::optional<wm_index> index = {}) {
    return winmenu_bar_get_info_impl(hwnd, OBJID_MENU, index);
}
dllg std::optional<int> winmenu_bar_get_height(GAME_HWND hwnd) {
    MENUBARINFO inf{};
    inf.cbSize = sizeof(inf);
    if (!GetMenuBarInfo(hwnd, OBJID_MENU, 0, &inf)) return {};
    return inf.rcBar.bottom - inf.rcBar.top + 1;
}
#pragma endregion

/// ~
dllg wm_menu winmenu_sysmenu_get_raw(GAME_HWND hwnd, bool revert) {
    wndproc_ensure(hwnd);
    return GetSystemMenu(hwnd, revert);
}
dllg std::optional<wm_bar_info> winmenu_sysmenu_get_info(GAME_HWND hwnd, std::optional<wm_index> index = {}) {
    return winmenu_bar_get_info_impl(hwnd, OBJID_SYSMENU, index);
}