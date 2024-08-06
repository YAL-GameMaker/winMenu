#include "stdafx.h"
#include "winmenu.h"

///
enum class wmpf {
    can_right_click = 0x2,
    //
    halign_left = 0x0,
    halign_center = 0x4,
    halign_right = 0x8,
    //
    valign_top = 0x0,
    valign_middle = 0x10,
    valign_bottom = 0x20,
    //
    anim_to_right = 0x400,
    anim_to_left = 0x800,
    anim_to_bottom = 0x1000,
    anim_to_top = 0x2000,
    anim_none = 0x4000,
};
dllg wm_item winmenu_show_popup(wm_menu menu, uint32_t flags, int x, int y, GAME_HWND hwnd) {
    #define X(name, val) static_assert((uint32_t)name == (val), #name)
    X(wmpf::can_right_click, TPM_RIGHTBUTTON);
    //
    X(wmpf::halign_left, TPM_LEFTALIGN);
    X(wmpf::halign_center, TPM_CENTERALIGN);
    X(wmpf::halign_right, TPM_RIGHTALIGN);
    //
    X(wmpf::valign_top, TPM_TOPALIGN);
    X(wmpf::valign_middle, TPM_VCENTERALIGN);
    X(wmpf::valign_bottom, TPM_BOTTOMALIGN);
    //
    X(wmpf::anim_none, TPM_NOANIMATION);
    X(wmpf::anim_to_left, TPM_HORNEGANIMATION);
    X(wmpf::anim_to_right, TPM_HORPOSANIMATION);
    X(wmpf::anim_to_bottom, TPM_VERPOSANIMATION);
    X(wmpf::anim_to_top, TPM_VERNEGANIMATION);
    #undef X
    flags |= TPM_RETURNCMD | TPM_NONOTIFY;
    return TrackPopupMenuEx(menu, flags, x, y, hwnd, nullptr);
}
dllg wm_item winmenu_show_popup_outside(wm_menu menu, uint32_t flags, int x, int y, GAME_HWND hwnd, int exclude_x, int exclude_y, int exclude_width, int exclude_height) {
    flags |= TPM_RETURNCMD | TPM_NONOTIFY;
    TPMPARAMS tpmp{};
    tpmp.cbSize = sizeof(tpmp);
    tpmp.rcExclude.left = exclude_x;
    tpmp.rcExclude.top = exclude_y;
    tpmp.rcExclude.right = exclude_x + exclude_width - 1;
    tpmp.rcExclude.bottom = exclude_y + exclude_height - 1;
    return TrackPopupMenuEx(menu, flags, x, y, hwnd, &tpmp);
}