#pragma once
#include "glfwType.h"


class GLFWwindow;

namespace Editor
{
	struct WindowHint
	{
	public:
		std::map<glfw::WindowHintType, int>					Hints{};
		std::map<glfw::WindowHintStringType, std::string>	StringHints{};
		std::pair<size_t, size_t>							WindowSize{};
		std::string											WindowTitle{};
	};


	class BaseWindow
	{
	public:
		BaseWindow(WindowHint hint);
		~BaseWindow() = default;

	public:
		GLFWwindow* GetGLFWwindow() const { return _Window; }
		std::pair<int, int> GetFrameBufferSize() const;
		int GetWindowWidth() const { return _WindowSize.first; }
		int GetWindowHeight() const { return _WindowSize.second; }
		const std::string& GetTitle() const { return _Title; }

		void SetWindowAttribute(glfw::WindowSetAttributeType type, int value);

	private:
		std::string											_Title{};
		std::pair<int, int>									_WindowSize{};
		GLFWwindow*											_Window{};
	};
}