

INCLUDE_DIRECTORIES( ./
	
)


ADD_LIBRARY(libyscript STATIC

	evaluator.cpp
	javascript.cpp
	jsobjects.cpp
	script.cpp
	
	yatescript.h
)

SET_PROPERTY(TARGET libyscript PROPERTY FOLDER "libs-yate")

## 链接Yate库
TARGET_LINK_LIBRARIES( libyscript yateengine )
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS libyscript LIBRARY DESTINATION lib )


INSTALL(FILES yatescript.h
	DESTINATION include 
)
