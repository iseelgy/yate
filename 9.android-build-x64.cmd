echo off

set "top_path=%~dp0"

:: ��Ҫ��ϵͳ�������� MY_ANDROID_CMAKE���ñ���ΪAndroidStudio�ṩ��cmake�Ŀ�ִ���ļ�·��,
:: ���磺SET MY_ANDROID_CMAKE=D:\Android\sdk\cmake\3.22.1\bin;

:: ��Ҫ��ϵͳ�������� MY_ANDROID_NDK���ñ���ΪAndroidStudio�ṩ��NDK·��, 
:: ���磺SET MY_ANDROID_NDK=D:\Android\sdk\ndk\21.0.6113669

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
	echo cmake ���� %errorlevel%
	exit /b 1
)


