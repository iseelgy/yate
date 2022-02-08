
del vs2017\CMakeCache.txt

cmake 	-B vs2017 ^
		-G "Visual Studio 15 2017" ^
		-DYATE_BUILD_ALL=ON ^
		-DYATE_BUILD_SIP=OFF ^
		-DYATE_BUILD_TEST=ON ^
		-DCMAKE_INSTALL_PREFIX=/install/windows/vs2017/yate ^
		.


