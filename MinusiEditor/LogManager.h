#pragma once
#include <logger.h>


namespace spdlog
{
	class logger;
}

namespace Editor
{
	enum class LogType
	{
		EDITOR,
		GRAPHICS,
	};

	class LogManager
	{
	public:
		LogManager();
		~LogManager() = default;

	public:
		spdlog::logger* GetLogger(LogType type) const;

	private:
		void _InitDefaultLogger(LogType type, const std::string& name);

	private:
		std::map<LogType, std::shared_ptr<spdlog::logger>>	_Loggers{};
	};
}
