#include "Fence.h"

#include<cassert>

Fence::~Fence()
{
	if (fence_) {
		fence_->Release();
		fence_ = nullptr;
	}
}

bool Fence::create(const Device & device) noexcept
{
	auto hr = device.get()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	if (FAILED(hr)) {
		assert(false && "フェンスの作成に失敗");
		return false;
	}

	waitGpuEvent_ = CreateEvent(nullptr, false, false, "WAIT_GPU");
	if (!waitGpuEvent_) {
		assert(false && "GPU同期用のイベントハンドルの作成に失敗");
		return false;
	}

	return true;
}

void Fence::wait(UINT fenceValue) const noexcept
{
	if (!fence_) {
		assert(false && "フェンスが未作成");
		return;
	}

	if (fence_->GetCompletedValue() < fenceValue) {
		fence_->SetEventOnCompletion(fenceValue, waitGpuEvent_);
		WaitForSingleObject(waitGpuEvent_, INFINITE);
	}
}

ID3D12Fence* Fence::get() const noexcept
{
	if (!fence_) {
		assert(false && "フェンスが未作成");
		return nullptr;
	}
	return fence_;
}
