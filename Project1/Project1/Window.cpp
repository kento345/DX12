#include "Window.h"



LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept {
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:

		return 0;
	case WM_KEYDOWN:

		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

HRESULT Window::create(HINSTANCE hInstance,std::string_view name, int width, int height) noexcept
{

	WNDCLASS wc{};
    wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = name.data();
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClass(&wc);

	handle_ = CreateWindow(
		wc.lpszClassName, wc.lpszMenuName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,
		width, height,
		nullptr, nullptr, hInstance, nullptr
	);
	if (!handle_) { return E_FAIL; }

	ShowWindow(handle_, SW_SHOW);

	UpdateWindow(handle_);

	width_ = width;
	height_ = height;

	return S_OK;
}

bool Window::massageloop() noexcept
{
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

HWND Window::handle() const noexcept
{
	return handle_;
}

std::pair<int, int> Window::Size() const noexcept
{
	return { width_,height_ };
}





