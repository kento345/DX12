#pragma once
#include<Windows.h>
#include<string_view>
#include<vector>

struct WindowProparty
{
	
};

class Window final	
{
public:
	Window()noexcept = default;
	
	~Window()noexcept = default;

public:
	[[nodiscard]] HRESULT create(HINSTANCE hInstance, std::string_view name, int width, int height)noexcept;

	[[nodiscard]] bool massageloop() noexcept;

	[[nodiscard]] HWND handle()const noexcept;
	/// <summary>
	/// サイズ取得
	/// </summary>
	/// <returns>{width, height}</returns>
	[[nodiscard]] std::pair<int,int> Size()const noexcept;


private:
	HWND handle_{};
	int height_ {};
	int	width_  {};
};

