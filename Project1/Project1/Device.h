#pragma once
#include<d3d12.h>
#include"DXGI.h"


class Device final
{
public:
    Device() = default;
	
	~Device() = default;

public:
	[[nodiscard]] bool create(const DXGI& dxgi)noexcept;


private:
	
	ID3D12Device* device = nullptr;
	HRESULT hr = E_FAIL;
};

