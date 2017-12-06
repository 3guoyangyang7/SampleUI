@echo off
cd /d %~dp0
rmdir /s /q imgout 
mkdir imgout
cd imgout
mkdir ui
mkdir lib
mkdir etc
cd ..
xcopy resources imgout\ui /d /y /e /h
copy build\*.ftu imgout\ui\
copy build\EasyUIimg.cfg imgout\etc\EasyUI.cfg
copy libs\armeabi\libzkgui.so imgout\lib\libzkgui.so

imagemaker32
echo %errorlevel%

if %errorlevel% == 0 ( 
echo success 
) else (
echo failed!  
)

echo �밴������˳�
pause >nul