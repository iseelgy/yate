#ifndef _AUX_YATE_LOG_H_
#define _AUX_YATE_LOG_H_

#ifdef _MSC_VER
#pragma warning ( disable : 4251 )
#endif 

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


#ifndef DISABLE_YATE_STREAM_LOG

#ifdef _WIN32

	#ifdef LIBYATE_EXPORTS
		#define YATE_API __declspec(dllexport)
	#else
		#ifndef LIBYATE_STATIC
		#define YATE_API __declspec(dllimport)
		#endif
	#endif


#else

	#define YATE_API


#endif  // _WIN32


namespace spdlog {
	class logger;
}


namespace TelEngine {

	#define SPDLOG_LEVEL_TRACE 0
	#define SPDLOG_LEVEL_DEBUG 1
	#define SPDLOG_LEVEL_INFO 2
	#define SPDLOG_LEVEL_WARN 3
	#define SPDLOG_LEVEL_ERROR 4
	#define SPDLOG_LEVEL_CRITICAL 5
	#define SPDLOG_LEVEL_OFF 6


	enum YATE_API level_enum : int
	{
		trace = SPDLOG_LEVEL_TRACE,
		debug = SPDLOG_LEVEL_DEBUG,
		info = SPDLOG_LEVEL_INFO,
		warn = SPDLOG_LEVEL_WARN,
		err = SPDLOG_LEVEL_ERROR,
		critical = SPDLOG_LEVEL_CRITICAL,
		off = SPDLOG_LEVEL_OFF,
		n_levels
	};


	struct YATE_API source_loc
	{
		source_loc() = default;
		source_loc(const char *filename_in, int line_in, const char *funcname_in)
			: filename{ filename_in }
			, line{ line_in }
			, funcname{ funcname_in }
		{}

		bool empty() const
		{
			return line == 0;
		}
		const char *filename{ nullptr };
		int line{ 0 };
		const char *funcname{ nullptr };
	};



	struct YATE_API log_stream 
	{
	public:
		log_stream(const source_loc& _loc, level_enum _lvl, const std::string& _prefix)
			: loc(_loc)
			, lvl(_lvl){
			if(_prefix.length()>0){
				prefix = "["+_prefix + "] ";
			}
		}

		~log_stream()
		{
			flush();
		}

		void flush();

		/*
		void flush()
		{
			logger::get().log(loc, lvl, (prefix + str()).c_str());
		}
		*/

		template<class T>
		log_stream& operator<<(const T& msg)
		{
			(_stream) << msg;
			return *this;
		}


	private:
		std::ostringstream _stream;
		source_loc loc;
		level_enum lvl = level_enum::info;
		std::string prefix;
	};


	class YATE_API logger {

	public:

		static logger& get() {
			static logger logger;
			return logger;
		}

		void shutdown() {
			//spdlog::shutdown(); 
		}

		template <typename... Args>
		void log(const source_loc& loc, level_enum lvl, const char* fmt, const Args &... args);

		template <typename... Args>
		void printf(const source_loc& loc, level_enum lvl, const char* fmt, const Args &... args);

		level_enum level() {
			return _log_level;
		}

		void set_level(int lvl);

		void set_level(level_enum lvl);

		void set_flush_on(level_enum lvl);

		std::shared_ptr<::spdlog::logger> _loger;

	private:
		logger(); // = default;
		~logger() = default;

		logger(const logger&) = delete;
		void operator=(const logger&) = delete;

	private:
		level_enum _log_level = level_enum::trace;
	};

}


#define l_trace(msg,...) { \
		if (TelEngine::logger::get().level() == TelEngine::level_enum::trace) \
		spdlog::log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::trace, msg, ##__VA_ARGS__); \
		};

// FMT ∏Ò Ω
//#define f_debug(msg,...) TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::debug, msg, ##__VA_ARGS__)
//#define f_info(msg,...)  TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::info, msg, ##__VA_ARGS__)
//#define f_warn(msg,...)  TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::warn, msg, ##__VA_ARGS__)
//#define f_error(msg,...) TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::err, msg, ##__VA_ARGS__)
//#define f_fatal(msg,...) TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::critical, msg, ##__VA_ARGS__)

// use like sprintf, e.g. p_warn("warn log, %d-%d", 1, 2);
//#define p_trace(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::trace, msg, ##__VA_ARGS__);
//#define p_debug(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::debug, msg, ##__VA_ARGS__);
//#define p_info(msg,...)  TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::info, msg, ##__VA_ARGS__);
//#define p_warn(msg,...)  TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::warn, msg, ##__VA_ARGS__);
//#define p_error(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::err, msg, ##__VA_ARGS__);
//#define p_fatal(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::critical, msg, ##__VA_ARGS__);

// use like stream , e.g. s_warn() << "warn log: " << 1;
#define s_trace() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::trace, "")
#define s_debug() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::debug, "")
#define s_info()  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::info, "")
#define s_warn()  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::warn, "")
#define s_error() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::err, "")
#define s_fatal() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::critical, "")

#define h_trace(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::trace, a)
#define h_debug(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::debug, a)
#define h_info(a)  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::info, a)
#define h_warn(a)  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::warn, a)
#define h_error(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::err, a)
#define h_fatal(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::critical, a)

const char * get_yate_module_name();

#define y_trace(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::trace, get_yate_module_name())
#define y_debug(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::debug, get_yate_module_name())
#define y_info(a)  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::info, get_yate_module_name())
#define y_warn(a)  TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::warn, get_yate_module_name())
#define y_error(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::err, get_yate_module_name())
#define y_fatal(a) TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::critical, get_yate_module_name())

#endif // #ifndef DISABLE_YATE_STREAM_LOG

#endif  // _AUX_YATE_LOG_H_