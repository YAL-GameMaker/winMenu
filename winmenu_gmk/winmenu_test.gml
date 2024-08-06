#define enum_start
/// (?enum_index)
if (argument_count > 0) {
	global.__enum_index = argument[0];
} else global.__enum_index = 0;

#define enum_next
var _index = global.__enum_index;
global.__enum_index += 1;
return _index;

#define enum_end
global.__enum_index = "";