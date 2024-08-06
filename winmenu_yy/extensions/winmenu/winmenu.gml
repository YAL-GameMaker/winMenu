#define winmenu_preinit
//#init winmenu_preinit
//#global winmenu_handler
//#global winmenu_system_handler
winmenu_handler = -1;
winmenu_system_handler = -1;
global.__ptrt_HMENU = ["HMENU"];
// GMS >= 1:
global.__winmenu_bar = undefined;
global.__winmenu_sysmenu = undefined;
/*/
global.__winmenu_bar = -1;
global.__winmenu_sysmenu = -1;
//*/

#define winmenu_update
/// ()
var _step, _handler, _count;
for (_step = 0; _step < 2; _step++) {
    if (_step) {
        _handler = winmenu_system_handler;
    } else {
        _handler = winmenu_handler;
    }
    var _has_handler = _handler != -1;
    /* GMS >= 2.3:
    var _is_method = _has_handler && is_method(_handler);
    //*/
    repeat (winmenu_queue_size(_step)) {
        var _cmd = winmenu_queue_pop(_step);
        /* GMS >= 2.3:
        if (_is_method) {
            _handler(_cmd);
        } else // ->
        //*/
        if (_has_handler) {
            script_execute(_handler, _cmd);
        } else {
            var _cmd_str = string(_cmd);
            // GMS >= 1:
            var _cmd_hex;
            if (_cmd != 0) {
                _cmd_hex = string(ptr(_cmd));
                var i = 1;
                repeat (16) {
                    if (string_byte_at(_cmd_hex, i) == ord("0")) {
                        i += 1;
                    } else break;
                }
                if (i > 1) _cmd_hex = string_delete(_cmd_hex, 1, i - 1);
            } else _cmd_hex = "0";
            _cmd_str += " (0x" + _cmd_hex + ")";
            //*/
            if (_step) {
                show_debug_message("[winmenu] System item " + _cmd_str + " was clicked.");
            } else {
                show_debug_message("[winmenu] Item " + _cmd_str + " was clicked.");
            }
        }
    }
}

#define winmenu_prepare_buffer
/// (size:int)->buffer~
var _size = argument0;
gml_pragma("global", "global.__winmenu_buffer = undefined");
var _buf = global.__winmenu_buffer;
if (_buf == undefined) {
    _buf = buffer_create(_size, buffer_grow, 1);
    global.__winmenu_buffer = _buf;
} else if (buffer_get_size(_buf) < _size) {
    buffer_resize(_buf, _size);
}
buffer_seek(_buf, buffer_seek_start, 0);
return _buf;

#define winmenu_bar_get
/// ()->
return global.__winmenu_bar;

#define winmenu_bar_set
/// (menu)
var _menu = argument0;
global.__winmenu_bar = _menu;
winmenu_bar_set_raw(_menu);

#define winmenu_bar_reset
/// ()
var _menu = argument0;
/// GMS >= 1:
global.__winmenu_bar = undefined;
/*/
global.__winmenu_bar = -1;
//*/
winmenu_bar_reset_raw();

#define winmenu_sysmenu_get
/// (?revert)->
var _revert = argument_count > 0 ? argument[0] : false;
if (!_revert) {
    /// GMS >= 1:
    if (global.__winmenu_sysmenu != undefined) return global.__winmenu_sysmenu;
    /*/
    if (global.__winmenu_sysmenu != -1) return global.__winmenu_sysmenu;
    //*/
}
global.__winmenu_sysmenu = winmenu_sysmenu_get_raw(_revert);
return global.__winmenu_sysmenu;
