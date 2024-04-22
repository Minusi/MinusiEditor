#pragma once
#include "BaseWindow.h"


struct GLFWwindow;

namespace spdlog
{
	class logger;
}

namespace Editor
{
	class LogManager;


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
		void _InitLog();
		void _InitGlfw();
		void _InitImgui();

		void _FinalizeGlfw();
		void _FinalizeImgui();

		void _CreateDefaultHint();

	private:
		void _Render();

	private:
		std::unique_ptr<WindowHint>			_DefaultHint{};
		std::unique_ptr<BaseWindow>			_MainWindow{};
		std::unique_ptr<LogManager>			_LogManager{};
		spdlog::logger*						_EditorLogger{};
	};
}