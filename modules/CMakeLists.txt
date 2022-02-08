if(LINUX)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_INIT} -fPIC")

endif()



function(yate_modules ymodule yfolder yinstall )


    unset(yateplugins)
    if(ARGC GREATER 0)
      set(yateplugins ${ARGV0})
    endif()
	
    unset(yatefolder)
    if(ARGC GREATER 1)
      set(yatefolder ${ARGV1})
    endif()
	
    unset(yateinstall)
    if(ARGC GREATER 2)
      set(yateinstall ${ARGV2})
    endif()
	
	if( NOT yateplugins )
		message(FATAL_ERROR "yate_modules args error")
	endif()
	
	if( NOT yatefolder )
		set( yatefolder "modules")
	endif()
	
	if( NOT yateinstall )
		set( yateinstall modules)
	endif()

	
	SET_PROPERTY(TARGET ${yateplugins} PROPERTY FOLDER ${yatefolder})
	
	TARGET_LINK_LIBRARIES( ${yateplugins} yateengine )

	## 设置插件的后缀为.yate 
	SET_TARGET_PROPERTIES(${yateplugins} PROPERTIES SUFFIX ".yate")

	SET_TARGET_PROPERTIES(${yateplugins} PROPERTIES PREFIX "")
	 	 
	# 安装
	# Note: may not work on windows
	INSTALL (TARGETS ${yateplugins} LIBRARY DESTINATION ${yateinstall} )

endfunction()


OPTION(YATE_BUILD_ALL "Build all moudles" OFF)

OPTION(YATE_BUILD_TEST "Build tests moudles" OFF)

OPTION(YATE_BUILD_SIP "Build with sip base moudles" OFF)

OPTION(YATE_BUILD_CLIENT "Build with sip client moudles" OFF)

OPTION(YATE_BUILD_SERVER "Build with sip server moduels " OFF)

OPTION(YATE_BUILD_QT4 "Build with qt moduels " OFF)


if(YATE_BUILD_ALL)
	set( YATE_BUILD_TEST ON )
	set( YATE_BUILD_SIP ON )
	set( YATE_BUILD_CLIENT ON )
	set( YATE_BUILD_SERVER ON )
	set( YATE_BUILD_QT4 ON )
endif()

include(CMake_engine.cmake)

if(YATE_BUILD_SIP)
	include(CMake_sip.cmake)
endif()

if(YATE_BUILD_CLIENT)
	include(CMake_client.cmake)
endif()

if(YATE_BUILD_SERVER)
	include(CMake_server.cmake)
endif()

if(YATE_BUILD_TEST)
	include(CMake_test.cmake)
endif()

if(YATE_BUILD_QT4)
	include(CMake_qt4.cmake)
endif()



