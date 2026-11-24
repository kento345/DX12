#include "Device.h"
#include<cassert>

bool Device::create(const DXGI& dxgi) noexcept
{
	const auto hr = D3D12CreateDevice(dxgi.GetAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
	if (FAILED(hr))
	{
		assert(false && "デバイス作成に失敗");
		return false;
	}

    return true;
}

ID3D12Device* Device::get() const noexcept
{
	if (!device) {
		assert(FALSE && "デバイスが未作成");
		return false;
	}
	return device;
}
