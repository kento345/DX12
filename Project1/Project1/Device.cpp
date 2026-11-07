#include "Device.h"

bool Device::create(const DXGI& dxgi) noexcept
{
	if (dxgi.GetAdapter() != nullptr)
	{
		hr = D3D12CreateDevice(dxgi.GetAdapter(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
	}

    return false;
}
