#pragma once

#include"Device.h"
#include"Descriptor_Heap.h"
#include"Swap_Chain.h"
#include<vector>

class Render_Target final
{
public:
	Render_Target() = default;
	
	~Render_Target();

public:
	[[nodiscard]] bool createBackBuffer(const Device& device, const Swap_Chain& swapChain, const Descriptor_Heap& heap)noexcept;

	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getDescriptorHandle(const Device& device, const Descriptor_Heap& heap, UINT index)const noexcept;

	[[nodiscard]] ID3D12Resource* get(uint32_t index)const noexcept;

private:
	std::vector<ID3D12Resource*> renderTargets_{};
};

