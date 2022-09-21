

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libymgcp STATIC

	endpoint.cpp
	engine.cpp
	message.cpp
	transaction.cpp

	yatemgcp.h
	
)

SET_PROPERTY(TARGET libymgcp PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libymgcp yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libymgcp LIBRARY DESTINATION lib )


INSTALL(FILES yatemgcp.h
	DESTINATION include 
)
