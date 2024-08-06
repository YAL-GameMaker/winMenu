@echo off

if not exist "winmenu-for-GMS1" mkdir "winmenu-for-GMS1"
cmd /C copyre ..\winmenu.gmx\extensions\winmenu.extension.gmx winmenu-for-GMS1\winmenu.extension.gmx
cmd /C copyre ..\winmenu.gmx\extensions\winmenu winmenu-for-GMS1\winmenu
cmd /C copyre ..\winmenu.gmx\datafiles\winmenu.html winmenu-for-GMS1\winmenu\Assets\datafiles\winmenu.html
cd winmenu-for-GMS1
cmd /C 7z a winmenu-for-GMS1.7z *
move /Y winmenu-for-GMS1.7z ../winmenu-for-GMS1.gmez
cd ..

if not exist "winmenu-for-GMS2\extensions" mkdir "winmenu-for-GMS2\extensions"
if not exist "winmenu-for-GMS2\datafiles" mkdir "winmenu-for-GMS2\datafiles"
if not exist "winmenu-for-GMS2\datafiles_yy" mkdir "winmenu-for-GMS2\datafiles_yy"
cmd /C copyre ..\winmenu_yy\extensions\winmenu winmenu-for-GMS2\extensions\winmenu
cmd /C copyre ..\winmenu_yy\datafiles\winmenu.html winmenu-for-GMS2\datafiles\winmenu.html
cmd /C copyre ..\winmenu_yy\datafiles_yy\winmenu.html.yy winmenu-for-GMS2\datafiles_yy\winmenu.html.yy
cd winmenu-for-GMS2
cmd /C 7z a winmenu-for-GMS2.zip *
move /Y winmenu-for-GMS2.zip ../winmenu-for-GMS2.yymp
cd ..

if not exist "winmenu-for-GMS2.3+\extensions" mkdir "winmenu-for-GMS2.3+\extensions"
if not exist "winmenu-for-GMS2.3+\datafiles" mkdir "winmenu-for-GMS2.3+\datafiles"
cmd /C copyre ..\winmenu_23\extensions\winmenu winmenu-for-GMS2.3+\extensions\winmenu
cmd /C copyre ..\winmenu_23\datafiles\winmenu.html winmenu-for-GMS2.3+\datafiles\winmenu.html
cd winmenu-for-GMS2.3+
cmd /C 7z a winmenu-for-GMS2.3+.zip *
move /Y winmenu-for-GMS2.3+.zip ../winmenu-for-GMS2.3+.yymps
cd ..

pause