#include "DXGI.h"

HRESULT DXGI::createFactory() noexcept
{
#if defined(_DEBUG)
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	HRESULT hr = CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&factory));
	if (FAILED(hr))
	{
		OutputDebugStringA("Failed to create DXGI Factory\n");
		return	hr;
	}

	return S_OK;
}

IDXGIAdapter1* DXGI::createAdapter(IDXGIFactory4* factory) noexcept
{
	//ハードフェアアダプターを順に検索
	for (UINT adapterIndex = 0; ; ++adapterIndex)
	{
		adapter = nullptr;
		if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &adapter))
		{
			break; //アダプタが見つからない
		}

		//アダプタの情報を取得
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		//ソフトウェアアダプタはスキップ
		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			adapter->Release(); 
			continue;
		}

		//DirectX12が利用可能か確認
		if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)))
		{
			return adapter; //DirectX12が利用可能なアダプタを発見
		}

		adapter->Release();	
	}
	return nullptr;
}

IDXGIFactory4* DXGI::GetFactory() const noexcept
{ 
	if (factory == nullptr)
	{
		OutputDebugStringA("DXGI Factory is not created\n");
		return nullptr;
	}
	//DXGIファクトリを返す
	return factory;
}

IDXGIAdapter1* DXGI::GetAdapter() const noexcept
{
	if (adapter == nullptr)
	{
		OutputDebugStringA("DXGI Adapter is not created\n");
		return nullptr;
	}
	return adapter;
}


