#event create
winmenu_init_dll();
room_caption = "winMenu by YellowAfterlife"

enum_start(100);
globalvar MenuCMD_File = enum_next();
	globalvar MenuCMD_New = enum_next();
	globalvar MenuCMD_Exit = enum_next();
globalvar MenuCMD_Numbers = enum_next();
	globalvar MenuCMD_Number_1 = enum_next();
	repeat (9) enum_next();
globalvar MenuCMD_Checkboxes = enum_next();
	globalvar MenuCMD_Check1 = enum_next();
	globalvar MenuCMD_Check2 = enum_next();
	globalvar MenuCMD_Radio1 = enum_next();
	globalvar MenuCMD_Radio2 = enum_next();
	globalvar MenuCMD_Radio3 = enum_next();
globalvar MenuCMD_Dont = enum_next();
	globalvar MenuCMD_Gun = enum_next();
globalvar MenuCMD_Help = enum_next();
enum_end();

background_color_start = background_color;
start_time = current_time;

m_bar = winmenu_create_bar();

m_file = winmenu_create_popup();
winmenu_add(m_file, MenuCMD_New, "New" + chr(vk_tab) + "Ctrl+N");
winmenu_add(m_file, MenuCMD_Exit, "Exit" + chr(vk_tab) + "Alt+F4");
//winmenu_set_bitmap_sys(m_file, MenuCMD_Exit, false, wmbm_popup_maximize);
var spr_thumb_up = sprite_add("thumb-up.png", 1, 0, 0, 0, 0);
var bmp_thumb_up = winmenu_bitmap_create_from_sprite(spr_thumb_up, 0);
var spr_thumb_up_d = sprite_add("thumb-up-d.png", 1, 0, 0, 0, 0);
var bmp_thumb_up_d = winmenu_bitmap_create_from_sprite(spr_thumb_up_d, 0);
winmenu_set_bitmap(m_file, MenuCMD_New, false, bmp_thumb_up);
winmenu_set_checkmark_bitmaps(m_file, MenuCMD_New, false, bmp_thumb_up_d, bmp_thumb_up_d);

m_number = winmenu_create_popup();
for (var i = 0; i < 10; i += 1) {
	var _cmd = MenuCMD_Number_1 + i;
	var _flags = 0;
	if (i == 5) _flags |= wmf_bar_break | wmf_hilite | wmf_default;
	winmenu_add(m_number, _cmd, string(i + 1), _flags);
}

m_check = winmenu_create_popup();
winmenu_add(m_check, MenuCMD_Check1, "Checkbox 1", wmf_checked);
winmenu_add(m_check, MenuCMD_Check2, "Checkbox 2");
winmenu_add(m_check, 0, "", wmf_separator);
winmenu_add(m_check, MenuCMD_Radio1, "Radio 1");
winmenu_add(m_check, MenuCMD_Radio2, "Radio 2", wmf_disabled);
winmenu_add(m_check, MenuCMD_Radio3, "Radio 3");
winmenu_set_radio_group(m_check, MenuCMD_Radio1, MenuCMD_Radio3, MenuCMD_Radio2, false);

m_dont = winmenu_create_popup();
winmenu_add(m_dont, MenuCMD_Gun, "?!");
var gun = sprite_add("gun.png", 1, 0, 0, 0, 0);
var gun_bmp = winmenu_bitmap_create_from_sprite(gun, 0);
var gun_l = sprite_add("gun-l.png", 1, 0, 0, 0, 0);
var gun_l_bmp = winmenu_bitmap_create_from_sprite(gun_l, 0);
var gun_ld = sprite_add("gun-ld.png", 1, 0, 0, 0, 0);
var gun_ld_bmp = winmenu_bitmap_create_from_sprite(gun_ld, 0);
winmenu_set_bitmap(m_dont, MenuCMD_Gun, false, gun_bmp);
winmenu_set_checkmark_bitmaps(m_dont, MenuCMD_Gun, false, gun_ld_bmp, gun_l_bmp);

winmenu_add_menu(m_bar, MenuCMD_File, m_file, "File");
winmenu_add_menu(m_bar, MenuCMD_Numbers, m_number, "Numbers");
winmenu_add_menu(m_bar, MenuCMD_Checkboxes, m_check, "Checkboxes");
winmenu_set_checked(m_bar, MenuCMD_Checkboxes, false, true);
winmenu_add_menu(m_bar, MenuCMD_Dont, m_dont, "Don't");

winmenu_add(m_bar, MenuCMD_Help, "?", wmf_right_justify);

winmenu_bar_set(m_bar);
// make space for the m_bar bar!
var bar_info = winmenu_bar_get_info();
var bar_height = ds_map_find_value(bar_info, "height");
window_set_size(window_get_width(), window_get_height() + bar_height);
ds_map_destroy(bar_info);

enum_start(100);
globalvar SysCMD_CustomMenus = enum_next();
globalvar SysCMD_InGameMaker = enum_next();
enum_end();

var m_sys = winmenu_sysmenu_get();
winmenu_add(m_sys, SysCMD_InGameMaker, "in GameMaker!");
winmenu_insert_menu(m_sys, SysCMD_InGameMaker, false, SysCMD_CustomMenus, m_check, "Custom menus");

#event alarm0
background_color = background_color_start;

#event other_user0
var _cmd = global.__winmenu_arg;
var _cmd_str = string(_cmd);
var _cmd_text = winmenu_get_text(m_bar, _cmd, false);
if (!is_string(_cmd_text)) _cmd_text = "???";
trace("[winmenu] Item " + _cmd_str + ' ("' + _cmd_text + '") was clicked.');
switch (_cmd) {
	case MenuCMD_New:
		background_color = $805040;
		alarm[0] = 30;
		break;
	case MenuCMD_Exit:
		game_end();
		break;
	case MenuCMD_Check1: case MenuCMD_Check2:
		var _checked = winmenu_get_checked(m_check, _cmd, false);
		if (is_real(_checked)) winmenu_set_checked(m_check, _cmd, false, !_checked);
		break;
	case MenuCMD_Radio1: case MenuCMD_Radio2: case MenuCMD_Radio3:
		winmenu_set_radio_group(m_check, MenuCMD_Radio1, MenuCMD_Radio3, _cmd, false);
		break;
	case MenuCMD_Gun:
		var _checked = winmenu_get_checked(m_dont, _cmd, false);
		if (is_real(_checked)) winmenu_set_checked(m_dont, _cmd, false, !_checked);
		break;
	case MenuCMD_Help:
		show_message("Help??");
		break;
}

#event other_user1
var _cmd = global.__winmenu_arg;
var _cmd_str = string(_cmd);
trace("[winmenu] System item " + _cmd_str + " was clicked.");

#event step
// winmenu_update();
// can't script_execute a snippet... for now
var _step, _handler, _count;
for (_step = 0; _step < 2; _step += 1) {
    repeat (winmenu_queue_size(_step)) {
    	global.__winmenu_arg = winmenu_queue_pop(_step);
    	event_user(_step);
    }
}

if (mouse_check_button_pressed(mb_right)) {
	var _item = winmenu_show_popup(m_check, 0, display_mouse_get_x(), display_mouse_get_y());
}


#event draw
draw_text(5, 5, string(floor((current_time - start_time) / 1000))
	 + "#Window: " + string(window_get_width()) + "x" + string(window_get_height())
)
draw_rectangle(3, 3, room_width - 3, room_height - 3, 1);