echo off

set "top_path=%~dp0"

:: 保存原有路径
set save_path=%PATH%

:: 需要在系统变量设置 MY_ANDROID_CMAKE，该变量为AndroidStudio提供的cmake的可执行文件路径,
:: 例如：SET MY_ANDROID_CMAKE=D:\Android\sdk\cmake\3.22.1\bin;

:: 需要在系统变量设置 MY_ANDROID_NDK，该变量为AndroidStudio提供的NDK路径, 
:: 例如：SET MY_ANDROID_NDK=D:\Android\sdk\ndk\21.0.6113669

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
	echo cmake %arch% 错误 %errorlevel%
	goto error_return
)

cmake.exe --build android-%arch%

if %errorlevel% NEQ 0 (
	echo cmake build %arch% 错误 %errorlevel%
	goto error_return
)

cmake.exe --install android-%arch%

if %errorlevel% NEQ 0 (
	echo cmake install %arch% 错误 %errorlevel%
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
	echo cmake %arch% 错误 %errorlevel%
	goto error_return
)

cmake.exe --build android-%arch%

if %errorlevel% NEQ 0 (
	echo cmake build %arch% 错误 %errorlevel%
	goto error_return
)

cmake.exe --install android-%arch%

if %errorlevel% NEQ 0 (
	echo cmake install %arch% 错误 %errorlevel%
	goto error_return
)

goto end_return

:: ================================================================================================
:: ================================================================================================

:error_return

:: 恢复路径
set PATH=%save_path%;

exit /b 1

:end_return

