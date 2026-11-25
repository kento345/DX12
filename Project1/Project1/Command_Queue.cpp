#include "Command_Queue.h"
#include<cassert>

Command_Queue::~Command_Queue()
{
	if (commandQueue_) {
		commandQueue_->Release();
		commandQueue_ = nullptr;
	}
}

bool Command_Queue::create(const Device& device) noexcept
{
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;

	const auto hr = device.get()->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue_));
	if (FAILED(hr)) {
		assert(false && "コマンドキューの作成に失敗");
		return false;
	}

	return true;
}

ID3D12CommandQueue* Command_Queue::get() const noexcept
{
	if (!commandQueue_) {
		assert(false && "コマンドキューが未作成");
		return nullptr;
	}
	return commandQueue_;
}
