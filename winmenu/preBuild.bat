@echo off
set dllPath=%~1
set solutionDir=%~2
set projectDir=%~3
set arch=%~4
set config=%~5

set extname=winmenu

echo Running pre-build for %config%

where /q GmlCppExtFuncs
if %ERRORLEVEL% EQU 0 (
	echo Running GmlCppExtFuncs...
	GmlCppExtFuncs ^
	--prefix winmenu^
	--cpp "%projectDir%autogen.cpp"^
	--gml "%solutionDir%winmenu_23/extensions/winmenu/autogen.gml"^
	--gmk "%solutionDir%%extname%_gmk/%extname%_autogen.gml"^
	--include "winmenu.h"^
	--index "%projectDir%winmenu.h"^
	--struct auto^
	%projectDir%winmenu.cpp^
	%projectDir%winmenu_*.cpp
)