#pragma once

#include"Device.h"
#include"Command_Allocator.h"

class Command_List final
{
public:
	Command_List() = default;
	
	~Command_List();

public:

	[[nodiscard]] bool create(const Device& device, const Command_Allocator& commandAllocator)noexcept;

	void reset(const Command_Allocator& commandAllocator)noexcept;

	[[nodiscard]] ID3D12GraphicsCommandList* get()const noexcept;

private:
	ID3D12GraphicsCommandList* commandList_{};
};

