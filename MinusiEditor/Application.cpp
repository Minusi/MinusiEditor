#include "precomp.h"
#include "Application.h"
#include "GLFW/glfw3.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Editor
{
	Application::Application()
	{
		_InitSpdlog();
		_InitGlfw();
		_InitImgui();
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

	void Application::_InitSpdlog()
	{
		_Logger = spdlog::create<spdlog::sinks::basic_file_sink_mt>("editor", "../Logs/editor.txt");
		_Logger->info("spdlog initialized");
		_Logger->flush();
	}

	void Application::_InitGlfw()
	{
		auto result = glfwInit();
		if (result == GLFW_FALSE)
		{
			_Logger->error("glfw init error");
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

	void Application::_InitImgui()
	{
		if (_MainWindow == nullptr)
		{
			return;
		}

		auto glfwWindow = _MainWindow->GetGLFWwindow();
		if (glfwWindow == nullptr)
		{
			return;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
		ImGui_ImplOpenGL3_Init();
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