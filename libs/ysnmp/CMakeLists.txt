

INCLUDE_DIRECTORIES( ./
	../yasn
	
)


ADD_LIBRARY(libysnmp STATIC

	yatesnmp.h
	snmp.cpp
)

SET_PROPERTY(TARGET libysnmp PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libysnmp yateengine libyateasn)
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libysnmp LIBRARY DESTINATION lib )


INSTALL(FILES yatesnmp.h
	DESTINATION include 
)
