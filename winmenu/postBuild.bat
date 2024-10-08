@echo off
set dllPath=%~1
set solutionDir=%~2
set projectDir=%~3
set arch=%~4
set config=%~5

echo Running post-build for %config%

set extName=winmenu
set dllName=winmenu

set gmlDir8=%solutionDir%winmenu_gmk
set gmlDir14=%solutionDir%winmenu.gmx
set gmlDir23=%solutionDir%winmenu_23

set ext8=%gmlDir8%
set ext14=%gmlDir14%\extensions\%extName%
set ext23=%gmlDir23%\extensions\%extName%

set dllRel=%dllName%.dll
set cppRel=%dllName%.cpp
set cppPath=%ext23%\%cppRel%
set gmlPath=%ext23%\*.gml
set docName=%extName%.html
set docPath=%solutionDir%export\%docName%

echo Copying documentation...
copy /Y %docPath% "%gmlDir8%\%docName%"
if not exist "%gmlDir14%\datafiles" mkdir "%gmlDir14%\datafiles"
copy /Y %docPath% "%gmlDir14%\datafiles\%docName%"
if not exist "%gmlDir23%\datafiles" mkdir "%gmlDir23%\datafiles"
copy /Y %docPath% "%gmlDir23%\datafiles\%docName%"

where /q gmxgen
if %ERRORLEVEL% EQU 0 (
	
	echo Combining the source files...
	type "%projectDir%*.h" "%projectDir%*.cpp" >"%cppPath%" 2>nul
	
	echo Running GmxGen...
	
	gmxgen "%ext23%\%extName%.yy" ^
	--copy "%dllPath%" "%dllRel%:%arch%"
	
	gmxgen "%ext14%.extension.gmx" ^
	--copy "%dllPath%" "%dllRel%:%arch%" ^
	--copy "%cppPath%" "%cppRel%" ^
	--copy "%gmlPath%" "*.gml"

	cmd /C gmxgen "%ext8%\%extName%.gmxgen81" ^
	--copy "%dllPath%" "%dllRel%:%arch%" ^
	--copy "%dllPath%" "%dllRel%:%arch%" ^
	--copy "%cppPath%" "%cppRel%" ^
	--copy "%ext23%\%extName%.gml" "%extName%_core.gml" ^
	--gmk-loader %extName%_init_dll^
	--strip-cc --disable-incompatible

) else (

	echo Copying DLLs...
	if "%arch%" EQU "x64" (
		copy /Y "%dllPath%" "%ext23%\%dllName%_x64.dll"
	) else (
		copy /Y "%dllPath%" "%ext22%\%dllRel%"
		copy /Y "%dllPath%" "%ext14%\%dllRel%"
		copy /Y "%dllPath%" "%ext8%\%dllRel%"
	)
	
	echo Copying GML files...
	robocopy %ext23% %ext22% *.gml /L >nul
	robocopy %ext23% %ext14% *.gml /L >nul

	echo postBuild.bat: Warning N/A: Could not find GmxGen - extensions will not be updated automatically. See https://github.com/YAL-GameMaker-Tools/GmxGen for setup.
)