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
	/// <summary>
	/// ウィンドウ作成
	/// </summary>
	/// <param name="hInstance"></param>
	/// <param name="name"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	[[nodiscard]] HRESULT create(HINSTANCE hInstance, std::string_view name, int width, int height)noexcept;

	/// <summary>
	/// メッセージループ
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] bool massageloop() noexcept;

	/// <summary>
	/// ハンドル取得
	/// </summary>
	/// <returns></returns>
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

