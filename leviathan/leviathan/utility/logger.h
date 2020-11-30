#pragma once
#pragma warning (disable : 4091)

#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"

namespace Leviathan
{

#define NAME_LOG_SYSTEM "SYS_LOG"
#define NAME_LOG_DB "DB_LOG"
#define NAME_LOG_TEST "TEST_LOG"

static class cLogger
{
public:
	static bool init(std::string name, int server_id, int log_level)
	{
		try
		{
			_mkdir("./logs");
			char logPath[MAX_PATH] = { 0 };

			_snprintf_s(logPath, _countof(logPath), "./logs/sys.%s.%03d.txt", name.c_str(), server_id);
			spdlog::daily_logger_mt(NAME_LOG_SYSTEM, logPath, 0, 0);

			_snprintf_s(logPath, _countof(logPath), "./logs/db.%s.%03d.txt", name.c_str(), server_id);
			spdlog::daily_logger_mt(NAME_LOG_DB, logPath, 0, 0);

			_snprintf_s(logPath, _countof(logPath), "./logs/test.%s.%03d.txt", name.c_str(), server_id);
			spdlog::daily_logger_mt(NAME_LOG_TEST, logPath, 0, 0);

			spdlog::set_level((spdlog::level::level_enum)log_level);
			spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
			std::cout << "[SYSTEM] success init log system" << std::endl;
		}
		catch (spdlog::spdlog_ex ex)
		{
			std::cout << "[SYSTEM] fail init log system :: " << ex.what() << std::endl;
			return false;
		}

		return true;
	}

public:
	static class sys
	{
	public:
		template <typename... Args>
		static void info(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_SYSTEM)->info(fmt, args...);
		}
	};
};

}