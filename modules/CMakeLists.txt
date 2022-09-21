
INCLUDE_DIRECTORIES( ./
	../libs/ysip
	../libs/yrtp
	../libs/ysdp
)


ADD_SUBDIRECTORY(client)

ADD_SUBDIRECTORY(server)


##==========================================================
	
ADD_LIBRARY(msgsniff SHARED
    msgsniff.cpp
)

SET_PROPERTY(TARGET msgsniff PROPERTY FOLDER "modules-yate")

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

SET_PROPERTY(TARGET ysockschan PROPERTY FOLDER "modules-yate")

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

SET_PROPERTY(TARGET ystunchan PROPERTY FOLDER "modules-yate")

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

SET_PROPERTY(TARGET rmanager PROPERTY FOLDER "modules-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( rmanager yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(rmanager PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(rmanager PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS rmanager LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(dumbchan SHARED
    dumbchan.cpp
)

SET_PROPERTY(TARGET dumbchan PROPERTY FOLDER "modules-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( dumbchan yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(dumbchan PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(dumbchan PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS dumbchan LIBRARY DESTINATION modules )

##==========================================================


ADD_LIBRARY(extmodule SHARED
    extmodule.cpp
)

SET_PROPERTY(TARGET extmodule PROPERTY FOLDER "modules-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( extmodule yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(extmodule PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(extmodule PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS extmodule LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(fileinfo SHARED
    fileinfo.cpp
)

SET_PROPERTY(TARGET fileinfo PROPERTY FOLDER "modules-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( fileinfo yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(fileinfo PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(fileinfo PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS fileinfo LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(wavefile SHARED
    wavefile.cpp
)

SET_PROPERTY(TARGET wavefile PROPERTY FOLDER "modules-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( wavefile yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(wavefile PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(wavefile PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS wavefile LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(tonedetect SHARED
    tonedetect.cpp
)

SET_PROPERTY(TARGET tonedetect PROPERTY FOLDER "modules-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( tonedetect yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(tonedetect PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(tonedetect PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS tonedetect LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(tonegen SHARED
    tonegen.cpp
)

SET_PROPERTY(TARGET tonegen PROPERTY FOLDER "modules-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( tonegen yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(tonegen PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(tonegen PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS tonegen LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(wiresniff SHARED
    wiresniff.cpp
)

SET_PROPERTY(TARGET wiresniff PROPERTY FOLDER "modules-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( wiresniff yateengine )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(wiresniff PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(wiresniff PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS wiresniff LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(ysipchan SHARED
    ysipchan.cpp
)

SET_PROPERTY(TARGET ysipchan PROPERTY FOLDER "modules-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( ysipchan yateengine libysip libysdp)

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(ysipchan PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(ysipchan PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS ysipchan LIBRARY DESTINATION modules )

##==========================================================

