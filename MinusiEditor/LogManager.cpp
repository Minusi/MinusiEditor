#include "precomp.h"
#include "LogManager.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"



namespace Editor
{
	LogManager::LogManager()
	{
		_InitDefaultLogger(LogType::EDITOR, "EDITOR");
		_InitDefaultLogger(LogType::GRAPHICS, "GRAPHICS");
	}

	spdlog::logger* LogManager::GetLogger(LogType type) const
	{
		auto it = _Loggers.find(type);
		if (it == _Loggers.end())
		{
			return nullptr;
		}

		return it->second.get();
	}

	void LogManager::_InitDefaultLogger(LogType type, const std::string& name)
	{
		std::string logPath = "../Logs/" + name + ".log";
		auto logger = spdlog::create<spdlog::sinks::basic_file_sink_mt>(name, logPath);
		if (logger == nullptr)
		{
			return;
		}

		auto it = _Loggers.find(type);
		if (it != _Loggers.end())
		{
			logger->info("{} type is already exists.", magic_enum::enum_name<LogType>(type));
			return;
		}

		_Loggers.insert({ type, std::move(logger) });
	}
}
