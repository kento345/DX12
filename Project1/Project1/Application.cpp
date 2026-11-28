#include "Application.h"
#include<cassert>

bool Application::initialize(HINSTANCE instance) noexcept
{
	if (S_OK != windoInstance_.create(instance, APP_NAME, 1280, 720)) {
		assert(false && "Windowの作成に失敗");
		return false;
	}
	if (!dxgiInstance_.setDisplayAdapter()) {
		assert(false && "DXGIの作成に失敗");
		return false;
	}
	if (!deviceInstance_.create(dxgiInstance_)) {
		assert(false && "Deviceの作成に失敗");
		return false;
	}
	if (!commandQueueInstance_.create(deviceInstance_)) {
		assert(false && "CommandQueueの作成に失敗");
		return false;
	}
	if (!swapChainInstance_.create(dxgiInstance_, windoInstance_, commandQueueInstance_)) {
		assert(false && "SwapChainの作成に失敗");
		return false;
	}
	if (!descriptorHeapInstance_.create(deviceInstance_, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, swapChainInstance_.getDesc().BufferCount)) {
		assert(false && "DescriptorHeapの作成に失敗");
		return false;
	}
	if (!renderTargetInstance_.createBackBuffer(deviceInstance_, swapChainInstance_, descriptorHeapInstance_)) {
		assert(false && "RenderTargetの作成に失敗");
		return false;
	}
	if (!commandAllocatorInstance_[0].create(deviceInstance_, D3D12_COMMAND_LIST_TYPE_DIRECT)) {
		assert(false && "CommandAllocator1を作成に失敗");
		return false;
	}
	if (!commandAllocatorInstance_[1].create(deviceInstance_, D3D12_COMMAND_LIST_TYPE_DIRECT)) {
		assert(false && "CommandAllocator2の作成に失敗 ");
		return false;
	}
	if (!commandListInstance_.create(deviceInstance_, commandAllocatorInstance_[0])) {
		assert(false && "CommandListの作成に失敗 ");
		return false;
	}
	if (!fenceInstance_.create(deviceInstance_)) {
		assert(false && "Fenceの作成に失敗 ");
		return false;
	}

	return true;
}

D3D12_RESOURCE_BARRIER resourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to) noexcept {
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = resource;
	barrier.Transition.StateBefore = from;
	barrier.Transition.StateAfter = to;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	return barrier;
}

void Application::loop() noexcept
{
	while (windoInstance_.massageloop())
	{
		const auto backBufferIndex = swapChainInstance_.get()->GetCurrentBackBufferIndex();
		
		if (frameFenceValue_[backBufferIndex] != 0) {
			fenceInstance_.wait(frameFenceValue_[backBufferIndex]);
		}


		commandAllocatorInstance_[backBufferIndex].reset();
		commandListInstance_.reset(commandAllocatorInstance_[backBufferIndex]);

		//プレゼントからレンダーターゲットに変更
		auto pToRT = resourceBarrier(renderTargetInstance_.get(backBufferIndex), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		commandListInstance_.get()->ResourceBarrier(1, &pToRT);

		D3D12_CPU_DESCRIPTOR_HANDLE handles[] = { renderTargetInstance_.getDescriptorHandle(deviceInstance_,descriptorHeapInstance_,backBufferIndex) };

		commandListInstance_.get()->OMSetRenderTargets(1, handles, false, nullptr);

		const float clearColor[] = { 1.0f,0.0f,0.0f,1.0f };
		commandListInstance_.get()->ClearRenderTargetView(handles[0], clearColor, 0, nullptr);

		auto rtToP = resourceBarrier(renderTargetInstance_.get(backBufferIndex), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		commandListInstance_.get()->ResourceBarrier(1, &rtToP);

		commandListInstance_.get()->Close();

		ID3D12CommandList* pCommandLists[] = { commandListInstance_.get() };
		commandQueueInstance_.get()->ExecuteCommandLists(_countof(pCommandLists), pCommandLists);

		swapChainInstance_.get()->Present(1, 0);

		commandQueueInstance_.get()->Signal(fenceInstance_.get(), nextFenceValue_);
		frameFenceValue_[backBufferIndex] = nextFenceValue_;
		nextFenceValue_++;
	}

	commandQueueInstance_.get()->Signal(fenceInstance_.get(), nextFenceValue_);
	fenceInstance_.wait(nextFenceValue_);
}
