#pragma once
#include "BaseWindow.h"


class GLFWwindow;

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
		void _CreateDefaultHint();

	private:
		std::unique_ptr<WindowHint>			_DefaultHint{};
		std::unique_ptr<BaseWindow>			_MainWindow{};
	};
}