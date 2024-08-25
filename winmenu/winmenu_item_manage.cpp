#include "stdafx.h"
#include "winmenu.h"

// add:
dllg bool winmenu_add(wm_menu menu, wm_command command, const char* text, wm_flags flags = 0) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STATE | MIIM_FTYPE | MIIM_STRING | MIIM_ID;
    wmii_set_flags(inf, flags);
    inf.wID = command;
    inf.dwTypeData = (wchar_t*)wm_cc(text);
    return InsertMenuItemW(menu, GetMenuItemCount(menu), true, &inf);
}
dllg bool winmenu_add_submenu(wm_menu menu, wm_command command, wm_menu submenu, const char* text, wm_flags flags = 0) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STATE | MIIM_FTYPE | MIIM_STRING | MIIM_ID | MIIM_SUBMENU;
    wmii_set_flags(inf, flags);
    inf.wID = command;
    inf.hSubMenu = submenu;
    inf.dwTypeData = (wchar_t*)wm_cc(text);
    return InsertMenuItemW(menu, GetMenuItemCount(menu), true, &inf);
}
dllg bool winmenu_add_separator(wm_menu menu, wm_command command = 0, wm_flags flags = 0) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STATE | MIIM_FTYPE | MIIM_ID;
    wmii_set_flags(inf, flags | MFT_SEPARATOR);
    inf.wID = command;
    return InsertMenuItemW(menu, GetMenuItemCount(menu), true, &inf);
}

// insert:
dllg bool winmenu_insert(wm_menu menu, wm_item item, bool bypos, wm_command command, const char* text, wm_flags flags = 0) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STATE | MIIM_FTYPE | MIIM_STRING | MIIM_ID;
    wmii_set_flags(inf, flags);
    inf.wID = command;
    inf.dwTypeData = (wchar_t*)wm_cc(text);
    return InsertMenuItemW(menu, item, bypos, &inf);
}
dllg bool winmenu_insert_submenu(wm_menu menu, wm_item item, bool bypos, wm_command command, wm_menu submenu, const char* text, wm_flags flags = 0) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STATE | MIIM_FTYPE | MIIM_STRING | MIIM_SUBMENU | MIIM_ID;
    wmii_set_flags(inf, flags);
    inf.wID = command;
    inf.hSubMenu = submenu;
    inf.dwTypeData = (wchar_t*)wm_cc(text);
    return InsertMenuItemW(menu, item, bypos, &inf);
}
dllg bool winmenu_insert_separator(wm_menu menu, wm_item item, bool bypos, wm_command command = 0, wm_flags flags = 0) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_STATE | MIIM_FTYPE | MIIM_ID;
    wmii_set_flags(inf, flags | MFT_SEPARATOR);
    inf.wID = command;
    return InsertMenuItemW(menu, item, bypos, &inf);
}

// delete:
dllg bool winmenu_delete(wm_menu menu, wm_item item, bool bypos) {
    return RemoveMenu(menu, item, wm_p2f(bypos));
}
dllg bool winmenu_delete_rec(wm_menu menu, wm_item item, bool bypos) {
    return DeleteMenu(menu, item, wm_p2f(bypos));
}