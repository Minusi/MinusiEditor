#include "precomp.h"
#include "Application.h"

using namespace Editor;

int main()
{
	std::unique_ptr<Application> window = std::make_unique<Application>();
	if (window == nullptr)
	{
		return 1;
	}

	window->Run();
	return 0;
}