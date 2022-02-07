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


include(CMake_base.cmake)

include(CMake_client.cmake)

include(CMake_server.cmake)




