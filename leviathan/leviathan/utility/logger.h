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
	static bool init(std::string name, int server_id, int log_level);

public:
	static class sys
	{
	public:
		template <typename... Args>
		static void info(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_SYSTEM)->info(fmt, args...);
		}

		template <typename... Args>
		static void warn(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_SYSTEM)->warn(fmt, args...);
		}

		template <typename... Args>
		static void debug(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_SYSTEM)->debug(fmt, args...);
		}

		template <typename... Args>
		static void error(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_SYSTEM)->error(fmt, args...);
		}

		template <typename... Args>
		static void critical(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_SYSTEM)->critical(fmt, args...);
		}
	};

public:
	static class db
	{
	public:
		template <typename... Args>
		static void info(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_DB)->info(fmt, args...);
		}

		template <typename... Args>
		static void warn(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_DB)->warn(fmt, args...);
		}

		template <typename... Args>
		static void debug(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_DB)->debug(fmt, args...);
		}

		template <typename... Args>
		static void error(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_DB)->error(fmt, args...);
		}

		template <typename... Args>
		static void critical(const char* fmt, const Args&... args)
		{
			spdlog::get(NAME_LOG_DB)->critical(fmt, args...);
		}
	};
};

}