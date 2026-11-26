#include "Command_List.h"
#include<cassert>

Command_List::~Command_List()
{
    if (commandList_) {
        commandList_->Release();
        commandList_ = nullptr;
    }
}

bool Command_List::create(const Device& device, const Command_Allocator& commandAllocator) noexcept
{
    const auto hr = device.get()->CreateCommandList(0, commandAllocator.getType(),commandAllocator.get(),nullptr, IID_PPV_ARGS(&commandList_));

    if (FAILED(hr)) {
        assert(false && "コマンドリストの作成に失敗");
        return false;
    }

    commandList_->Close();
    return true;
}

void Command_List::reset(const Command_Allocator& commandAllocator) noexcept
{
    if (!commandList_) {
        assert(false && "コマンドリストが未作成");
    }

    commandList_->Reset(commandAllocator.get(),nullptr);
}

ID3D12GraphicsCommandList* Command_List::get() const noexcept
{
    if (!commandList_) {
        assert(false && "コマンドリストが未作成");
        return nullptr;
    }
    return commandList_;
}
