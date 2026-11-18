#include "Application.h"

HRESULT Application::initialize(HINSTANCE instance) noexcept
{
    return windoInstance_.create(instance, APP_NAME, 1280, 720);
}

void Application::loop() noexcept
{
	while (windoInstance_.massageloop())
	{

	}
}
