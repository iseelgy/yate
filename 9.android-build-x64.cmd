echo off

set "top_path=%~dp0"

:: 需要在系统变量设置 MY_ANDROID_CMAKE，该变量为AndroidStudio提供的cmake的可执行文件路径,
:: 例如：SET MY_ANDROID_CMAKE=D:\Android\sdk\cmake\3.22.1\bin;

:: 需要在系统变量设置 MY_ANDROID_NDK，该变量为AndroidStudio提供的NDK路径, 
:: 例如：SET MY_ANDROID_NDK=D:\Android\sdk\ndk\21.0.6113669

set PATH=%MY_ANDROID_CMAKE%;

::cmake.exe --help

del android-x64\CMakeCache.txt

cmake.exe -G Ninja	^
		-B android-x64 ^
		-DCMAKE_PREFIX_PATH=/install/android-x64 ^
 		-DCMAKE_INSTALL_PREFIX=/install/android-x64 ^
		-DCMAKE_TOOLCHAIN_FILE=%MY_ANDROID_NDK%/build/cmake/android.toolchain.cmake ^
		-DANDROID_ABI="x86_64" ^
		-DANDROID_NDK=%MY_ANDROID_NDK% ^
		-DANDROID_PLATFORM=android-28 ^
		.

if %errorlevel% NEQ 0 (
	echo cmake 错误 %errorlevel%
	exit /b 1
)


