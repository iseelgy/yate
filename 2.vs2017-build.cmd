
del msvs2017\CMakeCache.txt

cmake 	-B msvs2017 ^
		-G "Visual Studio 15 2017" ^
		-DCMAKE_PREFIX_PATH=/install/vs2017 ^
 		-DCMAKE_INSTALL_PREFIX=/install/vs2017/yate ^
		.


