
INCLUDE_DIRECTORIES( . ../yasn)

SET(YATE_EXT_LIB_TARTGET ysig)

ADD_LIBRARY(${YATE_EXT_LIB_TARTGET} 
	${LIB_BUILD_TYPE}
    address.cpp
    dumper.cpp
    engine.cpp
    interface.cpp
    isup.cpp
    layer2.cpp
    layer3.cpp
    layer4.cpp
    main-ss7test.cpp
    management.cpp
    q921.cpp
    q931.cpp
    router.cpp
    sccp.cpp
    sigcall.cpp
    sigtran.cpp
    tcap.cpp
    testpart.cpp
    tup.cpp    
)


## 链接Yate库
TARGET_LINK_LIBRARIES( ${YATE_EXT_LIB_TARTGET} yateengine )

SET_PROPERTY(TARGET ${YATE_EXT_LIB_TARTGET} PROPERTY FOLDER "libs")

if( ${LIB_BUILD_TYPE} )
	INSTALL (TARGETS ${YATE_EXT_LIB_TARTGET} DESTINATION lib)
else()
	INSTALL (TARGETS ${YATE_EXT_LIB_TARTGET} DESTINATION .)
endif()

