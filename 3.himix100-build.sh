#!/bin/sh

cmake 	-B out-himix100 \
		-DCROSS_COMPILE_HIMIX100=1  \
		-DCMAKE_SYSTEM_NAME=Linux \
		-DTOOLCHAIN_DIR=aarch64-himix100-linux- \
		-DCMAKE_C_COMPILER=aarch64-himix100-linux-gcc \
		-DCMAKE_CXX_COMPILER=aarch64-himix100-linux-g++ \
		-DCMAKE_PREFIX_PATH=/mnt/c/install/out-himix100 \
		-DCMAKE_INSTALL_PREFIX=/mnt/c/install/out-himix100/yate \
		./
