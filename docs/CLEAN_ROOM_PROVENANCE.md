# Clean-Room Engineering & IP Provenance Declaration

## 1. Clean-Room Methodology

PrismX is an independent, sovereign graphics architecture designed from the ground up to achieve interface compatibility with DirectX (DXGI, Direct3D 11, Direct3D 12) and Khronos Vulkan 1.3 without using any proprietary, closed-source, or leaked code.

All implementation code in PrismX has been written following rigorous clean-room standards:
- **Functional Specification Conformance**: Development was performed exclusively against publicly documented specifications, published API documentation, and MIT/Apache-2.0 licensed header files.
- **Zero Decompilation / Reverse Engineering**: No proprietary binary disassembly, decompilation, or reverse engineering of Microsoft or third-party graphics drivers was performed.
- **Independent Algorithmic Implementation**: All rasterization algorithms (sub-pixel edge evaluation, barycentric coordinate interpolation), shader bytecode VM execution models, matrix transformations, and command queue fence synchronization mechanisms were written independently in standard modern ISO C++23.

---

## 2. Upstream Open-Source References & Licensing

PrismX interfaces and constants are aligned with the following openly licensed public repositories:

| Specification / Standard | Upstream Repository / Authority | License |
| :--- | :--- | :--- |
| **DirectX-Headers** (DXGI, D3D11, D3D12) | [microsoft/DirectX-Headers](https://github.com/microsoft/DirectX-Headers) | MIT License |
| **Win32 Metadata** | [microsoft/win32metadata](https://github.com/microsoft/win32metadata) | MIT License |
| **DirectX Tool Kit** (Math / Primitives) | [microsoft/DirectXTK](https://github.com/microsoft/DirectXTK) | MIT License |
| **Vulkan 1.3 Specification** | [KhronosGroup/Vulkan-Docs](https://github.com/KhronosGroup/Vulkan-Docs) | Apache-2.0 / MIT |

---

## 3. Trademark & Nominative Fair Use

- "DirectX", "Direct3D", "DXGI", "Windows", and "Windows NT" are registered trademarks of Microsoft Corporation.
- "Vulkan" is a registered trademark of the Khronos Group Inc.
- Use of these names throughout this repository is strictly nominative for describing interface compatibility, driver interoperability, and architectural standards under fair use principles.
- PrismX is not affiliated with, endorsed by, or sponsored by Microsoft Corporation or the Khronos Group.
