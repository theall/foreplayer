@echo off
set CURDIR=%cd%
pushd %temp%
if not exist audio3d_build md audio3d_build
cd audio3d_build
cmake %CURDIR% -G"MinGW Makefiles"
mingw32-make -j2 install
popd
@echo on