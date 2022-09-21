

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libysip STATIC

	yatesip.h
	util.h 
	util.cpp
	transaction.cpp
	message.cpp
	engine.cpp
)

SET_PROPERTY(TARGET libysip PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libysip yateengine libysdp)
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libysip LIBRARY DESTINATION lib )


INSTALL(FILES yatesip.h
	DESTINATION include 
)
