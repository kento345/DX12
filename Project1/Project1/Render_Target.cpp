#include "Render_Target.h"

#include<cassert>

Render_Target::~Render_Target()
{
	for (auto& rt : renderTargets_) {
		if (rt) {
			rt->Release();
			rt = nullptr;
		}
	}
	renderTargets_.clear();
}

bool Render_Target::createBackBuffer(const Device & device, const Swap_Chain & swapChain, const Descriptor_Heap & heap) noexcept
{
	const auto& desc = swapChain.getDesc();

	renderTargets_.resize(desc.BufferCount);

	auto handle = heap.get()->GetCPUDescriptorHandleForHeapStart();

	auto heapType = heap.getType();
	assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプタヒープのタイプがRTVではありません");

	for (uint8_t i = 0;i < desc.BufferCount;i++) {
		const auto hr = swapChain.get()->GetBuffer(i, IID_PPV_ARGS(&renderTargets_[i]));
		if (FAILED(hr)) {
			assert(false && "バックバッファの取得に失敗 ");
			return false;
		}

		device.get()->CreateRenderTargetView(renderTargets_[i], nullptr, handle);
		handle.ptr += device.get()->GetDescriptorHandleIncrementSize(heapType);
	}

	return true;
}

D3D12_CPU_DESCRIPTOR_HANDLE Render_Target::getDescriptorHandle(const Device& device, const Descriptor_Heap& heap, UINT index) const noexcept
{
	if (index >= renderTargets_.size() || !renderTargets_[index]) {
		assert(false && "不要なレンダーターゲットです ");
	}
	auto handle = heap.get()->GetCPUDescriptorHandleForHeapStart();

	auto heapType = heap.getType();
	assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプタヒープのタイプが RTV ではありません");
	
	handle.ptr += index * device.get()->GetDescriptorHandleIncrementSize(heapType);
	return handle;
}

ID3D12Resource* Render_Target::get(uint32_t index) const noexcept
{
	if (index >= renderTargets_.size() || !renderTargets_[index]) {
		assert(false && "不正なレンダーターゲット");
		return nullptr;
	}
	return renderTargets_[index];
}
