

INCLUDE_DIRECTORIES( . )

SET(YATE_EXT_LIB_TARTGET yjabber)

ADD_LIBRARY(${YATE_EXT_LIB_TARTGET} STATIC

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

