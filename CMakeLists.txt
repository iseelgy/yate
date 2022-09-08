cmake_minimum_required (VERSION 3.6)

PROJECT(yate)


# Disable in-source builds to prevent source tree corruption.
if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()


# ---------------------------------------------------------------------------------------
# Set SPDLOG_MASTER_PROJECT to ON if we are building spdlog
# ---------------------------------------------------------------------------------------
# Check if spdlog is being used directly or via add_subdirectory, but allow overriding
if(NOT DEFINED YATE_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(YATE_MASTER_PROJECT ON)
    else()
        set(YATE_MASTER_PROJECT OFF)
    endif()
endif()


SET_PROPERTY(GLOBAL PROPERTY YATE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# set cmake default folder name
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
SET_PROPERTY(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# Generate position-independent code (-fPIC on UNIX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(SPDLOG_INSTALL ON)

##find_package(fmt REQUIRED)
##find_package(spdlog REQUIRED)

ADD_SUBDIRECTORY(3rlibs/fmt-8.1.1 EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(3rlibs/spdlog-1.10.0 EXCLUDE_FROM_ALL)

#MESSAGE( STATUS "fmt_INCLUDE_DIRS: " ${fmt_INCLUDE_DIRS} )
#MESSAGE( STATUS "fmt_LIBRARIES: " ${fmt_LIBRARIES} )
#MESSAGE( STATUS "fmt_LIBRARIES: " fmt:fmt )
#MESSAGE( STATUS "spdlog_INCLUDE_DIRS: " ${spdlog_INCLUDE_DIRS} )
#MESSAGE( STATUS "spdlog_LIBRARIES: " ${spdlog_LIBRARIES} )


# ${LIBEVENT_LIBRARIES}

# ADD_DEFINITIONS( -DFMT_HEADER_ONLY )


INCLUDE_DIRECTORIES( ./
	3rlibs/fmt-8.1.1/include
	3rlibs/spdlog-1.10.0/include
)


if(MSVC)

    INCLUDE_DIRECTORIES(windows)

	set(MSVC_DISABLED_WARNINGS_LIST
	  "C4061"
      "C4100" # 'exarg' : unreferenced formal parameter
      "C4127" # conditional expression is constant
	  "C4131" # 
      "C4200" # nonstandard extension used : zero-sized array in
              # struct/union.
      "C4242" # 'function' : conversion from 'int' to 'uint8_t',
              # possible loss of data
      "C4244" # 'function' : conversion from 'int' to 'uint8_t',
              # possible loss of data
      "C4245" # 'initializing' : conversion from 'long' to
              # 'unsigned long', signed/unsigned mismatch
	  "C4263"
	  "C4264" 
      "C4267" # conversion from 'size_t' to 'int', possible loss of data
      "C4371" # layout of class may have changed from a previous version of the
              # compiler due to better packing of member '...'
      "C4388" # signed/unsigned mismatch
      "C4296" # '>=' : expression is always true
      "C4350" # behavior change: 'std::_Wrap_alloc...'
      "C4365" # '=' : conversion from 'size_t' to 'int',
              # signed/unsigned mismatch
      "C4389" # '!=' : signed/unsigned mismatch
	  "C4456"
	  "C4457"
      "C4464" # relative include path contains '..'
      "C4510" # 'argument' : default constructor could not be generated
      "C4512" # 'argument' : assignment operator could not be generated
      "C4514" # 'function': unreferenced inline function has been removed
      "C4548" # expression before comma has no effect; expected expression with
              # side-effect" caused by FD_* macros.
      "C4577" 
      "C4610" # struct 'argument' can never be instantiated - user defined
              # constructor required.
      "C4623" # default constructor was implicitly defined as deleted
      "C4625" # copy constructor could not be generated because a base class
              # copy constructor is inaccessible or deleted
      "C4626" # assignment operator could not be generated because a base class
              # assignment operator is inaccessible or deleted
	  "C4668" #
	  "C4702"
      "C4706" # assignment within conditional expression
      "C4710" # 'function': function not inlined
      "C4711" # function 'function' selected for inline expansion
	  "C4774"
      "C4800" # 'int' : forcing value to bool 'true' or 'false'
              # (performance warning)
      "C4820" # 'bytes' bytes padding added after construct 'member_name'
	  "C5026" #
	  "C5045" 
      "C5027" # move assignment operator was implicitly defined as deleted
      )
  
	set(MSVC_LEVEL4_WARNINGS_LIST
      # See https://connect.microsoft.com/VisualStudio/feedback/details/1217660/warning-c4265-when-using-functional-header
      "C4265" # class has virtual functions, but destructor is not virtual
      )
  
	string(REPLACE "C" " -wd" MSVC_DISABLED_WARNINGS_STR
                            ${MSVC_DISABLED_WARNINGS_LIST})
	string(REPLACE "C" " -w4" MSVC_LEVEL4_WARNINGS_STR
                            ${MSVC_LEVEL4_WARNINGS_LIST})
  
	set(CMAKE_C_FLAGS   "-Wall ${MSVC_DISABLED_WARNINGS_STR} ${MSVC_LEVEL4_WARNINGS_STR}")
	set(CMAKE_CXX_FLAGS "-Wall ${MSVC_DISABLED_WARNINGS_STR} ${MSVC_LEVEL4_WARNINGS_STR}")
	set(CMAKE_ASM_NASM_FLAGS "-g cv8")

#	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
#	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")  
#	SET(CMAKE_CXX_FLAGS "/EHsc")

	add_definitions(-DATOMIC_OPS)
	add_definitions(-DHAVE_DNS_NAPTR_DATA)

	ADD_DEFINITIONS(-DREGEX_MALLOC 
		-DSTDC_HEADERS 
		-D__STDC__ 
		-DLIBYATE_EXPORTS 
		-D_CRT_SECURE_NO_WARNINGS)	
else()

	SET(GNU_FLAGS "-Wall -O2 -fno-builtin -fpermissive ")
	SET(CMAKE_CXX_FLAGS "-lm ${GNU_FLAGS} ")
	SET(CMAKE_C_FLAGS "${GNU_FLAGS}  ")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

	ADD_DEFINITIONS( -DHAVE_STRING_H 
		-DDEBUG 
		-DSTDC_HEADERS 
		-DHAVE_GCC_FORMAT_CHECK 
		-DHAVE_BLOCK_RETURN 
		-DATOMIC_OPS
		-DHAVE_GMTOFF 
		-DHAVE_INT_TZ
		-DHAVE_POLL)

endif()
		
if(ANDROID)
	ADD_DEFINITIONS(-D_OS_ANDROID_)
endif()


if(WIN32)
	LINK_LIBRARIES(ws2_32 advapi32 dnsapi)	
else()
	if(ANDROID)
		LINK_LIBRARIES(m dl c)
	else()
		LINK_LIBRARIES(m dl c pthread resolv)
	endif()
endif(WIN32)



## 头文件目录
INCLUDE_DIRECTORIES( ./ engine/regex  engine/tables)

set(BUILD_SHARED_LIBS ON)

SET( YFMT_HEADER 
	yfmt/args.h
	yfmt/chrono.h
	yfmt/color.h
	yfmt/compile.h
	yfmt/core.h
	yfmt/format-inl.h
	yfmt/format.h
	yfmt/locale.h
	yfmt/os.h
	yfmt/ostream.h
	yfmt/printf.h
	yfmt/ranges.h
	yfmt/xchar.h
)

SET( YATE_HEADER

	Aux_type.h
	Aux_yate_hal.h
	Aux_yate_log.h
	Aux_cmd_define.h

	yatecbase.h
	yateclass.h
	yatemath.h
	yatemime.h
	yatengine.h
	yatepaths.h
	yatephone.h
	yateversn.h
	yatewin32.h
	yatewiresniff.h
	yatexml.h

)

SET( YATE_SRC 
    engine/regex/regex.c
	engine/Array.cpp
	engine/Base64.cpp
	engine/Channel.cpp
	engine/Cipher.cpp
	engine/Client.cpp
	engine/ClientLogic.cpp
	engine/Compressor.cpp
	engine/Configuration.cpp
	engine/DataBlock.cpp
	engine/DataFormat.cpp
	engine/Engine.cpp
	engine/Hasher.cpp
	engine/HashList.cpp
	engine/Iterator.cpp
	engine/Math.cpp
	engine/Message.cpp
	engine/Mime.cpp
	engine/Mutex.cpp
	engine/NamedList.cpp
	engine/ObjList.cpp
	engine/Plugin.cpp
	engine/Resolver.cpp
	engine/Socket.cpp
	engine/String.cpp
	engine/TelEngine.cpp
	engine/Thread.cpp
	engine/URI.cpp
	engine/XML.cpp
	engine/YMD5.cpp
	engine/YSHA1.cpp
	engine/YSHA256.cpp
	
	Aux_yate_hal.cpp
)

## 源文件
ADD_LIBRARY(yateengine  

	SHARED

	${YATE_SRC}
	${YATE_HEADER}
		
)

#target_link_libraries(yateengine PRIVATE fmt-header-only)
#target_link_libraries(yateengine PRIVATE $<BUILD_INTERFACE:fmt::fmt-header-only>)

## 链接Yate库
TARGET_LINK_LIBRARIES( yateengine 
	PRIVATE	fmt::fmt 
	PUBLIC spdlog::spdlog
)

SET_PROPERTY(TARGET yateengine PROPERTY FOLDER "libs")
			 
####### ====================================================================
## 应用

ADD_EXECUTABLE(yate
    main.cpp
)

SET_PROPERTY(TARGET yate PROPERTY FOLDER "apps")

# 链接Yate库
TARGET_LINK_LIBRARIES( yate yateengine )

# 安装二进制文件，Binaries
INSTALL (TARGETS yate DESTINATION .)



####### ====================================================================

include(CMakeFindDependencyMacro)

SET ( PackageName "Yate" )
SET ( INCLUDE_INSTALL_DIR include )
SET ( LIB_INSTALL_DIR lib  )
SET ( LIB_NAME "yateengine" )

# Library
# Note: may not work on windows
INSTALL (TARGETS yateengine DESTINATION .)

INSTALL (TARGETS yateengine  EXPORT ${PackageName}Targets DESTINATION lib)

## find_dependency(spdlog::spdlog)

SET ( dest ${LIB_INSTALL_DIR}/cmake/${PackageName} )

INCLUDE ( CMakePackageConfigHelpers )
CONFIGURE_PACKAGE_CONFIG_FILE ( ${PackageName}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PackageName}Config.cmake
  INSTALL_DESTINATION ${dest}
  PATH_VARS INCLUDE_INSTALL_DIR
)
  
WRITE_BASIC_PACKAGE_VERSION_FILE(
  ${CMAKE_CURRENT_BINARY_DIR}/${PackageName}ConfigVersion.cmake
  VERSION 1.2.3
  COMPATIBILITY AnyNewerVersion
)

INSTALL ( 
    EXPORT ${PackageName}Targets
    NAMESPACE YateSpace::
    DESTINATION ${dest}
)


INSTALL (
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PackageName}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PackageName}ConfigVersion.cmake
    DESTINATION ${dest}
)

INSTALL(FILES ${YATE_HEADER}
	DESTINATION include 
)

INSTALL(FILES ${YFMT_HEADER}
	DESTINATION include/yfmt 
)

	
# 安装运行脚本	
INSTALL( PROGRAMS run.cmake
	DESTINATION .
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
          GROUP_EXECUTE GROUP_READ	
	)
	
# 安装运行脚本	
INSTALL( PROGRAMS run.daemon
	DESTINATION .
   PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
          GROUP_EXECUTE GROUP_READ
	)
	
		
## 安装share目录下文件
INSTALL(DIRECTORY share/sounds 
		DESTINATION .
		PATTERN "CVS" EXCLUDE
        PERMISSIONS OWNER_WRITE OWNER_READ
                    GROUP_READ
		)
	
## 安装conf.d目录下文件
INSTALL(DIRECTORY conf.d 
		DESTINATION .
		PATTERN "CVS" EXCLUDE
        PERMISSIONS OWNER_WRITE OWNER_READ
                    GROUP_READ
		)
	



##==========================================================
	
ADD_LIBRARY(msgsniff SHARED
    modules/msgsniff.cpp
)

SET_PROPERTY(TARGET msgsniff PROPERTY FOLDER "modules")

## 链接Yate库
TARGET_LINK_LIBRARIES( msgsniff yateengine )

if(NOT ANDROID)
	## 设置插件的后缀为.yate 
	SET_TARGET_PROPERTIES(msgsniff PROPERTIES SUFFIX ".yate")
endif()

SET_TARGET_PROPERTIES(msgsniff PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS msgsniff LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(ysockschan SHARED
    modules/ysockschan.cpp
)

SET_PROPERTY(TARGET ysockschan PROPERTY FOLDER "modules")

## 链接Yate库
TARGET_LINK_LIBRARIES( ysockschan yateengine )

if(NOT ANDROID)
	## 设置插件的后缀为.yate 
	SET_TARGET_PROPERTIES(ysockschan PROPERTIES SUFFIX ".yate")
endif()

SET_TARGET_PROPERTIES(ysockschan PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS ysockschan LIBRARY DESTINATION modules )
	
##==========================================================

ADD_LIBRARY(ystunchan SHARED
    modules/ystunchan.cpp
)

SET_PROPERTY(TARGET ystunchan PROPERTY FOLDER "modules")

## 链接Yate库
TARGET_LINK_LIBRARIES( ystunchan yateengine )

if(NOT ANDROID)
	## 设置插件的后缀为.yate 
	SET_TARGET_PROPERTIES(ystunchan PROPERTIES SUFFIX ".yate")
endif()

SET_TARGET_PROPERTIES(ystunchan PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS ystunchan LIBRARY DESTINATION modules )

##==========================================================

ADD_LIBRARY(rmanager SHARED
    modules/rmanager.cpp
)

SET_PROPERTY(TARGET rmanager PROPERTY FOLDER "modules")

## 链接Yate库
TARGET_LINK_LIBRARIES( rmanager yateengine )

if(NOT ANDROID)
	## 设置插件的后缀为.yate 
	SET_TARGET_PROPERTIES(rmanager PROPERTIES SUFFIX ".yate")
endif()

SET_TARGET_PROPERTIES(rmanager PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS rmanager LIBRARY DESTINATION modules )


