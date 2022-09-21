

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libradio STATIC

	yateradio.h
	codec.cpp
	radio.cpp
)

SET_PROPERTY(TARGET libradio PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libradio yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libradio LIBRARY DESTINATION lib )


INSTALL(FILES yateradio.h
	DESTINATION include 
)
