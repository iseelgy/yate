

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libyrtp STATIC

	yatertp.h
	dejitter.cpp
    secure.cpp
	session.cpp
	transport.cpp
)

SET_PROPERTY(TARGET libyrtp PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libyrtp yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libyrtp LIBRARY DESTINATION lib )


INSTALL(FILES yatertp.h
	DESTINATION include 
)
