#include "precomp.h"
#include "Application.h"
#include "GLFW/glfw3.h"
#include "imgui_impl_glfw.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Editor
{
	Application::Application()
	{
		_Logger = spdlog::create<spdlog::sinks::basic_file_sink_mt>("editor", "Logs/editor.txt");

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

		glfwSetWindowAttrib(_MainWindow->GetGLFWwindow(), GLFW_ACCUM_ALPHA_BITS, GLFW_TRUE);
		glfwMakeContextCurrent(_MainWindow->GetGLFWwindow());
	}

	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::_HandleGlfwErrors(int error, const char* content)
	{
		auto logger = spdlog::get("editor");
		if (logger == nullptr)
		{
			return;
		}

		logger->error("glfw error occured: {}", content);
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