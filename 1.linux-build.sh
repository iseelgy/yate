
rm build/CMakeCache.txt

cmake 	-B build \
		-DCMAKE_PREFIX_PATH=/mnt/c/install/linux \
		-DCMAKE_INSTALL_PREFIX=/mnt/c/install/linux/yate \
		./
