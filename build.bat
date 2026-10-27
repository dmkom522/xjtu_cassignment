@echo off
setlocal
powershell.exe -NoProfile -File "%~dp0scripts\build.ps1" -Test
if errorlevel 1 (
    pause
    exit /b 1
)
exit /b 0
