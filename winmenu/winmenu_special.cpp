#include "stdafx.h"
#include "winmenu.h"
#include <queue>
#include <unordered_map>

struct winmenu_queue_item {
    uint32_t command;
    HWND hwnd;
};
std::queue<winmenu_queue_item> winmenu_bar_queue{};
std::queue<winmenu_queue_item> winmenu_sys_queue{};
std::unordered_map<HWND, WNDPROC> winmenu_baseprocs{};

LRESULT wndproc_hook(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_COMMAND) {
        switch (HIWORD(wParam)) {
            case 0: case 1: // menu, accelerator
                winmenu_queue_item item{};
                item.command = LOWORD(wParam);
                item.hwnd = hwnd;
                winmenu_bar_queue.push(item);
                break;
        }
    } else if (msg == WM_SYSCOMMAND) {
        auto cmd = (uint32_t)wParam;
        if (cmd < 0xF000) {
            winmenu_queue_item item{};
            item.command = cmd;
            item.hwnd = hwnd;
            winmenu_sys_queue.push(item);
        }
    }
    auto pair = winmenu_baseprocs.find(hwnd);
    if (pair != winmenu_baseprocs.end()) {
        return CallWindowProc(pair->second, hwnd, msg, wParam, lParam);
    } else return 0;
}
void wndproc_ensure(HWND hwnd) {
    if (winmenu_baseprocs.find(hwnd) != winmenu_baseprocs.end()) return;
    winmenu_baseprocs[hwnd] = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)wndproc_hook);
}

/// ~
dllg void winmenu_cleanup_for_raw(uintptr_t _hwnd) {
    auto hwnd = (HWND)_hwnd;
    auto pair = winmenu_baseprocs.find(hwnd);
    if (pair == winmenu_baseprocs.end()) return;
    // revert wndproc if it wasn't re-hooked:
    if (GetWindowLongPtr(hwnd, GWLP_WNDPROC) == (LONG_PTR)wndproc_hook) {
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)pair->second);
    }
    winmenu_baseprocs.erase(hwnd);
}

static winmenu_queue_item winmenu_queue_latest{};
dllx double winmenu_queue_size(double _kind) {
    if ((int)_kind > 0) {
        return (double)winmenu_sys_queue.size();
    } else return (double)winmenu_bar_queue.size();
}
dllx double winmenu_queue_pop(double _kind) {
    auto& q = (int)_kind > 0 ? winmenu_sys_queue : winmenu_bar_queue;
    if (q.empty()) return -1;
    winmenu_queue_latest = q.front();
    q.pop();
    return winmenu_queue_latest.command;
}
/// ~
dllg uintptr_t winmenu_queue_hwnd() {
    return (uintptr_t)winmenu_queue_latest.hwnd;
}

/// ~
dllg wm_menu winmenu_bar_get_raw(GAME_HWND hwnd) {
    return GetMenu(hwnd);
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