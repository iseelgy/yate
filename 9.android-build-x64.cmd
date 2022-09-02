echo off

set "top_path=%~dp0"

:: 需要在系统变量设置 MY_ANDROID_CMAKE，该变量为AndroidStudio提供的cmake的可执行文件路径,
:: 例如：SET MY_ANDROID_CMAKE=D:\Android\sdk\cmake\3.22.1\bin;

:: 需要在系统变量设置 MY_ANDROID_NDK，该变量为AndroidStudio提供的NDK路径, 
:: 例如：SET MY_ANDROID_NDK=D:\Android\sdk\ndk\21.0.6113669

set PATH=%MY_ANDROID_CMAKE%;

::cmake.exe --help

:: 系统版本
set platform_type=android-28

:: 安装路径
set install_prefix=/install/android

:: cmake 源码路径
set src_dir=.


set arch=x86_64

del android-%arch%\CMakeCache.txt

cmake.exe -G Ninja	^
		-B android-%arch% ^
		-DCMAKE_PREFIX_PATH=%install_prefix%-%arch% ^
 		-DCMAKE_INSTALL_PREFIX=%install_prefix%-%arch% ^
		-DCMAKE_TOOLCHAIN_FILE=%MY_ANDROID_NDK%/build/cmake/android.toolchain.cmake ^
		-DANDROID_ABI="%arch%" ^
		-DANDROID_NDK=%MY_ANDROID_NDK% ^
		-DANDROID_PLATFORM=%platform_type% ^
		%src_dir%

if %errorlevel% NEQ 0 (
	echo cmake %arch% 错误 %errorlevel%
	exit /b 1
)



