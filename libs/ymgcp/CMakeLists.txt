

INCLUDE_DIRECTORIES( . )

SET(YATE_EXT_LIB_TARTGET ymgcp)

ADD_LIBRARY(${YATE_EXT_LIB_TARTGET} STATIC

    endpoint.cpp
    engine.cpp
    message.cpp
    transaction.cpp

)


## 链接Yate库
TARGET_LINK_LIBRARIES( ${YATE_EXT_LIB_TARTGET} yateengine )

SET_PROPERTY(TARGET ${YATE_EXT_LIB_TARTGET} PROPERTY FOLDER "libs")

