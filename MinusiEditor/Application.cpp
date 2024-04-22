#include "precomp.h"
#include "Application.h"

#include "GLFW/glfw3.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "LogManager.h"

namespace Editor
{
	Application::Application()
	{
		_InitLog();
		_InitGlfw();
		_InitImgui();
	}

	Application::~Application()
	{
		_FinalizeImgui();
		_FinalizeGlfw();
	}

	void Application::_HandleGlfwErrors(int error, const char* content)
	{
		auto logger = spdlog::get("EDITOR");
		if (logger == nullptr)
		{
			return;
		}

		logger->error("glfw error occured: {}", content);
		logger->flush();
	}

	void Application::Run()
	{
		if (_MainWindow == nullptr)
		{
			return;
		}

		while (glfwWindowShouldClose(_MainWindow->GetGLFWwindow()) == false)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
			ImGui::BeginMainMenuBar();
			ImGui::EndMainMenuBar();
			ImGui::Begin("hello, world!");
			ImGui::Text("test text");
			ImGui::End();

			_Render();
			glfwSwapBuffers(_MainWindow->GetGLFWwindow());
			glfwPollEvents();
		}

		glfwDestroyWindow(_MainWindow->GetGLFWwindow());
	}

	void Application::_InitLog()
	{
		_LogManager = std::unique_ptr<LogManager>(new LogManager());
		if (_LogManager == nullptr)
		{
			assert(_LogManager);
			return;
		}

		_EditorLogger = _LogManager->GetLogger(LogType::EDITOR);
		if (_EditorLogger == nullptr)
		{
			assert(_EditorLogger);
			return;
		}
	}

	void Application::_InitGlfw()
	{
		auto result = glfwInit();
		if (result == GLFW_FALSE)
		{
			_EditorLogger->error("glfw init error");
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
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
		ImGui_ImplOpenGL3_Init();
	}

	void Application::_FinalizeGlfw()
	{
		glfwTerminate();
	}

	void Application::_FinalizeImgui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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

	void Application::_Render()
	{
		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		auto io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

} 