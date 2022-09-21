

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libyiax STATIC

	yateiax.h
	engine.cpp
	frame.cpp
	transaction.cpp
)

SET_PROPERTY(TARGET libyiax PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libyiax yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libyiax LIBRARY DESTINATION lib )


INSTALL(FILES yateiax.h
	DESTINATION include 
)
