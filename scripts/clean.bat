@echo off
setlocal

set "ROOT_DIR=%~dp0.."
pushd "%ROOT_DIR%" >nul

echo Cleaning build directories...

if exist build\bin rmdir /s /q build\bin
if exist build\bin-int rmdir /s /q build\bin-int

echo Cleaning Visual Studio files...

if exist build\.vs rmdir /s /q build\.vs

del /q build\*.sln >nul 2>&1
del /q build\*.vcxproj >nul 2>&1
del /q build\*.vcxproj.filters >nul 2>&1
del /q build\*.vcxproj.user >nul 2>&1

echo Clean complete!
popd >nul
pause
