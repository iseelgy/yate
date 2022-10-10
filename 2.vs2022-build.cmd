
del msvs2022\CMakeCache.txt

cmake 	-B msvs2022 ^
		-G "Visual Studio 17 2022" ^
		-DCMAKE_PREFIX_PATH=/install/vs2022 ^
 		-DCMAKE_INSTALL_PREFIX=/install/vs2022/yate ^
		.


