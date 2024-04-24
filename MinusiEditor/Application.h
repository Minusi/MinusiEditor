#pragma once
#include "BaseWindow.h"
#include "Singleton.h"


struct GLFWwindow;

namespace spdlog
{
	class logger;
}

namespace Editor
{
	class LogManager;


	class Application : public Singleton<Application>
	{
		DECLARE_SINGLETON(Application)

	protected:
		void Initialize() override;
		void Finalize() override;

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
		spdlog::logger*						_EditorLogger{};
	};
}