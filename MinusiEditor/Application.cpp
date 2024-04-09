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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		_MainWindow = glfwCreateWindow(640, 480, "Lineage Editor", nullptr, nullptr);
		if (_MainWindow == nullptr)
		{
			return;
		}

		auto window2 = glfwCreateWindow(640, 480, "Sub Window", nullptr, nullptr);
		

		glfwGetFramebufferSize(_MainWindow, &_WindowSize.first, &_WindowSize.second);
		glfwMakeContextCurrent(_MainWindow);
	}

	Application::~Application()
	{
		glfwDestroyWindow(_MainWindow);
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

		while (glfwWindowShouldClose(_MainWindow) == false)
		{
			glfwSwapBuffers(_MainWindow);
			glfwPollEvents();
		}

		glfwDestroyWindow(_MainWindow);
		while (true)
		{
			
		}
	}

}