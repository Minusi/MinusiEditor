#pragma once


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
		std::pair<int, int>		_WindowSize{};
		GLFWwindow*				_MainWindow{};
	};
}