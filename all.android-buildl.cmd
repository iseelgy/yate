echo off

set "top_path=%~dp0"

:: ����ԭ��·��
set save_path=%PATH%

:: ��Ҫ��ϵͳ�������� MY_ANDROID_CMAKE���ñ���ΪAndroidStudio�ṩ��cmake�Ŀ�ִ���ļ�·��,
:: ���磺SET MY_ANDROID_CMAKE=D:\Android\sdk\cmake\3.22.1\bin;

:: ��Ҫ��ϵͳ�������� MY_ANDROID_NDK���ñ���ΪAndroidStudio�ṩ��NDK·��, 
:: ���磺SET MY_ANDROID_NDK=D:\Android\sdk\ndk\21.0.6113669

set PATH=%MY_ANDROID_CMAKE%;

set platform_type=android-26

set src_dir=.


::cmake.exe --help

:: ================================================================================================
:: ================================================================================================

set arch=armeabi-v7a

del android-%arch%\CMakeCache.txt

cmake.exe -G "Unix Makefiles" ^
		-B android-%arch% ^
		-DCMAKE_PREFIX_PATH=/install/android/%arch% ^
		-DCMAKE_STAGING_PREFIX=/install/android/%arch%/yate ^
		-DCMAKE_INSTALL_PREFIX=/install/android/%arch%/yate ^
		-DCMAKE_TOOLCHAIN_FILE=%MY_ANDROID_NDK%/build/cmake/android.toolchain.cmake ^
		-DCMAKE_MAKE_PROGRAM="%MY_ANDROID_NDK%/prebuilt/windows-x86_64/bin/make.exe" ^
		-DANDROID_ABI="%arch%" ^
		-DANDROID_NDK=%MY_ANDROID_NDK% ^
		-DANDROID_PLATFORM=%platform_type% ^
		%src_dir%

if %errorlevel% NEQ 0 (
	echo cmake %arch% ���� %errorlevel%
	goto error_return
)

cmake.exe --build android-%arch%

if %errorlevel% NEQ 0 (
	echo cmake build %arch% ���� %errorlevel%
	goto error_return
)

cmake.exe --install android-%arch%

if %errorlevel% NEQ 0 (
	echo cmake install %arch% ���� %errorlevel%
	goto error_return
)

:: ================================================================================================
:: ================================================================================================

set arch=arm64-v8a

del android-%arch%\CMakeCache.txt

cmake.exe -G "Unix Makefiles"	^
		-B android-%arch% ^
		-DCMAKE_PREFIX_PATH=/install/android/%arch% ^
		-DCMAKE_STAGING_PREFIX=/install/android/%arch%/yate ^
		-DCMAKE_INSTALL_PREFIX=/install/android/%arch%/yate ^
		-DCMAKE_TOOLCHAIN_FILE=%MY_ANDROID_NDK%/build/cmake/android.toolchain.cmake ^
		-DCMAKE_MAKE_PROGRAM="%MY_ANDROID_NDK%/prebuilt/windows-x86_64/bin/make.exe" ^
		-DANDROID_ABI="%arch%" ^
		-DANDROID_NDK=%MY_ANDROID_NDK% ^
		-DANDROID_PLATFORM=%platform_type% ^
		%src_dir%

if %errorlevel% NEQ 0 (
	echo cmake %arch% ���� %errorlevel%
	goto error_return
)

cmake.exe --build android-%arch%

if %errorlevel% NEQ 0 (
	echo cmake build %arch% ���� %errorlevel%
	goto error_return
)

cmake.exe --install android-%arch%

if %errorlevel% NEQ 0 (
	echo cmake install %arch% ���� %errorlevel%
	goto error_return
)

goto end_return

:: ================================================================================================
:: ================================================================================================

:error_return

:: �ָ�·��
set PATH=%save_path%;

exit /b 1

:end_return

