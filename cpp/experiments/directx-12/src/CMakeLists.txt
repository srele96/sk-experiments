add_executable(
  directx-12

  main.cpp
)

target_link_libraries(directx-12 d3d12.lib)
target_link_libraries(directx-12 dxgi.lib)
target_link_libraries(directx-12 d3dcompiler.lib)
