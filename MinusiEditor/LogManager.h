#pragma once
#include <logger.h>
#include "Singleton.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/common.h"
#include <string>

namespace spdlog
{
	class logger;
}

namespace Editor
{
	enum class LogType
	{
		SYSTEM,
		EDITOR,
		GRAPHICS,
	};

	class LogManager : public Singleton<LogManager>
	{
	public:
		DECLARE_SINGLETON(LogManager)

	protected:
		void Initialize() override;

	public:
		spdlog::logger* GetLogger(LogType type) const;

	public:


	private:
		void _InitConfig();
		void _InitSink();
		void _InitLogger(LogType type, spdlog::sink_ptr sink, const std::string& category);


	private:
		std::map<LogType, std::shared_ptr<spdlog::logger>>	_Loggers{};
		std::shared_ptr<spdlog::sinks::basic_file_sink_mt>	_BasicMtSink{};
	};
}
