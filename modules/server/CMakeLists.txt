INCLUDE_DIRECTORIES( ./
		../libs/ysip
)


##==========================================================

ADD_LIBRARY(regfile SHARED
    regfile.cpp
)

SET_PROPERTY(TARGET regfile PROPERTY FOLDER "modules-server")

## 链接Yate库
TARGET_LINK_LIBRARIES( regfile yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(regfile PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(regfile PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS regfile LIBRARY DESTINATION modules/server )

##==========================================================

