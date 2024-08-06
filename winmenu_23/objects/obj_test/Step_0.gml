winmenu_update();
if (mouse_check_button_pressed(mb_right)) {
	var _item = winmenu_show_popup(m_rec, 0, display_mouse_get_x(), display_mouse_get_y());
	winmenu_handler(_item);
}

if (true) { // resize handling?
	var _width = window_get_width();
	var _height = window_get_height();
	var _bar_height = winmenu_bar_get_height();
	if (_bar_height != undefined) {
		_height += _bar_height;
	}
	if (_width > 0 && _height > 0
		&& surface_exists(application_surface)
		&& (
			surface_get_width(application_surface) != _width
			|| surface_get_height(application_surface) != _height
		)
	) {
		surface_resize(application_surface, _width, _height);
		room_width = _width;
		room_height = _height;
		trace("resizing to", _width, _height);
	}
}