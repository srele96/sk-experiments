#include <Windows.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <d3d12sdklayers.h>

// Initialize the pipeline.
//
// Enable the debug layer.
//
// Create the device.
// Create the command queue.
// Create the swap chain.
// Create a render target view (RTV) descriptor heap.
// Create frame resources (a render target view for each frame).
// Create a command allocator.

// Initialize the assets.
//
// Create an empty root signature.
// Compile the shaders.
// Create the vertex input layout.
// Create a pipeline state object description, then create the object.
// Create the command list.
// Close the command list.
// Create and load the vertex buffers.
// Create the vertex buffer views.
// Create a fence.
// Create an event handle.
// Wait for the GPU to finish.

int main() {
  // enable the debug layer
  ID3D12Debug* debugController;
  D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
  debugController->EnableDebugLayer();
  // create the device
  ID3D12Device* device;
  D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
  // create the command queue
  ID3D12CommandQueue* commandQueue;
  D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
  commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
  device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
  // create the swap chain
  IDXGIFactory4* factory;
  CreateDXGIFactory1(IID_PPV_ARGS(&factory));
  IDXGISwapChain* swapChain;
  DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
  swapChainDesc.BufferCount = 2;
  swapChainDesc.BufferDesc.Width = 0;
  swapChainDesc.BufferDesc.Height = 0;
  swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
  swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDesc.OutputWindow = GetConsoleWindow();
  swapChainDesc.SampleDesc.Count = 1;
  swapChainDesc.SampleDesc.Quality = 0;
  swapChainDesc.Windowed = TRUE;
  factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain);
  // create a render target view (RTV) descriptor heap
  ID3D12DescriptorHeap* rtvHeap;
  D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
  rtvHeapDesc.NumDescriptors = 2;
  rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
  // create frame resources (a render target view for each frame)
  ID3D12Resource* renderTargets[2];
  D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
  for (int i = 0; i < 2; i++) {
    swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargets[i]));
    device->CreateRenderTargetView(renderTargets[i], nullptr, rtvHandle);
    rtvHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  }
  // create a command allocator
  ID3D12CommandAllocator* commandAllocator;
  device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
  // create an empty root signature
  ID3D12RootSignature* rootSignature;
  D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
  rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
  ID3DBlob* signature;
  ID3DBlob* error;
  D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
  device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
  // compile the shaders
  ID3DBlob* vertexShader;
  ID3DBlob* pixelShader;
  D3DCompileFromFile(L"shaders.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &vertexShader, nullptr);
  D3DCompileFromFile(L"shaders.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &pixelShader, nullptr);
  // create the vertex input layout
  D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
  };
  // create a pipeline state object description, then create the object
  D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
  psoDesc.InputLayout = { inputElementDescs, 2 };
  psoDesc.pRootSignature = rootSignature;
  psoDesc.VS = { reinterpret_cast<UINT8*>(vertexShader->GetBufferPointer()), vertexShader->GetBufferSize() };
  psoDesc.PS = { reinterpret_cast<UINT8*>(pixelShader->GetBufferPointer()), pixelShader->GetBufferSize() };
  psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
  psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
  psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
  psoDesc.SampleMask = UINT_MAX;
  psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
  psoDesc.NumRenderTargets = 1;
  psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
  psoDesc.SampleDesc.Count = 1;
  ID3D12PipelineState* pipelineStateObject;
  device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineStateObject));


  return 0;
}
