@echo off
cls



:: Function to simulate loading with dots
echo.
echo.
call :loading "Initializing the system..."
echo.
call :loading "Members..."
call :loading "Samuel Angelo Udtohan"
call :loading "Marchus Deligero"
call :loading "David Gelasan"
echo.



:: Kill old instance if running
taskkill /f /im mcdoPayroll.exe >nul 2>&1



:: Compile
gcc mcdoPayroll.c -o mcdoPayroll

if exist mcdoPayroll.exe (
    echo Compilation successful...
    call :loading "Launching our MCDO PAYROLL SYSTEM..."
    mcdoPayroll.exe
) else (
    echo Compilation failed. Please check your code.
)
pause
exit /b



:: Loading function
:loading
setlocal
set text=%~1
<nul set /p= %text%
for /l %%i in (1,1,1) do (
    <nul set /p=
    timeout /t 1 >nul
)
echo.
endlocal
exit /b
