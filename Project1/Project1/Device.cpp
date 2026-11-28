#include "Device.h"
#include<cassert>

Device::~Device()
{
	if (device_) {
		device_->Release();
		device_ = nullptr;
	}
}

bool Device::create(const DXGI& dxgi) noexcept
{
	const auto hr = D3D12CreateDevice(dxgi.GetAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device_));
	if (FAILED(hr))
	{
		assert(false && "デバイス作成に失敗");
		return false;
	}

    return true;
}

ID3D12Device* Device::get() const noexcept
{
	if (!device_) {
		assert(FALSE && "デバイスが未作成");
		return nullptr;
	}
	return device_;
}
