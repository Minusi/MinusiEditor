#include "precomp.h"
#include "BaseWindow.h"
#include "GLFW/glfw3.h"


namespace Editor
{
	BaseWindow::BaseWindow(WindowHint hint)
	{
		for (const auto& it : hint.Hints)
		{
			glfwWindowHint(static_cast<int>(it.first), it.second);
		}
		for (const auto& it : hint.StringHints)
		{
			glfwWindowHintString(static_cast<int>(it.first), it.second.c_str());
		}

		_Window = glfwCreateWindow(hint.WindowSize.first, hint.WindowSize.second, hint.WindowTitle.c_str(), nullptr, nullptr);
		assert(_Window);
	}

	std::pair<int, int> BaseWindow::GetFrameBufferSize() const
	{
		std::pair<int, int> bufferSize{};
		glfwGetFramebufferSize(_Window, &bufferSize.first, &bufferSize.second);

		return bufferSize;
	}

	void BaseWindow::SetWindowAttribute(glfw::WindowSetAttributeType type, int value)
	{
		if (_Window == nullptr)
		{
			return;
		}

		glfwSetWindowAttrib(_Window, static_cast<int>(type), value);
	}
}