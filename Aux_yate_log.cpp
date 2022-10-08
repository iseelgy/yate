#include "Aux_yate_hal.h"

#ifndef _DISABLE_YATE_SDP_LOG_

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

#ifdef _DEBUG_MSVC_NEW_
#include "3rlibs/DebugNew.h"
#define new DEBUG_NEW
#endif



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
				out.assign(formatted.begin(), formatted.end() - eol_len);
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


/**

%v	The actual text to log				¡°some user text¡±
%t	Thread id							¡°1232¡±
%P	Process id							¡°3456¡±
%n	Logger¡¯s name						¡°some logger name¡±
%l	The log level of the message		¡°debug¡±, ¡°info¡±, etc
%L	Short log level of the message		¡°D¡±, ¡°I¡±, etc
%a	Abbreviated weekday name			¡°Thu¡±
%A	Full weekday name					¡°Thursday¡±
%b	Abbreviated month name				¡°Aug¡±
%B	Full month name						¡°August¡±
%c	Date and time representation		¡°Thu Aug 23 15:35:46 2014¡±
%C	Year in 2 digits					¡°14¡±
%Y	Year in 4 digits					¡°2014¡±
%D or %x	Short MM/DD/YY date			¡°08/23/14¡±
%m	Month 01-12							¡°11¡±
%d	Day of month 01-31					¡°29¡±
%H	Hours in 24 format 00-23			¡°23¡±
%I	Hours in 12 format 01-12			¡°11¡±
%M	Minutes 00-59						¡°59¡±
%S	Seconds 00-59						¡°58¡±
%e	Millisecond part of the current second 000-999	¡°678¡±
%f	Microsecond part of the current second 000000-999999	¡°056789¡±
%F	Nanosecond part of the current second 000000000-999999999	¡°256789123¡±
%p	AM/PM								¡°AM¡±
%r	12 hour clock						¡°02:55:02 pm¡±
%R	24-hour HH:MM time, equivalent to %H:%M	¡°23:55¡±
%T or %X	ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S	¡°23:55:59¡±
%z	ISO 8601 offset from UTC in timezone ([+/-]HH:MM)	¡°+02:00¡±
%E	Seconds since the epoch				¡°1528834770¡±
%%	The % sign							¡°%¡±
%+	spdlog¡¯s default format			¡°[2014-10-31 23:46:59.678] [mylogger] [info] Some message¡±
%^	start color range (can be used only once)	¡°[mylogger] [info(green)] Some message¡±
%$	end color range (for example %1%$ %v) (can be used only once)	[+++] Some message
%@	Source file and line (use SPDLOG_TRACE(¡­), SPDLOG_INFO(¡­) etc.)	my_file.cpp:123
%s	Basename of the source file (use SPDLOG_TRACE(¡­), SPDLOG_INFO(¡­) etc.)	my_file.cpp
%g	Full path of the source file (use SPDLOG_TRACE(¡­), SPDLOG_INFO(¡­) etc.)	/some/dir/my_file.cpp
%#	Source line (use SPDLOG_TRACE(¡­), SPDLOG_INFO(¡­) etc.)	123
%!	Source function (use SPDLOG_TRACE(¡­), SPDLOG_INFO(¡­) etc.	see tweakme for pretty-print) my_func
%o	Elapsed time in milliseconds since previous message	456
%i	Elapsed time in microseconds since previous message	456
%u	Elapsed time in nanoseconds since previous message	11456
%O	Elapsed time in seconds since previous message

*/



using abc_sink_mt = spdlog::sinks::test_sink<std::mutex>;

namespace TelEngine {


	void log_stream::flush()
	{
		logger::get().log(loc, lvl, (prefix + _stream.str()).c_str());
	}

	logger::logger() :
		_log_level(yate_log_level_trace)
	{
		auto abc_sink = std::make_shared<abc_sink_mt>();
		loger_ = std::make_shared< spdlog::logger>( "yate", abc_sink);
		loger_->set_pattern("[%L %D %T.%e %P#%t] %s(%#) %v");
	}

	template <typename... Args>
	void logger::log(const source_loc& loc, int lvl, const char* fmt, const Args &... args)
	{
		if (loger_) {
			spdlog::source_loc sloc(loc.filename, loc.line, loc.funcname);
			loger_->log(sloc, (spdlog::level::level_enum)lvl, fmt, args...);
		}
	}

	template <typename... Args>
	void logger::printf(const source_loc& loc, int lvl, const char* fmt, const Args &... args)
	{
		if (_loger) {
			spdlog::source_loc sloc(loc.filename, loc.line, loc.funcname);
			_loger->log(sloc, (spdlog::level::level_enum)lvl, fmt::sprintf(fmt, args...).c_str());
		}
	}

	void logger::set_level(int lvl) {
		_log_level = lvl;
		if (loger_) {
			loger_->set_level((spdlog::level::level_enum)lvl);
		}

	}


	void logger::set_flush_on(int lvl) {
		if (loger_) {
			loger_->flush_on((spdlog::level::level_enum)lvl);
		}
	}

	void logger::shutdown() {
		//spdlog::shutdown();
		if (loger_) {
			loger_->~logger();
		}
		loger_ = nullptr;
	}




}


#endif // #ifndef _DISABLE_YATE_SDP_LOG_
