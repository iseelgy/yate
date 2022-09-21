

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libysdp STATIC

	yatesdp.h
	media.cpp
	parser.cpp
	session.cpp
)

SET_PROPERTY(TARGET libysdp PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libysdp yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libysdp LIBRARY DESTINATION lib )


INSTALL(FILES yatesdp.h
	DESTINATION include 
)
