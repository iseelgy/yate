

#rm linux/CMakeCache.txt

rm -rf build

cmake 	-B build \
		-DCMAKE_INSTALL_PREFIX=build/install \
		./


