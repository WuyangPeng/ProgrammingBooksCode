echo off
if %2 == 95 goto win95
echo Creating project %1

"\Code Co-op\co-op.exe" -Project_Join project:"%1" recipient:"nowhere" user:"Anonymous" email:"anonymous" state:"Observer" script:"\Projects\%1.snc"
if errorlevel 1 goto error
"\Code Co-op\deliver.exe" \Projects\%1\*.snc
"\Code Co-op\co-op.exe"
goto end

:win95
echo Creating project %1 on Windows 95
"\Code Co-op\Win95\co-op.exe" -Project_Join project:"%1" recipient:"nowhere" user:"Anonymous" email:"anonymous" state:"Observer" script:"\Projects\%1.snc"
if errorlevel 1 goto error
"\Code Co-op\Win95\deliver.exe" \Projects\%1\*.snc
"\Code Co-op\Win95\co-op.exe"
:error
echo Error joining project
pause
:end