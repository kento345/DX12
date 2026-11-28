#pragma once

#include"Device.h"

class Command_Allocator final
{
public:
	Command_Allocator() = default;
	
	~Command_Allocator();

public:

	[[nodiscard]] bool create(const Device& device,const D3D12_COMMAND_LIST_TYPE type)noexcept;

	void reset()noexcept;

	[[nodiscard]] ID3D12CommandAllocator* get()const noexcept;

	[[nodiscard]] D3D12_COMMAND_LIST_TYPE getType()const noexcept;

private:
	ID3D12CommandAllocator* commandAllocator_{};
	D3D12_COMMAND_LIST_TYPE type_{};
};

