#pragma once
#include "BaseWindow.h"


struct GLFWwindow;

namespace spdlog
{
	class logger;
}

namespace Editor
{
	class Application
	{
	public:
		Application();
		~Application();

	private:
		static void _HandleGlfwErrors(int error, const char* content);

	public:
		void Run();

	private:
		void _InitGlfw();
		void _CreateDefaultHint();

	private:
		std::unique_ptr<WindowHint>			_DefaultHint{};
		std::unique_ptr<BaseWindow>			_MainWindow{};
		std::shared_ptr<spdlog::logger>		_Logger{};
	};
}