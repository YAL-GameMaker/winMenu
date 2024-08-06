#include "stdafx.h"
#include "winmenu.h"
#include <string>

// flags:
dllg std::optional<wm_flags> winmenu_get_flags(wm_menu menu, wm_item item, bool bypos) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STATE | MIIM_FTYPE;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return {};
    return wmii_get_flags(inf);
}
dllg bool winmenu_set_flags(wm_menu menu, wm_item item, bool bypos, wm_flags flags) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STATE | MIIM_FTYPE;
    wmii_set_flags(inf, flags);
    return SetMenuItemInfoW(menu, item, bypos, &inf);
}

// submenu:
dllg std::optional<wm_menu> winmenu_get_submenu(wm_menu menu, wm_item item, bool bypos) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_SUBMENU;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return {};
    return inf.hSubMenu;
}
dllg bool winmenu_set_submenu(wm_menu menu, wm_item item, bool bypos, wm_menu submenu) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_SUBMENU;
    inf.hSubMenu = submenu;
    return GetMenuItemInfoW(menu, item, bypos, &inf);
}
dllg std::optional<bool> winmenu_has_submenu(wm_menu menu, wm_item item, bool bypos) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_SUBMENU;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return {};
    return inf.hSubMenu != NULL;
}

// id
dllg std::optional<wm_item> winmenu_get_command(wm_menu menu, wm_index index) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_ID;
    if (!GetMenuItemInfoW(menu, index, true, &inf)) return {};
    return inf.wID;
}
dllg bool winmenu_set_command(wm_menu menu, wm_item item, bool bypos, wm_command new_command) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_ID;
    inf.wID = new_command;
    return SetMenuItemInfoW(menu, item, bypos, &inf);
}

// text:
dllg std::optional<const char*> winmenu_get_text(wm_menu menu, wm_item item, bool bypos) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STRING;
    inf.dwTypeData = nullptr;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return {};

    static std::wstring tmp{};
    tmp.resize(inf.cch + 2); tmp[0] = 0;
    inf.cch += 1; // missing the last letter otherwise..?
    inf.dwTypeData = tmp.data();
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return {};

    return wm_cc(tmp.c_str());
}
dllg bool winmenu_set_text(wm_menu menu, wm_item item, bool bypos, const char* text) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STRING;
    inf.dwTypeData = (wchar_t*)wm_cc(text);
    return SetMenuItemInfoW(menu, item, bypos, &inf);
}

// enabled:
dllg std::optional<bool> winmenu_get_enabled(wm_menu menu, wm_item item, bool bypos) {
    auto flags = winmenu_get_flags(menu, item, bypos);
    if (flags) {
        return (*flags & MFS_DISABLED) == 0;
    } else return {};
}
dllg bool winmenu_set_enabled(wm_menu menu, wm_item item, bool bypos, bool enabled) {
    return EnableMenuItem(menu, item, wm_p2f(bypos) | (enabled ? MF_ENABLED : MF_DISABLED));
}

// hilite:
dllg std::optional<bool> winmenu_get_hilite(wm_menu menu, wm_item item, bool bypos) {
    auto flags = winmenu_get_flags(menu, item, bypos);
    if (flags) {
        return (*flags & MFS_HILITE) != 0;
    } else return {};
}
dllg bool winmenu_set_hilite(GAME_HWND hwnd, wm_menu menu, wm_item item, bool bypos, bool hilite) {
    return HiliteMenuItem(hwnd, menu, item, wm_p2f(bypos) | (hilite ? MF_HILITE : MF_UNHILITE));
}

// checkmark:
dllg std::optional<bool> winmenu_get_checked(wm_menu menu, wm_item item, bool bypos) {
    auto flags = winmenu_get_flags(menu, item, bypos);
    if (flags) {
        return (*flags & MFS_CHECKED) != 0;
    } else return {};
}
dllg bool winmenu_set_checked(wm_menu menu, wm_item item, bool bypos, bool checked) {
    return CheckMenuItem(menu, item, wm_p2f(bypos) | (checked ? MF_CHECKED : MF_UNCHECKED));
}

// radio:
dllg std::optional<bool> winmenu_get_radio(wm_menu menu, wm_item item, bool bypos) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_FTYPE;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return {};
    return (inf.fType & MFT_RADIOCHECK) != 0;
}
dllg bool winmenu_set_radio(wm_menu menu, wm_item item, bool bypos, bool show_as_radio) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_FTYPE;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return false;
    wm_setflag(inf.fType, MFT_RADIOCHECK, show_as_radio);
    return SetMenuItemInfoW(menu, item, bypos, &inf);
}
dllg bool winmenu_set_radio_group(wm_menu menu, wm_item first, wm_item last, wm_item selection, bool bypos) {
    return CheckMenuRadioItem(menu, first, last, selection, wm_p2f(bypos));
}

struct winmenu_item_rect {
    int x, y, width, height;
    winmenu_item_rect(RECT rect) {
        x = rect.left;
        y = rect.top;
        width = rect.right - rect.left + 1;
        height = rect.bottom - rect.top + 1;
    }
};
dllg std::optional<winmenu_item_rect> winmenu_get_item_rect(GAME_HWND hwnd, bool use_hwnd, wm_menu menu, wm_index index) {
    RECT rect{};
    if (!GetMenuItemRect(use_hwnd ? hwnd : NULL, menu, index, &rect)) return {};
    return winmenu_item_rect(rect);
}

dllg int winmenu_item_from_point(GAME_HWND hwnd, bool use_hwnd, wm_menu menu, int x, int y) {
    POINT pt{};
    pt.x = x;
    pt.y = y;
    return MenuItemFromPoint(use_hwnd ? hwnd : NULL, menu, pt);
}
