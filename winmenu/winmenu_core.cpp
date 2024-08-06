#include "stdafx.h"
#include "winmenu.h"
#include <string>

StringConv wm_c1, wm_c2;

///
enum winmenu_flag {
    // states:
    wmf_enabled = 0x0,
    wmf_disabled = 0x3,
    //wmf_bitmap = 4,
    wmf_checked = 0x8,
    //wmf_submenu = 0x10,
    wmf_bar_break = 0x20,
    wmf_break = 0x40,
    wmf_hilite = 0x80,
    // types:
    wmf_radiocheck = 0x200,
    wmf_separator = 0x800,
    wmf_default = 0x1000,
    wmf_right_order = 0x2000,
    wmf_right_justify = 0x4000,
};
static void wmf_verify() {
    #define X(name, val) static_assert((uint32_t)name == (val), #name)
    X(wmf_disabled, MF_DISABLED | MF_GRAYED);
    X(wmf_checked, MF_CHECKED);
    //X(wmf_submenu, MF_POPUP);
    X(wmf_bar_break, MF_MENUBARBREAK);
    X(wmf_break, MF_MENUBREAK);
    //X(wmf_hilite, MF_HILITE);
    X(wmf_separator, MF_SEPARATOR);
    X(wmf_default, MF_DEFAULT);
    //
    X(wmf_checked, MFS_CHECKED);
    X(wmf_default, MFS_DEFAULT);
    X(wmf_disabled, MFS_DISABLED);
    X(wmf_enabled, MFS_ENABLED);
    X(wmf_hilite, MFS_HILITE);
    //
    X(wmf_bar_break, MF_MENUBARBREAK);
    X(wmf_break, MFT_MENUBREAK);
    X(wmf_separator, MFT_SEPARATOR);
    //
    X(wmf_right_justify, MFT_RIGHTJUSTIFY);
    X(wmf_right_order, MFT_RIGHTORDER);
    #undef X
}

///
enum class wmbm {
    mbar_close = 5,
    mbar_close_d = 6,
    mbar_minimize = 3,
    mbar_minimize_d = 7,
    mbar_restore = 2,
    popup_close = 8,
    popup_maximize = 10,
    popup_mimize = 11,
    popup_restore = 9,
};
static void wmbm_verify() {
    #define X(name, val) static_assert((HBITMAP)name == (val), #name)
    X(wmbm::mbar_close, HBMMENU_MBAR_CLOSE);
    X(wmbm::mbar_close_d, HBMMENU_MBAR_CLOSE_D);
    X(wmbm::mbar_minimize, HBMMENU_MBAR_MINIMIZE);
    X(wmbm::mbar_minimize_d, HBMMENU_MBAR_MINIMIZE_D);
    X(wmbm::mbar_restore, HBMMENU_MBAR_RESTORE);
    X(wmbm::popup_close, HBMMENU_POPUP_CLOSE);
    X(wmbm::popup_maximize, HBMMENU_POPUP_MAXIMIZE);
    X(wmbm::popup_mimize, HBMMENU_POPUP_MINIMIZE);
    X(wmbm::popup_restore, HBMMENU_POPUP_RESTORE);
    #undef X
}

///
dllx double winmenu_get_last_error() {
    return GetLastError();
}
///
dllx const char* winmenu_get_last_error_text() {
    auto id = GetLastError();
    if (id == 0) return "";

    wchar_t* msg = nullptr;
    auto size = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, id, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (wchar_t*)&msg, 0, nullptr
    );

    std::wstring result{};
    if (msg != nullptr) {
        result = msg;
        LocalFree(msg);
    } else result = L"Error " + std::to_wstring(id);

    return wm_c1.proc(result.c_str());
}