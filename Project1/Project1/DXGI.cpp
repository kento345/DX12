#include "DXGI.h"

#include<cassert>

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
#if defined(_DEBUG)
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
			OutputDebugStringA("Failed to create DXGI Factory\n");
			assert(false && "DXGIファクトリーの作成に失敗");
			return false;
		}
	}
	//アダプターの取得
	{
		auto select = 0;
		IDXGIAdapter1* dxgiAdapter{};

		//適切なアダプターを選ぶ
		while (factory_->EnumAdapters1(select,&adapter_) != DXGI_ERROR_NOT_FOUND) {
			DXGI_ADAPTER_DESC1 desc{};
			adapter_->GetDesc1(&desc);

			select++;

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
				adapter_->Release();
				continue;
			}

			if (FAILED(D3D12CreateDevice(adapter_, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr))) {
				adapter_->Release();
				continue;
			}
			adapter_ = dxgiAdapter;
			break;
		}
	}

	return true;
}

IDXGIFactory4* DXGI::GetFactory() const noexcept
{ 
	if (!factory_)
	{
		OutputDebugStringA("DXGI Factory is not created\n");
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
		OutputDebugStringA("DXGI Adapter is not created\n");
		assert(false && "ディスプレイアダプターが未作成です");
		return nullptr;
	}
	return adapter_;
}


