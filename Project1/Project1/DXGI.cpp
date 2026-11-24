#include "DXGI.h"

#include<cassert>

DXGI::~DXGI()
{
	if (factory) {
		factory->Release();
		factory = nullptr;
	}
	if (adapter) {
		adapter->Release();
		adapter = nullptr;
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
		const auto hr = CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&factory));
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
		while (factory->EnumAdapters1(select,&adapter) != DXGI_ERROR_NOT_FOUND) {
			DXGI_ADAPTER_DESC1 desc{};
			adapter->GetDesc1(&desc);

			select++;

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
				adapter->Release();
				continue;
			}

			if (FAILED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr))) {
				adapter->Release();
				continue;
			}
			adapter = dxgiAdapter;
			break;
		}
	}

	return true;
}

IDXGIFactory4* DXGI::GetFactory() const noexcept
{ 
	if (!factory)
	{
		OutputDebugStringA("DXGI Factory is not created\n");
		assert(false && "DXGIファクトリが未作成です");
		return nullptr;
	}
	//DXGIファクトリを返す
	return factory;
}

IDXGIAdapter1* DXGI::GetAdapter() const noexcept
{
	if (!adapter)
	{
		OutputDebugStringA("DXGI Adapter is not created\n");
		assert(false && "ディスプレイアダプターが未作成です");
		return nullptr;
	}
	return adapter;
}


