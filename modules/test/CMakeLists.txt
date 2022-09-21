
##==========================================================

ADD_LIBRARY(msgdelay SHARED
    msgdelay.cpp
)

SET_PROPERTY(TARGET msgdelay PROPERTY FOLDER "modules")

## 链接Yate库
TARGET_LINK_LIBRARIES( msgdelay yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(msgdelay PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(msgdelay PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS msgdelay LIBRARY DESTINATION modules )

##==========================================================


