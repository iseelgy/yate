#ifndef _AUX_YATE_LOG_H_
#define _AUX_YATE_LOG_H_

#ifdef _MSC_VER
#pragma warning ( disable : 4251 )
#endif 

#ifdef _DISABLE_YATE_SDP_LOG_

#define S_TRACE(message) do { \
}while(0)

#define S_DEBUG(message) do { \
}while(0)

#define S_INFO(message) do { \
}while(0)

#define S_WARN(message) do { \
}while(0)

#define S_ERROR(message) do { \
}while(0)

#define S_FATAL(message) do { \
}while(0)

#else

#include <string>
#include <iostream>
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


#include "yfmt/format.h"
#include "yfmt/xchar.h"
#include "yfmt/printf.h"
#include "yfmt/chrono.h"


#ifdef _WIN32
	#ifdef LIBYATE_EXPORTS
	#define YATE_API __declspec(dllexport)
	#else
	#ifndef LIBYATE_STATIC
	#define YATE_API __declspec(dllimport)
	#endif
	#endif
#endif

#ifndef YATE_API
#define YATE_API
#endif

namespace spdlog {
	class logger;
}

//#define SPDLOG_LEVEL_TRACE 0
//#define SPDLOG_LEVEL_DEBUG 1
//#define SPDLOG_LEVEL_INFO 2
//#define SPDLOG_LEVEL_WARN 3
//#define SPDLOG_LEVEL_ERROR 4
//#define SPDLOG_LEVEL_CRITICAL 5
//#define SPDLOG_LEVEL_OFF 6

const int yate_log_level_trace = 0;
const int yate_log_level_debug = 1;
const int yate_log_level_info = 2;
const int yate_log_level_warn = 3;
const int yate_log_level_error = 4;
const int yate_log_level_fatal = 5;


namespace TelEngine {


	struct YATE_API source_loc{
		source_loc() = default;
		source_loc(const char *filename_in, int line_in, const char *funcname_in)
			: filename{ filename_in }
			, line{ line_in }
			, funcname{ funcname_in }
		{}

		bool empty() const{
			return line == 0;
		}
		const char *filename{ nullptr };
		int line{ 0 };
		const char *funcname{ nullptr };
	};



	struct YATE_API log_stream 
	{
	public:
		log_stream(const source_loc& _loc, int _lvl, const std::string& _prefix)
			: loc(_loc)
			, lvl(_lvl){
			if(_prefix.length()>0){
				prefix = "["+_prefix + "] ";
			}
		}

		~log_stream(){
			flush();
		}

		void flush();

		template<class T>
		log_stream& operator<<(const T& msg){
			(_stream) << msg;
			return *this;
		}

	private:
		source_loc loc;
		std::ostringstream _stream;
		int lvl = yate_log_level_info;
		std::string prefix;
	};


	class YATE_API logger {

	public:

		static logger& get() {
			static logger logger;
			return logger;
		}

		void shutdown();

		template <typename... Args>
		void log(const source_loc& loc, int lvl, const char* fmt, const Args &... args);

		template <typename... Args>
		void printf(const source_loc& loc, int lvl, const char* fmt, const Args &... args);

		int level() {
			return _log_level;
		}

		void set_level(int lvl);

		void set_flush_on(int lvl);

		bool is_trace_enable() {
			return _log_level <= yate_log_level_trace;
		}

		bool is_debug_enable() {
			return _log_level <= yate_log_level_debug;
		}


		std::shared_ptr<::spdlog::logger> loger_;

	private:
		logger(); // = default;
		~logger() = default;

		logger(const logger&) = delete;
		void operator=(const logger&) = delete;

	private:
		int _log_level;
	};

}


// FMT 
//#define f_debug(msg,...) TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_debug, msg, ##__VA_ARGS__)
//#define f_info(msg,...)  TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_info, msg, ##__VA_ARGS__)
//#define f_warn(msg,...)  TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_warn, msg, ##__VA_ARGS__)
//#define f_error(msg,...) TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_err, msg, ##__VA_ARGS__)
//#define f_fatal(msg,...) TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_fatal, msg, ##__VA_ARGS__)

// use like sprintf, e.g. p_warn("warn log, %d-%d", 1, 2);
//#define p_trace(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_trace, msg, ##__VA_ARGS__);
//#define p_debug(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_debug, msg, ##__VA_ARGS__);
//#define p_info(msg,...)  TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_info, msg, ##__VA_ARGS__);
//#define p_warn(msg,...)  TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_warn, msg, ##__VA_ARGS__);
//#define p_error(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_err, msg, ##__VA_ARGS__);
//#define p_fatal(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, yate_log_level_fatal, msg, ##__VA_ARGS__);

// use like stream , e.g. s_warn() << "warn log: " << 1;
#define s_trace() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_trace, "")
#define s_debug() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_debug, "")
#define s_info()  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_info, "")
#define s_warn()  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_warn, "")
#define s_error() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_error, "")
#define s_fatal() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_fatal, "")

#define S_TRACE(message) do { \
	if( TelEngine::debugLevel() > TelEngine::DebugAll ){		\
		s_trace() << message; \
	}		\
}while(0)

#define S_DEBUG(message) do { \
	if( TelEngine::debugLevel() >= TelEngine::DebugAll ){		\
		s_debug() << message; \
	}		\
}while(0)

#define S_INFO(message) do { \
	if( TelEngine::debugLevel() >= TelEngine::DebugInfo ){		\
		s_info() << message; \
	}		\
}while(0)

#define S_WARN(message) do { \
	if( TelEngine::debugLevel() >= TelEngine::DebugWarn ){		\
		s_warn() << message; \
	}		\
}while(0)

#define S_ERROR(message) do { \
	if( TelEngine::debugLevel() >= TelEngine::DebugCrit ){		\
		s_error() << message; \
	}		\
}while(0)

#define S_FATAL(message) do { \
	if( TelEngine::debugLevel() >= TelEngine::DebugFail ){		\
		s_fatal() << message; \
	}		\
}while(0)


#define h_trace(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_trace, a)
#define h_debug(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_debug, a)
#define h_info(a)  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_info, a)
#define h_warn(a)  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_warn, a)
#define h_error(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_error, a)
#define h_fatal(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  yate_log_level_fatal, a)


#endif // #ifndef _DISABLE_YATE_SDP_LOG_

#endif  // _AUX_YATE_LOG_H_