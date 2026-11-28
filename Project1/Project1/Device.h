#pragma once
#include<d3d12.h>
#include"DXGI.h"


class Device final
{
public:
    Device() = default;
	
	~Device();

public:
	[[nodiscard]] bool create(const DXGI& dxgi)noexcept;

	[[nodiscard]] ID3D12Device* get()const noexcept;
private:
	
	ID3D12Device* device_{};
};

