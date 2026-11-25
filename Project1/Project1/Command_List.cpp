#include "Command_List.h"
#include<cassert>

bool Command_List::create(const Device& device, const Command_Allocator& commandAllocator) noexcept
{


    return true;
}

void Command_List::reset(const Command_Allocator& commandAllocator) noexcept
{

}

ID3D12GraphicsCommandList* Command_List::get() const noexcept
{
    if (!commandList_) {
        assert(false && "コマンドリストが未作成");
        return nullptr;
    }
    return commandList_;
}
