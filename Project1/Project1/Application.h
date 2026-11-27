#pragma once
#include<string_view>

#include"Window.h"

namespace {
	constexpr std::string_view APP_NAME = "MyApp";
}

class Application final
{
public:
	Application() = default;
	
	~Application() = default;
    
public:
	[[nodiscard]] bool initialize(HINSTANCE instance)noexcept;

	void loop()noexcept;


private:
	Window windoInstance_; //ウィンドウインスタンス
};

