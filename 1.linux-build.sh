
rm build/CMakeCache.txt

cmake 	-B build \
		-DCMAKE_PREFIX_PATH=/install/linux \
		-DCMAKE_INSTALL_PREFIX=/install/linux/yate \
		./
