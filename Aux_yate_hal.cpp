#include "Aux_yate_hal.h"

#include <string>

//#include <fmt/core.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/logger.h>

#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/bundled/printf.h>
#include "spdlog/sinks/rotating_file_sink.h"

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
//#include <spdlog/sinks/daily_file_sink.h>
//#include <spdlog/sinks/msvc_sink.h>
//#include <spdlog/sinks/stdout_sinks.h>
//#include <spdlog/sinks/stdout_color_sinks.h>

bool b64_decode(const char * in, TelEngine::DataBlock& dest)
{
	TelEngine::Base64 b64Decode((U8 *)in, strlen(in));
	return b64Decode.decode(dest);
}

void show_data(void * data, int size)
{
	int i;
	std::string info;
	char show[64];
	u8* buf = (u8*)data;
	for (i = 0; i < size; i++) {
		if ((i % 16) == 0) {
			info += "\r\n""        ";
		}
		::sprintf(show, "%02X ", buf[i]);
		info += show;
	}
	info += "\r\n";
	TE::Output( "%s", info.c_str() );
}

void show_data_x(void * data, int size)
{
	int i;
	std::string info;
	char show[64];
	u8 * buf = (u8*)data;
	for (i = 0; i < size; i++) {
		if ((i % 16) == 0) {
			info += "\r\n""        ";
		}
		::sprintf(show, "0x%02X, ", buf[i]);
		info += show;
	}
	info += "\r\n";
	TE::Output("%s", info.c_str());
}


#define strtok_r( _s, _sep, _lasts ) (*(_lasts) = strtok( (_s),(_sep)))

Aux_cmd_line::Aux_cmd_line(void)
{
	m_argc = 0;
	m_argv = 0;
}


Aux_cmd_line::~Aux_cmd_line(void)
{
	clear();
}


void Aux_cmd_line::clear()
{
	int i;
	for (i = 0; i < m_argc; i++) {
		delete m_argv[i];
	}
	delete m_argv;
	m_argc = 0;
	m_argv = 0;
}


int Aux_cmd_line::set(int argc, char ** argv)
{
	int i, len;

	clear();
	m_argv = new char *[argc];
	for (i = 0; i < argc; i++) {
		len = strlen(argv[i]) + 2;
		m_argv[i] = new char[len];
		strcpy(m_argv[i], argv[i]);
	}
	m_argc = argc;
	return 0;
}


int Aux_cmd_line::format(const char * cmd)
{
	#define MAX_ARGV_NUM 1024
	#define COMMAND_LINE_LENGTH 64*1024

	int argc;           /* My argc value */
	char *argv[MAX_ARGV_NUM+6];     /* Collected argv[] array */
	char * buf;      /* Command buffer */

	char *svptr;        /* strtok_r() updates this */
	char *s;            /* Returned strtok_r() pointer */
	//int x;              /* Work index */  
	const char delim[] = " \t\n"; /* Delimiters */
	int cmdLen = strlen(cmd); //ÃüÁîÐÐ³¤¶È  
	if (cmdLen > COMMAND_LINE_LENGTH - 1) return -1;

	buf = new char[cmdLen + 8];

	memcpy(buf, cmd, cmdLen);  /* Fake a command */
	*(buf + cmdLen) = 0;
	s = strtok_r(buf, delim, &svptr); /* First call */
	argc = 0;                    /* Start on my_argv[0] */
	while (s != 0){
		if (argc >= MAX_ARGV_NUM) {
			delete buf;
			return -1;
		}
		argv[argc++] = s;     /* Save argv[] value */
		s = strtok_r(NULL, delim, &svptr); /* Parse next tkn */
	}
	argv[argc] = 0;
	set(argc, argv);
	delete buf;

	return 0;
}


void logStartup()
{

	TelEngine::logger::get().set_level(spdlog::level::trace);

	// Debug()

	TelEngine::Debug(TelEngine::DebugFail, "**********************************************************************");

	s_debug() << "YATE_STM_DEBUG" << 1;
	p_warn("YATE_PRINT_WARN, %d", 1);
	f_info("YATE_LOG_INFO {}", 1);

	//TelEngine::logger::get().set_level(spdlog::level::info);
	//STM_DEBUG() << "YATE_STM_DEBUG " << 2;
	//PRINT_WARN("YATE_PRINT_WARN, %d", 2);
	//LOG_INFO("YATE_LOG_INFO {}", 2);
}

void logShutdown()
{


}

void logShowDemo()
{


}

void yateLog(const char * file, const char * function, int line, const char * category, int level, const char * fmt ...)
{
	if (level > TE::debugLevel()) {
		return;
	}

#ifdef WIN32 


#else


#endif

	// TelEngine::Debug(TelEngine::DebugFail, "%s, %s, %d", file, function, line);


}

namespace spdlog {

	namespace sinks {

		template<class Mutex>
		class test_sink : public base_sink<Mutex>
		{
			const size_t lines_to_save = 100;

			int eol_len;

		public:
			test_sink() {
				eol_len = strlen(details::os::default_eol);
			}

			size_t msg_counter()
			{
				std::lock_guard<Mutex> lock(base_sink<Mutex>::mutex_);
				return msg_counter_;
			}

			size_t flush_counter()
			{
				std::lock_guard<Mutex> lock(base_sink<Mutex>::mutex_);
				return flush_counter_;
			}

			void set_delay(std::chrono::milliseconds delay)
			{
				std::lock_guard<Mutex> lock(base_sink<Mutex>::mutex_);
				delay_ = delay;
			}

		protected:
			void sink_it_(const spdlog::details::log_msg &msg) override
			{
				memory_buf_t formatted;
				base_sink<Mutex>::formatter_->format(msg, formatted);

				// save the line without the eol
				std::string out;
				out.assign(formatted.begin(), formatted.end()-eol_len);
				TE::Output(out.c_str());

				msg_counter_++;
				//std::this_thread::sleep_for(delay_);
			}

			void flush_() override
			{
				flush_counter_++;
			}

			size_t msg_counter_{ 0 };
			size_t flush_counter_{ 0 };
			std::chrono::milliseconds delay_{ std::chrono::milliseconds::zero() };

		};

	}
}

using abc_sink_mt = spdlog::sinks::test_sink<std::mutex>;

namespace TelEngine {


	void log_stream::flush()
	{
		logger::get().log(loc, lvl, (prefix + str()).c_str());
	}

	logger::logger()
	{
		auto abc_sink = std::make_shared<abc_sink_mt>();
		_loger = std::make_shared< spdlog::logger>( "yate", abc_sink);
		_loger->set_pattern("[%L %D %T.%e %P %t] %s(%#) %v");
	}

	template <typename... Args>
	void logger::log(const source_loc& loc, level_enum lvl, const char* fmt, const Args &... args)
	{
		if (_loger) {
			spdlog::source_loc sloc(loc.filename, loc.line, loc.funcname);
			_loger->log(sloc, (spdlog::level::level_enum)lvl, fmt, args...);
		}
	}

	template <typename... Args>
	void logger::printf(const source_loc& loc, level_enum lvl, const char* fmt, const Args &... args)
	{
		if (_loger) {
			spdlog::source_loc sloc(loc.filename, loc.line, loc.funcname);
			_loger->log(sloc, (spdlog::level::level_enum)lvl, fmt::sprintf(fmt, args...).c_str());
		}
	}

	void logger::set_level(level_enum lvl) {
		_log_level = lvl;
		if (_loger) {
			_loger->set_level((spdlog::level::level_enum)lvl);
		}

	}

	void logger::set_level(int lvl) {
		_log_level = (level_enum)lvl;
		if (_loger) {
			_loger->set_level((spdlog::level::level_enum)lvl);
		}

	}


	void logger::set_flush_on(level_enum lvl) {
		if (_loger) {
			_loger->flush_on((spdlog::level::level_enum)lvl);
		}
	}


}