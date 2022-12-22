#include <Windows.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

int main() {
  // Create the DXGI factory
  IDXGIFactory4* dxgiFactory = nullptr;
  CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));

  // Create the D3D12 device
  ID3D12Device* device = nullptr;
  D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

  // Create the command queue
  ID3D12CommandQueue* commandQueue = nullptr;
  D3D12_COMMAND_QUEUE_DESC queueDesc = {};
  queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
  device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));

  // Create the swap chain
  IDXGISwapChain4* swapChain = nullptr;
  DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
  swapChainDesc.Width = 800;
  swapChainDesc.Height = 600;
  swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swapChainDesc.SampleDesc.Count = 1;
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDesc.BufferCount = 2;
  dxgiFactory->CreateSwapChainForHwnd(commandQueue, GetActiveWindow(),
                                      &swapChainDesc, nullptr, nullptr,
                                      &swapChain);

  // Create the render target view
  ID3D12Resource* backBuffer = nullptr;

  return 0;
}
