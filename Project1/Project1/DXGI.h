#pragma once
#include<d3d12.h>
#include<dxgi1_4.h>

class DXGI final
{
public:
	DXGI() = default;
	
	~DXGI() = default;


public:

	[[nodiscard]] HRESULT createFactory()noexcept;

	[[nodiscard]] IDXGIFactory4* GetFactory()const noexcept;

	[[nodiscard]] IDXGIAdapter1* createAdapter(IDXGIFactory4* factory) noexcept;

	[[nodiscard]] IDXGIAdapter1* GetAdapter()const noexcept;

private:
	IDXGIFactory4* factory = nullptr;
	UINT createFactoryFlags = 0;
	IDXGIAdapter1* adapter = nullptr;
};

