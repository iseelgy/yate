
rm build/CMakeCache.txt

cmake 	-B build \
		-DCMAKE_INSTALL_PREFIX=build/bin \
		./
