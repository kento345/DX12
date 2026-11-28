#include "DXGI.h"
#include<cassert>

#pragma comment(lib,"dxgi.lib")

DXGI::~DXGI()
{
	if (factory_) {
		factory_->Release();
		factory_ = nullptr;
	}
	if (adapter_) {
		adapter_->Release();
		adapter_ = nullptr;
	}
}

bool DXGI::setDisplayAdapter() noexcept
{
#if _DEBUG
	ID3D12Debug* debug;

	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)))) {
		debug->EnableDebugLayer();
	}
#endif

	//ファクトリ作成
	{
		UINT createFactoryFlags = 0;
#if  _DEBUG
		createFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif //  _DEBUG
		const auto hr = CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&factory_));
		if (FAILED(hr)) {
			assert(false && "DXGIファクトリーの作成に失敗");
			return false;
		}
	}
	//アダプターの取得
	{
		auto select = 0;
		IDXGIAdapter1* dxgiAdapter{};

		//適切なアダプターを選ぶ
		while (factory_->EnumAdapters1(select,&dxgiAdapter) != DXGI_ERROR_NOT_FOUND) {
			DXGI_ADAPTER_DESC1 desc{};
			dxgiAdapter->GetDesc1(&desc);

			select++;

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
				dxgiAdapter->Release();
				continue;
			}

			if (FAILED(D3D12CreateDevice(dxgiAdapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr))) {
				dxgiAdapter->Release();
				continue;
			}
			adapter_ = dxgiAdapter;
			break;
		}

		if (!adapter_) {
			assert(false && "アダプタの取得に失敗");
			return false;
		}
	}

	return true;
}

IDXGIFactory4* DXGI::GetFactory() const noexcept
{ 
	if (!factory_)
	{
		assert(false && "DXGIファクトリが未作成です");
		return nullptr;
	}
	//DXGIファクトリを返す
	return factory_;
}

IDXGIAdapter1* DXGI::GetAdapter() const noexcept
{
	if (!adapter_)
	{
		assert(false && "ディスプレイアダプターが未作成です");
		return nullptr;
	}
	return adapter_;
}


