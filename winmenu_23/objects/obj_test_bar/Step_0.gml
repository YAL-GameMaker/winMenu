// match room and application surface size to window size:
var _width = window_get_width();
var _height = window_get_height();
if (_width > 0 && _height > 0
	&& surface_exists(application_surface)
	&& (
		surface_get_width(application_surface) != _width
		|| surface_get_height(application_surface) != _height
	)
) {
	trace("resizing from",
		surface_get_width(application_surface),
		surface_get_height(application_surface),
		"to", _width, _height
	);
	
	surface_resize(application_surface, _width, _height);
	if (view_enabled) {
		view_wport[0] = _width;
		view_hport[0] = _height;
	} else {
		room_width = _width;
		room_height = _height;
	}
}