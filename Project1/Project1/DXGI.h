#pragma once
#include<d3d12.h>
#include<dxgi1_4.h>

class DXGI final
{
public:
	DXGI() = default;
	
	~DXGI();


public:

	[[nodiscard]] bool setDisplayAdapter()noexcept;

	[[nodiscard]] IDXGIFactory4* GetFactory()const noexcept;

	[[nodiscard]] IDXGIAdapter1* GetAdapter()const noexcept;

private:
	IDXGIFactory4* factory = nullptr;
	IDXGIAdapter1* adapter = nullptr;
};

