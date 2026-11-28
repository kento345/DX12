#pragma once

#include"DXGI.h"
#include"Command_Queue.h"
#include"Window.h"

class Swap_Chain final
{
public:
	Swap_Chain() = default;
	
	~Swap_Chain();

public:

	[[nodiscard]] bool create(const DXGI& dxgi, const Window& window, const Command_Queue& commandQueue)noexcept;

	[[nodiscard]] IDXGISwapChain3* get()const noexcept;

	[[nodiscard]] const DXGI_SWAP_CHAIN_DESC1& getDesc()const noexcept;

private:
	IDXGISwapChain3* swapChain_{};
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
};

