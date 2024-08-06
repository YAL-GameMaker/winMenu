#include "stdafx.h"
#include "winmenu.h"

// manage:
dllg wm_menu winmenu_create_bar() {
    return CreateMenu();
}
dllg wm_menu winmenu_create_popup() {
    return CreatePopupMenu();
}
dllg bool winmenu_destroy(gml_id_destroy<HMENU> menu) {
    return DestroyMenu(menu);
}

// refs:
dllg wm_handle winmenu_get_handle(wm_menu menu) {
    return (wm_handle)menu;
}
dllg wm_menu winmenu_from_handle(wm_handle handle) {
    return (HMENU)handle;
}
dllg bool winmenu_deref(gml_id_destroy<HMENU> menu) {
    return menu != NULL;
}

// misc:
dllg bool winmenu_handle_is_menu(wm_handle handle) {
    return IsMenu((HMENU)handle);
}
dllg bool winmenu_equals(wm_menu menu1, wm_menu menu2) {
    return menu1 == menu2;
}

//
dllg int winmenu_size(wm_menu menu) {
    return GetMenuItemCount(menu);
}

dllg std::optional<wm_item> winmenu_get_default_item(wm_menu menu, bool want_pos, bool recursive, bool allow_disabled) {
    UINT flags = 0;
    if (recursive) flags |= GMDI_GOINTOPOPUPS;
    if (allow_disabled) flags |= GMDI_USEDISABLED;
    auto item = GetMenuDefaultItem(menu, want_pos, flags);
    if (item == (UINT)-1) return {};
    return item;
}
dllg bool winmenu_set_default_item(wm_menu menu, wm_item item, bool want_pos) {
    return SetMenuDefaultItem(menu, item, want_pos);
}

dllg std::optional<uint32_t> winmenu_get_max_height(wm_menu menu) {
    MENUINFO inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIM_MAXHEIGHT;
    if (!GetMenuInfo(menu, &inf)) return {};
    return inf.cyMax;
}
dllg bool winmenu_set_max_height(wm_menu menu, uint32_t max_height) {
    MENUINFO inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIM_MAXHEIGHT;
    inf.cyMax = max_height;
    return SetMenuInfo(menu, &inf);
}