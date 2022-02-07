
INCLUDE_DIRECTORIES( . )

SET(YATE_EXT_LIB_TARTGET ysdp)

ADD_LIBRARY(${YATE_EXT_LIB_TARTGET} STATIC

    media.cpp
    parser.cpp
    session.cpp
    
)


## 链接Yate库
TARGET_LINK_LIBRARIES( ${YATE_EXT_LIB_TARTGET} yateengine )

SET_PROPERTY(TARGET ${YATE_EXT_LIB_TARTGET} PROPERTY FOLDER "libs")
