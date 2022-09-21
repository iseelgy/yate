

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libyasn STATIC

	yateasn.h
	asn.cpp
)

SET_PROPERTY(TARGET libyasn PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libyasn yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libyasn LIBRARY DESTINATION lib )


INSTALL(FILES yateasn.h
	DESTINATION include 
)
