enum MenuCMD {
	File = 100,
		Create,
		Exit,
	Checkboxes,
		Check1,
		Check2,
		Radio1,
		Radio2,
		Radio3,
	Help,
	Numbers,
		Number_1,
}

m_bar = winmenu_create_bar();

m_file = winmenu_create_popup();
winmenu_add(m_file, MenuCMD.Create, "New\tCtrl+N");
var bmp = winmenu_bitmap_create_from_sprite(spr_thumb_up, 0)
winmenu_set_bitmap(m_file, MenuCMD.Create, false, bmp);
winmenu_add(m_file, MenuCMD.Exit, "Exit\tAlt+F4");

m_number = winmenu_create_popup();
for (var i = 0; i < 10; i++) {
	var _cmd = MenuCMD.Number_1 + i;
	var _flags = 0;
	if (i == 5) _flags |= wmf_bar_break;
	winmenu_add(m_number, _cmd, string(i + 1), _flags);
	if (i == 7) winmenu_set_hilite(m_number, _cmd, false, true);
}

m_check = winmenu_create_popup();
winmenu_add(m_check, MenuCMD.Check1, "Checkbox 1", wmf_checked);
winmenu_add(m_check, MenuCMD.Check2, "Checkbox 2");
winmenu_add(m_check, 0, "", wmf_separator);
winmenu_add(m_check, MenuCMD.Radio1, "Radio 1");
winmenu_add(m_check, MenuCMD.Radio2, "Radio 2", wmf_disabled);
winmenu_add(m_check, MenuCMD.Radio3, "Radio 3");
winmenu_set_radio_group(m_check, MenuCMD.Radio1, MenuCMD.Radio3, MenuCMD.Radio2, false);

winmenu_add_submenu(m_bar, MenuCMD.File, m_file, "&File");
winmenu_add_submenu(m_bar, MenuCMD.Numbers, m_number, "&Numbers");
winmenu_add_submenu(m_bar, MenuCMD.Checkboxes, m_check, "&Checkboxes");
winmenu_add(m_bar, MenuCMD.Help, "?", wmf_right_order);

winmenu_bar_set(m_bar);
// make space for the menu bar!
var _height = winmenu_bar_get_height();
if (_height != undefined) {
	window_set_size(window_get_width(), window_get_height() + _height);
}

label = "";
winmenu_bar_handler = function(_cmd) {
	label = "Menu item: #" + string(_cmd) + " > " + winmenu_get_text(m_bar, _cmd, false);
	trace(label);
	switch (_cmd) {
		case MenuCMD.Check1: case MenuCMD.Check2:
			var _checked = winmenu_get_checked(m_check, _cmd, false);
			if (_checked != undefined) winmenu_set_checked(m_check, _cmd, false, !_checked);
			break;
		case MenuCMD.Radio1: case MenuCMD.Radio2: case MenuCMD.Radio3:
			winmenu_set_radio_group(m_check, MenuCMD.Radio1, MenuCMD.Radio3, _cmd, false);
			break;
	}
}
