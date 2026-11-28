#include "Command_Allocator.h"
#include<cassert>

Command_Allocator::~Command_Allocator()
{
    if (commandAllocator_) {
        commandAllocator_->Release();
        commandAllocator_ = nullptr;
    }
}

bool Command_Allocator::create(const Device& device, const D3D12_COMMAND_LIST_TYPE type) noexcept
{
    type_ = type;

    const auto hr = device.get()->CreateCommandAllocator(type_, IID_PPV_ARGS(&commandAllocator_));
    if (FAILED(hr)) {
        assert(false && "コマンドアロケータの作成に失敗 ");
        return false;
    }

    return true;
}

void Command_Allocator::reset() noexcept
{
    if (!commandAllocator_) {
        assert(false && "コマンドアロケータが未作成");
    }

    commandAllocator_->Reset();
}

ID3D12CommandAllocator* Command_Allocator::get() const noexcept
{
    if (!commandAllocator_) {
        assert(false && "コマンドアロケータが未作成");
        return nullptr;
    }

    return commandAllocator_;
}

D3D12_COMMAND_LIST_TYPE Command_Allocator::getType() const noexcept
{
    if (!commandAllocator_) {
        assert(false && "コマンドリストのタイプが未設定 ");
    }
    return type_;
}
