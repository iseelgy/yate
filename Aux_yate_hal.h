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

#include <yatecbase.h>
#include <yatephone.h>


#define ShowLevel TelEngine::DebugNote

#define TE TelEngine

void YATE_API show_data(void * data, int size);
void YATE_API show_data_x(void * data, int size);

bool YATE_API b64_decode(const char * in, TelEngine::DataBlock& dest);
bool YATE_API b64_decode(void * in, int size, TelEngine::DataBlock& dest);

void YATE_API logStartup();

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



namespace spdlog {
	class logger;
}


namespace TelEngine{

	#define SPDLOG_LEVEL_TRACE 0
	#define SPDLOG_LEVEL_DEBUG 1
	#define SPDLOG_LEVEL_INFO 2
	#define SPDLOG_LEVEL_WARN 3
	#define SPDLOG_LEVEL_ERROR 4
	#define SPDLOG_LEVEL_CRITICAL 5
	#define SPDLOG_LEVEL_OFF 6


	enum level_enum : int
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



	struct YATE_API log_stream : public std::ostringstream
	{
	public:
		log_stream(const source_loc& _loc, level_enum _lvl, const std::string& _prefix)
			: loc(_loc)
			, lvl(_lvl)
			, prefix(_prefix)
		{
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

	private:
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


#define LOG_TRACE(msg,...) { if (TelEngine::logger::get().level() == TelEngine::level_enum::trace) spdlog::log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::trace, msg, ##__VA_ARGS__); };
#define LOG_DEBUG(msg,...) TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::debug, msg, ##__VA_ARGS__)
#define LOG_INFO(msg,...)  TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::info, msg, ##__VA_ARGS__)
#define LOG_WARN(msg,...)  TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::warn, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg,...) TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::err, msg, ##__VA_ARGS__)
#define LOG_FATAL(msg,...) TelEngine::logger::get().log({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::critical, msg, ##__VA_ARGS__)

// use like sprintf, e.g. PRINT_WARN("warn log, %d-%d", 1, 2);
#define PRINT_TRACE(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::trace, msg, ##__VA_ARGS__);
#define PRINT_DEBUG(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::debug, msg, ##__VA_ARGS__);
#define PRINT_INFO(msg,...)  TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::info, msg, ##__VA_ARGS__);
#define PRINT_WARN(msg,...)  TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::warn, msg, ##__VA_ARGS__);
#define PRINT_ERROR(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::err, msg, ##__VA_ARGS__);
#define PRINT_FATAL(msg,...) TelEngine::logger::get().printf({__FILE__, __LINE__, __FUNCTION__}, TelEngine::level_enum::critical, msg, ##__VA_ARGS__);

// use like stream , e.g. STM_WARN() << "warn log: " << 1;
#define STM_TRACE() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::trace, "")
#define STM_DEBUG() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::debug, "")
#define STM_INFO()	TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::info, "")
#define STM_WARN()	TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::warn, "")
#define STM_ERROR() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::err, "")
#define STM_FATAL() TelEngine::log_stream({__FILE__, __LINE__, __FUNCTION__},  TelEngine::level_enum::critical, "")


#endif