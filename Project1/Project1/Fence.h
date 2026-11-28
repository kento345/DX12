#pragma once

#include"Device.h"

class Fence final
{
public:
	Fence() = default;
	
	~Fence();

public:

	[[nodiscard]] bool create(const Device& device)noexcept;

	void wait(UINT fenceValue)const noexcept;

	[[nodiscard]] ID3D12Fence* get()const noexcept;

private:
	ID3D12Fence* fence_{};
	HANDLE waitGpuEvent_{};
};

