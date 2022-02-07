

INCLUDE_DIRECTORIES( . )

SET(YATE_EXT_LIB_TARTGET yjabber)

ADD_LIBRARY(${YATE_EXT_LIB_TARTGET} 

	${LIB_BUILD_TYPE}

    jbengine.cpp
    jbstream.cpp
    jgengine.cpp
    session.cpp
    xmpputils.cpp

    xmpputils.h
    yatejabber.h
    yatejingle.h
    
)


## 链接Yate库
TARGET_LINK_LIBRARIES( ${YATE_EXT_LIB_TARTGET} yateengine )

SET_PROPERTY(TARGET ${YATE_EXT_LIB_TARTGET} PROPERTY FOLDER "libs")

if( ${LIB_BUILD_TYPE} )
	INSTALL (TARGETS ${YATE_EXT_LIB_TARTGET} DESTINATION lib)
else()
	INSTALL (TARGETS ${YATE_EXT_LIB_TARTGET} DESTINATION .)
endif()