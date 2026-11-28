#include "Descriptor_Heap.h"
#include<cassert>

Descriptor_Heap::~Descriptor_Heap()
{
    if (descriptorHeap_) {
        descriptorHeap_->Release();
        descriptorHeap_ = nullptr;
    }
}

bool Descriptor_Heap::create(const Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible) noexcept
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
    heapDesc.Type = type;
    heapDesc.NumDescriptors = numDescriptors;
    heapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    type_ = type;

    auto hr = device.get()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descriptorHeap_));
    if (FAILED(hr)) {
        assert(false && "ディスクリプタヒープの作成に失敗 ");
        return false;
    }

    return true;
}

ID3D12DescriptorHeap* Descriptor_Heap::get() const noexcept
{
    if (!descriptorHeap_) {
        assert(false && "ディスクリプタヒープが未作成");
        return nullptr;
    }
    return descriptorHeap_;
}

D3D12_DESCRIPTOR_HEAP_TYPE Descriptor_Heap::getType() const noexcept
{
    if (!type_) {
        assert(false && "ディスクリプタヒープのタイプが未設定 ");
    }
    return type_;
}
