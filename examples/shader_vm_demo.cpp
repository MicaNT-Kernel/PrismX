// ============================================================================
// PrismX Example: RISC SIMD Programmable Shader Bytecode Execution
// 
// Demonstrates assembling custom bytecode, setting registers, and executing
// vertex & lighting equations on the PrismShaderVM.
// ============================================================================

#include "prismx.hpp"
#include <iostream>
#include <array>

using namespace prismx;

int main() {
    std::cout << "[PrismX] Initializing PrismShaderVM...\n";

    // Build custom fragment shader:
    // r0 = dot3(v3.xyz, c0.xyz) [Lambertian diffuse lighting from normal]
    // r0 = max(r0, 0.0)
    // r1 = c2 * r0 [Diffuse contribution]
    // r2 = r1 + c1 [Ambient + Diffuse]
    // o1 = v1 * r2 [Modulate vertex color by lighting]
    auto lightProg = PrismShaderVM::BuildDirectionalLightingPS();

    std::cout << "[PrismX] Assembled lighting shader: " << lightProg.InstructionCount() << " instructions\n";

    VectorRegister clipPos(0.0f, 0.0f, 1.0f, 1.0f);
    VectorRegister vertColor(1.0f, 0.2f, 0.1f, 1.0f); // Red-orange surface color
    VectorRegister vertUV(0.5f, 0.5f, 0.0f, 0.0f);
    VectorRegister vertNormal(0.0f, 1.0f, 0.0f, 0.0f); // Pointing +Y

    std::array<VectorRegister, 16> consts{};
    consts[0] = VectorRegister(0.0f, 1.0f, 0.0f, 0.0f); // Light direction (+Y)
    consts[1] = VectorRegister(0.2f, 0.2f, 0.2f, 1.0f); // Ambient lighting
    consts[2] = VectorRegister(0.8f, 0.8f, 0.8f, 1.0f); // Diffuse lighting
    consts[4] = VectorRegister(0.0f, 0.0f, 0.0f, 0.0f); // Zero clamp vector

    VectorRegister outLitColor;
    PrismShaderVM::ExecutePixelShader(lightProg, clipPos, vertColor, vertUV, vertNormal, consts, nullptr, outLitColor);

    std::cout << "[PrismX] Shaded Pixel Output: ("
              << outLitColor.x() << ", "
              << outLitColor.y() << ", "
              << outLitColor.z() << ", "
              << outLitColor.w() << ")\n";
    return 0;
}
