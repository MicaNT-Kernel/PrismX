cmake_minimum_required(VERSION 3.25)
project(PrismX VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header-only interface library
add_library(prismx INTERFACE)
target_include_directories(prismx INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Optional sibling Microsoft open-source DirectX repositories in C:/Users/admin/source
foreach(_dx_inc
    "${CMAKE_CURRENT_SOURCE_DIR}/../DirectX-Headers/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../DirectXMath/Inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../DirectXMesh/DirectXMesh"
    "${CMAKE_CURRENT_SOURCE_DIR}/../DirectXTex/DirectXTex"
    "${CMAKE_CURRENT_SOURCE_DIR}/../DirectXTK12/Inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../D3D12TranslationLayer/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../D3D11On12/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../D3D9On12/include"
)
    if(EXISTS "${_dx_inc}")
        target_include_directories(prismx INTERFACE "$<BUILD_INTERFACE:${_dx_inc}>")
    endif()
endforeach()

# Compiler warnings and optimization flags
if (MSVC)
    add_compile_options(/W4 /permissive- /O2 /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()

# Standalone Test Suite
add_executable(prismx_tests tests/test_main.cpp)
target_link_libraries(prismx_tests PRIVATE prismx)

enable_testing()
add_test(NAME PrismXCoreTests COMMAND prismx_tests)

# Standalone Examples
add_executable(prismx_cube_demo examples/cube_3d_demo.cpp)
target_link_libraries(prismx_cube_demo PRIVATE prismx)

add_executable(prismx_d3d12_demo examples/d3d12_demo.cpp)
target_link_libraries(prismx_d3d12_demo PRIVATE prismx)

add_executable(prismx_shader_vm_demo examples/shader_vm_demo.cpp)
target_link_libraries(prismx_shader_vm_demo PRIVATE prismx)

add_executable(prismx_vulkan_demo examples/vulkan_demo.cpp)
target_link_libraries(prismx_vulkan_demo PRIVATE prismx)

add_executable(prismx_multimedia_demo examples/multimedia_demo.cpp)
target_link_libraries(prismx_multimedia_demo PRIVATE prismx)

# Output binaries to bin/
set_target_properties(
    prismx_tests
    prismx_cube_demo
    prismx_d3d12_demo
    prismx_shader_vm_demo
    prismx_vulkan_demo
    prismx_multimedia_demo
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
