#include "Swap_Chain.h"
#include<cassert>

Swap_Chain::~Swap_Chain()
{
	if (swapChain_) {
		swapChain_->Release();
		swapChain_ = nullptr;
	}
}

bool Swap_Chain::create(const DXGI& dxgi, const Window& window, const Command_Queue& commandQueue) noexcept
{
	const auto [w, h] = window.Size();

	swapChainDesc_ = {};
	swapChainDesc_.BufferCount = 2;
	swapChainDesc_.Width = w;
	swapChainDesc_.Height = h;
	swapChainDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc_.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc_.SampleDesc.Count = 1;

	IDXGISwapChain1* tempSwapChin{};
	{
		const auto hr = dxgi.GetFactory()->CreateSwapChainForHwnd(commandQueue.get(), window.handle(), &swapChainDesc_, nullptr, nullptr, &tempSwapChin);
		if (FAILED(hr)) {
			assert(false && "スワップチェインの作成に失敗 ");
			return false;
		}
	}

	{
		const auto hr = tempSwapChin->QueryInterface(IID_PPV_ARGS(&swapChain_));
		tempSwapChin->Release();

		if (FAILED(hr)) {
			assert(false && "スワップチェインのアップグレードに失敗 ");
			return false;
		}
	}
	
	return true;
}


IDXGISwapChain3* Swap_Chain::get() const noexcept
{
	if (!swapChain_) {
		assert(false && "スワップチェインが未作成");
		return nullptr;
	}
	return swapChain_;
}

const DXGI_SWAP_CHAIN_DESC1& Swap_Chain::getDesc() const noexcept
{
	if (!swapChain_) {
		assert(false && "スワップチェインが未作成");
    }
	return swapChainDesc_;
}
