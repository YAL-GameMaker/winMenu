enum SysCMD {
	CustomMenus = 200,
	InGameMaker,
		Radio1,
		Radio2,
		Icon,
}

m_sub = winmenu_create_popup();
winmenu_add(m_sub, SysCMD.Radio1, "Radio &1", wmf_radiocheck|wmf_checked);
winmenu_add(m_sub, SysCMD.Radio2, "Radio &2", wmf_radiocheck);
winmenu_add_separator(m_sub);
winmenu_add(m_sub, SysCMD.Icon, "&Icons too!");
var bmp = winmenu_bitmap_create_from_sprite(spr_thumb_up, 0)
winmenu_set_bitmap(m_sub, SysCMD.Icon, false, bmp);

m_sys = winmenu_sysmenu_get();

winmenu_add(m_sys, SysCMD.InGameMaker, "in GameMaker!");
winmenu_insert_submenu(m_sys, SysCMD.InGameMaker, false, SysCMD.CustomMenus, m_sub, "Custom menus");

label = "";
winmenu_system_handler = function(_cmd) {
	label = "System item clicked: #" + string(_cmd) + " > " + winmenu_get_text(m_sys, _cmd, false);
	trace(label);
	switch (_cmd) {
		case SysCMD.Radio1: case SysCMD.Radio2:
			winmenu_set_radio_group(m_sys, SysCMD.Radio1, SysCMD.Radio2, _cmd, false);
			break;
	}
}