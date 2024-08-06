- AppendMenu ➜ `winmenu_add`
	> Appends a new item to the end of the specified menu bar, drop-down menu, submenu, or shortcut menu. You can use this function to specify the content, appearance, and behavior of the menu item.
- CheckMenuItem ➜ `winmenu_set_checked`
	> Sets the state of the specified menu item's check-mark attribute to either selected or clear.
- CheckMenuRadioItem ➜ `winmenu_set_radio_group`
	> Checks a specified menu item and makes it a radio item. At the same time, the function clears all other menu items in the associated group and clears the radio-item type flag for those items.
- CreateMenu ➜ `winmenu_create`
	> Creates a menu. The menu is initially empty, but it can be filled with menu items by using the InsertMenuItem, AppendMenu, and InsertMenu functions.
- CreatePopupMenu ➜ `winmenu_create_popup`
	> Creates a drop-down menu, submenu, or shortcut menu. The menu is initially empty. You can insert or append menu items by using the InsertMenuItem function. You can also use the InsertMenu function to insert menu items and the AppendMenu function to append menu items.
- DeleteMenu ➜ `winmenu_delete`
	> Deletes an item from the specified menu. If the menu item opens a menu or submenu, this function destroys the handle to the menu or submenu and frees the memory used by the menu or submenu.
- DestroyMenu ➜ `winmenu_destroy`
	> Destroys the specified menu and frees any memory that the menu occupies.
- DrawMenuBar ➜ `winmenu_bar_redraw`
	> Redraws the menu bar of the specified window. If the menu bar changes after the system has created the window, this function must be called to draw the changed menu bar.
- EnableMenuItem ➜ `winmenu_set_enabled`
	> Enables, disables, or grays the specified menu item.
- EndMenu ➜ not needed?
	> Ends the calling thread's active menu.
- GetMenu ➜ not needed? Blocks thread anyway
	> Retrieves a handle to the menu assigned to the specified window.
- GetMenuBarInfo ➜ `winmenu_bar_get_info`, `winmenu_sysmenu_get_info`
	> Retrieves information about the specified menu bar.
- GetMenuCheckMarkDimensions ➜ not now
	> Retrieves the dimensions of the default check-mark bitmap. The system displays this bitmap next to selected menu items. Before calling the SetMenuItemBitmaps function to replace the default check-mark bitmap for a menu item, an application must determine the correct bitmap size by calling GetMenuCheckMarkDimensions.
- GetMenuDefaultItem ➜ `winmenu_get_default_item`
	> Determines the default menu item on the specified menu.
- GetMenuInfo ➜ `winmenu_get_max_height` (height only)
	> Retrieves information about a specified menu.
- GetMenuItemCount ➜ `winmenu_size`
	> Retrieves the number of items in the specified menu.
- GetMenuItemID ➜ `winmenu_get_id` (GetMenuItemInfoW)
	> Retrieves the menu item identifier of a menu item located at the specified position in a menu.
- GetMenuItemInfo ➜ (many)
	> Retrieves information about a menu item.
- GetMenuItemRect ➜ `winmenu_get_item_rect`
	> Retrieves the bounding rectangle for the specified menu item.
- GetMenuState ➜ `winmenu_get_flags` (GetMenuItemInfoW)
	> Retrieves the menu flags associated with the specified menu item. If the menu item opens a submenu, this function also returns the number of items in the submenu.
- GetMenuString ➜ `winmenu_get_text` (GetMenuItemInfoW)
	> Copies the text string of the specified menu item into the specified buffer.
- GetSubMenu ➜ `winmenu_get_submenu` (GetMenuItemInfoW)
	> Retrieves a handle to the drop-down menu or submenu activated by the specified menu item.
- GetSystemMenu ➜ `winmenu_sysmenu_get`
	> Enables the application to access the window menu (also known as the system menu or the control menu) for copying and modifying.
- HiliteMenuItem ➜ `winmenu_set_hilite`
	> Highlights or removes the highlighting from an item in a menu bar.
- InsertMenu ➜ undocumented
- InsertMenuItem ➜ `winmenu_insert`
	> Inserts a new menu item at the specified position in a menu.
- IsMenu ➜ `winmenu_handle_is_menu`
	> Determines whether a handle is a menu handle.
- LoadMenu ➜ incompatible
	> Loads the specified menu resource from the executable (.exe) file associated with an application instance.
- LoadMenuIndirect ➜ incompatible
	> Loads the specified menu template in memory.
- MenuItemFromPoint ➜ `winmenu_item_from_point`
	> Determines which menu item, if any, is at the specified location.
- ModifyMenu ➜ obsolete
	> Changes an existing menu item. This function is used to specify the content, appearance, and behavior of the menu item.
- RemoveMenu ➜ `winmenu_delete_soft`
	> Deletes a menu item or detaches a submenu from the specified menu. If the menu item opens a drop-down menu or submenu, RemoveMenu does not destroy the menu or its handle, allowing the menu to be reused. Before this function is called, the GetSubMenu function should retrieve a handle to the drop-down menu or submenu.
- SetMenu ➜ `winmenu_bar_set`
	> Assigns a new menu to the specified window.
- SetMenuDefaultItem ➜ `winmenu_set_default_item`
	> Sets the default menu item for the specified menu.
- SetMenuInfo ➜ `winmenu_set_max_height` (height only)
	> Sets information for a specified menu.
- SetMenuItemBitmaps ➜ not now
	> Associates the specified bitmap with a menu item. Whether the menu item is selected or clear, the system displays the appropriate bitmap next to the menu item.
- SetMenuItemInfo ➜ (many)
	> Changes information about a menu item.
- TrackPopupMenu ➜ obsolete
	> Displays a shortcut menu at the specified location and tracks the selection of items on the menu. The shortcut menu can appear anywhere on the screen.
- TrackPopupMenuEx ➜ `winmenu_popup_show`
	> Displays a shortcut menu at the specified location and tracks the selection of items on the shortcut menu. The shortcut menu can appear anywhere on the screen.