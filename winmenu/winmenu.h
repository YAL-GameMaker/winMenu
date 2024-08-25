#pragma once
#include "gml_ext.h"
#include "StringConv.h"

using wm_flags = uint32_t;
using wm_item = uint32_t;
using wm_command = uint32_t;
using wm_index = uint32_t;
using wm_menu = gml_id<HMENU>;
using wm_handle = intptr_t;
using wm_bitmap = gml_id<HBITMAP>;

#define wm_p2f(bypos) ((bypos) ? MF_BYPOSITION : MF_BYCOMMAND)
#define wm_cc(str) (wm_c1.proc(str))
#define wm_setflag(val, flag, on) if (on) val |= (flag); else val &= ~(flag);

#define wmf_mft (MFT_RADIOCHECK | MFT_RIGHTJUSTIFY | MFT_RIGHTORDER | MFT_SEPARATOR | MFT_MENUBARBREAK | MFT_MENUBREAK)
inline void wmii_set_flags(MENUITEMINFOW& inf, wm_flags flags) {
	inf.fState = flags & ~wmf_mft;
	inf.fType = flags & wmf_mft;
}
inline wm_flags wmii_get_flags(MENUITEMINFOW& inf) {
	return (inf.fType & wmf_mft) | (inf.fState & ~wmf_mft);
}

#define wm_hook_adj