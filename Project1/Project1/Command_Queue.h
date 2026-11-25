#pragma once

#include"Device.h"

class Command_Queue final
{
public:
	Command_Queue() = default;
	
	~Command_Queue();

public:

	[[nodiscard]] bool create(const Device& device)noexcept;

	[[nodiscard]] ID3D12CommandQueue* get()const noexcept;

private:
	ID3D12CommandQueue* commandQueue_{};
};

