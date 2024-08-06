#include "stdafx.h"
#include "winmenu.h"
#define winmenu_parex

#ifdef winmenu_parex
#include <algorithm>
#include <execution>
#endif

dllg bool winmenu_bitmap_destroy(gml_id_destroy<HBITMAP> bitmap) {
    return DeleteObject(bitmap);
}
dllg bool winmenu_bitmap_deref(gml_id_destroy<HBITMAP> bitmap) {
    return bitmap != NULL;
}
dllg bool winmenu_bitmap_equals(wm_bitmap a, wm_bitmap b) {
    return a == b;
}

dllg wm_bitmap winmenu_bitmap_add(const char* fname) {
    return (HBITMAP)LoadImageW(NULL, wm_cc(fname), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
}
dllg wm_bitmap winmenu_bitmap_create_from_buffer(gml_buffer buffer, int width, int height, bool is_rgba) {
    if (buffer.size() < width * height * 4) return NULL;
    //return CreateBitmap(width, height, 1, 32, buffer.data()); // no alpha?
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    auto hdc = GetDC(NULL);
    if (!hdc) return NULL;

    void* pBits = nullptr;
    auto bmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);

    if (!bmp) {
        // uh oh
    } else if (!is_rgba) {
        memcpy(pBits, buffer.data(), width * height * 4);
    } else {
        #ifdef winmenu_parex
        auto dest = (uint32_t*)pBits;
        auto src = (uint32_t*)(buffer.data());
        std::transform(std::execution::par_unseq, src, src + width * height, dest, [](uint32_t c) -> uint32_t {
            return (c & 0xFF00FF00) | ((c & 0xFF0000) >> 16) | ((c & 0xFF) << 16);
        });
        #else
        auto dest = (uint8_t*)pBits;
        auto src = (uint8_t*)buffer.data();
        for (int i = 0; i < width * height; ++i) {
            dest[0] = src[2];
            dest[1] = src[1];
            dest[2] = src[0];
            dest[3] = src[3];
            dest += 4;
            src += 4;
        }
        #endif
    }

    ReleaseDC(NULL, hdc);
    return bmp;
}

// regular:
dllg bool winmenu_set_bitmap(wm_menu menu, wm_item item, bool bypos, wm_bitmap bitmap) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_BITMAP;
    inf.hbmpItem = bitmap;
    return SetMenuItemInfoW(menu, item, bypos, &inf);
}
dllg bool winmenu_set_bitmap_sys(wm_menu menu, wm_item item, bool bypos, int bitmap_index) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_BITMAP;
    inf.hbmpItem = (HBITMAP)(intptr_t)bitmap_index;
    return SetMenuItemInfoW(menu, item, bypos, &inf);
}
dllg bool winmenu_reset_bitmap(wm_menu menu, wm_item item, bool bypos) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_BITMAP;
    inf.hbmpItem = NULL;
    return SetMenuItemInfoW(menu, item, bypos, &inf);
}
dllg wm_bitmap winmenu_get_bitmap(wm_menu menu, wm_item item, bool bypos) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_BITMAP;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return NULL;
    return inf.hbmpItem;
}

dllg std::optional<bool> winmenu_has_bitmap(wm_menu menu, wm_item item, bool bypos) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_BITMAP;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return NULL;
    return inf.hbmpItem != NULL;
}


// checkmarks:
dllg int winmenu_get_checkmark_width() {
    return GetSystemMetrics(SM_CXMENUCHECK);
}
dllg int winmenu_get_checkmark_height() {
    return GetSystemMetrics(SM_CYMENUCHECK);
}
dllg bool winmenu_set_checkmark_bitmaps(wm_menu menu, wm_item item, bool bypos, wm_bitmap bitmap_unchecked, wm_bitmap bitmap_checked) {
    return SetMenuItemBitmaps(menu, item, wm_p2f(bypos), bitmap_unchecked, bitmap_checked);
}
dllg bool winmenu_reset_checkmark_bitmaps(wm_menu menu, wm_item item, bool bypos) {
    return SetMenuItemBitmaps(menu, item, wm_p2f(bypos), NULL, NULL);
}
dllg wm_bitmap winmenu_get_checkmark_bitmap(wm_menu menu, wm_item item, bool bypos, bool checked) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_CHECKMARKS;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return NULL;
    return checked ? inf.hbmpChecked : inf.hbmpUnchecked;
}
dllg std::optional<bool> winmenu_has_checkmark_bitmap(wm_menu menu, wm_item item, bool bypos, bool checked) {
    MENUITEMINFOW inf{};
    inf.cbSize = sizeof(inf);
    inf.fMask = MIIM_CHECKMARKS;
    if (!GetMenuItemInfoW(menu, item, bypos, &inf)) return NULL;
    return (checked ? inf.hbmpChecked : inf.hbmpUnchecked) != NULL;
}