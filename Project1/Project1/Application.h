#pragma once
#include<string_view>

#include"Window.h"
#include"Device.h"
#include"DXGI.h"
#include"Command_Allocator.h"
#include"Command_Queue.h"
#include"Command_List.h"
#include"Descriptor_Heap.h"
#include"Fence.h"
#include"Swap_Chain.h"
#include"Render_Target.h"

namespace {
	constexpr std::string_view APP_NAME = "MyApp";
}

class Application final
{
public:
	Application() = default;
	
	~Application() = default;
    
public:
	[[nodiscard]] bool initialize(HINSTANCE instance)noexcept;

	void loop()noexcept;


private:
	Window windoInstance_{}; //ウィンドウインスタンス
	DXGI dxgiInstance_{};
	Device deviceInstance_{};
	Command_Queue commandQueueInstance_{};
	Swap_Chain swapChainInstance_{};
	Descriptor_Heap descriptorHeapInstance_{};
	Render_Target renderTargetInstance_{};
	Command_Allocator commandAllocatorInstance_[2]{};
	Command_List commandListInstance_{};
	Fence fenceInstance_{};

	UINT64 frameFenceValue_[2]{};
	UINT64 nextFenceValue_ = 1;
};

