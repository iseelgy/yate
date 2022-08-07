cmake_minimum_required (VERSION 3.2)

PROJECT(extlogger)


## 头文件目录
INCLUDE_DIRECTORIES( 
		../../
		../../../libs/json 
			)
			


ADD_LIBRARY(extlogger STATIC
	extlogger.h
    extlogger.cpp
)

SET_PROPERTY(TARGET extlogger PROPERTY FOLDER "ext-libs")

## 链接Yate库
TARGET_LINK_LIBRARIES( extlogger yateengine json )

# Library
# Note: may not work on windows
install (TARGETS extlogger ARCHIVE DESTINATION "lib" LIBRARY DESTINATION "lib" )


	 
	 
