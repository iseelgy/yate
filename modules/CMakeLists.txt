

##==========================================================
	
ADD_LIBRARY(msgsniff SHARED
    msgsniff.cpp
)

SET_PROPERTY(TARGET msgsniff PROPERTY FOLDER "modules")

## 链接Yate库
TARGET_LINK_LIBRARIES( msgsniff yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(msgsniff PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(msgsniff PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS msgsniff LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(ysockschan SHARED
    ysockschan.cpp
)

SET_PROPERTY(TARGET ysockschan PROPERTY FOLDER "modules")

## 链接Yate库
TARGET_LINK_LIBRARIES( ysockschan yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(ysockschan PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(ysockschan PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS ysockschan LIBRARY DESTINATION modules )
	
##==========================================================

ADD_LIBRARY(ystunchan SHARED
    ystunchan.cpp
)

SET_PROPERTY(TARGET ystunchan PROPERTY FOLDER "modules")

## 链接Yate库
TARGET_LINK_LIBRARIES( ystunchan yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(ystunchan PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(ystunchan PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS ystunchan LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(rmanager SHARED
    rmanager.cpp
)

SET_PROPERTY(TARGET rmanager PROPERTY FOLDER "modules")

## 链接Yate库
TARGET_LINK_LIBRARIES( rmanager yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(rmanager PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(rmanager PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS rmanager LIBRARY DESTINATION modules )


