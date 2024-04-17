#include "precomp.h"
#include "Application.h"
#include "GLFW/glfw3.h"

namespace Editor
{
	Application::Application()
	{
		auto result = glfwInit();
		if (result == GLFW_FALSE)
		{
			return;
		}

		glfwSetErrorCallback(Application::_HandleGlfwErrors);

		_CreateDefaultHint();
		_MainWindow = std::unique_ptr<BaseWindow>(new BaseWindow(*_DefaultHint.get()));
		if (_MainWindow == nullptr)
		{
			return;
		}

		glfwMakeContextCurrent(_MainWindow->GetGLFWwindow());
	}

	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::_HandleGlfwErrors(int error, const char* content)
	{
		std::cout << "[ERROR] glfw error occured: " << content << std::endl;
	}

	void Application::Run()
	{
		if (_MainWindow == nullptr)
		{
			return;
		}

		while (glfwWindowShouldClose(_MainWindow->GetGLFWwindow()) == false)
		{
			glfwSwapBuffers(_MainWindow->GetGLFWwindow());
			glfwPollEvents();
		}

		glfwDestroyWindow(_MainWindow->GetGLFWwindow());
	}

	void Application::_CreateDefaultHint()
	{
		_DefaultHint.reset();
		_DefaultHint = std::make_unique<WindowHint>();
		if (_DefaultHint == nullptr)
		{
			return;
		}
		
		_DefaultHint->Hints.insert({ glfw::WindowHintType::_GLFW_CONTEXT_VERSION_MAJOR, 3 });
		_DefaultHint->Hints.insert({ glfw::WindowHintType::_GLFW_CONTEXT_VERSION_MINOR, 3 });
		_DefaultHint->WindowSize = { 640, 480 };
		_DefaultHint->WindowTitle = "Minusi Editor";
	}

} 