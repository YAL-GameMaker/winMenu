draw_set_font(fnt_test);
draw_set_color(c_white);

draw_rectangle(3, 3, room_width - 3, room_height - 3, 1);
draw_text(5, 5, "Timer: " + string(floor(current_time / 1000))
	 + "\nWindow: " + string(window_get_width()) + "x" + string(window_get_height())
	 + "\nSurface: " + string(surface_get_width(application_surface)) + "x" + string(surface_get_height(application_surface))
)