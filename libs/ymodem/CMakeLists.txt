

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libymodem STATIC

	yatemodem.h
	
	modem.cpp
	uart.cpp
	
)

SET_PROPERTY(TARGET libymodem PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libymodem yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libymodem LIBRARY DESTINATION lib )


INSTALL(FILES yatemodem.h
	DESTINATION include 
)
