#include "precomp.h"
#include "Application.h"
#include "LogManager.h"

using namespace Editor;
using namespace std;

void Init()
{
	LogManager::CreateInstance();
	Application::CreateInstance();
}

void Release()
{
	Application::DestroyInstance();
	LogManager::DestroyInstance();
}

int main()
{
	Init();
	Application::Instance()->Run();
	Release();
	return 0;
}