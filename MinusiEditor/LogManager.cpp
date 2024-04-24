#include "precomp.h"
#include "LogManager.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"



namespace Editor
{
	void LogManager::Initialize()
	{
		_InitConfig();
		_InitSink();
		_InitLogger(LogType::SYSTEM, _BasicMtSink, "SYSTEM");
		_InitLogger(LogType::EDITOR, _BasicMtSink, "EDITOR");
		_InitLogger(LogType::GRAPHICS, _BasicMtSink, "GRAPHICS");
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

	void LogManager::_InitConfig()
	{
		spdlog::flush_on(spdlog::level::n_levels);
	}

	void LogManager::_InitSink()
	{
		_BasicMtSink = std::shared_ptr<spdlog::sinks::basic_file_sink_mt>(new spdlog::sinks::basic_file_sink_mt("../Log/editor.log"));
		if (_BasicMtSink == nullptr)
		{
			assert(_BasicMtSink);
			return;
		}
	}

	void LogManager::_InitLogger(LogType type, spdlog::sink_ptr sink, const std::string& category)
	{
		if (sink == nullptr)
		{
			assert(sink);
			return;
		}

		auto logger = std::shared_ptr<spdlog::logger>(new spdlog::logger(category, sink));
		if (logger == nullptr)
		{
			assert(logger);
			return;
		}

		spdlog::initialize_logger(logger);

		auto it = _Loggers.find(type);
		if (it != _Loggers.end())
		{
			logger->warn("{} type is already exists.", magic_enum::enum_name<LogType>(type));
			return;
		}

		_Loggers.insert({ type, std::move(logger) });
	}
}
