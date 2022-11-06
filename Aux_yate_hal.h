#ifndef _AUX_YATE_HAL_H_
#define _AUX_YATE_HAL_H_


#include <time.h>
#include <cstdlib>
#include <cstring>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <sstream>
#include <memory>


#ifdef _MSC_VER
#include <WinSock2.h>
#include <ws2ipdef.h>
#include <WS2tcpip.h>
#endif


#include "Aux_type.h"
#include "Aux_yate_log.h"

#include <yateclass.h>
#include <yatecbase.h>
#include <yatephone.h>



#define ShowLevel TelEngine::DebugNote

#define TE TelEngine

void YATE_API show_data(void * data, int size);
void YATE_API show_data_x(void * data, int size);

bool YATE_API b64_decode(const char * in, TelEngine::DataBlock& dest);
bool YATE_API b64_decode(void * in, int size, TelEngine::DataBlock& dest);

void YATE_API logStartup();
void YATE_API logShutdown();

class YATE_API Aux_cmd_line
{
public:
	Aux_cmd_line(void);
	~Aux_cmd_line(void);

public:

	int m_argc;
	char ** m_argv;

	void clear();

	int set(int argc, char ** argv);

	int format(const char * cmd);

protected:

};

/*
* withDebugEnabler() 需要在各自组件内部定义
* 
*/
TelEngine::DebugEnabler * withDebugEnabler();

#define y_trace(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_trace, a)
#define y_debug(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_debug, a)
#define y_info(a)  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_info, a)
#define y_warn(a)  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_warn, a)
#define y_error(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_error, a)
#define y_fatal(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_fatal, a)

#define Y_TRACE(message) do { \
	TelEngine::DebugEnabler * d = withDebugEnabler(); \
	if( d ){		\
		if( d->debugLevel() > TelEngine::DebugAll){ \
			y_trace(d->debugName()) << message; \
		} \
	}	\
}while(0)

#define Y_DEBUG(message) do { \
	TelEngine::DebugEnabler * d = withDebugEnabler(); \
	if( d ){		\
		if( d->debugLevel() >= TelEngine::DebugAll){ \
			y_debug(d->debugName()) << message; \
		} \
	}	\
}while(0)

#define Y_INFO(message) do { \
	TelEngine::DebugEnabler * d = withDebugEnabler(); \
	if( d ){		\
		if( d->debugLevel() >= TelEngine::DebugInfo){ \
			y_info(d->debugName()) << message; \
		} \
	}	\
}while(0)

#define Y_WARN(message) do { \
	TelEngine::DebugEnabler * d = withDebugEnabler(); \
	if( d ){		\
		if( d->debugLevel() >= TelEngine::DebugWarn){ \
			y_warn(d->debugName()) << message; \
		} \
	}	\
}while(0)

#define Y_ERROR(message) do { \
	TelEngine::DebugEnabler * d = withDebugEnabler(); \
	if( d ){		\
		if( d->debugLevel() >= TelEngine::DebugCrit){ \
			y_error(d->debugName()) << message; \
		} \
	}	\
}while(0)

#define Y_FATAL(message) do { \
	TelEngine::DebugEnabler * d = withDebugEnabler(); \
	if( d ){		\
		if( d->debugLevel() >= TelEngine::DebugFail){ \
			y_fatal(d->debugName()) << message; \
		} \
	}	\
}while(0)



#endif