echo off

set "top_path=%~dp0"

:: ��Ҫ��ϵͳ�������� MY_ANDROID_CMAKE���ñ���ΪAndroidStudio�ṩ��cmake�Ŀ�ִ���ļ�·��,
:: ���磺SET MY_ANDROID_CMAKE=D:\Android\sdk\cmake\3.22.1\bin;

:: ��Ҫ��ϵͳ�������� MY_ANDROID_NDK���ñ���ΪAndroidStudio�ṩ��NDK·��, 
:: ���磺SET MY_ANDROID_NDK=D:\Android\sdk\ndk\21.0.6113669

set PATH=%MY_ANDROID_CMAKE%;

::cmake.exe --help

:: ϵͳ�汾
set platform_type=android-28

:: ��װ·��
set install_prefix=/install/android

:: cmake Դ��·��
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
	echo cmake %arch% ���� %errorlevel%
	exit /b 1
)



