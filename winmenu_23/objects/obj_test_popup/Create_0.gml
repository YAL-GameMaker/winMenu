enum TestPopup {
	Button = 1,
	Checkbox,
	Radio1,
	Radio2,
	Colors,
		Red,
		Green,
		Blue,
}
m_popup = winmenu_create_popup();
winmenu_add(m_popup, TestPopup.Button, "Button");
winmenu_add_separator(m_popup, 0);
winmenu_add(m_popup, TestPopup.Checkbox, "Checkbox", wmf_checked);
winmenu_add_separator(m_popup, 0);
winmenu_add(m_popup, TestPopup.Radio1, "Radio 1", wmf_radiocheck|wmf_checked);
winmenu_add(m_popup, TestPopup.Radio2, "Radio 2", wmf_radiocheck);
winmenu_add_separator(m_popup, 0);

b_color_red = winmenu_bitmap_create_from_sprite(spr_rgb, 0);
b_color_green = winmenu_bitmap_create_from_sprite(spr_rgb, 1);
b_color_blue = winmenu_bitmap_create_from_sprite(spr_rgb, 2);
m_colors = winmenu_create_popup();
winmenu_add(m_colors, TestPopup.Red, "Red");
winmenu_add(m_colors, TestPopup.Green, "Green");
winmenu_add(m_colors, TestPopup.Blue, "Blue");
winmenu_set_bitmap(m_colors, TestPopup.Red, false, b_color_red);
winmenu_set_bitmap(m_colors, TestPopup.Green, false, b_color_green);
winmenu_set_bitmap(m_colors, TestPopup.Blue, false, b_color_blue);
winmenu_add_submenu(m_popup, TestPopup.Colors, m_colors, "Colors");