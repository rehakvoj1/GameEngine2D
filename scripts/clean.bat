@echo off

echo Cleaning build directories...

if exist bin rmdir /s /q bin
if exist bin-int rmdir /s /q bin-int

echo Cleaning Visual Studio files...

if exist .vs rmdir /s /q .vs

del /s /q *.sln >nul 2>&1
del /s /q *.vcxproj >nul 2>&1
del /s /q *.vcxproj.filters >nul 2>&1
del /s /q *.vcxproj.user >nul 2>&1

echo Clean complete!
pause