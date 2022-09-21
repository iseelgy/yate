

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libyjabber STATIC

	yatejingle.h
	jbengine.cpp
	jbstream.cpp
	jgengine.cpp
	session.cpp
	xmpputils.cpp xmpputils.h
	yatejabber.h
	yatejingle.h
)

SET_PROPERTY(TARGET libyjabber PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libyjabber yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libyjabber LIBRARY DESTINATION lib )


INSTALL(FILES 
	yatejabber.h
	yatejingle.h
	xmpputils.h
	DESTINATION include 
)
