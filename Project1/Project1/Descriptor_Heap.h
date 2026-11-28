#pragma once
#include"Device.h"

class Descriptor_Heap final
{
public:
	Descriptor_Heap() = default;
	
	~Descriptor_Heap();

public:
	[[nodiscard]] bool create(const Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible = false)noexcept;

	[[nodiscard]] ID3D12DescriptorHeap* get()const noexcept;

	[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE getType()const noexcept;

private:
	ID3D12DescriptorHeap* descriptorHeap_{};
	D3D12_DESCRIPTOR_HEAP_TYPE type_{};
};

