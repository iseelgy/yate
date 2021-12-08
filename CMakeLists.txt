cmake_minimum_required (VERSION 2.8)

PROJECT(yate)

# include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)


set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Installation directory for executables")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libraries")
set(INSTALL_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers")


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

  SET(GNU_FLAGS "-Wall -O2 -fno-builtin -fpermissive ")
  SET(CMAKE_CXX_FLAGS "-lm ${GNU_FLAGS} ")
  SET(CMAKE_C_FLAGS "${GNU_FLAGS}  ")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

  set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")
  set(CMAKE_C_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${C_CXX_FLAGS} -Wmissing-declarations")
##  # Clang's integerated assembler does not support debug symbols.
  if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  	set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Wa,-g")
  endif()

  ADD_DEFINITIONS(  
	-DHAVE_GCC_FORMAT_CHECK 
	-DHAVE_POLL)

elseif(MSVC)
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
      "C4464" # relative include path contains '..'
      "C4510" # 'argument' : default constructor could not be generated
      "C4512" # 'argument' : assignment operator could not be generated
      "C4514" # 'function': unreferenced inline function has been removed
      "C4548" # expression before comma has no effect; expected expression with
              # side-effect" caused by FD_* macros.
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
#  add_definitions(-D_HAS_EXCEPTIONS=0)
#  add_definitions(-DWIN32_LEAN_AND_MEAN)

  add_definitions(-DLIBYATE_EXPORTS)
  add_definitions(-D__STDC__)
  add_definitions(-DHAVE_STRING_H)
  add_definitions(-DREGEX_MALLOC)
  add_definitions(-DSTDC_HEADERS)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  add_definitions(-DATOMIC_OPS)
  add_definitions(-DHAVE_DNS_NAPTR_DATA)
##add_definitions(-D)

#  add_definitions(-DOS_WIN)
#  add_definitions(-D_CRT_SECURE_NO_WARNINGS) # Allow use of fopen
#  ADD_DEFINITIONS(-DREGEX_MALLOC -D__STDC__ -DLIBYATE_EXPORTS -D_CRT_SECURE_NO_WARNINGS)	

  INCLUDE_DIRECTORIES(windows)
   
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
#  set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
  
  #set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
  
#  -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE -DBUILD_SHARED_LIBS=TRUE

endif()

		
ADD_DEFINITIONS( -DHAVE_STRING_H 
	-DSTDC_HEADERS 
#	-DHAVE_BLOCK_RETURN 
#	-DATOMIC_OPS
#	-DHAVE_GMTOFF 
	-DHAVE_INT_TZ
	)

if(WIN32)
	LINK_LIBRARIES(ws2_32 advapi32 dnsapi)	
else()
	LINK_LIBRARIES(m dl c pthread resolv)
endif(WIN32)



## 头文件目录
INCLUDE_DIRECTORIES( ./ engine/regex  engine/tables)


set(BUILD_SHARED_LIBS ON)
## set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS True)


SET( YATE_PUBLIC_HDRS 

	Aux_type.h
	Aux_yate_hal.h
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


## 源文件
ADD_LIBRARY(Libyate  

	${YATE_PUBLIC_HDRS}

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


# TARGET_LINK_LIBRARIES( yate.s liblog4cpp.a)

# TARGET_LINK_LIBRARIES( yateengine liblog4cpp.a)

# Library
# Note: may not work on windows
INSTALL (TARGETS Libyate DESTINATION .)
	
		 
####### ====================================================================
## 应用

ADD_EXECUTABLE(yate
    main.cpp
)

# 链接Yate库
TARGET_LINK_LIBRARIES( yate Libyate )


install(FILES ${YATE_PUBLIC_HDRS} DESTINATION "${INSTALL_INC_DIR}")

# 安装二进制文件，Binaries
INSTALL (TARGETS yate DESTINATION .)
	
# 安装运行脚本	
INSTALL( PROGRAMS run 
	DESTINATION .
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
          GROUP_EXECUTE GROUP_READ	
	)
	
# 安装运行脚本	
INSTALL( PROGRAMS daemon.run 
	DESTINATION .
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
          GROUP_EXECUTE GROUP_READ	
	)
	
		
## 安装share目录下文件		
INSTALL(DIRECTORY share 
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

## 链接Yate库
TARGET_LINK_LIBRARIES( msgsniff Libyate )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(msgsniff PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(msgsniff PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS msgsniff  DESTINATION modules )

##==========================================================	



ADD_LIBRARY(demo SHARED
    modules/demo.cpp
)

## 链接Yate库
TARGET_LINK_LIBRARIES( demo Libyate )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(demo PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(demo PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS demo DESTINATION modules )

##==========================================================	

ADD_LIBRARY(ysockschan SHARED
    modules/ysockschan.cpp
)

## 链接Yate库
TARGET_LINK_LIBRARIES( ysockschan Libyate )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(ysockschan PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(ysockschan PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS ysockschan DESTINATION modules )
	
##==========================================================	

ADD_LIBRARY(ystunchan SHARED
    modules/ystunchan.cpp
)

## 链接Yate库
TARGET_LINK_LIBRARIES( ystunchan Libyate )

## 设置插件的后缀为.yate 
SET_TARGET_PROPERTIES(ystunchan PROPERTIES SUFFIX ".yate")

SET_TARGET_PROPERTIES(ystunchan PROPERTIES PREFIX "")
	 	 
# 安装
# Note: may not work on windows
INSTALL (TARGETS ystunchan DESTINATION modules )


	


