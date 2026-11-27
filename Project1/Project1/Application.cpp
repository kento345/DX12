#include "Application.h"
#include<cassert>

bool Application::initialize(HINSTANCE instance) noexcept
{
	if (S_OK != windoInstance_.create(instance, "MyApp", 1280, 720)) {
		assert(false && "ウィンドwの作成に失敗");
		return false;
	}


	return true;
}

void Application::loop() noexcept
{
	while (windoInstance_.massageloop())
	{

	}
}
