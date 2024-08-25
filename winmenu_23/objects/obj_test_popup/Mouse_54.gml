var i = winmenu_show_popup(m_popup, 0, display_mouse_get_x(), display_mouse_get_y());
if (i == 0) {
	trace("Dismissed!");
	exit;
}
trace("Popup item clicked:", i, winmenu_get_text(m_popup, i, false));

var _bg = -1;
switch (i) {
	case TestPopup.Checkbox:
		winmenu_set_checked(m_popup, i, false, !winmenu_get_checked(m_popup, i, false));
		break;
	case TestPopup.Radio1:
	case TestPopup.Radio2:
		winmenu_set_radio_group(m_popup, TestPopup.Radio1, TestPopup.Radio2, i, false);
		break;
	case TestPopup.Red: _bg = $3232FA; break;
	case TestPopup.Green: _bg = $5EF997; break;
	case TestPopup.Blue: _bg = $F9964A; break;
}

if (_bg != -1) {
	// GMS >= 2:
	var _bge = layer_background_get_id("Compatibility_Colour");
	layer_background_blend(_bge, _bg);
	/*/
	
	//*/
}