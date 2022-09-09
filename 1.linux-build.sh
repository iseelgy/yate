
rm build/CMakeCache.txt

cmake 	-B build \
		-DCMAKE_PREFIX_PATH=/mnt/e/install/linux \
		-DCMAKE_INSTALL_PREFIX=/mnt/e/install/linux \
		./
