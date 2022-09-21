

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libypbx STATIC

	yatepbx.h
	
	assist.cpp
	multiroute.cpp
)

SET_PROPERTY(TARGET libypbx PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libypbx yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libypbx LIBRARY DESTINATION lib )


INSTALL(FILES yatepbx.h
	DESTINATION include 
)
