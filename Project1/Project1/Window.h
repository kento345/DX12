#pragma once
#include<Windows.h>
#include<string_view>

struct WindowProparty
{

};

class Window final	
{
	[[nodiscard]] bool create(std::string_view name, int width, int height)noexcept;

	//[[nodiscrad]] 

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept;
};

