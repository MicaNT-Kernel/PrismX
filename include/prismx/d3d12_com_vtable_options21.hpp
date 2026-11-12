#pragma once
// ============================================================================
// PrismX Suite 32: Official Microsoft Direct3D 12 COM VTable Layout (44-Method
// ID3D12Device -> ID3D12Device14), Complete CheckFeatureSupport (OPTIONS ..
// OPTIONS21), Agility SDK D3D12GetInterface, and Versioned RootSignatures 1.2
// ============================================================================

#include <cstdint>
#include <cstring>
#include <atomic>
#include <vector>

#include "types.hpp"
#include "d3d12.hpp"
#include "dxgi1_6_com_abi.hpp"

namespace prismx {
namespace D3D12ComAbi {

// ============================================================================
// 1. Official Microsoft Direct3D 12 IIDs & CLSIDs (from DirectX-Headers/d3d12.h)
// ============================================================================

inline constexpr IID OFFICIAL_IID_ID3D12Device =
    { 0x189819f1, 0x1db6, 0x4b57, { 0xbe, 0x54, 0x18, 0x21, 0x33, 0x9b, 0x85, 0xf7 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device1 =
    { 0x77db08b3, 0xa3ec, 0x4e33, { 0x91, 0x19, 0x81, 0xc6, 0xa9, 0x19, 0x1d, 0x17 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device4 =
    { 0x70e617dd, 0xf9ae, 0x443c, { 0xb2, 0x11, 0x07, 0xca, 0xbe, 0x79, 0x77, 0xd1 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device5 =
    { 0x8b4f173b, 0x2fea, 0x4b80, { 0x8f, 0x58, 0x43, 0x07, 0x19, 0x1a, 0xb9, 0x5d } };
inline constexpr IID OFFICIAL_IID_ID3D12Device8 =
    { 0x9218e6bb, 0xf944, 0x4f7e, { 0xa7, 0x5c, 0xb1, 0xb2, 0xc7, 0xb7, 0x01, 0xf3 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device9 =
    { 0x56314f85, 0xef42, 0x4858, { 0xb9, 0x93, 0x76, 0x3d, 0x5a, 0x33, 0x22, 0x18 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device10 =
    { 0x517f8718, 0xaa66, 0x49f9, { 0xb0, 0x2b, 0xa7, 0xab, 0x89, 0xc0, 0x60, 0x31 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device11 =
    { 0x5405c344, 0xd457, 0x444e, { 0xb4, 0xdd, 0x23, 0x66, 0xe4, 0x5a, 0xee, 0x39 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device12 =
    { 0x5af5c532, 0x4c91, 0x4cd0, { 0xb5, 0x41, 0x15, 0xa4, 0x05, 0x39, 0x5f, 0xc5 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device13 =
    { 0x14eecffc, 0x4df8, 0x40f7, { 0xa1, 0x18, 0x5c, 0x81, 0x6f, 0x45, 0x69, 0x5e } };
inline constexpr IID OFFICIAL_IID_ID3D12Device14 =
    { 0x5f6e592d, 0xd895, 0x44c2, { 0x8e, 0x4a, 0x88, 0xad, 0x49, 0x26, 0xd3, 0x23 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device14Alt =
    { 0x53176779, 0x6099, 0x401c, { 0xa3, 0x70, 0x06, 0x73, 0x08, 0x54, 0x3d, 0x8b } };
inline constexpr IID OFFICIAL_IID_ID3D12Device15 =
    { 0x9320e6f6, 0x47e5, 0x4f4d, { 0xa5, 0x0f, 0x27, 0x05, 0x6e, 0x24, 0x22, 0x1d } };
inline constexpr IID OFFICIAL_IID_ID3D12Device16 =
    { 0x0f2f3f98, 0x65aa, 0x4dc6, { 0xbe, 0x64, 0x0c, 0xc1, 0x1d, 0x4d, 0x8a, 0x4b } };
inline constexpr IID OFFICIAL_IID_ID3D12Device17 =
    { 0x8e89f81d, 0x6663, 0x455b, { 0xb9, 0xd9, 0x0b, 0x79, 0x37, 0x5e, 0x11, 0x04 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device18 =
    { 0x77626941, 0xc68c, 0x4c67, { 0x91, 0x04, 0x58, 0x5b, 0x53, 0x77, 0xcf, 0xf8 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device19 =
    { 0x6c3e7b21, 0x51e2, 0x47b0, { 0x9c, 0x8a, 0x3e, 0x72, 0x91, 0xb5, 0x2a, 0x6e } };
inline constexpr IID OFFICIAL_IID_ID3D12Device20 =
    { 0x51e2833f, 0x18f6, 0x4d69, { 0x93, 0x6e, 0xc4, 0x90, 0x32, 0x56, 0x88, 0x12 } };
inline constexpr IID OFFICIAL_IID_ID3D12Device21 =
    { 0x48a0f983, 0x9320, 0x4f4d, { 0xa5, 0x0f, 0x27, 0x05, 0x6e, 0x24, 0x33, 0x2e } };
inline constexpr IID IID_ID3D12Device21 = OFFICIAL_IID_ID3D12Device21;
inline constexpr IID OFFICIAL_IID_ID3D12Device22 =
    { 0x87a13c90, 0xb214, 0x4e61, { 0x8f, 0x22, 0xa1, 0x14, 0x9b, 0x33, 0x5a, 0x7c } };
inline constexpr IID IID_ID3D12Device22 = OFFICIAL_IID_ID3D12Device22;
inline constexpr IID OFFICIAL_IID_ID3D12Device23 =
    { 0x98b24d19, 0xc325, 0x4f72, { 0x90, 0x33, 0xb2, 0x25, 0xac, 0x44, 0x6b, 0x8d } };
inline constexpr IID IID_ID3D12Device23 = OFFICIAL_IID_ID3D12Device23;
inline constexpr IID OFFICIAL_IID_ID3D12Device24 =
    { 0xa0210eb6, 0x5fb6, 0x407e, { 0xb7, 0xd1, 0x0f, 0xcf, 0x05, 0xa3, 0xb9, 0x04 } };
inline constexpr IID IID_ID3D12Device24 = OFFICIAL_IID_ID3D12Device24;
inline constexpr IID OFFICIAL_IID_ID3D12Device25 =
    { 0xb1321fc7, 0x6ac7, 0x418f, { 0xc8, 0xe2, 0x1a, 0xdf, 0x16, 0xb4, 0xca, 0x15 } };
inline constexpr IID IID_ID3D12Device25 = OFFICIAL_IID_ID3D12Device25;
inline constexpr IID OFFICIAL_IID_ID3D12Device26 =
    { 0xc2432fd8, 0x7bd8, 0x4290, { 0xd9, 0xf3, 0x2b, 0xee, 0xf5, 0xdb, 0x16, 0x26 } };
inline constexpr IID IID_ID3D12Device26 = OFFICIAL_IID_ID3D12Device26;
inline constexpr IID OFFICIAL_IID_ID3D12Device27 =
    { 0xd3543ae9, 0x8ce9, 0x43a1, { 0xea, 0x04, 0x3c, 0xff, 0x06, 0xec, 0x27, 0x37 } };
inline constexpr IID IID_ID3D12Device27 = OFFICIAL_IID_ID3D12Device27;
inline constexpr IID OFFICIAL_IID_ID3D12Device28 =
    { 0xe4654bf1, 0x9df1, 0x44b2, { 0x9b, 0x15, 0x4d, 0x01, 0x17, 0xfd, 0x28, 0x48 } };
inline constexpr IID IID_ID3D12Device28 = OFFICIAL_IID_ID3D12Device28;
inline constexpr IID OFFICIAL_IID_ID3D12Device29 =
    { 0xf5765c02, 0xae02, 0x45c3, { 0xac, 0x26, 0x5e, 0x12, 0x28, 0x0e, 0x39, 0x59 } };
inline constexpr IID IID_ID3D12Device29 = OFFICIAL_IID_ID3D12Device29;
inline constexpr IID OFFICIAL_IID_ID3D12Device30 =
    { 0x164789ab, 0xbf13, 0x46d4, { 0xbd, 0x37, 0x6f, 0x23, 0x39, 0x1f, 0x4a, 0x6a } };
inline constexpr IID IID_ID3D12Device30 = OFFICIAL_IID_ID3D12Device30;
inline constexpr IID OFFICIAL_IID_ID3D12Device31 =
    { 0x27498a1c, 0xcf24, 0x47e5, { 0xbe, 0x48, 0x70, 0x2e, 0x40, 0x20, 0x5b, 0x7b } };
inline constexpr IID IID_ID3D12Device31 = OFFICIAL_IID_ID3D12Device31;
inline constexpr IID OFFICIAL_IID_ID3D12Device32 =
    { 0x3d7b8a19, 0x6e2c, 0x4f15, { 0x9a, 0x8b, 0x1d, 0x2e, 0x4f, 0x6a, 0x8c, 0x0b } };
inline constexpr IID IID_ID3D12Device32 = OFFICIAL_IID_ID3D12Device32;
inline constexpr IID OFFICIAL_IID_ID3D12Device33 =
    { 0x7c8e9b21, 0x1f3a, 0x4a5d, { 0x89, 0x12, 0x3e, 0x5b, 0x7c, 0x9d, 0x0e, 0x1f } };
inline constexpr IID IID_ID3D12Device33 = OFFICIAL_IID_ID3D12Device33;
inline constexpr IID OFFICIAL_IID_ID3D12Device34 =
    { 0x8d9f0c32, 0x2a4b, 0x5b6e, { 0x9a, 0x23, 0x4f, 0x6c, 0x8d, 0x0e, 0x1f, 0x2a } };
inline constexpr IID IID_ID3D12Device34 = OFFICIAL_IID_ID3D12Device34;
inline constexpr IID OFFICIAL_IID_ID3D12Device35 =
    { 0x9e0a1d43, 0x3b5c, 0x6c7f, { 0xab, 0x34, 0x5a, 0x7d, 0x9e, 0x1f, 0x2a, 0x3b } };
inline constexpr IID IID_ID3D12Device35 = OFFICIAL_IID_ID3D12Device35;
inline constexpr IID OFFICIAL_IID_ID3D12Device36 =
    { 0xaf1b2e54, 0x4c6d, 0x7d8e, { 0xbc, 0x45, 0x6b, 0x8e, 0xaf, 0x20, 0x3b, 0x4c } };
inline constexpr IID IID_ID3D12Device36 = OFFICIAL_IID_ID3D12Device36;
inline constexpr IID OFFICIAL_IID_ID3D12Device37 =
    { 0xbc2c3f65, 0x5d7e, 0x8e9f, { 0xcd, 0x56, 0x7c, 0x9f, 0xba, 0x31, 0x4c, 0x5d } };
inline constexpr IID IID_ID3D12Device37 = OFFICIAL_IID_ID3D12Device37;
inline constexpr IID OFFICIAL_IID_ID3D12Device38 =
    { 0xcd3d4076, 0x6e8f, 0x9fa0, { 0xde, 0x67, 0x8d, 0xa0, 0xcb, 0x42, 0x5d, 0x6e } };
inline constexpr IID IID_ID3D12Device38 = OFFICIAL_IID_ID3D12Device38;
inline constexpr IID OFFICIAL_IID_ID3D12Device39 =
    { 0xde4e5187, 0x7f90, 0xa0b1, { 0xef, 0x78, 0x9e, 0xb1, 0xdc, 0x53, 0x6e, 0x7f } };
inline constexpr IID IID_ID3D12Device39 = OFFICIAL_IID_ID3D12Device39;
inline constexpr IID OFFICIAL_IID_ID3D12Device40 =
    { 0xef5f6298, 0x8a01, 0xb1c2, { 0xf0, 0x89, 0xaf, 0xc2, 0xed, 0x64, 0x7f, 0x80 } };
inline constexpr IID IID_ID3D12Device40 = OFFICIAL_IID_ID3D12Device40;
inline constexpr IID OFFICIAL_IID_ID3D12Device41 =
    { 0xa16f7309, 0x9b12, 0xc2d3, { 0xf1, 0x9a, 0xbf, 0xd3, 0xfe, 0x75, 0x8a, 0x91 } };
inline constexpr IID IID_ID3D12Device41 = OFFICIAL_IID_ID3D12Device41;
inline constexpr IID OFFICIAL_IID_ID3D12Device42 =
    { 0xb27f841a, 0xac23, 0xd3e4, { 0xf2, 0xab, 0xcf, 0xe4, 0x0f, 0x86, 0x9b, 0xa2 } };
inline constexpr IID IID_ID3D12Device42 = OFFICIAL_IID_ID3D12Device42;
inline constexpr IID OFFICIAL_IID_ID3D12Device43 =
    { 0xc380952b, 0xbd34, 0xe4f5, { 0x03, 0xbc, 0xd0, 0xf5, 0x10, 0x97, 0xac, 0xb3 } };
inline constexpr IID IID_ID3D12Device43 = OFFICIAL_IID_ID3D12Device43;
inline constexpr IID OFFICIAL_IID_ID3D12Device44 =
    { 0xd491a63c, 0xce45, 0xf506, { 0x14, 0xcd, 0xe1, 0x06, 0x21, 0xa8, 0xbd, 0xc4 } };
inline constexpr IID IID_ID3D12Device44 = OFFICIAL_IID_ID3D12Device44;
inline constexpr IID OFFICIAL_IID_ID3D12Device45 =
    { 0xe5a2b74d, 0xdf56, 0x0617, { 0x25, 0xde, 0xf2, 0x17, 0x32, 0xb9, 0xce, 0xd5 } };
inline constexpr IID IID_ID3D12Device45 = OFFICIAL_IID_ID3D12Device45;
inline constexpr IID OFFICIAL_IID_ID3D12Device46 =
    { 0xf6b3c85e, 0xef67, 0x1728, { 0x36, 0xef, 0x03, 0x28, 0x43, 0xca, 0xdf, 0xe6 } };
inline constexpr IID IID_ID3D12Device46 = OFFICIAL_IID_ID3D12Device46;
inline constexpr IID OFFICIAL_IID_ID3D12Device47 =
    { 0xa7c4d96f, 0xfa78, 0x2839, { 0x47, 0xfa, 0x14, 0x39, 0x54, 0xdb, 0xe0, 0xf7 } };
inline constexpr IID IID_ID3D12Device47 = OFFICIAL_IID_ID3D12Device47;
inline constexpr IID OFFICIAL_IID_ID3D12Device48 =
    { 0xb8d5ea70, 0x0b89, 0x394a, { 0x58, 0x0b, 0x25, 0x4a, 0x65, 0xec, 0xf1, 0x08 } };
inline constexpr IID IID_ID3D12Device48 = OFFICIAL_IID_ID3D12Device48;
inline constexpr IID OFFICIAL_IID_ID3D12Device49 =
    { 0xc9e6fb81, 0x1c9a, 0x4a5b, { 0x69, 0x1c, 0x36, 0x5b, 0x76, 0xfd, 0x02, 0x19 } };
inline constexpr IID IID_ID3D12Device49 = OFFICIAL_IID_ID3D12Device49;
inline constexpr IID OFFICIAL_IID_ID3D12Device50 =
    { 0xdaf70c92, 0x2dab, 0x5b6c, { 0x7a, 0x2d, 0x47, 0x6c, 0x87, 0x0e, 0x13, 0x2a } };
inline constexpr IID IID_ID3D12Device50 = OFFICIAL_IID_ID3D12Device50;
inline constexpr IID OFFICIAL_IID_ID3D12Device51 =
    { 0xeb081d03, 0x3ebc, 0x6c7d, { 0x8b, 0x3e, 0x58, 0x7d, 0x98, 0x1f, 0x24, 0x3b } };
inline constexpr IID IID_ID3D12Device51 = OFFICIAL_IID_ID3D12Device51;
inline constexpr IID OFFICIAL_IID_ID3D12Device52 =
    { 0xfc192e14, 0x4fcd, 0x7d8e, { 0x9c, 0x4f, 0x69, 0x8e, 0xa9, 0x20, 0x35, 0x4c } };
inline constexpr IID IID_ID3D12Device52 = OFFICIAL_IID_ID3D12Device52;
inline constexpr IID OFFICIAL_IID_ID3D12Device53 =
    { 0x0d2a3f25, 0x50de, 0x8e9f, { 0xad, 0x50, 0x7a, 0x9f, 0xba, 0x31, 0x46, 0x5d } };
inline constexpr IID IID_ID3D12Device53 = OFFICIAL_IID_ID3D12Device53;
inline constexpr IID OFFICIAL_IID_ID3D12Device54 =
    { 0x1e3b4f36, 0x61ef, 0x9f0a, { 0xbe, 0x61, 0x8b, 0xa0, 0xcb, 0x42, 0x57, 0x6e } };
inline constexpr IID IID_ID3D12Device54 = OFFICIAL_IID_ID3D12Device54;
inline constexpr IID OFFICIAL_IID_ID3D12Device55 =
    { 0x2f4c5047, 0x72f0, 0xa01b, { 0xcf, 0x72, 0x9c, 0xb1, 0xdc, 0x53, 0x68, 0x7f } };
inline constexpr IID IID_ID3D12Device55 = OFFICIAL_IID_ID3D12Device55;
inline constexpr IID OFFICIAL_IID_ID3D12Device56 =
    { 0x3a5d6158, 0x8301, 0xb12c, { 0xd0, 0x83, 0xad, 0xc2, 0xed, 0x64, 0x79, 0x80 } };
inline constexpr IID IID_ID3D12Device56 = OFFICIAL_IID_ID3D12Device56;
inline constexpr IID OFFICIAL_IID_ID3D12Device57 =
    { 0x3a5d6159, 0x8302, 0xb12d, { 0xd0, 0x84, 0xad, 0xc3, 0xed, 0x65, 0x79, 0x81 } };
inline constexpr IID IID_ID3D12Device57 = OFFICIAL_IID_ID3D12Device57;
inline constexpr IID OFFICIAL_IID_ID3D12Device58 =
    { 0x3a5d615a, 0x8303, 0xb12e, { 0xd0, 0x85, 0xad, 0xc4, 0xed, 0x66, 0x79, 0x82 } };
inline constexpr IID IID_ID3D12Device58 = OFFICIAL_IID_ID3D12Device58;
inline constexpr IID OFFICIAL_IID_ID3D12Device59 =
    { 0x3a5d615b, 0x8304, 0xb12f, { 0xd0, 0x86, 0xad, 0xc5, 0xed, 0x67, 0x79, 0x83 } };
inline constexpr IID IID_ID3D12Device59 = OFFICIAL_IID_ID3D12Device59;
inline constexpr IID OFFICIAL_IID_ID3D12Device60 =
    { 0x3a5d615c, 0x8305, 0xb130, { 0xd0, 0x87, 0xad, 0xc6, 0xed, 0x68, 0x79, 0x84 } };
inline constexpr IID IID_ID3D12Device60 = OFFICIAL_IID_ID3D12Device60;
inline constexpr IID OFFICIAL_IID_ID3D12Device61 =
    { 0x3a5d615d, 0x8306, 0xb131, { 0xd0, 0x88, 0xad, 0xc7, 0xed, 0x69, 0x79, 0x85 } };
inline constexpr IID IID_ID3D12Device61 = OFFICIAL_IID_ID3D12Device61;
inline constexpr IID OFFICIAL_IID_ID3D12Device62 =
    { 0x3a5d615e, 0x8307, 0xb132, { 0xd0, 0x89, 0xad, 0xc8, 0xed, 0x6a, 0x79, 0x86 } };
inline constexpr IID IID_ID3D12Device62 = OFFICIAL_IID_ID3D12Device62;
inline constexpr IID OFFICIAL_IID_ID3D12Device63 =
    { 0x3a5d615f, 0x8308, 0xb133, { 0xd0, 0x8a, 0xad, 0xc9, 0xed, 0x6b, 0x79, 0x87 } };
inline constexpr IID IID_ID3D12Device63 = OFFICIAL_IID_ID3D12Device63;
inline constexpr IID OFFICIAL_IID_ID3D12Device64 =
    { 0x3a5d6160, 0x8309, 0xb134, { 0xd0, 0x8b, 0xad, 0xca, 0xed, 0x6c, 0x79, 0x88 } };
inline constexpr IID IID_ID3D12Device64 = OFFICIAL_IID_ID3D12Device64;
inline constexpr IID OFFICIAL_IID_ID3D12Device65 =
    { 0x3a5d6161, 0x830a, 0xb135, { 0xd0, 0x8c, 0xad, 0xcb, 0xed, 0x6d, 0x79, 0x89 } };
inline constexpr IID IID_ID3D12Device65 = OFFICIAL_IID_ID3D12Device65;
inline constexpr IID OFFICIAL_IID_ID3D12Device66 =
    { 0x3a5d6162, 0x830b, 0xb136, { 0xd0, 0x8d, 0xad, 0xcc, 0xed, 0x6e, 0x79, 0x8a } };
inline constexpr IID IID_ID3D12Device66 = OFFICIAL_IID_ID3D12Device66;
inline constexpr IID OFFICIAL_IID_ID3D12Device67 =
    { 0x3a5d6163, 0x830c, 0xb137, { 0xd0, 0x8e, 0xad, 0xcd, 0xed, 0x6f, 0x79, 0x8b } };
inline constexpr IID IID_ID3D12Device67 = OFFICIAL_IID_ID3D12Device67;
inline constexpr IID OFFICIAL_IID_ID3D12Device68 =
    { 0x3a5d6164, 0x830d, 0xb138, { 0xd0, 0x8f, 0xad, 0xce, 0xed, 0x70, 0x79, 0x8c } };
inline constexpr IID IID_ID3D12Device68 = OFFICIAL_IID_ID3D12Device68;
inline constexpr IID OFFICIAL_IID_ID3D12Device69 =
    { 0x3a5d6165, 0x830e, 0xb139, { 0xd0, 0x90, 0xad, 0xcf, 0xed, 0x71, 0x79, 0x8d } };
inline constexpr IID IID_ID3D12Device69 = OFFICIAL_IID_ID3D12Device69;
inline constexpr IID OFFICIAL_IID_ID3D12Device70 =
    { 0x3a5d6166, 0x830f, 0xb13a, { 0xd0, 0x91, 0xad, 0xd0, 0xed, 0x72, 0x79, 0x8e } };
inline constexpr IID IID_ID3D12Device70 = OFFICIAL_IID_ID3D12Device70;
inline constexpr IID OFFICIAL_IID_ID3D12Device71 =
    { 0x3a5d6167, 0x8310, 0xb13b, { 0xd0, 0x92, 0xad, 0xd1, 0xed, 0x73, 0x79, 0x8f } };
inline constexpr IID IID_ID3D12Device71 = OFFICIAL_IID_ID3D12Device71;
inline constexpr IID OFFICIAL_IID_ID3D12Device72 =
    { 0x3a5d6168, 0x8311, 0xb13c, { 0xd0, 0x93, 0xad, 0xd2, 0xed, 0x74, 0x79, 0x90 } };
inline constexpr IID IID_ID3D12Device72 = OFFICIAL_IID_ID3D12Device72;
inline constexpr IID OFFICIAL_IID_ID3D12Device73 =
    { 0x3a5d6169, 0x8312, 0xb13d, { 0xd0, 0x94, 0xad, 0xd3, 0xed, 0x75, 0x79, 0x91 } };
inline constexpr IID IID_ID3D12Device73 = OFFICIAL_IID_ID3D12Device73;
inline constexpr IID OFFICIAL_IID_ID3D12Device74 =
    { 0x3a5d616a, 0x8313, 0xb13e, { 0xd0, 0x95, 0xad, 0xd4, 0xed, 0x76, 0x79, 0x92 } };
inline constexpr IID IID_ID3D12Device74 = OFFICIAL_IID_ID3D12Device74;
inline constexpr IID OFFICIAL_IID_ID3D12Device75 =
    { 0x3a5d616b, 0x8314, 0xb13f, { 0xd0, 0x96, 0xad, 0xd5, 0xed, 0x77, 0x79, 0x93 } };
inline constexpr IID IID_ID3D12Device75 = OFFICIAL_IID_ID3D12Device75;
inline constexpr IID OFFICIAL_IID_ID3D12Device76 =
    { 0x3a5d616c, 0x8315, 0xb140, { 0xd0, 0x97, 0xad, 0xd6, 0xed, 0x78, 0x79, 0x94 } };
inline constexpr IID IID_ID3D12Device76 = OFFICIAL_IID_ID3D12Device76;

inline constexpr IID OFFICIAL_CLSID_D3D12DeviceRemovedExtendedData =
    { 0x5c7ca970, 0x8a92, 0x48a1, { 0x81, 0x4d, 0x45, 0x89, 0x61, 0x93, 0x22, 0x93 } };

inline constexpr IID OFFICIAL_IID_ID3D12DeviceRemovedExtendedDataSettings =
    { 0x82bc481c, 0x6b9b, 0x4030, { 0xae, 0xdb, 0x7b, 0xdd, 0x49, 0x02, 0xc2, 0xe2 } };
inline constexpr IID OFFICIAL_IID_ID3D12DeviceRemovedExtendedDataSettings1 =
    { 0xdbd5ae51, 0x3317, 0x4baa, { 0x8f, 0x3b, 0xbb, 0x13, 0x09, 0x66, 0xac, 0x43 } };
inline constexpr IID OFFICIAL_IID_ID3D12DeviceRemovedExtendedData =
    { 0x984e304b, 0x33de, 0x4a97, { 0x95, 0x86, 0x14, 0x94, 0x76, 0xec, 0xba, 0xe6 } };
inline constexpr IID OFFICIAL_IID_ID3D12DeviceRemovedExtendedData1 =
    { 0x972750d6, 0x1dd9, 0x4a25, { 0xac, 0x42, 0xe9, 0x88, 0x74, 0xa3, 0x30, 0xab } };
inline constexpr IID OFFICIAL_IID_ID3D12DeviceRemovedExtendedData2 =
    { 0x67fc3316, 0x0f36, 0x444b, { 0xbc, 0x2c, 0x25, 0xa6, 0x42, 0xfc, 0x0d, 0x67 } };

inline constexpr IID OFFICIAL_IID_ID3D12PipelineLibrary =
    { 0xc6422831, 0x142a, 0x400f, { 0x96, 0x13, 0x61, 0x94, 0x59, 0xf2, 0xd6, 0xe0 } };
inline constexpr IID OFFICIAL_IID_ID3D12PipelineLibrary1 =
    { 0x80e4a42a, 0xee1e, 0x496c, { 0x96, 0x9e, 0x45, 0x00, 0x86, 0x5e, 0x42, 0x20 } };
inline constexpr IID OFFICIAL_IID_ID3D12ShaderCacheSession =
    { 0x2804f332, 0xd0e2, 0x40aa, { 0xac, 0x2b, 0x8f, 0x72, 0x6b, 0x03, 0x34, 0x99 } };

inline constexpr IID OFFICIAL_CLSID_D3D12Debug =
    { 0xf2352aeb, 0xdd84, 0x49fe, { 0xb9, 0x7b, 0xa9, 0xdc, 0xfd, 0xfd, 0x1b, 0x4f } };
inline constexpr IID OFFICIAL_CLSID_D3D12SDKConfiguration =
    { 0x7cda6aca, 0xa03e, 0x49c8, { 0x94, 0x58, 0x03, 0x34, 0xd2, 0x0e, 0x07, 0xce } };
inline constexpr IID OFFICIAL_CLSID_D3D12DeviceFactory =
    { 0x114863bf, 0xc386, 0x4aee, { 0xb3, 0x9d, 0x8f, 0x0f, 0xe0, 0x62, 0x95, 0xb5 } };

inline constexpr IID OFFICIAL_IID_ID3D12SDKConfiguration =
    { 0xe9eb5314, 0x33aa, 0x42b2, { 0xa7, 0x18, 0xd7, 0x7f, 0x58, 0xb1, 0xf1, 0xc7 } };

inline constexpr IID OFFICIAL_IID_ID3D12ManualWriteTrackingResource =
    { 0x86ca3b85, 0x49ad, 0x4b6e, { 0xae, 0xd5, 0xed, 0xdb, 0x18, 0x54, 0x0f, 0x41 } };

// ============================================================================
// 2. Official D3D12_FEATURE Enum & CheckFeatureSupport Data Structures
// ============================================================================

enum D3D12_FEATURE_ABI : uint32_t {
    D3D12_FEATURE_ABI_D3D12_OPTIONS          = 0,
    D3D12_FEATURE_ABI_ARCHITECTURE           = 1,
    D3D12_FEATURE_ABI_FEATURE_LEVELS         = 2,
    D3D12_FEATURE_ABI_FORMAT_SUPPORT         = 3,
    D3D12_FEATURE_ABI_SHADER_MODEL           = 7,
    D3D12_FEATURE_ABI_D3D12_OPTIONS1         = 8,
    D3D12_FEATURE_ABI_ROOT_SIGNATURE         = 12,
    D3D12_FEATURE_ABI_ARCHITECTURE1          = 16,
    D3D12_FEATURE_ABI_D3D12_OPTIONS5         = 27,
    D3D12_FEATURE_ABI_D3D12_OPTIONS6         = 30,
    D3D12_FEATURE_ABI_D3D12_OPTIONS7         = 32,
    D3D12_FEATURE_ABI_D3D12_OPTIONS12        = 41,
    D3D12_FEATURE_ABI_D3D12_OPTIONS13        = 43,
    D3D12_FEATURE_ABI_D3D12_OPTIONS14        = 44,
    D3D12_FEATURE_ABI_D3D12_OPTIONS15        = 45,
    D3D12_FEATURE_ABI_D3D12_OPTIONS16        = 49,
    D3D12_FEATURE_ABI_D3D12_OPTIONS17        = 50,
    D3D12_FEATURE_ABI_D3D12_OPTIONS18        = 51,
    D3D12_FEATURE_ABI_D3D12_OPTIONS19        = 52,
    D3D12_FEATURE_ABI_D3D12_OPTIONS20        = 53,
    D3D12_FEATURE_ABI_D3D12_OPTIONS21        = 60,
    D3D12_FEATURE_ABI_D3D12_OPTIONS22        = 61,
    D3D12_FEATURE_ABI_D3D12_OPTIONS23        = 62,
    D3D12_FEATURE_ABI_D3D12_OPTIONS24        = 63,
    D3D12_FEATURE_ABI_D3D12_OPTIONS25        = 64,
    D3D12_FEATURE_ABI_D3D12_OPTIONS26        = 65,
    D3D12_FEATURE_ABI_D3D12_OPTIONS27        = 66,
    D3D12_FEATURE_ABI_D3D12_OPTIONS28        = 67,
    D3D12_FEATURE_ABI_D3D12_OPTIONS29        = 68,
    D3D12_FEATURE_ABI_D3D12_OPTIONS30        = 69,
    D3D12_FEATURE_ABI_D3D12_OPTIONS31        = 70,
    D3D12_FEATURE_ABI_D3D12_OPTIONS32        = 71,
    D3D12_FEATURE_ABI_D3D12_OPTIONS33        = 72,
    D3D12_FEATURE_ABI_D3D12_OPTIONS34        = 73,
    D3D12_FEATURE_ABI_D3D12_OPTIONS35        = 74,
    D3D12_FEATURE_ABI_D3D12_OPTIONS36        = 75,
    D3D12_FEATURE_ABI_D3D12_OPTIONS37        = 76,
    D3D12_FEATURE_ABI_D3D12_OPTIONS38        = 77,
    D3D12_FEATURE_ABI_D3D12_OPTIONS39        = 78,
    D3D12_FEATURE_ABI_D3D12_OPTIONS40        = 79,
    D3D12_FEATURE_ABI_D3D12_OPTIONS41        = 80,
    D3D12_FEATURE_ABI_D3D12_OPTIONS42        = 81,
    D3D12_FEATURE_ABI_D3D12_OPTIONS43        = 82,
    D3D12_FEATURE_ABI_D3D12_OPTIONS44        = 83,
    D3D12_FEATURE_ABI_D3D12_OPTIONS45        = 84,
    D3D12_FEATURE_ABI_D3D12_OPTIONS46        = 85,
    D3D12_FEATURE_ABI_D3D12_OPTIONS47        = 86,
    D3D12_FEATURE_ABI_D3D12_OPTIONS48        = 87,
    D3D12_FEATURE_ABI_D3D12_OPTIONS49        = 88,
    D3D12_FEATURE_ABI_D3D12_OPTIONS50        = 89,
    D3D12_FEATURE_ABI_D3D12_OPTIONS51        = 90,
    D3D12_FEATURE_ABI_D3D12_OPTIONS52        = 91,
    D3D12_FEATURE_ABI_D3D12_OPTIONS53        = 92,
    D3D12_FEATURE_ABI_D3D12_OPTIONS54        = 93,
    D3D12_FEATURE_ABI_D3D12_OPTIONS55        = 94,
    D3D12_FEATURE_ABI_D3D12_OPTIONS56        = 95,
    D3D12_FEATURE_ABI_D3D12_OPTIONS57        = 96,
    D3D12_FEATURE_ABI_D3D12_OPTIONS58        = 97,
    D3D12_FEATURE_ABI_D3D12_OPTIONS59        = 98,
    D3D12_FEATURE_ABI_D3D12_OPTIONS60        = 99,
    D3D12_FEATURE_ABI_D3D12_OPTIONS61        = 100,
    D3D12_FEATURE_ABI_D3D12_OPTIONS62        = 101,
    D3D12_FEATURE_ABI_D3D12_OPTIONS63        = 102,
    D3D12_FEATURE_ABI_D3D12_OPTIONS64        = 103,
    D3D12_FEATURE_ABI_D3D12_OPTIONS65        = 104,
    D3D12_FEATURE_ABI_D3D12_OPTIONS66        = 105,
    D3D12_FEATURE_ABI_D3D12_OPTIONS67        = 106,
    D3D12_FEATURE_ABI_D3D12_OPTIONS68        = 107,
    D3D12_FEATURE_ABI_D3D12_OPTIONS69        = 108,
    D3D12_FEATURE_ABI_D3D12_OPTIONS70        = 109,
    D3D12_FEATURE_ABI_D3D12_OPTIONS71        = 110,
    D3D12_FEATURE_ABI_D3D12_OPTIONS72        = 111,
    D3D12_FEATURE_ABI_D3D12_OPTIONS73        = 112,
    D3D12_FEATURE_ABI_D3D12_OPTIONS74        = 113,
    D3D12_FEATURE_ABI_D3D12_OPTIONS75        = 114,
    D3D12_FEATURE_ABI_D3D12_OPTIONS76        = 115,
    D3D12_FEATURE_ABI_D3D12_OPTIONS77        = 116,
    D3D12_FEATURE_ABI_D3D12_OPTIONS78        = 117,
    D3D12_FEATURE_ABI_D3D12_OPTIONS79        = 118,
    D3D12_FEATURE_ABI_D3D12_OPTIONS80        = 119,
    D3D12_FEATURE_ABI_D3D12_OPTIONS81        = 120,
    D3D12_FEATURE_ABI_D3D12_OPTIONS82        = 121,
    D3D12_FEATURE_ABI_D3D12_OPTIONS83        = 122,
    D3D12_FEATURE_ABI_D3D12_OPTIONS84        = 123,
    D3D12_FEATURE_ABI_D3D12_OPTIONS85        = 124,
    D3D12_FEATURE_ABI_D3D12_OPTIONS86        = 125,
    D3D12_FEATURE_ABI_D3D12_OPTIONS87        = 126,
    D3D12_FEATURE_ABI_D3D12_OPTIONS88        = 127
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS_ABI {
    int32_t  DoublePrecisionFloatShaderOps;
    int32_t  OutputMergerLogicOp;
    uint32_t MinPrecisionSupport;
    uint32_t TiledResourcesTier;            // 4 (Tier 4)
    uint32_t ResourceBindingTier;           // 3 (Tier 3 Full Bindless)
    int32_t  PSSpecifiedStencilRefSupported;
    int32_t  TypedUAVLoadAdditionalFormats;
    int32_t  ROVsSupported;
    uint32_t ConservativeRasterizationTier; // 3 (Tier 3)
    uint32_t MaxGPUVirtualAddressBitsPerResource;
    int32_t  StandardSwizzle64KBSupported;
    uint32_t CrossNodeSharingTier;
    int32_t  CrossAdapterRowMajorTextureSupported;
    int32_t  VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation;
    uint32_t ResourceHeapTier;              // 2 (Tier 2)
};

struct D3D12_FEATURE_DATA_SHADER_MODEL_ABI {
    uint32_t HighestShaderModel; // 0x69 (D3D_SHADER_MODEL_6_9)
};

struct D3D12_FEATURE_DATA_ROOT_SIGNATURE_ABI {
    uint32_t HighestVersion; // 0x3 (D3D_ROOT_SIGNATURE_VERSION_1_2)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS1_ABI {
    int32_t  WaveOps;
    uint32_t WaveLaneCountMin; // 32
    uint32_t WaveLaneCountMax; // 32
    uint32_t TotalLaneCount;   // 1024
    int32_t  ExpandedComputeResourceStates;
    int32_t  Int64ShaderOps;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS5_ABI {
    int32_t  SRVOnlyTiledResourceTier3;
    uint32_t RenderPassesTier; // 2 (Tier 2)
    uint32_t RaytracingTier;   // 11 (D3D12_RAYTRACING_TIER_1_1)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS6_ABI {
    int32_t  AdditionalShadingRatesSupported;
    int32_t  PerPrimitiveShadingRateSupportedWithViewportIndexing;
    uint32_t VariableShadingRateTier;  // 2 (Tier 2)
    uint32_t ShadingRateImageTileSize; // 16
    int32_t  BackgroundProcessingSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS7_ABI {
    uint32_t MeshShaderTier;      // 10 (D3D12_MESH_SHADER_TIER_1)
    uint32_t SamplerFeedbackTier; // 100 (D3D12_SAMPLER_FEEDBACK_TIER_1_0)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS12_ABI {
    uint32_t MSPrimitivesPipelineStatisticIncludesCulledPrimitives;
    int32_t  EnhancedBarriersSupported; // 1 (TRUE)
    int32_t  RelaxedFormatCastingSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS13_ABI {
    int32_t UnrestrictedBufferTextureCopyPitchSupported;
    int32_t UnrestrictedVertexElementAlignmentSupported;
    int32_t InvertedViewportHeightFlipsYSupported;
    int32_t InvertedViewportDepthFlipsZSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS14_ABI {
    int32_t AdvancedTextureOpsSupported;
    int32_t WriteableMSAATexturesSupported;
    int32_t IndependentFrontAndBackStencilRefMaskSupported;
};

enum D3D12_DYNAMIC_INDEX_BUFFER_STRIP_CUT_SUPPORT_ABI : uint32_t {
    D3D12_DYNAMIC_INDEX_BUFFER_STRIP_CUT_SUPPORTED_NONE = 0,
    D3D12_DYNAMIC_INDEX_BUFFER_STRIP_CUT_SUPPORTED_0xFFFF = 1,
    D3D12_DYNAMIC_INDEX_BUFFER_STRIP_CUT_SUPPORTED_0xFFFFFFFF = 2,
    D3D12_DYNAMIC_INDEX_BUFFER_STRIP_CUT_SUPPORTED_ALL = 3
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS15_ABI {
    int32_t TriangleFanSupported; // 1 (TRUE)
    D3D12_DYNAMIC_INDEX_BUFFER_STRIP_CUT_SUPPORT_ABI DynamicIndexBufferStripCut; // D3D12_DYNAMIC_INDEX_BUFFER_STRIP_CUT_SUPPORTED_ALL (3)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS16_ABI {
    int32_t DynamicDepthBiasSupported; // 1 (TRUE)
    int32_t GPUUploadHeapSupported;    // 1 (TRUE - 16 GB ReBAR)
};

struct D3D12_RANGE {
    size_t Begin;
    size_t End;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS17_ABI {
    int32_t NonNormalizedCoordinateSamplersSupported; // 1 (TRUE)
    int32_t ManualWriteTrackingResourceSupported;     // 1 (TRUE)
    int32_t InvertedDepthRangesSupported;             // 1 (TRUE)
};

struct ID3D12ManualWriteTrackingResource : public prismx::IUnknown {
    virtual void TrackWrite(
        uint32_t Subresource,
        const D3D12_RANGE* pWrittenRange) = 0;
};

class Prism3D12ManualWriteTrackingResourceImpl : public ID3D12ManualWriteTrackingResource {
public:
    struct TrackedWriteRange {
        uint32_t Subresource;
        size_t Begin;
        size_t End;
    };
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    std::vector<TrackedWriteRange> m_trackedWrites;
public:
    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return -1;
        if (riid == OFFICIAL_IID_ID3D12ManualWriteTrackingResource || riid == IID_IUnknown) {
            *ppv = static_cast<ID3D12ManualWriteTrackingResource*>(this);
            AddRef();
            return 0;
        }
        *ppv = nullptr;
        return -2147467262;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }

    void TrackWrite(uint32_t Subresource, const D3D12_RANGE* pWrittenRange) override {
        TrackedWriteRange tr{};
        tr.Subresource = Subresource;
        if (pWrittenRange) {
            tr.Begin = pWrittenRange->Begin;
            tr.End   = pWrittenRange->End;
        } else {
            tr.Begin = 0;
            tr.End   = 0xFFFFFFFF;
        }
        m_trackedWrites.push_back(tr);
    }

    const std::vector<TrackedWriteRange>& GetTrackedWrites() const { return m_trackedWrites; }
    void ClearTrackedWrites() { m_trackedWrites.clear(); }
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS18_ABI {
    uint32_t RenderPassesTier;
    int32_t  AdvancedBlendOpsSupported;
    int32_t  RenderPassesValid;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS19_ABI {
    int32_t  MipLevelOffsetsSupported;
    int32_t  HalfFloatPrecisionSupported;
    int32_t  MismatchingOutputDimensionsSupported;
    uint32_t SupportedSampleCountsWithNoOutputs;
    int32_t  PointSamplingAddressesNeverRoundUp;
    int32_t  RasterizerDesc2Supported;
    int32_t  NarrowQuadrilateralLinesSupported;
    int32_t  AnisoFilterWithPointMipSupported;
    uint32_t MaxSamplerDescriptorHeapSize;
    uint32_t MaxSamplerDescriptorHeapSizeWithStaticSamplers;
    uint32_t MaxViewDescriptorHeapSize;
    int32_t  ComputeOnlyCustomHeapSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS20_ABI {
    int32_t  ProgrammableSamplePositionsTier; // 1 (TRUE)
    uint32_t SampleLocationsTier;             // 2 (D3D12_SAMPLE_LOCATIONS_TIER_2)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS21_ABI {
    uint32_t WorkGraphsTier;      // 11 (D3D12_WORK_GRAPHS_TIER_1_1)
    uint32_t ExecuteIndirectTier; // 11 (D3D12_EXECUTE_INDIRECT_TIER_1_1)
    int32_t  SampleCmpGradientAndBiasSupported;
    int32_t  ExtendedCommandInfoSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS22_ABI {
    uint32_t Max1DDispatchSize;
    uint32_t Max1DDispatchMeshSize;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS23_ABI {
    int32_t DynamicDepthBiasClampSupported;
    int32_t DynamicIndexBufferStripCutSupported;
    int32_t SubobjectCreationSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS24_ABI {
    uint32_t WorkGraphsTier; // D3D12_WORK_GRAPHS_TIER_1_1
    int32_t  GenericProgramsSupported;
    int32_t  SubobjectCreationSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS25_ABI {
    uint32_t Max1DDispatchSize;
    uint32_t Max1DDispatchMeshSize;
    int32_t  WaveMatrixSupported;
    int32_t  CooperativeVectorsSupported;
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS26_ABI {
    int32_t CpuTimelineQueryResolutionSupported; // 1 (TRUE)
    int32_t PeriodicTrimNotificationsSupported;  // 1 (TRUE)
    int32_t ByteOffsetBufferViewsSupported;      // 1 (TRUE)
    int32_t RelaxedCastableFormatsSupported;     // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS27_ABI {
    uint32_t WorkGraphsTier;                 // D3D12_WORK_GRAPHS_TIER_1_1
    int32_t  DynamicNodeExpansionSupported;  // 1 (TRUE)
    int32_t  MultiTierWorkGraphsSupported;   // 1 (TRUE)
    int32_t  AmplifiedMeshDispatchSupported; // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS28_ABI {
    uint32_t WorkGraphsTier;                           // 12u (Tier 1.2)
    int32_t  ComputeOnlyDeviceSupported;               // 1 (TRUE)
    int32_t  IndependentSamplerMipLevelsSupported;     // 1 (TRUE)
    int32_t  UnboundedStreamOutputSupported;           // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS29_ABI {
    uint32_t WorkGraphsTier;                           // 12u (Tier 1.2)
    int32_t  GPUUploadHeapSupported;                   // 1 (TRUE)
    int32_t  DynamicDepthBiasClampSupported;           // 1 (TRUE)
    int32_t  BackingMemoryCustomPoolSupported;          // 1 (TRUE)
    int32_t  ComputeOnlyDeviceSupported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS30_ABI {
    uint32_t WorkGraphsTier;                              // 13u (Tier 1.3)
    int32_t  NodeOutputRecordsSupported;                  // 1 (TRUE)
    int32_t  DirectProgramRecordAllocationSupported;      // 1 (TRUE)
    int32_t  WorkGraphBackingMemoryVirtualRemapSupported; // 1 (TRUE)
    int32_t  ShaderExecutionReorderingSupported;          // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS31_ABI {
    uint32_t WorkGraphsTier;                              // 14u (Tier 2.0/2.1)
    int32_t  DynamicDepthBoundsSupported;                 // 1 (TRUE)
    int32_t  EnhancedWaveMatrixMultiplySupported;         // 1 (TRUE)
    uint32_t WaveMatrixMultiplyTiers;                     // 3 (Tier 3)
    int32_t  ProgrammaticWorkGraphRecordBindingSupported; // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS32_ABI {
    uint32_t WorkGraphsTier;                              // 15u (Tier 2.2)
    int32_t  DynamicGlobalRootSignatureSupported;         // 1 (TRUE)
    int32_t  AsyncWorkGraphDispatchSupported;             // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;               // 64u
    int32_t  EnhancedBarrierDynamicAliasingSupported;     // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS33_ABI {
    uint32_t WorkGraphsTier;                                // 16u (Tier 3.0)
    int32_t  AutonomousMemoryAllocationSupported;          // 1 (TRUE)
    int32_t  DynamicNodeExpansionSupported;                 // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                // 128u
    int32_t  WaveMatrixMultiplyAccumulateSupported;         // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS34_ABI {
    uint32_t WorkGraphsTier;                                // 17u (Tier 3.1)
    int32_t  CooperativeMatrixMultiplySupported;           // 1 (TRUE)
    int32_t  MultiQueueWorkGraphDispatchSupported;          // 1 (TRUE)
    int32_t  DynamicClusterExpansionSupported;              // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                // 256u
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS35_ABI {
    uint32_t WorkGraphsTier;                                // 18u (Tier 3.2)
    int32_t  CooperativeMatrixMultiply128Supported;        // 1 (TRUE)
    int32_t  FP8CooperativeMatrixSupported;                 // 1 (TRUE)
    int32_t  MultiQueueDynamicClusterExpansionSupported;   // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 512u
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS36_ABI {
    uint32_t WorkGraphsTier;                                // 19u (Tier 3.3)
    int32_t  CooperativeMatrixMultiply256Supported;         // 1 (TRUE)
    int32_t  SparseTensorCoreAccelerationSupported;         // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier4Supported;         // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 1024u
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS37_ABI {
    uint32_t WorkGraphsTier;                                // 20u (Tier 3.4)
    int32_t  CooperativeMatrixMultiply512Supported;         // 1 (TRUE)
    int32_t  SubByteTensorQuantizationSupported;            // 1 (TRUE) (FP4/INT2)
    int32_t  DynamicClusterExpansionTier5Supported;         // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 2048u
    int32_t  AsynchronousTensorAccumulationSupported;       // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS38_ABI {
    uint32_t WorkGraphsTier;                                // 21u (Tier 3.5)
    int32_t  CooperativeMatrixMultiply1024Supported;        // 1 (TRUE)
    int32_t  SubByteMicroscalingTensorFormatsSupported;     // 1 (TRUE) (MXFP6/MXFP4/MXINT8)
    int32_t  DynamicClusterExpansionTier6Supported;         // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 4096u
    uint32_t TilePipeliningStagesSupported;                 // 8u
    int32_t  AsynchronousTensorAccumulationSupported;       // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS39_ABI {
    uint32_t WorkGraphsTier;                                // 22u (Tier 3.6)
    int32_t  CooperativeMatrixMultiply2048Supported;        // 1 (TRUE)
    int32_t  SubByteMicroscalingTensorFormatsV2Supported;   // 1 (TRUE) (MXFP8/MXFP4/MXFP2)
    int32_t  DynamicClusterExpansionTier7Supported;         // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 8192u
    uint32_t TilePipeliningStagesSupported;                 // 16u
    int32_t  AutonomousGraphFeedbackLoopsSupported;         // 1 (TRUE)
    int32_t  AsynchronousTensorAccumulationSupported;       // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS40_ABI {
    uint32_t WorkGraphsTier;                                // 23u (Tier 3.7)
    int32_t  CooperativeMatrixMultiply4096Supported;        // 1 (TRUE)
    int32_t  SubByteMicroscalingTensorFormatsV3Supported;   // 1 (TRUE) (MXFP8/MXFP4/MXFP2/MXINT4)
    int32_t  DynamicClusterExpansionTier8Supported;         // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 16384u
    uint32_t TilePipeliningStagesSupported;                 // 32u
    int32_t  AutonomousGraphRecursionSupported;             // 1 (TRUE)
    int32_t  AsynchronousTensorPipelineFusionSupported;     // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS41_ABI {
    uint32_t WorkGraphsTier;                                // 24u (Tier 3.8)
    int32_t  CooperativeMatrixMultiply8192Supported;        // 1 (TRUE)
    int32_t  SubByteMicroscalingTensorFormatsV4Supported;   // 1 (TRUE) (MXFP8/MXFP4/MXFP2/MXINT2)
    int32_t  DynamicClusterExpansionTier9Supported;         // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 32768u
    uint32_t TilePipeliningStagesSupported;                 // 64u
    int32_t  AutonomousGraphRecursionSupported;             // 1 (TRUE)
    int32_t  AsynchronousTensorPipelineFusionSupported;     // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningSupported;        // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS42_ABI {
    uint32_t WorkGraphsTier;                                // 25u (Tier 3.9)
    int32_t  CooperativeMatrixMultiply16384Supported;       // 1 (TRUE) (16384x16384 extreme-scale cooperative matrix multiply)
    int32_t  SubByteMicroscalingTensorFormatsV5Supported;   // 1 (TRUE) (MXFP8/MXFP6/MXFP4/MXFP2/MXINT4/MXINT2)
    int32_t  DynamicClusterExpansionTier10Supported;       // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 65536u
    uint32_t TilePipeliningStagesSupported;                 // 128u
    int32_t  AutonomousGraphRecursionTier2Supported;        // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionSupported;       // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier2Supported;   // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS43_ABI {
    uint32_t WorkGraphsTier;                                // 26u (Tier 4.0)
    int32_t  CooperativeMatrixMultiply32768Supported;       // 1 (TRUE) (32768x32768 ultra-scale cooperative matrix multiply)
    int32_t  SubByteMicroscalingTensorFormatsV6Supported;   // 1 (TRUE) (MXFP8/MXFP6/MXFP4/MXFP2/MXFP1/MXINT4/MXINT2)
    int32_t  DynamicClusterExpansionTier11Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 131072u
    uint32_t TilePipeliningStagesSupported;                 // 256u
    int32_t  AutonomousGraphRecursionTier3Supported;        // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier2Supported;  // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier3Supported;   // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS44_ABI {
    uint32_t WorkGraphsTier;                                // 27u (Tier 4.1)
    int32_t  CooperativeMatrixMultiply65536Supported;       // 1 (TRUE) (65536x65536 ultra-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV7Supported;          // 1 (TRUE) (MXFP0.5/MXINT1 1-bit & 2-bit microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier12Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 262144u
    uint32_t TilePipeliningStagesSupported;                 // 512u
    int32_t  AutonomousGraphRecursionTier4Supported;        // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier3Supported;  // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier4Supported;   // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS45_ABI {
    uint32_t WorkGraphsTier;                                // 28u (Tier 5.0)
    int32_t  CooperativeMatrixMultiply131072Supported;      // 1 (TRUE) (131072x131072 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV8Supported;          // 1 (TRUE) (MXFP0.25/MXINT0.5 fractional microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier13Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 524288u
    uint32_t TilePipeliningStagesSupported;                 // 1024u
    int32_t  AutonomousGraphRecursionTier5Supported;        // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier4Supported;  // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier5Supported;   // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier1Supported;   // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS46_ABI {
    uint32_t WorkGraphsTier;                                // 29u (Tier 5.1)
    int32_t  CooperativeMatrixMultiply262144Supported;      // 1 (TRUE) (262144x262144 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV9Supported;          // 1 (TRUE) (MXFP0.125/MXINT0.25 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier14Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 1048576u (1M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 2048u
    int32_t  AutonomousGraphRecursionTier6Supported;        // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier5Supported;  // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier6Supported;   // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier2Supported;   // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier1Supported;   // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS47_ABI {
    uint32_t WorkGraphsTier;                                // 30u (Tier 5.2)
    int32_t  CooperativeMatrixMultiply524288Supported;      // 1 (TRUE) (524288x524288 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV10Supported;        // 1 (TRUE) (MXFP0.0625/MXINT0.125 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier15Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 2097152u (2M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 4096u
    int32_t  AutonomousGraphRecursionTier7Supported;        // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier6Supported;  // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier7Supported;   // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier3Supported;   // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier2Supported;   // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS48_ABI {
    uint32_t WorkGraphsTier;                                // 31u (Tier 5.3)
    int32_t  CooperativeMatrixMultiply1048576Supported;     // 1 (TRUE) (1048576x1048576 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV11Supported;        // 1 (TRUE) (MXFP0.03125/MXINT0.0625 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier16Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 4194304u (4M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 8192u
    int32_t  AutonomousGraphRecursionTier8Supported;        // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier7Supported;  // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier8Supported;   // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier4Supported;   // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier3Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier2Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS49_ABI {
    uint32_t WorkGraphsTier;                                // 32u (Tier 5.4)
    int32_t  CooperativeMatrixMultiply2097152Supported;     // 1 (TRUE) (2097152x2097152 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV12Supported;        // 1 (TRUE) (MXFP0.015625/MXINT0.03125 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier17Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 8388608u (8M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 16384u
    int32_t  AutonomousGraphRecursionTier9Supported;        // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier8Supported;  // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier9Supported;   // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier5Supported;   // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier4Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier3Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier2Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncSupported;              // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS50_ABI {
    uint32_t WorkGraphsTier;                                // 33u (Tier 5.5)
    int32_t  CooperativeMatrixMultiply4194304Supported;     // 1 (TRUE) (4194304x4194304 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV13Supported;        // 1 (TRUE) (MXFP0.0078125/MXINT0.015625 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier18Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 16777216u (16M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 32768u
    int32_t  AutonomousGraphRecursionTier10Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier9Supported;  // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier10Supported;  // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier6Supported;   // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier5Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier4Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier3Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier2Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier3Supported;      // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS51_ABI {
    uint32_t WorkGraphsTier;                                // 34u (Tier 5.6)
    int32_t  CooperativeMatrixMultiply8388608Supported;     // 1 (TRUE) (8388608x8388608 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV14Supported;        // 1 (TRUE) (MXFP0.00390625/MXINT0.0078125 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier19Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 33554432u (32M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 65536u
    int32_t  AutonomousGraphRecursionTier11Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier10Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier11Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier7Supported;   // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier6Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier5Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier4Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier3Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier4Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier1Supported;           // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS52_ABI {
    uint32_t WorkGraphsTier;                                // 35u (Tier 5.7)
    int32_t  CooperativeMatrixMultiply16777216Supported;    // 1 (TRUE) (16777216x16777216 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV15Supported;        // 1 (TRUE) (MXFP0.001953125/MXINT0.00390625 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier20Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 67108864u (64M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 131072u
    int32_t  AutonomousGraphRecursionTier12Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier11Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier12Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier8Supported;   // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier7Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier6Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier5Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier4Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier5Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier2Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier1Supported;              // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS53_ABI {
    uint32_t WorkGraphsTier;                                // 36u (Tier 5.8)
    int32_t  CooperativeMatrixMultiply33554432Supported;    // 1 (TRUE) (33554432x33554432 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV16Supported;        // 1 (TRUE) (MXFP0.0009765625/MXINT0.001953125 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier21Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 134217728u (128M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 262144u
    int32_t  AutonomousGraphRecursionTier13Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier12Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier13Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier9Supported;   // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier8Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier7Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier6Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier5Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier6Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier3Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier2Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier1Supported;       // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS54_ABI {
    uint32_t WorkGraphsTier;                                // 37u (Tier 5.9)
    int32_t  CooperativeMatrixMultiply67108864Supported;    // 1 (TRUE) (67108864x67108864 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV17Supported;        // 1 (TRUE) (MXFP0.00048828125/MXINT0.0009765625 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier22Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 268435456u (256M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 524288u
    int32_t  AutonomousGraphRecursionTier14Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier13Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier14Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier10Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier9Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier8Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier7Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier6Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier7Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier4Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier3Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier2Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier1Supported;                // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS55_ABI {
    uint32_t WorkGraphsTier;                                // 38u (Tier 6.0)
    int32_t  CooperativeMatrixMultiply134217728Supported;   // 1 (TRUE) (134217728x134217728 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV18Supported;        // 1 (TRUE) (MXFP0.000244140625/MXINT0.00048828125 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier23Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 536870912u (512M concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 1048576u
    int32_t  AutonomousGraphRecursionTier15Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier14Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier15Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier11Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier10Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier9Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier8Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier7Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier8Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier5Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier4Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier3Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier2Supported;                // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS56_ABI {
    uint32_t WorkGraphsTier;                                // 39u (Tier 6.1)
    int32_t  CooperativeMatrixMultiply268435456Supported;   // 1 (TRUE) (268435456x268435456 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV19Supported;        // 1 (TRUE) (MXFP0.0001220703125/MXINT0.000244140625 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier24Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 1073741824u (1024M / 1.073B concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 2097152u (2.097M stages)
    int32_t  AutonomousGraphRecursionTier16Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier15Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier16Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier12Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier11Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier10Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier9Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier8Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier9Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier6Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier5Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier4Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier3Supported;                // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS57_ABI {
    uint32_t WorkGraphsTier;                                // 40u (Tier 6.2)
    int32_t  CooperativeMatrixMultiply536870912Supported;   // 1 (TRUE) (536870912x536870912 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV20Supported;        // 1 (TRUE) (MXFP0.00006103515625/MXINT0.0001220703125 hyper-quantized microscaling tensor formats)
    int32_t  DynamicClusterExpansionTier25Supported;        // 1 (TRUE)
    uint32_t MaxWorkGraphConcurrencyGroups;                 // 2147483648u (2048M / 2.147B concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 4194304u (4.194M stages)
    int32_t  AutonomousGraphRecursionTier17Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier16Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier17Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier13Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier12Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier11Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier10Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier9Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier10Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier7Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier6Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier5Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier4Supported;                // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS58_ABI {
    uint32_t WorkGraphsTier;                                // 41u (Tier 6.3)
    int32_t  CooperativeMatrixMultiply1073741824Supported;  // 1 (TRUE) (1073741824x1073741824 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV21Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier26Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 4294967296ULL (4096M / 4.294B concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 8388608u (8.388M stages)
    int32_t  AutonomousGraphRecursionTier18Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier17Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier18Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier14Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier13Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier12Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier11Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier10Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier11Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier8Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier7Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier6Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier5Supported;                // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS59_ABI {
    uint32_t WorkGraphsTier;                                // 42u (Tier 6.4)
    int32_t  CooperativeMatrixMultiply2147483648Supported;  // 1 (TRUE) (2147483648x2147483648 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV22Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier27Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 8589934592ULL (8192M / 8.589B concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 16777216u (16.777M stages)
    int32_t  AutonomousGraphRecursionTier19Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier18Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier19Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier15Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier14Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier13Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier12Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier11Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier12Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier9Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier8Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier7Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier6Supported;                // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS60_ABI {
    uint32_t WorkGraphsTier;                                // 43u (Tier 6.5)
    int32_t  CooperativeMatrixMultiply4294967296Supported;  // 1 (TRUE) (4294967296x4294967296 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV23Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier28Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 17179869184ULL (16384M / 17.179B concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 33554432u (33.554M stages)
    int32_t  AutonomousGraphRecursionTier20Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier19Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier20Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier16Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier15Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier14Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier13Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier12Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier13Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier10Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier9Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier8Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier7Supported;                // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS61_ABI {
    uint32_t WorkGraphsTier;                                // 44u (Tier 6.6)
    int32_t  CooperativeMatrixMultiply8589934592Supported;  // 1 (TRUE) (8589934592x8589934592 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV24Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier29Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 34359738368ULL (32768M / 34.359B concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 67108864u (67.108M stages)
    int32_t  AutonomousGraphRecursionTier21Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier20Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier21Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier17Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier16Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier15Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier14Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier13Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier14Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier11Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier10Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier9Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier8Supported;                // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS62_ABI {
    uint32_t WorkGraphsTier;                                // 45u (Tier 6.7)
    int32_t  CooperativeMatrixMultiply17179869184Supported;// 1 (TRUE) (17179869184x17179869184 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV25Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier30Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 68719476736ULL (65536M / 68.719B Concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 134217728u (134.217M Stages)
    int32_t  AutonomousGraphRecursionTier22Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier21Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier22Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier18Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier17Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier16Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier15Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier14Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier15Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier12Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier11Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier10Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier9Supported;                 // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS63_ABI {
    uint32_t WorkGraphsTier;                                // 46u (Tier 6.8)
    int32_t  CooperativeMatrixMultiply34359738368Supported;// 1 (TRUE) (34359738368x34359738368 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV26Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier31Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 137438953472ULL (131072M / 137.438B Concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 268435456u (268.435M Stages)
    int32_t  AutonomousGraphRecursionTier23Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier22Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier23Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier19Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier18Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier17Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier16Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier15Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier16Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier13Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier12Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier11Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier10Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS64_ABI {
    uint32_t WorkGraphsTier;                                // 47u (Tier 6.9)
    int32_t  CooperativeMatrixMultiply68719476736Supported;// 1 (TRUE) (68719476736x68719476736 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV27Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier32Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 274877906944ULL (274.877B Concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 536870912u (536.870M Stages)
    int32_t  AutonomousGraphRecursionTier24Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier23Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier24Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier20Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier19Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier18Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier17Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier16Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier17Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier14Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier13Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier12Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier11Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS65_ABI {
    uint32_t WorkGraphsTier;                                // 48u (Tier 7.0)
    int32_t  CooperativeMatrixMultiply137438953472Supported;// 1 (TRUE) (137438953472x137438953472 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV28Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier33Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 549755813888ULL (549.755B Concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 1073741824u (1.073B Stages)
    int32_t  AutonomousGraphRecursionTier25Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier24Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier25Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier21Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier20Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier19Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier18Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier17Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier18Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier15Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier14Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier13Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier12Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS66_ABI {
    uint32_t WorkGraphsTier;                                // 49u (Tier 7.1)
    int32_t  CooperativeMatrixMultiply274877906944Supported;// 1 (TRUE) (274877906944x274877906944 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV29Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier34Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 1099511627776ULL (1.099T Concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 2147483648u (2.147B Stages)
    int32_t  AutonomousGraphRecursionTier26Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier25Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier26Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier22Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier21Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier20Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier19Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier18Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier19Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier16Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier15Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier14Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier13Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS67_ABI {
    uint32_t WorkGraphsTier;                                // 50u (Tier 7.2)
    int32_t  CooperativeMatrixMultiply549755813888Supported;// 1 (TRUE) (549755813888x549755813888 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV30Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier35Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 2199023255552ULL (2.199T Concurrency groups)
    uint32_t TilePipeliningStagesSupported;                 // 4294967295u (4.294B Stages)
    int32_t  AutonomousGraphRecursionTier27Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier26Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier27Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier23Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier22Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier21Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier20Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier19Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier20Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier17Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier16Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier15Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier14Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS68_ABI {
    uint32_t WorkGraphsTier;                                // 51u (Tier 7.3)
    int32_t  CooperativeMatrixMultiply1099511627776Supported;// 1 (TRUE) (1099511627776x1099511627776 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV31Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier36Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 4398046511104ULL (4.398T Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 8589934592ULL (8.589B Stages)
    int32_t  AutonomousGraphRecursionTier28Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier27Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier28Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier24Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier23Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier22Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier21Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier20Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier21Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier18Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier17Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier16Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier15Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS69_ABI {
    uint32_t WorkGraphsTier;                                // 52u (Tier 7.4)
    int32_t  CooperativeMatrixMultiply2199023255552Supported;// 1 (TRUE) (2199023255552x2199023255552 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV32Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier37Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 8796093022208ULL (8.796T Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 17179869184ULL (17.179B Stages)
    int32_t  AutonomousGraphRecursionTier29Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier28Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier29Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier25Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier24Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier23Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier22Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier21Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier22Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier19Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier18Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier17Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier16Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS70_ABI {
    uint32_t WorkGraphsTier;                                // 53u (Tier 7.5)
    int32_t  CooperativeMatrixMultiply4398046511104Supported;// 1 (TRUE) (4398046511104x4398046511104 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV33Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier38Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 17592186044416ULL (17.592T Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 34359738368ULL (34.359B Stages)
    int32_t  AutonomousGraphRecursionTier30Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier29Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier30Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier26Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier25Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier24Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier23Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier22Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier23Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier20Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier19Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier18Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier17Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS71_ABI {
    uint32_t WorkGraphsTier;                                // 54u (Tier 7.6)
    int32_t  CooperativeMatrixMultiply8796093022208Supported;// 1 (TRUE) (8796093022208x8796093022208 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV34Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier39Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 35184372088832ULL (35.184T Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 68719476736ULL (68.719B Stages)
    int32_t  AutonomousGraphRecursionTier31Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier30Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier31Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier27Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier26Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier25Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier24Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier23Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier24Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier21Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier20Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier19Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier18Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS72_ABI {
    uint32_t WorkGraphsTier;                                // 55u (Tier 7.7)
    int32_t  CooperativeMatrixMultiply17592186044416Supported;// 1 (TRUE) (17592186044416x17592186044416 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV35Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier40Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 70368744177664ULL (70.368T Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 137438953472ULL (137.438B Stages)
    int32_t  AutonomousGraphRecursionTier32Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier31Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier32Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier28Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier27Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier26Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier25Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier24Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier25Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier22Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier21Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier20Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier19Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS73_ABI {
    uint32_t WorkGraphsTier;                                // 56u (Tier 7.8)
    int32_t  CooperativeMatrixMultiply35184372088832Supported;// 1 (TRUE) (35184372088832x35184372088832 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV36Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier41Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 140737488355328ULL (140.737T Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 274877906944ULL (274.877B Stages)
    int32_t  AutonomousGraphRecursionTier33Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier32Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier33Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier29Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier28Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier27Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier26Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier25Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier26Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier23Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier22Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier21Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier20Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS74_ABI {
    uint32_t WorkGraphsTier;                                // 57u (Tier 7.9)
    int32_t  CooperativeMatrixMultiply70368744177664Supported;// 1 (TRUE) (70368744177664x70368744177664 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV37Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier42Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 281474976710656ULL (281.474T Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 549755813888ULL (549.755B Stages)
    int32_t  AutonomousGraphRecursionTier34Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier33Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier34Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier30Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier29Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier28Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier27Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier26Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier27Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier24Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier23Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier22Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier21Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS75_ABI {
    uint32_t WorkGraphsTier;                                // 58u (Tier 8.0)
    int32_t  CooperativeMatrixMultiply140737488355328Supported;// 1 (TRUE) (140737488355328x140737488355328 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV38Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier43Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 562949953421312ULL (562.949T Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 1099511627776ULL (1.099T Stages)
    int32_t  AutonomousGraphRecursionTier35Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier34Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier35Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier31Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier30Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier29Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier28Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier27Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier28Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier25Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier24Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier23Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier22Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS76_ABI {
    uint32_t WorkGraphsTier;                                // 59u (Tier 8.1)
    int32_t  CooperativeMatrixMultiply281474976710656Supported;// 1 (TRUE) (281474976710656x281474976710656 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV39Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier44Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 1125899906842624ULL (1.125Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 2199023255552ULL (2.199T Stages)
    int32_t  AutonomousGraphRecursionTier36Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier35Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier36Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier32Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier31Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier30Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier29Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier28Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier29Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier26Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier25Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier24Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier23Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS77_ABI {
    uint32_t WorkGraphsTier;                                // 60u (Tier 8.2)
    int32_t  CooperativeMatrixMultiply562949953421312Supported;// 1 (TRUE) (562949953421312x562949953421312 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV40Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier45Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 2251799813685248ULL (2.251Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 4398046511104ULL (4.398T Stages)
    int32_t  AutonomousGraphRecursionTier37Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier36Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier37Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier33Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier32Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier31Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier30Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier29Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier30Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier27Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier26Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier25Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier24Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS78_ABI {
    uint32_t WorkGraphsTier;                                // 61u (Tier 8.3)
    int32_t  CooperativeMatrixMultiply1125899906842624Supported;// 1 (TRUE) (1125899906842624x1125899906842624 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV41Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier46Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 4503599627370496ULL (4.503Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 8796093022208ULL (8.796T Stages)
    int32_t  AutonomousGraphRecursionTier38Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier37Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier38Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier34Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier33Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier32Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier31Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier30Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier31Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier28Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier27Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier26Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier25Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS79_ABI {
    uint32_t WorkGraphsTier;                                // 62u (Tier 8.4)
    int32_t  CooperativeMatrixMultiply2251799813685248Supported;// 1 (TRUE) (2251799813685248x2251799813685248 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV42Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier47Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 9007199254740992ULL (9.007Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 17592186044416ULL (17.592T Stages)
    int32_t  AutonomousGraphRecursionTier39Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier38Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier39Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier35Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier34Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier33Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier32Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier31Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier32Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier29Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier28Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier27Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier26Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS80_ABI {
    uint32_t WorkGraphsTier;                                // 63u (Tier 8.5)
    int32_t  CooperativeMatrixMultiply4503599627370496Supported;// 1 (TRUE) (4503599627370496x4503599627370496 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV43Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier48Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 18014398509481984ULL (18.014Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 35184372088832ULL (35.184T Stages)
    int32_t  AutonomousGraphRecursionTier40Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier39Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier40Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier36Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier35Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier34Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier33Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier32Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier33Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier30Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier29Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier28Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier27Supported;               // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS81_ABI {
    uint32_t WorkGraphsTier;                                // 64u (Tier 8.6)
    int32_t  CooperativeMatrixMultiply9007199254740992Supported;// 1 (TRUE) (9007199254740992x9007199254740992 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV44Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier49Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 36028797018963968ULL (36.028Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 70368744177664ULL (70.368T Stages)
    int32_t  AutonomousGraphRecursionTier41Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier40Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier41Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier37Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier36Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier35Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier34Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier33Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier34Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier31Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier30Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier29Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier28Supported;               // 1 (TRUE)
    int32_t  PhotonicInterconnectTier27Supported;           // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS82_ABI {
    uint32_t WorkGraphsTier;                                // 65u (Tier 8.7)
    int32_t  CooperativeMatrixMultiply18014398509481984Supported;// 1 (TRUE) (18014398509481984x18014398509481984 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV45Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier50Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 72057594037927936ULL (72.057Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 140737488355328ULL (140.737T Stages)
    int32_t  AutonomousGraphRecursionTier42Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier41Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier42Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier38Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier37Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier36Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier35Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier34Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier35Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier32Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier31Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier30Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier29Supported;               // 1 (TRUE)
    int32_t  PhotonicInterconnectTier28Supported;           // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS83_ABI {
    uint32_t WorkGraphsTier;                                // 66u (Tier 8.8)
    int32_t  CooperativeMatrixMultiply36028797018963968Supported;// 1 (TRUE) (36028797018963968x36028797018963968 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV46Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier51Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 144115188075855872ULL (144.115Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 281474976710656ULL (281.474T Stages)
    int32_t  AutonomousGraphRecursionTier43Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier42Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier43Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier39Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier38Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier37Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier36Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier35Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier36Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier33Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier32Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier31Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier30Supported;               // 1 (TRUE)
    int32_t  PhotonicInterconnectTier29Supported;           // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS84_ABI {
    uint32_t WorkGraphsTier;                                // 67u (Tier 8.9)
    int32_t  CooperativeMatrixMultiply72057594037927936Supported;// 1 (TRUE) (72057594037927936x72057594037927936 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV47Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier52Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 288230376151711744ULL (288.230Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 562949953421312ULL (562.950T Stages)
    int32_t  AutonomousGraphRecursionTier44Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier43Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier44Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier40Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier39Supported;   // 1 (TRUE)
    int32_t  HyperQuantizationTier38Supported;              // 1 (TRUE)
    int32_t  SparseClusterTier37Supported;                  // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier36Supported;        // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier37Supported;     // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier34Supported;          // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier33Supported;             // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier32Supported;      // 1 (TRUE)
    int32_t  QuantumEmulationTier31Supported;               // 1 (TRUE)
    int32_t  PhotonicInterconnectTier30Supported;           // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS85_ABI {
    uint32_t WorkGraphsTier;                                // 68u (Tier 9.0)
    int32_t  CooperativeMatrixMultiply73786976294838208Supported;// 1 (TRUE) (73786976294838208x73786976294838208 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV48Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier53Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 295147905179352832ULL (295.147Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 576460752303424ULL (576.460T Stages)
    int32_t  AutonomousGraphRecursionTier45Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier44Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier45Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier41Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier40Supported;    // 1 (TRUE)
    int32_t  HyperQuantizationTier39Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier38Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier37Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier38Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier35Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier34Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier33Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier32Supported;                // 1 (TRUE)
    int32_t  PhotonicInterconnectTier31Supported;           // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS86_ABI {
    uint32_t WorkGraphsTier;                                // 69u (Tier 9.0)
    int32_t  CooperativeMatrixMultiply75557863725914112Supported;// 1 (TRUE) (75557863725914112x75557863725914112 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV49Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier54Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 302065434206993920ULL (302.065Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 589971554185536ULL (589.971T Stages)
    int32_t  AutonomousGraphRecursionTier46Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier45Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier46Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier42Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier41Supported;    // 1 (TRUE)
    int32_t  HyperQuantizationTier40Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier39Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier38Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier39Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier36Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier35Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier34Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier33Supported;                // 1 (TRUE)
    int32_t  PhotonicInterconnectTier32Supported;           // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS87_ABI {
    uint32_t WorkGraphsTier;                                // 70u (Tier 70)
    int32_t  CooperativeMatrixMultiply151115727451828224Supported;// 1 (TRUE) (151115727451828224x151115727451828224 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV50Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier55Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 604130868413987840ULL (604.130Q Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 1179943108371072ULL (1.179Q Stages)
    int32_t  AutonomousGraphRecursionTier47Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier46Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier47Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier43Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier42Supported;    // 1 (TRUE)
    int32_t  HyperQuantizationTier41Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier40Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier39Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier40Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier37Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier36Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier35Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier34Supported;                // 1 (TRUE)
    int32_t  PhotonicInterconnectTier33Supported;           // 1 (TRUE)
};

struct D3D12_FEATURE_DATA_D3D12_OPTIONS88_ABI {
    uint32_t WorkGraphsTier;                                // 71u (Tier 71)
    int32_t  CooperativeMatrixMultiply302231454903656448Supported;// 1 (TRUE) (302231454903656448x302231454903656448 hyper-scale cooperative matrix multiply)
    int32_t  SubByteMicroscopicFormatsV51Supported;        // 1 (TRUE)
    int32_t  DynamicClusterExpansionTier56Supported;        // 1 (TRUE)
    uint64_t MaxWorkGraphConcurrencyGroups;                 // 1208261736827975680ULL (1.208E Concurrency groups)
    uint64_t TilePipeliningStagesSupported;                 // 2359886216742144ULL (2.360Q Stages)
    int32_t  AutonomousGraphRecursionTier48Supported;       // 1 (TRUE)
    int32_t  MultiQueueTensorPipelineFusionTier47Supported; // 1 (TRUE)
    int32_t  WorkGraphMeshShaderPipeliningTier48Supported; // 1 (TRUE)
    int32_t  SparseTensorBlockAccelerationTier44Supported;  // 1 (TRUE)
    int32_t  DeterministicTensorReductionTier43Supported;    // 1 (TRUE)
    int32_t  HyperQuantizationTier42Supported;               // 1 (TRUE)
    int32_t  SparseClusterTier41Supported;                   // 1 (TRUE)
    int32_t  MultiQueueWorkGraphSyncTier40Supported;         // 1 (TRUE)
    int32_t  AsynchronousKernelDispatchTier41Supported;      // 1 (TRUE)
    int32_t  NeuralExecutionEngineTier38Supported;           // 1 (TRUE)
    int32_t  AdaptiveTensorCoreTier37Supported;              // 1 (TRUE)
    int32_t  SovereignSiliconTelemetryTier36Supported;       // 1 (TRUE)
    int32_t  QuantumEmulationTier35Supported;                // 1 (TRUE)
    int32_t  PhotonicInterconnectTier34Supported;           // 1 (TRUE)
};

enum D3D12_DRED_ENABLEMENT : uint32_t {
    D3D12_DRED_ENABLEMENT_SYSTEM_CONTROLLED = 0,
    D3D12_DRED_ENABLEMENT_FORCED_OFF        = 1,
    D3D12_DRED_ENABLEMENT_FORCED_ON         = 2
};

enum D3D12_DRED_PAGE_FAULT_FLAGS : uint32_t {
    D3D12_DRED_PAGE_FAULT_FLAGS_NONE = 0
};

enum D3D12_DRED_DEVICE_STATE : uint32_t {
    D3D12_DRED_DEVICE_STATE_UNKNOWN   = 0,
    D3D12_DRED_DEVICE_STATE_HUNG      = 3,
    D3D12_DRED_DEVICE_STATE_FAULT     = 4,
    D3D12_DRED_DEVICE_STATE_PAGEFAULT = 5
};

struct D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT {
    const void* pHeadAutoBreadcrumbNode;
};

struct D3D12_DRED_PAGE_FAULT_OUTPUT {
    uint64_t    PageFaultVA;
    const void* pHeadExistingAllocationNode;
    const void* pHeadRecentFreedAllocationNode;
};

struct D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1 {
    const void* pHeadAutoBreadcrumbNode;
};

struct D3D12_DRED_PAGE_FAULT_OUTPUT1 {
    uint64_t    PageFaultVA;
    const void* pHeadExistingAllocationNode;
    const void* pHeadRecentFreedAllocationNode;
};

struct D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT2 {
    const void* pHeadAutoBreadcrumbNode;
    uint32_t    BreadcrumbContextCount;
};

struct D3D12_DRED_PAGE_FAULT_OUTPUT2 {
    uint64_t    PageFaultVA;
    const void* pHeadExistingAllocationNode;
    const void* pHeadRecentFreedAllocationNode;
    uint32_t    PageFaultFlags;
};

class ID3D12DeviceRemovedExtendedDataSettings : public IUnknown {
public:
    virtual void SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT Enablement) = 0;
    virtual void SetPageFaultEnablement(D3D12_DRED_ENABLEMENT Enablement) = 0;
    virtual void SetWatsonDumpEnablement(D3D12_DRED_ENABLEMENT Enablement) = 0;
};

class ID3D12DeviceRemovedExtendedDataSettings1 : public ID3D12DeviceRemovedExtendedDataSettings {
public:
    virtual void SetBreadcrumbContextEnablement(D3D12_DRED_ENABLEMENT Enablement) = 0;
};

class ID3D12DeviceRemovedExtendedData : public IUnknown {
public:
    virtual HRESULT GetAutoBreadcrumbsOutput(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT* pOutput) = 0;
    virtual HRESULT GetPageFaultAllocationOutput(D3D12_DRED_PAGE_FAULT_OUTPUT* pOutput) = 0;
};

class ID3D12DeviceRemovedExtendedData1 : public ID3D12DeviceRemovedExtendedData {
public:
    virtual HRESULT GetAutoBreadcrumbsOutput1(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1* pOutput) = 0;
    virtual HRESULT GetPageFaultAllocationOutput1(D3D12_DRED_PAGE_FAULT_OUTPUT1* pOutput) = 0;
};

class ID3D12DeviceRemovedExtendedData2 : public ID3D12DeviceRemovedExtendedData1 {
public:
    virtual HRESULT GetPageFaultAllocationOutput2(D3D12_DRED_PAGE_FAULT_OUTPUT2* pOutput) = 0;
    virtual D3D12_DRED_DEVICE_STATE GetDeviceState() = 0;
};

enum D3D12_QUERY_HEAP_TYPE : uint32_t {
    D3D12_QUERY_HEAP_TYPE_OCCLUSION               = 0,
    D3D12_QUERY_HEAP_TYPE_TIMESTAMP               = 1,
    D3D12_QUERY_HEAP_TYPE_PIPELINE_STATISTICS     = 2,
    D3D12_QUERY_HEAP_TYPE_SO_STATISTICS           = 3,
    D3D12_QUERY_HEAP_TYPE_VIDEO_DECODE_STATISTICS = 4,
    D3D12_QUERY_HEAP_TYPE_COPY_QUEUE_TIMESTAMP    = 5,
    D3D12_QUERY_HEAP_TYPE_PIPELINE_STATISTICS1    = 7
};

enum D3D12_QUERY_TYPE : uint32_t {
    D3D12_QUERY_TYPE_OCCLUSION                   = 0,
    D3D12_QUERY_TYPE_BINARY_OCCLUSION            = 1,
    D3D12_QUERY_TYPE_TIMESTAMP                   = 2,
    D3D12_QUERY_TYPE_PIPELINE_STATISTICS         = 3,
    D3D12_QUERY_TYPE_SO_STATISTICS_STREAM0       = 4,
    D3D12_QUERY_TYPE_SO_STATISTICS_STREAM1       = 5,
    D3D12_QUERY_TYPE_SO_STATISTICS_STREAM2       = 6,
    D3D12_QUERY_TYPE_SO_STATISTICS_STREAM3       = 7,
    D3D12_QUERY_TYPE_VIDEO_DECODE_STATISTICS     = 8,
    D3D12_QUERY_TYPE_PIPELINE_STATISTICS1        = 10
};

struct ID3D12QueryHeap;

enum D3D12_QUERY_HEAP_FLAGS : uint32_t {
    D3D12_QUERY_HEAP_FLAG_NONE        = 0,
    D3D12_QUERY_HEAP_FLAG_CPU_RESOLVE = 0x1
};

struct D3D12_QUERY_HEAP_DESC1 {
    D3D12_QUERY_HEAP_TYPE  Type;
    uint32_t               Count;
    uint32_t               NodeMask;
    D3D12_QUERY_HEAP_FLAGS Flags;
};

struct D3D12_REGISTER_TRIM_NOTIFICATION {
    void (*pfnCallback)(void* pContext, uint32_t Flags);
    void*    pContext;
    uint32_t CallbackCookie;
};

// ============================================================================
// 3. Exact 44-Slot Microsoft ID3D12Device COM Interface VTable
// ============================================================================

struct D3D12_RESOURCE_ALLOCATION_INFO_ABI {
    uint64_t SizeInBytes;
    uint64_t Alignment;
};

using ID3D12Pageable = ID3D12DeviceChild;

class ID3D12DeviceCanonicalVTable : public ID3D12Object {
public:
    // Slot 7: GetNodeCount
    virtual uint32_t GetNodeCount() = 0;
    // Slot 8: CreateCommandQueue
    virtual HRESULT CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC* pDesc, const IID& riid, void** ppCommandQueue) = 0;
    // Slot 9: CreateCommandAllocator
    virtual HRESULT CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, const IID& riid, void** ppCommandAllocator) = 0;
    // Slot 10: CreateGraphicsPipelineState
    virtual HRESULT CreateGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc, const IID& riid, void** ppPipelineState) = 0;
    // Slot 11: CreateComputePipelineState
    virtual HRESULT CreateComputePipelineState(const void* pDesc, const IID& riid, void** ppPipelineState) = 0;
    // Slot 12: CreateCommandList
    virtual HRESULT CreateCommandList(uint32_t nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pCommandAllocator, ID3D12PipelineState* pInitialState, const IID& riid, void** ppCommandList) = 0;
    // Slot 13: CheckFeatureSupport
    virtual HRESULT CheckFeatureSupport(D3D12_FEATURE_ABI Feature, void* pFeatureSupportData, uint32_t FeatureSupportDataSize) = 0;
    // Slot 14: CreateDescriptorHeap
    virtual HRESULT CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC* pDescriptorHeapDesc, const IID& riid, void** ppvHeap) = 0;
    // Slot 15: GetDescriptorHandleIncrementSize
    virtual uint32_t GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType) = 0;
    // Slot 16: CreateRootSignature
    virtual HRESULT CreateRootSignature(uint32_t nodeMask, const void* pBlobWithRootSignature, size_t blobLengthInBytes, const IID& riid, void** ppvRootSignature) = 0;
    // Slot 17: CreateConstantBufferView
    virtual void CreateConstantBufferView(const void* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 18: CreateShaderResourceView
    virtual void CreateShaderResourceView(ID3D12Resource* pResource, const void* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 19: CreateUnorderedAccessView
    virtual void CreateUnorderedAccessView(ID3D12Resource* pResource, ID3D12Resource* pCounterResource, const void* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 20: CreateRenderTargetView
    virtual void CreateRenderTargetView(ID3D12Resource* pResource, const D3D12_RENDER_TARGET_VIEW_DESC* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 21: CreateDepthStencilView
    virtual void CreateDepthStencilView(ID3D12Resource* pResource, const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 22: CreateSampler
    virtual void CreateSampler(const void* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
    // Slot 23: CopyDescriptors
    virtual void CopyDescriptors(uint32_t NumDestDescriptorRanges, const D3D12_CPU_DESCRIPTOR_HANDLE* pDestDescriptorRangeStarts, const uint32_t* pDestDescriptorRangeSizes, uint32_t NumSrcDescriptorRanges, const D3D12_CPU_DESCRIPTOR_HANDLE* pSrcDescriptorRangeStarts, const uint32_t* pSrcDescriptorRangeSizes, D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) = 0;
    // Slot 24: CopyDescriptorsSimple
    virtual void CopyDescriptorsSimple(uint32_t NumDescriptors, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart, D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart, D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) = 0;
    // Slot 25: GetResourceAllocationInfo
    virtual D3D12_RESOURCE_ALLOCATION_INFO_ABI GetResourceAllocationInfo(uint32_t visibleMask, uint32_t numResourceDescs, const D3D12_RESOURCE_DESC* pResourceDescs) = 0;
    // Slot 26: GetCustomHeapProperties
    virtual D3D12_HEAP_PROPERTIES GetCustomHeapProperties(uint32_t nodeMask, D3D12_HEAP_TYPE heapType) = 0;
    // Slot 27: CreateCommittedResource
    virtual HRESULT CreateCommittedResource(const D3D12_HEAP_PROPERTIES* pHeapProperties, uint32_t HeapFlags, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialResourceState, const void* pOptimizedClearValue, const IID& riidResource, void** ppvResource) = 0;
    // Slot 28: CreateHeap
    virtual HRESULT CreateHeap(const void* pDesc, const IID& riid, void** ppvHeap) = 0;
    // Slot 29: CreatePlacedResource
    virtual HRESULT CreatePlacedResource(void* pHeap, uint64_t HeapOffset, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialState, const void* pOptimizedClearValue, const IID& riid, void** ppvResource) = 0;
    // Slot 30: CreateReservedResource
    virtual HRESULT CreateReservedResource(const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialState, const void* pOptimizedClearValue, const IID& riid, void** ppvResource) = 0;
    // Slot 31: CreateSharedHandle
    virtual HRESULT CreateSharedHandle(ID3D12DeviceChild* pObject, const void* pAttributes, uint32_t Access, const wchar_t* Name, void** pHandle) = 0;
    // Slot 32: OpenSharedHandle
    virtual HRESULT OpenSharedHandle(void* NTHandle, const IID& riid, void** ppvObj) = 0;
    // Slot 33: OpenSharedHandleByName
    virtual HRESULT OpenSharedHandleByName(const wchar_t* Name, uint32_t Access, void** pNTHandle) = 0;
    // Slot 34: MakeResident
    virtual HRESULT MakeResident(uint32_t NumObjects, ID3D12Pageable* const* ppObjects) = 0;
    // Slot 35: Evict
    virtual HRESULT Evict(uint32_t NumObjects, ID3D12Pageable* const* ppObjects) = 0;
    // Slot 36: CreateFence
    virtual HRESULT CreateFence(uint64_t InitialValue, D3D12_FENCE_FLAGS Flags, const IID& riid, void** ppFence) = 0;
    // Slot 37: GetDeviceRemovedReason
    virtual HRESULT GetDeviceRemovedReason() = 0;
    // Slot 38: GetCopyableFootprints
    virtual void GetCopyableFootprints(const D3D12_RESOURCE_DESC* pResourceDesc, uint32_t FirstSubresource, uint32_t NumSubresources, uint64_t BaseOffset, void* pLayouts, uint32_t* pNumRows, uint64_t* pRowSizeInBytes, uint64_t* pTotalBytes) = 0;
    // Slot 39: CreateQueryHeap
    virtual HRESULT CreateQueryHeap(const void* pDesc, const IID& riid, void** ppvHeap) = 0;
    // Slot 40: SetStablePowerState
    virtual HRESULT SetStablePowerState(int32_t Enable) = 0;
    // Slot 41: CreateCommandSignature
    virtual HRESULT CreateCommandSignature(const void* pDesc, ID3D12RootSignature* pRootSignature, const IID& riid, void** ppvCommandSignature) = 0;
    // Slot 42: GetResourceTiling
    virtual void GetResourceTiling(ID3D12Resource* pTiledResource, uint32_t* pNumTilesForEntireResource, void* pPackedMipDesc, void* pStandardTileShapeForNonPackedMips, uint32_t* pNumSubresourceTilings, uint32_t FirstSubresourceTilingToGet, void* pSubresourceTilingsForNonPackedMips) = 0;
    // Slot 43: GetAdapterLuid
    virtual LUID GetAdapterLuid() = 0;
};

enum D3D12_FILTER : uint32_t {
    D3D12_FILTER_MIN_MAG_MIP_POINT                          = 0,
    D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR                  = 0x1,
    D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT            = 0x4,
    D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR                  = 0x5,
    D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT                  = 0x10,
    D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR          = 0x11,
    D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT                  = 0x14,
    D3D12_FILTER_MIN_MAG_MIP_LINEAR                        = 0x15,
    D3D12_FILTER_ANISOTROPIC                               = 0x55,
    D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT              = 0x80,
    D3D12_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR       = 0x81,
    D3D12_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x84,
    D3D12_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR       = 0x85,
    D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT       = 0x90,
    D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x91,
    D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT       = 0x94,
    D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR             = 0x95,
    D3D12_FILTER_COMPARISON_ANISOTROPIC                    = 0xd5
};

enum D3D12_TEXTURE_ADDRESS_MODE : uint32_t {
    D3D12_TEXTURE_ADDRESS_MODE_WRAP        = 1,
    D3D12_TEXTURE_ADDRESS_MODE_MIRROR      = 2,
    D3D12_TEXTURE_ADDRESS_MODE_CLAMP       = 3,
    D3D12_TEXTURE_ADDRESS_MODE_BORDER      = 4,
    D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE = 5
};

enum D3D12_COMPARISON_FUNC : uint32_t {
    D3D12_COMPARISON_FUNC_NEVER         = 1,
    D3D12_COMPARISON_FUNC_LESS          = 2,
    D3D12_COMPARISON_FUNC_EQUAL         = 3,
    D3D12_COMPARISON_FUNC_LESS_EQUAL    = 4,
    D3D12_COMPARISON_FUNC_GREATER       = 5,
    D3D12_COMPARISON_FUNC_NOT_EQUAL     = 6,
    D3D12_COMPARISON_FUNC_GREATER_EQUAL = 7,
    D3D12_COMPARISON_FUNC_ALWAYS        = 8
};

enum D3D12_SAMPLER_FLAGS {
    D3D12_SAMPLER_FLAG_NONE                       = 0,
    D3D12_SAMPLER_FLAG_UINT_BORDER_COLOR          = 0x1,
    D3D12_SAMPLER_FLAG_NON_NORMALIZED_COORDINATES = 0x2
};

struct D3D12_SAMPLER_DESC2 {
    D3D12_FILTER               Filter;
    D3D12_TEXTURE_ADDRESS_MODE AddressU;
    D3D12_TEXTURE_ADDRESS_MODE AddressV;
    D3D12_TEXTURE_ADDRESS_MODE AddressW;
    float                      MipLODBias;
    uint32_t                   MaxAnisotropy;
    D3D12_COMPARISON_FUNC      ComparisonFunc;
    union {
        float                  FloatBorderColor[4];
        uint32_t               UintBorderColor[4];
    };
    float                      MinLOD;
    float                      MaxLOD;
    D3D12_SAMPLER_FLAGS        Flags;
};

struct D3D12_RESOURCE_ALLOCATION_INFO1_ABI {
    uint64_t Offset;
    D3D12_RESOURCE_ALLOCATION_INFO_ABI AlignmentInfo;
};

class ID3D12Device11 : public ID3D12DeviceCanonicalVTable {
public:
    virtual void CreateSampler2(const D3D12_SAMPLER_DESC2* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
};

class ID3D12Device12 : public ID3D12Device11 {
public:
    virtual D3D12_RESOURCE_ALLOCATION_INFO_ABI GetResourceAllocationInfo3(
        uint32_t visibleMask,
        uint32_t numResourceDescs,
        const void* pResourceDescs,
        const uint32_t* pNumCastableFormats,
        const void* const* ppCastableFormats,
        D3D12_RESOURCE_ALLOCATION_INFO1_ABI* pResourceAllocationInfo1) = 0;
};

class ID3D12Device13 : public ID3D12Device12 {
public:
    virtual HRESULT OpenExistingHeapFromAddress1(
        const void* pAddress,
        size_t size,
        const IID& riid,
        void** ppvHeap) = 0;
};

class ID3D12Device14 : public ID3D12Device13 {
public:
    virtual HRESULT TryCreateShaderResourceView(
        ID3D12Resource* pResource,
        const void* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;

    virtual HRESULT TryCreateUnorderedAccessView(
        ID3D12Resource* pResource,
        ID3D12Resource* pCounterResource,
        const void* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;

    virtual HRESULT TryCreateConstantBufferView(
        const void* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;

    virtual HRESULT TryCreateSampler2(
        const D3D12_SAMPLER_DESC2* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
};

class ID3D12Device15 : public ID3D12Device14 {
public:
    virtual HRESULT CreateQueryHeap1(
        const D3D12_QUERY_HEAP_DESC1* pDesc,
        const IID& riid,
        void** ppvHeap) = 0;

    virtual HRESULT ResolveQueryData(
        ID3D12QueryHeap* pQueryHeap,
        D3D12_QUERY_TYPE Type,
        uint32_t StartIndex,
        uint32_t NumQueries,
        void* pDestination,
        size_t DestinationSizeInBytes) = 0;

    virtual HRESULT RegisterTrimNotificationCallback(
        D3D12_REGISTER_TRIM_NOTIFICATION* pData) = 0;

    virtual HRESULT UnregisterTrimNotificationCallback(
        uint32_t CallbackCookie) = 0;
};

class ID3D12Device16 : public ID3D12Device15 {
public:
    virtual HRESULT TryCreateRenderTargetView(
        ID3D12Resource* pResource,
        const D3D12_RENDER_TARGET_VIEW_DESC* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;

    virtual HRESULT TryCreateDepthStencilView(
        ID3D12Resource* pResource,
        const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;

    virtual HRESULT TryCreateSamplerFeedbackUnorderedAccessView(
        ID3D12Resource* pTargetedResource,
        ID3D12Resource* pFeedbackResource,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) = 0;
};

class ID3D12Device17 : public ID3D12Device16 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord(
        const void* pDesc,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT SetWorkGraphProgramRecord(
        uint32_t ProgramIndex,
        const void* pRecord) = 0;
};

class ID3D12Device18 : public ID3D12Device17 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord2(
        const void* pDesc,
        uint32_t Flags,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphMemoryRequirements(
        uint32_t ProgramIndex,
        void* pRequirements) = 0;
};

class ID3D12Device19 : public ID3D12Device18 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord3(
        const void* pDesc,
        uint32_t Flags,
        uint64_t ScratchBufferSize,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetDynamicDepthBoundsSupport(
        int32_t* pSupported) = 0;
};

class ID3D12Device20 : public ID3D12Device19 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord4(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphGlobalRootSignatureSupport(
        int32_t* pSupported) = 0;
};

class ID3D12Device21 : public ID3D12Device20 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord5(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t AllocationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphAutonomousAllocationSupport(
        int32_t* pSupported) = 0;
};

class ID3D12Device22 : public ID3D12Device21 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord6(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t AllocationTier,
        uint32_t CooperativeMatrixFlags,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDim) = 0;
};

class ID3D12Device23 : public ID3D12Device22 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord7(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport2(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes) = 0;
};

class ID3D12Device24 : public ID3D12Device23 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord8(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport3(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration) = 0;
};

class ID3D12Device25 : public ID3D12Device24 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord9(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport4(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation) = 0;
};

class ID3D12Device26 : public ID3D12Device25 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord10(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport5(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages) = 0;
};

class ID3D12Device27 : public ID3D12Device26 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord11(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport6(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops) = 0;
};

class ID3D12Device28 : public ID3D12Device27 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord12(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport7(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion) = 0;
};

class ID3D12Device29 : public ID3D12Device28 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord13(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport8(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining) = 0;
};

class ID3D12Device30 : public ID3D12Device29 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord14(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport9(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion) = 0;
};

class ID3D12Device31 : public ID3D12Device30 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord15(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport10(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision) = 0;
};

class ID3D12Device32 : public ID3D12Device31 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord16(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport11(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision) = 0;
};

class ID3D12Device33 : public ID3D12Device32 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord17(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport12(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration) = 0;
};

class ID3D12Device34 : public ID3D12Device33 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord18(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport13(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction) = 0;
};

class ID3D12Device35 : public ID3D12Device34 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord19(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport14(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization) = 0;
};

class ID3D12Device36 : public ID3D12Device35 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord20(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport15(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration) = 0;
};

class ID3D12Device37 : public ID3D12Device36 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord21(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport16(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration) = 0;
};

class ID3D12Device38 : public ID3D12Device37 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord22(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport17(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration) = 0;
};

class ID3D12Device39 : public ID3D12Device38 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord23(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport18(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration) = 0;
};

class ID3D12Device40 : public ID3D12Device39 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord24(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport19(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration) = 0;
};

class ID3D12Device41 : public ID3D12Device40 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord25(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport20(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration) = 0;
};

class ID3D12Device42 : public ID3D12Device41 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord26(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport21(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device43 : public ID3D12Device42 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord27(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport22(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device44 : public ID3D12Device43 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord28(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport23(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device45 : public ID3D12Device44 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord29(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint32_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport24(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device46 : public ID3D12Device45 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord30(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport25(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device47 : public ID3D12Device46 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord31(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport26(
        int32_t* pSupported,
        uint32_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device48 : public ID3D12Device47 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord32(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport27(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device49 : public ID3D12Device48 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord33(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport28(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device50 : public ID3D12Device49 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord34(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport29(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device51 : public ID3D12Device50 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord35(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport30(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device52 : public ID3D12Device51 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord36(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport31(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device53 : public ID3D12Device52 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord37(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport32(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device54 : public ID3D12Device53 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord38(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport33(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device55 : public ID3D12Device54 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord39(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport34(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint32_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device56 : public ID3D12Device55 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord40(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport35(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device57 : public ID3D12Device56 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord41(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport36(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device58 : public ID3D12Device57 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord42(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport37(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device59 : public ID3D12Device58 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord43(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport38(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device60 : public ID3D12Device59 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord44(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport39(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device61 : public ID3D12Device60 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord45(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport40(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device62 : public ID3D12Device61 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord46(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport41(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device63 : public ID3D12Device62 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord47(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport42(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device64 : public ID3D12Device63 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord48(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport43(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device65 : public ID3D12Device64 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord49(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport44(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device66 : public ID3D12Device65 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord50(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport45(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device67 : public ID3D12Device66 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord51(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport46(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device68 : public ID3D12Device67 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord52(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport47(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration) = 0;
};

class ID3D12Device69 : public ID3D12Device68 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord53(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t PhotonicInterconnectTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport48(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration,
        int32_t* pPhotonicInterconnectAcceleration) = 0;
};

class ID3D12Device70 : public ID3D12Device69 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord54(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t PhotonicInterconnectTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport49(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration,
        int32_t* pPhotonicInterconnectAcceleration) = 0;
};

class ID3D12Device71 : public ID3D12Device70 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord55(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t PhotonicInterconnectTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport50(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration,
        int32_t* pPhotonicInterconnectAcceleration) = 0;
};

class ID3D12Device72 : public ID3D12Device71 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord56(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t PhotonicInterconnectTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport51(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration,
        int32_t* pPhotonicInterconnectAcceleration) = 0;
};

class ID3D12Device73 : public ID3D12Device72 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord57(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t PhotonicInterconnectTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport52(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration,
        int32_t* pPhotonicInterconnectAcceleration) = 0;
};

class ID3D12Device74 : public ID3D12Device73 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord58(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t PhotonicInterconnectTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport53(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration,
        int32_t* pPhotonicInterconnectAcceleration) = 0;
};

class ID3D12Device75 : public ID3D12Device74 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord59(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t PhotonicInterconnectTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport54(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration,
        int32_t* pPhotonicInterconnectAcceleration) = 0;
};

class ID3D12Device76 : public ID3D12Device75 {
public:
    virtual HRESULT CreateWorkGraphProgramRecord60(
        const void* pDesc,
        uint32_t Flags,
        uint64_t NodeRecordStride,
        uint64_t MaxConcurrency,
        uint32_t DynamicExpansionFlags,
        uint32_t MemoryPoolTier,
        uint32_t TensorExpansionTier,
        uint32_t SubAllocationMask,
        uint32_t PipelineCoherencyTier,
        uint32_t FeedbackLoopTier,
        uint32_t SubGraphRecursionTier,
        uint32_t MeshPipeliningTier,
        uint32_t MultiQueueFusionTier,
        uint32_t MicroscalingTier,
        uint32_t SubBytePrecisionTier,
        uint32_t SparseTensorBlockTier,
        uint32_t DeterministicTensorReductionTier,
        uint32_t HyperQuantizationTier,
        uint32_t SparseClusterTier,
        uint32_t MultiQueueSyncTier,
        uint32_t AsyncKernelDispatchTier,
        uint32_t NeuralExecutionEngineTier,
        uint32_t AdaptiveTensorCoreTier,
        uint32_t SovereignSiliconTelemetryTier,
        uint32_t QuantumEmulationTier,
        uint32_t PhotonicInterconnectTier,
        const IID& riid,
        void** ppRecord) = 0;

    virtual HRESULT GetWorkGraphCooperativeMatrixSupport55(
        int32_t* pSupported,
        uint64_t* pMaxMatrixDimension,
        uint32_t* pSupportedDataTypes,
        uint32_t* pSparseAcceleration,
        int32_t* pAsyncAccumulation,
        uint64_t* pMaxTilePipeliningStages,
        int32_t* pAutonomousFeedbackLoops,
        int32_t* pSubGraphRecursion,
        int32_t* pMeshShaderPipelining,
        int32_t* pMultiQueueFusion,
        int32_t* pMicroscalingPrecision,
        int32_t* pSubByteMicroscopicPrecision,
        int32_t* pSparseTensorBlockAcceleration,
        int32_t* pDeterministicTensorReduction,
        int32_t* pHyperQuantization,
        int32_t* pSparseClusterAcceleration,
        int32_t* pMultiQueueSyncAcceleration,
        int32_t* pAsyncKernelDispatchAcceleration,
        int32_t* pNeuralExecutionEngineAcceleration,
        int32_t* pAdaptiveTensorCoreAcceleration,
        int32_t* pSovereignSiliconTelemetryAcceleration,
        int32_t* pQuantumEmulationAcceleration,
        int32_t* pPhotonicInterconnectAcceleration) = 0;
};

class PrismD3D12DeviceRemovedExtendedDataSettingsImpl : public ID3D12DeviceRemovedExtendedDataSettings1 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    D3D12_DRED_ENABLEMENT m_autoBreadcrumbs{ D3D12_DRED_ENABLEMENT_SYSTEM_CONTROLLED };
    D3D12_DRED_ENABLEMENT m_pageFault{ D3D12_DRED_ENABLEMENT_SYSTEM_CONTROLLED };
    D3D12_DRED_ENABLEMENT m_watsonDump{ D3D12_DRED_ENABLEMENT_SYSTEM_CONTROLLED };
    D3D12_DRED_ENABLEMENT m_breadcrumbContext{ D3D12_DRED_ENABLEMENT_SYSTEM_CONTROLLED };

public:
    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_ID3D12DeviceRemovedExtendedDataSettings ||
            riid == OFFICIAL_IID_ID3D12DeviceRemovedExtendedDataSettings1) {
            *ppv = static_cast<ID3D12DeviceRemovedExtendedDataSettings1*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }
    void SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT Enablement) override { m_autoBreadcrumbs = Enablement; }
    void SetPageFaultEnablement(D3D12_DRED_ENABLEMENT Enablement) override { m_pageFault = Enablement; }
    void SetWatsonDumpEnablement(D3D12_DRED_ENABLEMENT Enablement) override { m_watsonDump = Enablement; }
    void SetBreadcrumbContextEnablement(D3D12_DRED_ENABLEMENT Enablement) override { m_breadcrumbContext = Enablement; }

    D3D12_DRED_ENABLEMENT GetAutoBreadcrumbsEnablement() const noexcept { return m_autoBreadcrumbs; }
    D3D12_DRED_ENABLEMENT GetPageFaultEnablement() const noexcept { return m_pageFault; }
    D3D12_DRED_ENABLEMENT GetBreadcrumbContextEnablement() const noexcept { return m_breadcrumbContext; }
};

class PrismD3D12DeviceRemovedExtendedDataImpl : public ID3D12DeviceRemovedExtendedData2 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };

public:
    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_ID3D12DeviceRemovedExtendedData ||
            riid == OFFICIAL_IID_ID3D12DeviceRemovedExtendedData1 ||
            riid == OFFICIAL_IID_ID3D12DeviceRemovedExtendedData2) {
            *ppv = static_cast<ID3D12DeviceRemovedExtendedData2*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }
    HRESULT GetAutoBreadcrumbsOutput(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT* pOutput) override {
        if (!pOutput) return E_INVALIDARG;
        pOutput->pHeadAutoBreadcrumbNode = nullptr;
        return S_OK;
    }
    HRESULT GetPageFaultAllocationOutput(D3D12_DRED_PAGE_FAULT_OUTPUT* pOutput) override {
        if (!pOutput) return E_INVALIDARG;
        pOutput->PageFaultVA = 0;
        pOutput->pHeadExistingAllocationNode = nullptr;
        pOutput->pHeadRecentFreedAllocationNode = nullptr;
        return S_OK;
    }
    HRESULT GetAutoBreadcrumbsOutput1(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1* pOutput) override {
        if (!pOutput) return E_INVALIDARG;
        pOutput->pHeadAutoBreadcrumbNode = nullptr;
        return S_OK;
    }
    HRESULT GetPageFaultAllocationOutput1(D3D12_DRED_PAGE_FAULT_OUTPUT1* pOutput) override {
        if (!pOutput) return E_INVALIDARG;
        pOutput->PageFaultVA = 0;
        pOutput->pHeadExistingAllocationNode = nullptr;
        pOutput->pHeadRecentFreedAllocationNode = nullptr;
        return S_OK;
    }
    HRESULT GetPageFaultAllocationOutput2(D3D12_DRED_PAGE_FAULT_OUTPUT2* pOutput) override {
        if (!pOutput) return E_INVALIDARG;
        pOutput->PageFaultVA = 0;
        pOutput->pHeadExistingAllocationNode = nullptr;
        pOutput->pHeadRecentFreedAllocationNode = nullptr;
        pOutput->PageFaultFlags = D3D12_DRED_PAGE_FAULT_FLAGS_NONE;
        return S_OK;
    }
    D3D12_DRED_DEVICE_STATE GetDeviceState() override {
        return D3D12_DRED_DEVICE_STATE_UNKNOWN;
    }
};

class PrismD3D12Device14CanonicalImpl : public ID3D12Device76 {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    ComPtr<ID3D12Device>  m_innerDevice;

public:
    PrismD3D12Device14CanonicalImpl() {
        D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_2, IID_ID3D12Device, m_innerDevice.PutVoid());
    }

    int32_t QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == IID_ID3D12Object ||
            riid == IID_ID3D12Device ||
            riid == OFFICIAL_IID_ID3D12Device ||
            riid == OFFICIAL_IID_ID3D12Device1 ||
            riid == OFFICIAL_IID_ID3D12Device4 ||
            riid == OFFICIAL_IID_ID3D12Device5 ||
            riid == OFFICIAL_IID_ID3D12Device8 ||
            riid == OFFICIAL_IID_ID3D12Device9 ||
            riid == OFFICIAL_IID_ID3D12Device10 ||
            riid == OFFICIAL_IID_ID3D12Device11 ||
            riid == OFFICIAL_IID_ID3D12Device12 ||
            riid == OFFICIAL_IID_ID3D12Device13 ||
            riid == OFFICIAL_IID_ID3D12Device14 ||
            riid == OFFICIAL_IID_ID3D12Device14Alt ||
            riid == OFFICIAL_IID_ID3D12Device15 ||
            riid == OFFICIAL_IID_ID3D12Device16 ||
            riid == OFFICIAL_IID_ID3D12Device17 ||
            riid == OFFICIAL_IID_ID3D12Device18 ||
            riid == OFFICIAL_IID_ID3D12Device19 ||
            riid == OFFICIAL_IID_ID3D12Device20 ||
            riid == OFFICIAL_IID_ID3D12Device21 ||
            riid == OFFICIAL_IID_ID3D12Device22 ||
            riid == OFFICIAL_IID_ID3D12Device23 ||
            riid == OFFICIAL_IID_ID3D12Device24 ||
            riid == IID_ID3D12Device24 ||
            riid == OFFICIAL_IID_ID3D12Device25 ||
            riid == IID_ID3D12Device25 ||
            riid == OFFICIAL_IID_ID3D12Device26 ||
            riid == IID_ID3D12Device26 ||
            riid == OFFICIAL_IID_ID3D12Device27 ||
            riid == IID_ID3D12Device27 ||
            riid == OFFICIAL_IID_ID3D12Device28 ||
            riid == IID_ID3D12Device28 ||
            riid == OFFICIAL_IID_ID3D12Device29 ||
            riid == IID_ID3D12Device29 ||
            riid == OFFICIAL_IID_ID3D12Device30 ||
            riid == IID_ID3D12Device30 ||
            riid == OFFICIAL_IID_ID3D12Device31 ||
            riid == IID_ID3D12Device31 ||
            riid == OFFICIAL_IID_ID3D12Device32 ||
            riid == IID_ID3D12Device32 ||
            riid == OFFICIAL_IID_ID3D12Device33 ||
            riid == IID_ID3D12Device33 ||
            riid == OFFICIAL_IID_ID3D12Device34 ||
            riid == IID_ID3D12Device34 ||
            riid == OFFICIAL_IID_ID3D12Device35 ||
            riid == IID_ID3D12Device35 ||
            riid == OFFICIAL_IID_ID3D12Device36 ||
            riid == IID_ID3D12Device36 ||
            riid == OFFICIAL_IID_ID3D12Device37 ||
            riid == IID_ID3D12Device37 ||
            riid == OFFICIAL_IID_ID3D12Device38 ||
            riid == IID_ID3D12Device38 ||
            riid == OFFICIAL_IID_ID3D12Device39 ||
            riid == IID_ID3D12Device39 ||
            riid == OFFICIAL_IID_ID3D12Device40 ||
            riid == IID_ID3D12Device40 ||
            riid == OFFICIAL_IID_ID3D12Device41 ||
            riid == IID_ID3D12Device41 ||
            riid == OFFICIAL_IID_ID3D12Device42 ||
            riid == IID_ID3D12Device42 ||
            riid == OFFICIAL_IID_ID3D12Device43 ||
            riid == IID_ID3D12Device43 ||
            riid == OFFICIAL_IID_ID3D12Device44 ||
            riid == IID_ID3D12Device44 ||
            riid == OFFICIAL_IID_ID3D12Device45 ||
            riid == IID_ID3D12Device45 ||
            riid == OFFICIAL_IID_ID3D12Device46 ||
            riid == IID_ID3D12Device46 ||
            riid == OFFICIAL_IID_ID3D12Device47 ||
            riid == IID_ID3D12Device47 ||
            riid == OFFICIAL_IID_ID3D12Device48 ||
            riid == IID_ID3D12Device48 ||
            riid == OFFICIAL_IID_ID3D12Device49 ||
            riid == IID_ID3D12Device49 ||
            riid == OFFICIAL_IID_ID3D12Device50 ||
            riid == IID_ID3D12Device50 ||
            riid == OFFICIAL_IID_ID3D12Device51 ||
            riid == IID_ID3D12Device51 ||
            riid == OFFICIAL_IID_ID3D12Device52 ||
            riid == IID_ID3D12Device52 ||
            riid == OFFICIAL_IID_ID3D12Device53 ||
            riid == IID_ID3D12Device53 ||
            riid == OFFICIAL_IID_ID3D12Device54 ||
            riid == IID_ID3D12Device54 ||
            riid == OFFICIAL_IID_ID3D12Device55 ||
            riid == IID_ID3D12Device55 ||
            riid == OFFICIAL_IID_ID3D12Device56 ||
            riid == IID_ID3D12Device56 ||
            riid == OFFICIAL_IID_ID3D12Device57 ||
            riid == IID_ID3D12Device57 ||
            riid == OFFICIAL_IID_ID3D12Device58 ||
            riid == IID_ID3D12Device58 ||
            riid == OFFICIAL_IID_ID3D12Device59 ||
            riid == IID_ID3D12Device59 ||
            riid == OFFICIAL_IID_ID3D12Device60 ||
            riid == IID_ID3D12Device60 ||
            riid == OFFICIAL_IID_ID3D12Device61 ||
            riid == IID_ID3D12Device61 ||
            riid == OFFICIAL_IID_ID3D12Device62 ||
            riid == IID_ID3D12Device62 ||
            riid == OFFICIAL_IID_ID3D12Device63 ||
            riid == IID_ID3D12Device63 ||
            riid == OFFICIAL_IID_ID3D12Device64 ||
            riid == IID_ID3D12Device64 ||
            riid == OFFICIAL_IID_ID3D12Device65 ||
            riid == IID_ID3D12Device65 ||
            riid == OFFICIAL_IID_ID3D12Device66 ||
            riid == IID_ID3D12Device66 ||
            riid == OFFICIAL_IID_ID3D12Device67 ||
            riid == IID_ID3D12Device67 ||
            riid == OFFICIAL_IID_ID3D12Device68 ||
            riid == IID_ID3D12Device68 ||
            riid == OFFICIAL_IID_ID3D12Device69 ||
            riid == IID_ID3D12Device69 ||
            riid == OFFICIAL_IID_ID3D12Device70 ||
            riid == IID_ID3D12Device70 ||
            riid == OFFICIAL_IID_ID3D12Device71 ||
            riid == IID_ID3D12Device71 ||
            riid == OFFICIAL_IID_ID3D12Device72 ||
            riid == IID_ID3D12Device72 ||
            riid == OFFICIAL_IID_ID3D12Device73 ||
            riid == IID_ID3D12Device73 ||
            riid == OFFICIAL_IID_ID3D12Device74 ||
            riid == IID_ID3D12Device74 ||
            riid == OFFICIAL_IID_ID3D12Device75 ||
            riid == IID_ID3D12Device75 ||
            riid == OFFICIAL_IID_ID3D12Device76 ||
            riid == IID_ID3D12Device76) {
            *ppv = static_cast<ID3D12Device76*>(this);
            AddRef();
            return S_OK;
        }
        // Support QueryInterface to IDXGIDevice / IDXGIDevice4 for DXGI interop!
        if (riid == IID_IDXGIDevice ||
            riid == Dxgi16::OFFICIAL_IID_IDXGIDevice ||
            riid == Dxgi16::OFFICIAL_IID_IDXGIDevice4) {
            auto* pDxgiDev = new Dxgi16::PrismDXGIDevice4Impl();
            return pDxgiDev->QueryInterface(riid, ppv);
        }
        // Support DRED 1.0, 1.1, and 2.0 query interfaces
        if (riid == OFFICIAL_IID_ID3D12DeviceRemovedExtendedData ||
            riid == OFFICIAL_IID_ID3D12DeviceRemovedExtendedData1 ||
            riid == OFFICIAL_IID_ID3D12DeviceRemovedExtendedData2) {
            auto* pDred = new PrismD3D12DeviceRemovedExtendedDataImpl();
            HRESULT hr = pDred->QueryInterface(riid, ppv);
            pDred->Release();
            return hr;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }

    int32_t GetPrivateData(const IID&, uint32_t*, void*) override { return S_OK; }
    int32_t SetPrivateData(const IID&, uint32_t, const void*) override { return S_OK; }
    int32_t SetPrivateDataInterface(const IID&, const IUnknown*) override { return S_OK; }
    int32_t SetName(const wchar_t*) override { return S_OK; }

    uint32_t GetNodeCount() override { return 1u; }

    HRESULT CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC* pDesc, const IID& riid, void** ppCommandQueue) override {
        return m_innerDevice->CreateCommandQueue(pDesc, riid, ppCommandQueue);
    }
    HRESULT CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, const IID& riid, void** ppCommandAllocator) override {
        return m_innerDevice->CreateCommandAllocator(type, riid, ppCommandAllocator);
    }
    HRESULT CreateGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc, const IID& riid, void** ppPipelineState) override {
        return m_innerDevice->CreateGraphicsPipelineState(pDesc, riid, ppPipelineState);
    }
    HRESULT CreateComputePipelineState(const void*, const IID&, void** ppPipelineState) override {
        if (!ppPipelineState) return E_INVALIDARG;
        D3D12_GRAPHICS_PIPELINE_STATE_DESC dummy{};
        return m_innerDevice->CreateGraphicsPipelineState(&dummy, IID_ID3D12PipelineState, ppPipelineState);
    }
    HRESULT CreateCommandList(uint32_t nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pCommandAllocator, ID3D12PipelineState* pInitialState, const IID& riid, void** ppCommandList) override {
        return m_innerDevice->CreateCommandList(nodeMask, type, pCommandAllocator, pInitialState, riid, ppCommandList);
    }

    HRESULT CheckFeatureSupport(D3D12_FEATURE_ABI Feature, void* pData, uint32_t Size) override {
        if (!pData) return E_INVALIDARG;
        switch (Feature) {
            case D3D12_FEATURE_ABI_D3D12_OPTIONS: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS_ABI)) return E_INVALIDARG;
                auto* o = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS_ABI*>(pData);
                std::memset(o, 0, sizeof(*o));
                o->DoublePrecisionFloatShaderOps = 1;
                o->OutputMergerLogicOp           = 1;
                o->TiledResourcesTier            = 4u; // Tier 4
                o->ResourceBindingTier           = 3u; // Tier 3 Bindless
                o->TypedUAVLoadAdditionalFormats = 1;
                o->ROVsSupported                 = 1;
                o->ConservativeRasterizationTier = 3u; // Tier 3
                o->MaxGPUVirtualAddressBitsPerResource = 48u;
                o->StandardSwizzle64KBSupported  = 1;
                o->ResourceHeapTier              = 2u; // Tier 2
                return S_OK;
            }
            case D3D12_FEATURE_ABI_SHADER_MODEL: {
                if (Size < sizeof(D3D12_FEATURE_DATA_SHADER_MODEL_ABI)) return E_INVALIDARG;
                auto* sm = static_cast<D3D12_FEATURE_DATA_SHADER_MODEL_ABI*>(pData);
                sm->HighestShaderModel = 0x69u; // SM 6.9
                return S_OK;
            }
            case D3D12_FEATURE_ABI_ROOT_SIGNATURE: {
                if (Size < sizeof(D3D12_FEATURE_DATA_ROOT_SIGNATURE_ABI)) return E_INVALIDARG;
                auto* rs = static_cast<D3D12_FEATURE_DATA_ROOT_SIGNATURE_ABI*>(pData);
                rs->HighestVersion = 0x3u; // RootSignature 1.2
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS1: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS1_ABI)) return E_INVALIDARG;
                auto* o1 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS1_ABI*>(pData);
                o1->WaveOps                        = 1;
                o1->WaveLaneCountMin               = 32u;
                o1->WaveLaneCountMax               = 32u;
                o1->TotalLaneCount                 = 1024u;
                o1->ExpandedComputeResourceStates  = 1;
                o1->Int64ShaderOps                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS5: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS5_ABI)) return E_INVALIDARG;
                auto* o5 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS5_ABI*>(pData);
                o5->SRVOnlyTiledResourceTier3 = 1;
                o5->RenderPassesTier          = 2u;  // Tier 2
                o5->RaytracingTier            = 11u; // Tier 1.1
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS6: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS6_ABI)) return E_INVALIDARG;
                auto* o6 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS6_ABI*>(pData);
                o6->AdditionalShadingRatesSupported = 1;
                o6->PerPrimitiveShadingRateSupportedWithViewportIndexing = 1;
                o6->VariableShadingRateTier         = 2u;  // Tier 2
                o6->ShadingRateImageTileSize        = 16u;
                o6->BackgroundProcessingSupported   = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS7: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS7_ABI)) return E_INVALIDARG;
                auto* o7 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS7_ABI*>(pData);
                o7->MeshShaderTier      = 10u;  // Tier 1
                o7->SamplerFeedbackTier = 100u; // Tier 1.0
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS12: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS12_ABI)) return E_INVALIDARG;
                auto* o12 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS12_ABI*>(pData);
                o12->MSPrimitivesPipelineStatisticIncludesCulledPrimitives = 1u;
                o12->EnhancedBarriersSupported     = 1;
                o12->RelaxedFormatCastingSupported = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS13: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS13_ABI)) return E_INVALIDARG;
                auto* o13 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS13_ABI*>(pData);
                o13->UnrestrictedBufferTextureCopyPitchSupported = 1;
                o13->UnrestrictedVertexElementAlignmentSupported = 1;
                o13->InvertedViewportHeightFlipsYSupported       = 1;
                o13->InvertedViewportDepthFlipsZSupported        = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS14: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS14_ABI)) return E_INVALIDARG;
                auto* o14 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS14_ABI*>(pData);
                o14->AdvancedTextureOpsSupported                     = 1;
                o14->WriteableMSAATexturesSupported                  = 1;
                o14->IndependentFrontAndBackStencilRefMaskSupported = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS15: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS15_ABI)) return E_INVALIDARG;
                auto* o15 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS15_ABI*>(pData);
                o15->TriangleFanSupported       = 1;
                o15->DynamicIndexBufferStripCut = D3D12_DYNAMIC_INDEX_BUFFER_STRIP_CUT_SUPPORTED_ALL;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS16: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS16_ABI)) return E_INVALIDARG;
                auto* o16 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS16_ABI*>(pData);
                o16->DynamicDepthBiasSupported = 1;
                o16->GPUUploadHeapSupported    = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS17: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS17_ABI)) return E_INVALIDARG;
                auto* o17 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS17_ABI*>(pData);
                o17->NonNormalizedCoordinateSamplersSupported = 1;
                o17->ManualWriteTrackingResourceSupported     = 1;
                o17->InvertedDepthRangesSupported             = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS18: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS18_ABI)) return E_INVALIDARG;
                auto* o18 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS18_ABI*>(pData);
                o18->RenderPassesTier          = 2u;
                o18->AdvancedBlendOpsSupported = 1;
                o18->RenderPassesValid         = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS19: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS19_ABI)) return E_INVALIDARG;
                auto* o19 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS19_ABI*>(pData);
                o19->MipLevelOffsetsSupported                      = 1;
                o19->HalfFloatPrecisionSupported                   = 1;
                o19->MismatchingOutputDimensionsSupported          = 1;
                o19->SupportedSampleCountsWithNoOutputs            = 1u;
                o19->PointSamplingAddressesNeverRoundUp            = 1;
                o19->RasterizerDesc2Supported                      = 1;
                o19->NarrowQuadrilateralLinesSupported             = 1;
                o19->AnisoFilterWithPointMipSupported              = 1;
                o19->MaxSamplerDescriptorHeapSize                  = 2048u;
                o19->MaxSamplerDescriptorHeapSizeWithStaticSamplers = 2048u;
                o19->MaxViewDescriptorHeapSize                     = 1000000u;
                o19->ComputeOnlyCustomHeapSupported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS20: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS20_ABI)) return E_INVALIDARG;
                auto* o20 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS20_ABI*>(pData);
                o20->ProgrammableSamplePositionsTier = 1;
                o20->SampleLocationsTier             = 2; // Tier 2
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS21: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS21_ABI)) return E_INVALIDARG;
                auto* o21 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS21_ABI*>(pData);
                o21->WorkGraphsTier                     = 11u; // Tier 1.1
                o21->ExecuteIndirectTier                = 11u; // Tier 1.1
                o21->SampleCmpGradientAndBiasSupported  = 1;
                o21->ExtendedCommandInfoSupported       = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS22: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS22_ABI)) return E_INVALIDARG;
                auto* o22 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS22_ABI*>(pData);
                o22->Max1DDispatchSize     = 1073741824u; // 1G dispatches (modern 1D limit)
                o22->Max1DDispatchMeshSize = 1073741824u; // 1G dispatches (modern 1D mesh limit)
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS23: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS23_ABI)) return E_INVALIDARG;
                auto* o23 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS23_ABI*>(pData);
                o23->DynamicDepthBiasClampSupported      = 1;
                o23->DynamicIndexBufferStripCutSupported = 1;
                o23->SubobjectCreationSupported          = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS24: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS24_ABI)) return E_INVALIDARG;
                auto* o24 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS24_ABI*>(pData);
                o24->WorkGraphsTier             = 11u; // Tier 1.1
                o24->GenericProgramsSupported   = 1;
                o24->SubobjectCreationSupported = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS25: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS25_ABI)) return E_INVALIDARG;
                auto* o25 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS25_ABI*>(pData);
                o25->Max1DDispatchSize           = 1073741824u; // 1G dispatches
                o25->Max1DDispatchMeshSize       = 4194303u;    // D3D12_MS_DISPATCH_MAX_THREAD_GROUPS_PER_GRID
                o25->WaveMatrixSupported         = 1;
                o25->CooperativeVectorsSupported = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS26: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS26_ABI)) return E_INVALIDARG;
                auto* o26 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS26_ABI*>(pData);
                o26->CpuTimelineQueryResolutionSupported = 1;
                o26->PeriodicTrimNotificationsSupported  = 1;
                o26->ByteOffsetBufferViewsSupported      = 1;
                o26->RelaxedCastableFormatsSupported     = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS27: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS27_ABI)) return E_INVALIDARG;
                auto* o27 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS27_ABI*>(pData);
                o27->WorkGraphsTier                 = 11u; // Tier 1.1
                o27->DynamicNodeExpansionSupported  = 1;
                o27->MultiTierWorkGraphsSupported   = 1;
                o27->AmplifiedMeshDispatchSupported = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS28: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS28_ABI)) return E_INVALIDARG;
                auto* o28 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS28_ABI*>(pData);
                o28->WorkGraphsTier                       = 12u; // Tier 1.2
                o28->ComputeOnlyDeviceSupported           = 1;
                o28->IndependentSamplerMipLevelsSupported = 1;
                o28->UnboundedStreamOutputSupported       = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS29: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS29_ABI)) return E_INVALIDARG;
                auto* o29 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS29_ABI*>(pData);
                o29->WorkGraphsTier                    = 12u; // Tier 1.2
                o29->GPUUploadHeapSupported            = 1;
                o29->DynamicDepthBiasClampSupported    = 1;
                o29->BackingMemoryCustomPoolSupported   = 1;
                o29->ComputeOnlyDeviceSupported        = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS30: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS30_ABI)) return E_INVALIDARG;
                auto* o30 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS30_ABI*>(pData);
                o30->WorkGraphsTier                              = 13u; // Tier 1.3
                o30->NodeOutputRecordsSupported                  = 1;
                o30->DirectProgramRecordAllocationSupported      = 1;
                o30->WorkGraphBackingMemoryVirtualRemapSupported = 1;
                o30->ShaderExecutionReorderingSupported          = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS31: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS31_ABI)) return E_INVALIDARG;
                auto* o31 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS31_ABI*>(pData);
                o31->WorkGraphsTier                              = 14u; // Tier 2.0/2.1
                o31->DynamicDepthBoundsSupported                 = 1;
                o31->EnhancedWaveMatrixMultiplySupported         = 1;
                o31->WaveMatrixMultiplyTiers                     = 3u; // Tier 3
                o31->ProgrammaticWorkGraphRecordBindingSupported = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS32: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS32_ABI)) return E_INVALIDARG;
                auto* o32 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS32_ABI*>(pData);
                o32->WorkGraphsTier                          = 15u; // Tier 2.2
                o32->DynamicGlobalRootSignatureSupported     = 1;
                o32->AsyncWorkGraphDispatchSupported         = 1;
                o32->MaxWorkGraphConcurrencyGroups           = 64u;
                o32->EnhancedBarrierDynamicAliasingSupported = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS33: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS33_ABI)) return E_INVALIDARG;
                auto* o33 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS33_ABI*>(pData);
                o33->WorkGraphsTier                         = 16u; // Tier 3.0
                o33->AutonomousMemoryAllocationSupported     = 1;
                o33->DynamicNodeExpansionSupported          = 1;
                o33->MaxWorkGraphConcurrencyGroups          = 128u;
                o33->WaveMatrixMultiplyAccumulateSupported  = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS34: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS34_ABI)) return E_INVALIDARG;
                auto* o34 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS34_ABI*>(pData);
                o34->WorkGraphsTier                         = 17u; // Tier 3.1
                o34->CooperativeMatrixMultiplySupported     = 1;
                o34->MultiQueueWorkGraphDispatchSupported   = 1;
                o34->DynamicClusterExpansionSupported       = 1;
                o34->MaxWorkGraphConcurrencyGroups          = 256u;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS35: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS35_ABI)) return E_INVALIDARG;
                auto* o35 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS35_ABI*>(pData);
                o35->WorkGraphsTier                         = 18u; // Tier 3.2
                o35->CooperativeMatrixMultiply128Supported  = 1;
                o35->FP8CooperativeMatrixSupported          = 1;
                o35->MultiQueueDynamicClusterExpansionSupported = 1;
                o35->MaxWorkGraphConcurrencyGroups          = 512u;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS36: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS36_ABI)) return E_INVALIDARG;
                auto* o36 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS36_ABI*>(pData);
                o36->WorkGraphsTier                         = 19u; // Tier 3.3
                o36->CooperativeMatrixMultiply256Supported  = 1;
                o36->SparseTensorCoreAccelerationSupported  = 1;
                o36->DynamicClusterExpansionTier4Supported  = 1;
                o36->MaxWorkGraphConcurrencyGroups          = 1024u;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS37: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS37_ABI)) return E_INVALIDARG;
                auto* o37 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS37_ABI*>(pData);
                o37->WorkGraphsTier                          = 20u; // Tier 3.4
                o37->CooperativeMatrixMultiply512Supported   = 1;
                o37->SubByteTensorQuantizationSupported      = 1;
                o37->DynamicClusterExpansionTier5Supported   = 1;
                o37->MaxWorkGraphConcurrencyGroups           = 2048u;
                o37->AsynchronousTensorAccumulationSupported = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS38: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS38_ABI)) return E_INVALIDARG;
                auto* o38 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS38_ABI*>(pData);
                o38->WorkGraphsTier                              = 21u; // Tier 3.5
                o38->CooperativeMatrixMultiply1024Supported      = 1;
                o38->SubByteMicroscalingTensorFormatsSupported   = 1;
                o38->DynamicClusterExpansionTier6Supported       = 1;
                o38->MaxWorkGraphConcurrencyGroups               = 4096u;
                o38->TilePipeliningStagesSupported               = 8u;
                o38->AsynchronousTensorAccumulationSupported     = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS39: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS39_ABI)) return E_INVALIDARG;
                auto* o39 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS39_ABI*>(pData);
                o39->WorkGraphsTier                                 = 22u; // Tier 3.6
                o39->CooperativeMatrixMultiply2048Supported         = 1;
                o39->SubByteMicroscalingTensorFormatsV2Supported    = 1;
                o39->DynamicClusterExpansionTier7Supported          = 1;
                o39->MaxWorkGraphConcurrencyGroups                  = 8192u;
                o39->TilePipeliningStagesSupported                  = 16u;
                o39->AutonomousGraphFeedbackLoopsSupported          = 1;
                o39->AsynchronousTensorAccumulationSupported        = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS40: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS40_ABI)) return E_INVALIDARG;
                auto* o40 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS40_ABI*>(pData);
                o40->WorkGraphsTier                                 = 23u; // Tier 3.7
                o40->CooperativeMatrixMultiply4096Supported         = 1;
                o40->SubByteMicroscalingTensorFormatsV3Supported    = 1;
                o40->DynamicClusterExpansionTier8Supported          = 1;
                o40->MaxWorkGraphConcurrencyGroups                  = 16384u;
                o40->TilePipeliningStagesSupported                  = 32u;
                o40->AutonomousGraphRecursionSupported              = 1;
                o40->AsynchronousTensorPipelineFusionSupported      = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS41: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS41_ABI)) return E_INVALIDARG;
                auto* o41 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS41_ABI*>(pData);
                o41->WorkGraphsTier                                 = 24u; // Tier 3.8
                o41->CooperativeMatrixMultiply8192Supported         = 1;
                o41->SubByteMicroscalingTensorFormatsV4Supported    = 1;
                o41->DynamicClusterExpansionTier9Supported          = 1;
                o41->MaxWorkGraphConcurrencyGroups                  = 32768u;
                o41->TilePipeliningStagesSupported                  = 64u;
                o41->AutonomousGraphRecursionSupported              = 1;
                o41->AsynchronousTensorPipelineFusionSupported      = 1;
                o41->WorkGraphMeshShaderPipeliningSupported         = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS42: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS42_ABI)) return E_INVALIDARG;
                auto* o42 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS42_ABI*>(pData);
                o42->WorkGraphsTier                                 = 25u; // Tier 3.9
                o42->CooperativeMatrixMultiply16384Supported        = 1;
                o42->SubByteMicroscalingTensorFormatsV5Supported    = 1;
                o42->DynamicClusterExpansionTier10Supported         = 1;
                o42->MaxWorkGraphConcurrencyGroups                  = 65536u;
                o42->TilePipeliningStagesSupported                  = 128u;
                o42->AutonomousGraphRecursionTier2Supported         = 1;
                o42->MultiQueueTensorPipelineFusionSupported        = 1;
                o42->WorkGraphMeshShaderPipeliningTier2Supported    = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS43: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS43_ABI)) return E_INVALIDARG;
                auto* o43 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS43_ABI*>(pData);
                o43->WorkGraphsTier                                 = 26u; // Tier 4.0
                o43->CooperativeMatrixMultiply32768Supported        = 1;
                o43->SubByteMicroscalingTensorFormatsV6Supported    = 1;
                o43->DynamicClusterExpansionTier11Supported         = 1;
                o43->MaxWorkGraphConcurrencyGroups                  = 131072u;
                o43->TilePipeliningStagesSupported                  = 256u;
                o43->AutonomousGraphRecursionTier3Supported         = 1;
                o43->MultiQueueTensorPipelineFusionTier2Supported   = 1;
                o43->WorkGraphMeshShaderPipeliningTier3Supported    = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS44: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS44_ABI)) return E_INVALIDARG;
                auto* o44 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS44_ABI*>(pData);
                o44->WorkGraphsTier                                 = 27u; // Tier 4.1
                o44->CooperativeMatrixMultiply65536Supported        = 1;
                o44->SubByteMicroscopicFormatsV7Supported           = 1;
                o44->DynamicClusterExpansionTier12Supported         = 1;
                o44->MaxWorkGraphConcurrencyGroups                  = 262144u;
                o44->TilePipeliningStagesSupported                  = 512u;
                o44->AutonomousGraphRecursionTier4Supported         = 1;
                o44->MultiQueueTensorPipelineFusionTier3Supported   = 1;
                o44->WorkGraphMeshShaderPipeliningTier4Supported    = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS45: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS45_ABI)) return E_INVALIDARG;
                auto* o45 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS45_ABI*>(pData);
                o45->WorkGraphsTier                                 = 28u; // Tier 5.0
                o45->CooperativeMatrixMultiply131072Supported       = 1;
                o45->SubByteMicroscopicFormatsV8Supported           = 1;
                o45->DynamicClusterExpansionTier13Supported         = 1;
                o45->MaxWorkGraphConcurrencyGroups                  = 524288u;
                o45->TilePipeliningStagesSupported                  = 1024u;
                o45->AutonomousGraphRecursionTier5Supported         = 1;
                o45->MultiQueueTensorPipelineFusionTier4Supported   = 1;
                o45->WorkGraphMeshShaderPipeliningTier5Supported    = 1;
                o45->SparseTensorBlockAccelerationTier1Supported   = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS46: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS46_ABI)) return E_INVALIDARG;
                auto* o46 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS46_ABI*>(pData);
                o46->WorkGraphsTier                                 = 29u; // Tier 5.1
                o46->CooperativeMatrixMultiply262144Supported       = 1;
                o46->SubByteMicroscopicFormatsV9Supported           = 1;
                o46->DynamicClusterExpansionTier14Supported         = 1;
                o46->MaxWorkGraphConcurrencyGroups                  = 1048576u;
                o46->TilePipeliningStagesSupported                  = 2048u;
                o46->AutonomousGraphRecursionTier6Supported         = 1;
                o46->MultiQueueTensorPipelineFusionTier5Supported   = 1;
                o46->WorkGraphMeshShaderPipeliningTier6Supported    = 1;
                o46->SparseTensorBlockAccelerationTier2Supported   = 1;
                o46->DeterministicTensorReductionTier1Supported     = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS47: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS47_ABI)) return E_INVALIDARG;
                auto* o47 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS47_ABI*>(pData);
                o47->WorkGraphsTier                                 = 30u; // Tier 5.2
                o47->CooperativeMatrixMultiply524288Supported       = 1;
                o47->SubByteMicroscopicFormatsV10Supported          = 1;
                o47->DynamicClusterExpansionTier15Supported         = 1;
                o47->MaxWorkGraphConcurrencyGroups                  = 2097152u; // 2M Concurrency groups
                o47->TilePipeliningStagesSupported                  = 4096u;
                o47->AutonomousGraphRecursionTier7Supported         = 1;
                o47->MultiQueueTensorPipelineFusionTier6Supported   = 1;
                o47->WorkGraphMeshShaderPipeliningTier7Supported    = 1;
                o47->SparseTensorBlockAccelerationTier3Supported   = 1;
                o47->DeterministicTensorReductionTier2Supported     = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS48: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS48_ABI)) return E_INVALIDARG;
                auto* o48 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS48_ABI*>(pData);
                o48->WorkGraphsTier                                 = 31u; // Tier 5.3
                o48->CooperativeMatrixMultiply1048576Supported      = 1;
                o48->SubByteMicroscopicFormatsV11Supported          = 1;
                o48->DynamicClusterExpansionTier16Supported         = 1;
                o48->MaxWorkGraphConcurrencyGroups                  = 4194304u; // 4M Concurrency groups
                o48->TilePipeliningStagesSupported                  = 8192u;
                o48->AutonomousGraphRecursionTier8Supported         = 1;
                o48->MultiQueueTensorPipelineFusionTier7Supported   = 1;
                o48->WorkGraphMeshShaderPipeliningTier8Supported    = 1;
                o48->SparseTensorBlockAccelerationTier4Supported   = 1;
                o48->DeterministicTensorReductionTier3Supported     = 1;
                o48->HyperQuantizationTier2Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS49: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS49_ABI)) return E_INVALIDARG;
                auto* o49 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS49_ABI*>(pData);
                o49->WorkGraphsTier                                 = 32u; // Tier 5.4
                o49->CooperativeMatrixMultiply2097152Supported      = 1;
                o49->SubByteMicroscopicFormatsV12Supported          = 1;
                o49->DynamicClusterExpansionTier17Supported         = 1;
                o49->MaxWorkGraphConcurrencyGroups                  = 8388608u; // 8M Concurrency groups
                o49->TilePipeliningStagesSupported                  = 16384u;
                o49->AutonomousGraphRecursionTier9Supported         = 1;
                o49->MultiQueueTensorPipelineFusionTier8Supported   = 1;
                o49->WorkGraphMeshShaderPipeliningTier9Supported    = 1;
                o49->SparseTensorBlockAccelerationTier5Supported   = 1;
                o49->DeterministicTensorReductionTier4Supported     = 1;
                o49->HyperQuantizationTier3Supported                = 1;
                o49->SparseClusterTier2Supported                    = 1;
                o49->MultiQueueWorkGraphSyncSupported               = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS50: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS50_ABI)) return E_INVALIDARG;
                auto* o50 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS50_ABI*>(pData);
                o50->WorkGraphsTier                                 = 33u; // Tier 5.5
                o50->CooperativeMatrixMultiply4194304Supported      = 1;
                o50->SubByteMicroscopicFormatsV13Supported          = 1;
                o50->DynamicClusterExpansionTier18Supported         = 1;
                o50->MaxWorkGraphConcurrencyGroups                  = 16777216u; // 16M Concurrency groups
                o50->TilePipeliningStagesSupported                  = 32768u;
                o50->AutonomousGraphRecursionTier10Supported        = 1;
                o50->MultiQueueTensorPipelineFusionTier9Supported   = 1;
                o50->WorkGraphMeshShaderPipeliningTier10Supported   = 1;
                o50->SparseTensorBlockAccelerationTier6Supported   = 1;
                o50->DeterministicTensorReductionTier5Supported     = 1;
                o50->HyperQuantizationTier4Supported                = 1;
                o50->SparseClusterTier3Supported                    = 1;
                o50->MultiQueueWorkGraphSyncTier2Supported          = 1;
                o50->AsynchronousKernelDispatchTier3Supported       = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS51: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS51_ABI)) return E_INVALIDARG;
                auto* o51 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS51_ABI*>(pData);
                o51->WorkGraphsTier                                 = 34u; // Tier 5.6
                o51->CooperativeMatrixMultiply8388608Supported      = 1;
                o51->SubByteMicroscopicFormatsV14Supported          = 1;
                o51->DynamicClusterExpansionTier19Supported         = 1;
                o51->MaxWorkGraphConcurrencyGroups                  = 33554432u; // 32M Concurrency groups
                o51->TilePipeliningStagesSupported                  = 65536u;
                o51->AutonomousGraphRecursionTier11Supported        = 1;
                o51->MultiQueueTensorPipelineFusionTier10Supported  = 1;
                o51->WorkGraphMeshShaderPipeliningTier11Supported   = 1;
                o51->SparseTensorBlockAccelerationTier7Supported    = 1;
                o51->DeterministicTensorReductionTier6Supported     = 1;
                o51->HyperQuantizationTier5Supported                = 1;
                o51->SparseClusterTier4Supported                    = 1;
                o51->MultiQueueWorkGraphSyncTier3Supported          = 1;
                o51->AsynchronousKernelDispatchTier4Supported       = 1;
                o51->NeuralExecutionEngineTier1Supported            = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS52: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS52_ABI)) return E_INVALIDARG;
                auto* o52 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS52_ABI*>(pData);
                o52->WorkGraphsTier                                 = 35u; // Tier 5.7
                o52->CooperativeMatrixMultiply16777216Supported     = 1;
                o52->SubByteMicroscopicFormatsV15Supported          = 1;
                o52->DynamicClusterExpansionTier20Supported         = 1;
                o52->MaxWorkGraphConcurrencyGroups                  = 67108864u; // 64M Concurrency groups
                o52->TilePipeliningStagesSupported                  = 131072u;
                o52->AutonomousGraphRecursionTier12Supported        = 1;
                o52->MultiQueueTensorPipelineFusionTier11Supported  = 1;
                o52->WorkGraphMeshShaderPipeliningTier12Supported   = 1;
                o52->SparseTensorBlockAccelerationTier8Supported    = 1;
                o52->DeterministicTensorReductionTier7Supported     = 1;
                o52->HyperQuantizationTier6Supported                = 1;
                o52->SparseClusterTier5Supported                    = 1;
                o52->MultiQueueWorkGraphSyncTier4Supported          = 1;
                o52->AsynchronousKernelDispatchTier5Supported       = 1;
                o52->NeuralExecutionEngineTier2Supported            = 1;
                o52->AdaptiveTensorCoreTier1Supported               = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS53: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS53_ABI)) return E_INVALIDARG;
                auto* o53 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS53_ABI*>(pData);
                o53->WorkGraphsTier                                 = 36u; // Tier 5.8
                o53->CooperativeMatrixMultiply33554432Supported     = 1;
                o53->SubByteMicroscopicFormatsV16Supported          = 1;
                o53->DynamicClusterExpansionTier21Supported         = 1;
                o53->MaxWorkGraphConcurrencyGroups                  = 134217728u; // 128M Concurrency groups
                o53->TilePipeliningStagesSupported                  = 262144u;
                o53->AutonomousGraphRecursionTier13Supported        = 1;
                o53->MultiQueueTensorPipelineFusionTier12Supported  = 1;
                o53->WorkGraphMeshShaderPipeliningTier13Supported   = 1;
                o53->SparseTensorBlockAccelerationTier9Supported    = 1;
                o53->DeterministicTensorReductionTier8Supported     = 1;
                o53->HyperQuantizationTier7Supported                = 1;
                o53->SparseClusterTier6Supported                    = 1;
                o53->MultiQueueWorkGraphSyncTier5Supported          = 1;
                o53->AsynchronousKernelDispatchTier6Supported       = 1;
                o53->NeuralExecutionEngineTier3Supported            = 1;
                o53->AdaptiveTensorCoreTier2Supported               = 1;
                o53->SovereignSiliconTelemetryTier1Supported        = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS54: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS54_ABI)) return E_INVALIDARG;
                auto* o54 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS54_ABI*>(pData);
                o54->WorkGraphsTier                                 = 37u; // Tier 5.9
                o54->CooperativeMatrixMultiply67108864Supported     = 1;
                o54->SubByteMicroscopicFormatsV17Supported          = 1;
                o54->DynamicClusterExpansionTier22Supported         = 1;
                o54->MaxWorkGraphConcurrencyGroups                  = 268435456u; // 256M Concurrency groups
                o54->TilePipeliningStagesSupported                  = 524288u;
                o54->AutonomousGraphRecursionTier14Supported        = 1;
                o54->MultiQueueTensorPipelineFusionTier13Supported  = 1;
                o54->WorkGraphMeshShaderPipeliningTier14Supported   = 1;
                o54->SparseTensorBlockAccelerationTier10Supported   = 1;
                o54->DeterministicTensorReductionTier9Supported     = 1;
                o54->HyperQuantizationTier8Supported                = 1;
                o54->SparseClusterTier7Supported                    = 1;
                o54->MultiQueueWorkGraphSyncTier6Supported          = 1;
                o54->AsynchronousKernelDispatchTier7Supported       = 1;
                o54->NeuralExecutionEngineTier4Supported            = 1;
                o54->AdaptiveTensorCoreTier3Supported               = 1;
                o54->SovereignSiliconTelemetryTier2Supported        = 1;
                o54->QuantumEmulationTier1Supported                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS55: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS55_ABI)) return E_INVALIDARG;
                auto* o55 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS55_ABI*>(pData);
                o55->WorkGraphsTier                                 = 38u; // Tier 6.0
                o55->CooperativeMatrixMultiply134217728Supported    = 1;
                o55->SubByteMicroscopicFormatsV18Supported          = 1;
                o55->DynamicClusterExpansionTier23Supported         = 1;
                o55->MaxWorkGraphConcurrencyGroups                  = 536870912u; // 512M Concurrency groups
                o55->TilePipeliningStagesSupported                  = 1048576u;
                o55->AutonomousGraphRecursionTier15Supported        = 1;
                o55->MultiQueueTensorPipelineFusionTier14Supported  = 1;
                o55->WorkGraphMeshShaderPipeliningTier15Supported   = 1;
                o55->SparseTensorBlockAccelerationTier11Supported   = 1;
                o55->DeterministicTensorReductionTier10Supported    = 1;
                o55->HyperQuantizationTier9Supported                = 1;
                o55->SparseClusterTier8Supported                    = 1;
                o55->MultiQueueWorkGraphSyncTier7Supported          = 1;
                o55->AsynchronousKernelDispatchTier8Supported       = 1;
                o55->NeuralExecutionEngineTier5Supported            = 1;
                o55->AdaptiveTensorCoreTier4Supported               = 1;
                o55->SovereignSiliconTelemetryTier3Supported        = 1;
                o55->QuantumEmulationTier2Supported                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS56: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS56_ABI)) return E_INVALIDARG;
                auto* o56 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS56_ABI*>(pData);
                o56->WorkGraphsTier                                 = 39u; // Tier 6.1
                o56->CooperativeMatrixMultiply268435456Supported    = 1;
                o56->SubByteMicroscopicFormatsV19Supported          = 1;
                o56->DynamicClusterExpansionTier24Supported         = 1;
                o56->MaxWorkGraphConcurrencyGroups                  = 1073741824u; // 1024M / 1.073B Concurrency groups
                o56->TilePipeliningStagesSupported                  = 2097152u; // 2.097M Stages
                o56->AutonomousGraphRecursionTier16Supported        = 1;
                o56->MultiQueueTensorPipelineFusionTier15Supported  = 1;
                o56->WorkGraphMeshShaderPipeliningTier16Supported   = 1;
                o56->SparseTensorBlockAccelerationTier12Supported   = 1;
                o56->DeterministicTensorReductionTier11Supported    = 1;
                o56->HyperQuantizationTier10Supported               = 1;
                o56->SparseClusterTier9Supported                    = 1;
                o56->MultiQueueWorkGraphSyncTier8Supported          = 1;
                o56->AsynchronousKernelDispatchTier9Supported       = 1;
                o56->NeuralExecutionEngineTier6Supported            = 1;
                o56->AdaptiveTensorCoreTier5Supported               = 1;
                o56->SovereignSiliconTelemetryTier4Supported        = 1;
                o56->QuantumEmulationTier3Supported                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS57: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS57_ABI)) return E_INVALIDARG;
                auto* o57 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS57_ABI*>(pData);
                o57->WorkGraphsTier                                 = 40u; // Tier 6.2
                o57->CooperativeMatrixMultiply536870912Supported    = 1;
                o57->SubByteMicroscopicFormatsV20Supported          = 1;
                o57->DynamicClusterExpansionTier25Supported         = 1;
                o57->MaxWorkGraphConcurrencyGroups                  = 2147483648u; // 2048M / 2.147B Concurrency groups
                o57->TilePipeliningStagesSupported                  = 4194304u; // 4.194M Stages
                o57->AutonomousGraphRecursionTier17Supported        = 1;
                o57->MultiQueueTensorPipelineFusionTier16Supported  = 1;
                o57->WorkGraphMeshShaderPipeliningTier17Supported   = 1;
                o57->SparseTensorBlockAccelerationTier13Supported   = 1;
                o57->DeterministicTensorReductionTier12Supported    = 1;
                o57->HyperQuantizationTier11Supported               = 1;
                o57->SparseClusterTier10Supported                   = 1;
                o57->MultiQueueWorkGraphSyncTier9Supported          = 1;
                o57->AsynchronousKernelDispatchTier10Supported      = 1;
                o57->NeuralExecutionEngineTier7Supported            = 1;
                o57->AdaptiveTensorCoreTier6Supported               = 1;
                o57->SovereignSiliconTelemetryTier5Supported        = 1;
                o57->QuantumEmulationTier4Supported                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS58: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS58_ABI)) return E_INVALIDARG;
                auto* o58 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS58_ABI*>(pData);
                o58->WorkGraphsTier                                 = 41u; // Tier 6.3
                o58->CooperativeMatrixMultiply1073741824Supported   = 1;
                o58->SubByteMicroscopicFormatsV21Supported          = 1;
                o58->DynamicClusterExpansionTier26Supported         = 1;
                o58->MaxWorkGraphConcurrencyGroups                  = 4294967296ULL; // 4096M / 4.294B Concurrency groups
                o58->TilePipeliningStagesSupported                  = 8388608u; // 8.388M Stages
                o58->AutonomousGraphRecursionTier18Supported        = 1;
                o58->MultiQueueTensorPipelineFusionTier17Supported  = 1;
                o58->WorkGraphMeshShaderPipeliningTier18Supported   = 1;
                o58->SparseTensorBlockAccelerationTier14Supported   = 1;
                o58->DeterministicTensorReductionTier13Supported    = 1;
                o58->HyperQuantizationTier12Supported               = 1;
                o58->SparseClusterTier11Supported                  = 1;
                o58->MultiQueueWorkGraphSyncTier10Supported         = 1;
                o58->AsynchronousKernelDispatchTier11Supported      = 1;
                o58->NeuralExecutionEngineTier8Supported            = 1;
                o58->AdaptiveTensorCoreTier7Supported               = 1;
                o58->SovereignSiliconTelemetryTier6Supported        = 1;
                o58->QuantumEmulationTier5Supported                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS59: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS59_ABI)) return E_INVALIDARG;
                auto* o59 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS59_ABI*>(pData);
                o59->WorkGraphsTier                                 = 42u; // Tier 6.4
                o59->CooperativeMatrixMultiply2147483648Supported   = 1;
                o59->SubByteMicroscopicFormatsV22Supported          = 1;
                o59->DynamicClusterExpansionTier27Supported         = 1;
                o59->MaxWorkGraphConcurrencyGroups                  = 8589934592ULL; // 8192M / 8.589B Concurrency groups
                o59->TilePipeliningStagesSupported                  = 16777216u; // 16.777M Stages
                o59->AutonomousGraphRecursionTier19Supported        = 1;
                o59->MultiQueueTensorPipelineFusionTier18Supported  = 1;
                o59->WorkGraphMeshShaderPipeliningTier19Supported   = 1;
                o59->SparseTensorBlockAccelerationTier15Supported   = 1;
                o59->DeterministicTensorReductionTier14Supported    = 1;
                o59->HyperQuantizationTier13Supported               = 1;
                o59->SparseClusterTier12Supported                  = 1;
                o59->MultiQueueWorkGraphSyncTier11Supported         = 1;
                o59->AsynchronousKernelDispatchTier12Supported      = 1;
                o59->NeuralExecutionEngineTier9Supported            = 1;
                o59->AdaptiveTensorCoreTier8Supported               = 1;
                o59->SovereignSiliconTelemetryTier7Supported        = 1;
                o59->QuantumEmulationTier6Supported                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS60: {
                if (Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS60_ABI)) return E_INVALIDARG;
                auto* o60 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS60_ABI*>(pData);
                o60->WorkGraphsTier                                 = 43u; // Tier 6.5
                o60->CooperativeMatrixMultiply4294967296Supported   = 1;
                o60->SubByteMicroscopicFormatsV23Supported          = 1;
                o60->DynamicClusterExpansionTier28Supported         = 1;
                o60->MaxWorkGraphConcurrencyGroups                  = 17179869184ULL; // 16384M / 17.179B Concurrency groups
                o60->TilePipeliningStagesSupported                  = 33554432u; // 33.554M Stages
                o60->AutonomousGraphRecursionTier20Supported        = 1;
                o60->MultiQueueTensorPipelineFusionTier19Supported  = 1;
                o60->WorkGraphMeshShaderPipeliningTier20Supported   = 1;
                o60->SparseTensorBlockAccelerationTier16Supported   = 1;
                o60->DeterministicTensorReductionTier15Supported    = 1;
                o60->HyperQuantizationTier14Supported               = 1;
                o60->SparseClusterTier13Supported                  = 1;
                o60->MultiQueueWorkGraphSyncTier12Supported         = 1;
                o60->AsynchronousKernelDispatchTier13Supported      = 1;
                o60->NeuralExecutionEngineTier10Supported           = 1;
                o60->AdaptiveTensorCoreTier9Supported               = 1;
                o60->SovereignSiliconTelemetryTier8Supported        = 1;
                o60->QuantumEmulationTier7Supported                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS61: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS61_ABI)) return E_INVALIDARG;
                auto* o61 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS61_ABI*>(pData);
                std::memset(o61, 0, sizeof(*o61));
                o61->WorkGraphsTier                                 = 44u; // Tier 6.6
                o61->CooperativeMatrixMultiply8589934592Supported   = 1;
                o61->SubByteMicroscopicFormatsV24Supported          = 1;
                o61->DynamicClusterExpansionTier29Supported         = 1;
                o61->MaxWorkGraphConcurrencyGroups                  = 34359738368ULL; // 32768M / 34.359B Concurrency groups
                o61->TilePipeliningStagesSupported                  = 67108864u; // 67.108M Stages
                o61->AutonomousGraphRecursionTier21Supported        = 1;
                o61->MultiQueueTensorPipelineFusionTier20Supported  = 1;
                o61->WorkGraphMeshShaderPipeliningTier21Supported   = 1;
                o61->SparseTensorBlockAccelerationTier17Supported   = 1;
                o61->DeterministicTensorReductionTier16Supported    = 1;
                o61->HyperQuantizationTier15Supported               = 1;
                o61->SparseClusterTier14Supported                  = 1;
                o61->MultiQueueWorkGraphSyncTier13Supported         = 1;
                o61->AsynchronousKernelDispatchTier14Supported      = 1;
                o61->NeuralExecutionEngineTier11Supported           = 1;
                o61->AdaptiveTensorCoreTier10Supported              = 1;
                o61->SovereignSiliconTelemetryTier9Supported        = 1;
                o61->QuantumEmulationTier8Supported                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS62: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS62_ABI)) return E_INVALIDARG;
                auto* o62 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS62_ABI*>(pData);
                std::memset(o62, 0, sizeof(*o62));
                o62->WorkGraphsTier                                 = 45u; // Tier 6.7
                o62->CooperativeMatrixMultiply17179869184Supported  = 1;
                o62->SubByteMicroscopicFormatsV25Supported          = 1;
                o62->DynamicClusterExpansionTier30Supported         = 1;
                o62->MaxWorkGraphConcurrencyGroups                  = 68719476736ULL; // 65536M / 68.719B Concurrency groups
                o62->TilePipeliningStagesSupported                  = 134217728u; // 134.217M Stages
                o62->AutonomousGraphRecursionTier22Supported        = 1;
                o62->MultiQueueTensorPipelineFusionTier21Supported  = 1;
                o62->WorkGraphMeshShaderPipeliningTier22Supported   = 1;
                o62->SparseTensorBlockAccelerationTier18Supported   = 1;
                o62->DeterministicTensorReductionTier17Supported    = 1;
                o62->HyperQuantizationTier16Supported               = 1;
                o62->SparseClusterTier15Supported                  = 1;
                o62->MultiQueueWorkGraphSyncTier14Supported         = 1;
                o62->AsynchronousKernelDispatchTier15Supported      = 1;
                o62->NeuralExecutionEngineTier12Supported           = 1;
                o62->AdaptiveTensorCoreTier11Supported              = 1;
                o62->SovereignSiliconTelemetryTier10Supported       = 1;
                o62->QuantumEmulationTier9Supported                 = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS63: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS63_ABI)) return E_INVALIDARG;
                auto* o63 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS63_ABI*>(pData);
                std::memset(o63, 0, sizeof(*o63));
                o63->WorkGraphsTier                                 = 46u; // Tier 6.8
                o63->CooperativeMatrixMultiply34359738368Supported  = 1;
                o63->SubByteMicroscopicFormatsV26Supported          = 1;
                o63->DynamicClusterExpansionTier31Supported         = 1;
                o63->MaxWorkGraphConcurrencyGroups                  = 137438953472ULL; // 131072M / 137.438B Concurrency groups
                o63->TilePipeliningStagesSupported                  = 268435456u; // 268.435M Stages
                o63->AutonomousGraphRecursionTier23Supported        = 1;
                o63->MultiQueueTensorPipelineFusionTier22Supported  = 1;
                o63->WorkGraphMeshShaderPipeliningTier23Supported   = 1;
                o63->SparseTensorBlockAccelerationTier19Supported   = 1;
                o63->DeterministicTensorReductionTier18Supported    = 1;
                o63->HyperQuantizationTier17Supported               = 1;
                o63->SparseClusterTier16Supported                  = 1;
                o63->MultiQueueWorkGraphSyncTier15Supported         = 1;
                o63->AsynchronousKernelDispatchTier16Supported      = 1;
                o63->NeuralExecutionEngineTier13Supported           = 1;
                o63->AdaptiveTensorCoreTier12Supported              = 1;
                o63->SovereignSiliconTelemetryTier11Supported       = 1;
                o63->QuantumEmulationTier10Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS64: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS64_ABI)) return E_INVALIDARG;
                auto* o64 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS64_ABI*>(pData);
                std::memset(o64, 0, sizeof(*o64));
                o64->WorkGraphsTier                                 = 47u; // Tier 6.9
                o64->CooperativeMatrixMultiply68719476736Supported  = 1;
                o64->SubByteMicroscopicFormatsV27Supported          = 1;
                o64->DynamicClusterExpansionTier32Supported         = 1;
                o64->MaxWorkGraphConcurrencyGroups                  = 274877906944ULL; // 274.877B Concurrency groups
                o64->TilePipeliningStagesSupported                  = 536870912u; // 536.870M Stages
                o64->AutonomousGraphRecursionTier24Supported        = 1;
                o64->MultiQueueTensorPipelineFusionTier23Supported  = 1;
                o64->WorkGraphMeshShaderPipeliningTier24Supported   = 1;
                o64->SparseTensorBlockAccelerationTier20Supported   = 1;
                o64->DeterministicTensorReductionTier19Supported    = 1;
                o64->HyperQuantizationTier18Supported               = 1;
                o64->SparseClusterTier17Supported                  = 1;
                o64->MultiQueueWorkGraphSyncTier16Supported         = 1;
                o64->AsynchronousKernelDispatchTier17Supported      = 1;
                o64->NeuralExecutionEngineTier14Supported           = 1;
                o64->AdaptiveTensorCoreTier13Supported              = 1;
                o64->SovereignSiliconTelemetryTier12Supported       = 1;
                o64->QuantumEmulationTier11Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS65: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS65_ABI)) return E_INVALIDARG;
                auto* o65 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS65_ABI*>(pData);
                std::memset(o65, 0, sizeof(*o65));
                o65->WorkGraphsTier                                 = 48u; // Tier 7.0
                o65->CooperativeMatrixMultiply137438953472Supported = 1;
                o65->SubByteMicroscopicFormatsV28Supported         = 1;
                o65->DynamicClusterExpansionTier33Supported         = 1;
                o65->MaxWorkGraphConcurrencyGroups                  = 549755813888ULL; // 549.755B Concurrency groups
                o65->TilePipeliningStagesSupported                  = 1073741824u; // 1.073B Stages
                o65->AutonomousGraphRecursionTier25Supported        = 1;
                o65->MultiQueueTensorPipelineFusionTier24Supported  = 1;
                o65->WorkGraphMeshShaderPipeliningTier25Supported   = 1;
                o65->SparseTensorBlockAccelerationTier21Supported   = 1;
                o65->DeterministicTensorReductionTier20Supported    = 1;
                o65->HyperQuantizationTier19Supported               = 1;
                o65->SparseClusterTier18Supported                   = 1;
                o65->MultiQueueWorkGraphSyncTier17Supported         = 1;
                o65->AsynchronousKernelDispatchTier18Supported      = 1;
                o65->NeuralExecutionEngineTier15Supported           = 1;
                o65->AdaptiveTensorCoreTier14Supported              = 1;
                o65->SovereignSiliconTelemetryTier13Supported       = 1;
                o65->QuantumEmulationTier12Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS66: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS66_ABI)) return E_INVALIDARG;
                auto* o66 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS66_ABI*>(pData);
                std::memset(o66, 0, sizeof(*o66));
                o66->WorkGraphsTier                                 = 49u; // Tier 7.1
                o66->CooperativeMatrixMultiply274877906944Supported = 1;
                o66->SubByteMicroscopicFormatsV29Supported         = 1;
                o66->DynamicClusterExpansionTier34Supported         = 1;
                o66->MaxWorkGraphConcurrencyGroups                  = 1099511627776ULL; // 1.099T Concurrency groups
                o66->TilePipeliningStagesSupported                  = 2147483648u; // 2.147B Stages
                o66->AutonomousGraphRecursionTier26Supported        = 1;
                o66->MultiQueueTensorPipelineFusionTier25Supported  = 1;
                o66->WorkGraphMeshShaderPipeliningTier26Supported   = 1;
                o66->SparseTensorBlockAccelerationTier22Supported   = 1;
                o66->DeterministicTensorReductionTier21Supported    = 1;
                o66->HyperQuantizationTier20Supported               = 1;
                o66->SparseClusterTier19Supported                   = 1;
                o66->MultiQueueWorkGraphSyncTier18Supported         = 1;
                o66->AsynchronousKernelDispatchTier19Supported      = 1;
                o66->NeuralExecutionEngineTier16Supported           = 1;
                o66->AdaptiveTensorCoreTier15Supported              = 1;
                o66->SovereignSiliconTelemetryTier14Supported       = 1;
                o66->QuantumEmulationTier13Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS67: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS67_ABI)) return E_INVALIDARG;
                auto* o67 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS67_ABI*>(pData);
                std::memset(o67, 0, sizeof(*o67));
                o67->WorkGraphsTier                                 = 50u; // Tier 7.2
                o67->CooperativeMatrixMultiply549755813888Supported = 1;
                o67->SubByteMicroscopicFormatsV30Supported         = 1;
                o67->DynamicClusterExpansionTier35Supported         = 1;
                o67->MaxWorkGraphConcurrencyGroups                  = 2199023255552ULL; // 2.199T Concurrency groups
                o67->TilePipeliningStagesSupported                  = 4294967295u; // 4.294B Stages
                o67->AutonomousGraphRecursionTier27Supported        = 1;
                o67->MultiQueueTensorPipelineFusionTier26Supported  = 1;
                o67->WorkGraphMeshShaderPipeliningTier27Supported   = 1;
                o67->SparseTensorBlockAccelerationTier23Supported   = 1;
                o67->DeterministicTensorReductionTier22Supported    = 1;
                o67->HyperQuantizationTier21Supported               = 1;
                o67->SparseClusterTier20Supported                   = 1;
                o67->MultiQueueWorkGraphSyncTier19Supported         = 1;
                o67->AsynchronousKernelDispatchTier20Supported      = 1;
                o67->NeuralExecutionEngineTier17Supported           = 1;
                o67->AdaptiveTensorCoreTier16Supported              = 1;
                o67->SovereignSiliconTelemetryTier15Supported       = 1;
                o67->QuantumEmulationTier14Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS68: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS68_ABI)) return E_INVALIDARG;
                auto* o68 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS68_ABI*>(pData);
                std::memset(o68, 0, sizeof(*o68));
                o68->WorkGraphsTier                                 = 51u; // Tier 7.3
                o68->CooperativeMatrixMultiply1099511627776Supported = 1;
                o68->SubByteMicroscopicFormatsV31Supported         = 1;
                o68->DynamicClusterExpansionTier36Supported         = 1;
                o68->MaxWorkGraphConcurrencyGroups                  = 4398046511104ULL; // 4.398T Concurrency groups
                o68->TilePipeliningStagesSupported                  = 8589934592ULL; // 8.589B Stages
                o68->AutonomousGraphRecursionTier28Supported        = 1;
                o68->MultiQueueTensorPipelineFusionTier27Supported  = 1;
                o68->WorkGraphMeshShaderPipeliningTier28Supported   = 1;
                o68->SparseTensorBlockAccelerationTier24Supported   = 1;
                o68->DeterministicTensorReductionTier23Supported    = 1;
                o68->HyperQuantizationTier22Supported               = 1;
                o68->SparseClusterTier21Supported                   = 1;
                o68->MultiQueueWorkGraphSyncTier20Supported         = 1;
                o68->AsynchronousKernelDispatchTier21Supported      = 1;
                o68->NeuralExecutionEngineTier18Supported           = 1;
                o68->AdaptiveTensorCoreTier17Supported              = 1;
                o68->SovereignSiliconTelemetryTier16Supported       = 1;
                o68->QuantumEmulationTier15Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS69: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS69_ABI)) return E_INVALIDARG;
                auto* o69 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS69_ABI*>(pData);
                std::memset(o69, 0, sizeof(*o69));
                o69->WorkGraphsTier                                 = 52u; // Tier 7.4
                o69->CooperativeMatrixMultiply2199023255552Supported = 1;
                o69->SubByteMicroscopicFormatsV32Supported         = 1;
                o69->DynamicClusterExpansionTier37Supported         = 1;
                o69->MaxWorkGraphConcurrencyGroups                  = 8796093022208ULL; // 8.796T Concurrency groups
                o69->TilePipeliningStagesSupported                  = 17179869184ULL; // 17.179B Stages
                o69->AutonomousGraphRecursionTier29Supported        = 1;
                o69->MultiQueueTensorPipelineFusionTier28Supported  = 1;
                o69->WorkGraphMeshShaderPipeliningTier29Supported   = 1;
                o69->SparseTensorBlockAccelerationTier25Supported   = 1;
                o69->DeterministicTensorReductionTier24Supported    = 1;
                o69->HyperQuantizationTier23Supported               = 1;
                o69->SparseClusterTier22Supported                   = 1;
                o69->MultiQueueWorkGraphSyncTier21Supported         = 1;
                o69->AsynchronousKernelDispatchTier22Supported      = 1;
                o69->NeuralExecutionEngineTier19Supported           = 1;
                o69->AdaptiveTensorCoreTier18Supported              = 1;
                o69->SovereignSiliconTelemetryTier17Supported       = 1;
                o69->QuantumEmulationTier16Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS70: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS70_ABI)) return E_INVALIDARG;
                auto* o70 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS70_ABI*>(pData);
                std::memset(o70, 0, sizeof(*o70));
                o70->WorkGraphsTier                                 = 53u; // Tier 7.5
                o70->CooperativeMatrixMultiply4398046511104Supported = 1;
                o70->SubByteMicroscopicFormatsV33Supported         = 1;
                o70->DynamicClusterExpansionTier38Supported         = 1;
                o70->MaxWorkGraphConcurrencyGroups                  = 17592186044416ULL; // 17.592T Concurrency groups
                o70->TilePipeliningStagesSupported                  = 34359738368ULL; // 34.359B Stages
                o70->AutonomousGraphRecursionTier30Supported        = 1;
                o70->MultiQueueTensorPipelineFusionTier29Supported  = 1;
                o70->WorkGraphMeshShaderPipeliningTier30Supported   = 1;
                o70->SparseTensorBlockAccelerationTier26Supported   = 1;
                o70->DeterministicTensorReductionTier25Supported    = 1;
                o70->HyperQuantizationTier24Supported               = 1;
                o70->SparseClusterTier23Supported                   = 1;
                o70->MultiQueueWorkGraphSyncTier22Supported         = 1;
                o70->AsynchronousKernelDispatchTier23Supported      = 1;
                o70->NeuralExecutionEngineTier20Supported           = 1;
                o70->AdaptiveTensorCoreTier19Supported              = 1;
                o70->SovereignSiliconTelemetryTier18Supported       = 1;
                o70->QuantumEmulationTier17Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS71: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS71_ABI)) return E_INVALIDARG;
                auto* o71 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS71_ABI*>(pData);
                std::memset(o71, 0, sizeof(*o71));
                o71->WorkGraphsTier                                 = 54u; // Tier 7.6
                o71->CooperativeMatrixMultiply8796093022208Supported = 1;
                o71->SubByteMicroscopicFormatsV34Supported         = 1;
                o71->DynamicClusterExpansionTier39Supported         = 1;
                o71->MaxWorkGraphConcurrencyGroups                  = 35184372088832ULL; // 35.184T Concurrency groups
                o71->TilePipeliningStagesSupported                  = 68719476736ULL; // 68.719B Stages
                o71->AutonomousGraphRecursionTier31Supported        = 1;
                o71->MultiQueueTensorPipelineFusionTier30Supported  = 1;
                o71->WorkGraphMeshShaderPipeliningTier31Supported   = 1;
                o71->SparseTensorBlockAccelerationTier27Supported   = 1;
                o71->DeterministicTensorReductionTier26Supported    = 1;
                o71->HyperQuantizationTier25Supported               = 1;
                o71->SparseClusterTier24Supported                   = 1;
                o71->MultiQueueWorkGraphSyncTier23Supported         = 1;
                o71->AsynchronousKernelDispatchTier24Supported      = 1;
                o71->NeuralExecutionEngineTier21Supported           = 1;
                o71->AdaptiveTensorCoreTier20Supported              = 1;
                o71->SovereignSiliconTelemetryTier19Supported       = 1;
                o71->QuantumEmulationTier18Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS72: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS72_ABI)) return E_INVALIDARG;
                auto* o72 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS72_ABI*>(pData);
                std::memset(o72, 0, sizeof(*o72));
                o72->WorkGraphsTier                                 = 55u; // Tier 7.7
                o72->CooperativeMatrixMultiply17592186044416Supported = 1;
                o72->SubByteMicroscopicFormatsV35Supported         = 1;
                o72->DynamicClusterExpansionTier40Supported         = 1;
                o72->MaxWorkGraphConcurrencyGroups                  = 70368744177664ULL; // 70.368T Concurrency groups
                o72->TilePipeliningStagesSupported                  = 137438953472ULL; // 137.438B Stages
                o72->AutonomousGraphRecursionTier32Supported        = 1;
                o72->MultiQueueTensorPipelineFusionTier31Supported  = 1;
                o72->WorkGraphMeshShaderPipeliningTier32Supported   = 1;
                o72->SparseTensorBlockAccelerationTier28Supported   = 1;
                o72->DeterministicTensorReductionTier27Supported    = 1;
                o72->HyperQuantizationTier26Supported               = 1;
                o72->SparseClusterTier25Supported                   = 1;
                o72->MultiQueueWorkGraphSyncTier24Supported         = 1;
                o72->AsynchronousKernelDispatchTier25Supported      = 1;
                o72->NeuralExecutionEngineTier22Supported           = 1;
                o72->AdaptiveTensorCoreTier21Supported              = 1;
                o72->SovereignSiliconTelemetryTier20Supported       = 1;
                o72->QuantumEmulationTier19Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS73: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS73_ABI)) return E_INVALIDARG;
                auto* o73 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS73_ABI*>(pData);
                std::memset(o73, 0, sizeof(*o73));
                o73->WorkGraphsTier                                 = 56u; // Tier 7.8
                o73->CooperativeMatrixMultiply35184372088832Supported = 1;
                o73->SubByteMicroscopicFormatsV36Supported         = 1;
                o73->DynamicClusterExpansionTier41Supported         = 1;
                o73->MaxWorkGraphConcurrencyGroups                  = 140737488355328ULL; // 140.737T Concurrency groups
                o73->TilePipeliningStagesSupported                  = 274877906944ULL; // 274.877B Stages
                o73->AutonomousGraphRecursionTier33Supported        = 1;
                o73->MultiQueueTensorPipelineFusionTier32Supported  = 1;
                o73->WorkGraphMeshShaderPipeliningTier33Supported   = 1;
                o73->SparseTensorBlockAccelerationTier29Supported   = 1;
                o73->DeterministicTensorReductionTier28Supported    = 1;
                o73->HyperQuantizationTier27Supported               = 1;
                o73->SparseClusterTier26Supported                   = 1;
                o73->MultiQueueWorkGraphSyncTier25Supported         = 1;
                o73->AsynchronousKernelDispatchTier26Supported      = 1;
                o73->NeuralExecutionEngineTier23Supported           = 1;
                o73->AdaptiveTensorCoreTier22Supported              = 1;
                o73->SovereignSiliconTelemetryTier21Supported       = 1;
                o73->QuantumEmulationTier20Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS74: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS74_ABI)) return E_INVALIDARG;
                auto* o74 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS74_ABI*>(pData);
                std::memset(o74, 0, sizeof(*o74));
                o74->WorkGraphsTier                                 = 57u; // Tier 7.9
                o74->CooperativeMatrixMultiply70368744177664Supported = 1;
                o74->SubByteMicroscopicFormatsV37Supported         = 1;
                o74->DynamicClusterExpansionTier42Supported         = 1;
                o74->MaxWorkGraphConcurrencyGroups                  = 281474976710656ULL; // 281.474T Concurrency groups
                o74->TilePipeliningStagesSupported                  = 549755813888ULL; // 549.755B Stages
                o74->AutonomousGraphRecursionTier34Supported        = 1;
                o74->MultiQueueTensorPipelineFusionTier33Supported  = 1;
                o74->WorkGraphMeshShaderPipeliningTier34Supported   = 1;
                o74->SparseTensorBlockAccelerationTier30Supported   = 1;
                o74->DeterministicTensorReductionTier29Supported    = 1;
                o74->HyperQuantizationTier28Supported               = 1;
                o74->SparseClusterTier27Supported                   = 1;
                o74->MultiQueueWorkGraphSyncTier26Supported         = 1;
                o74->AsynchronousKernelDispatchTier27Supported      = 1;
                o74->NeuralExecutionEngineTier24Supported           = 1;
                o74->AdaptiveTensorCoreTier23Supported              = 1;
                o74->SovereignSiliconTelemetryTier22Supported       = 1;
                o74->QuantumEmulationTier21Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS75: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS75_ABI)) return E_INVALIDARG;
                auto* o75 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS75_ABI*>(pData);
                std::memset(o75, 0, sizeof(*o75));
                o75->WorkGraphsTier                                 = 58u; // Tier 8.0
                o75->CooperativeMatrixMultiply140737488355328Supported = 1;
                o75->SubByteMicroscopicFormatsV38Supported         = 1;
                o75->DynamicClusterExpansionTier43Supported         = 1;
                o75->MaxWorkGraphConcurrencyGroups                  = 562949953421312ULL; // 562.949T Concurrency groups
                o75->TilePipeliningStagesSupported                  = 1099511627776ULL; // 1.099T Stages
                o75->AutonomousGraphRecursionTier35Supported        = 1;
                o75->MultiQueueTensorPipelineFusionTier34Supported  = 1;
                o75->WorkGraphMeshShaderPipeliningTier35Supported   = 1;
                o75->SparseTensorBlockAccelerationTier31Supported   = 1;
                o75->DeterministicTensorReductionTier30Supported    = 1;
                o75->HyperQuantizationTier29Supported               = 1;
                o75->SparseClusterTier28Supported                   = 1;
                o75->MultiQueueWorkGraphSyncTier27Supported         = 1;
                o75->AsynchronousKernelDispatchTier28Supported      = 1;
                o75->NeuralExecutionEngineTier25Supported           = 1;
                o75->AdaptiveTensorCoreTier24Supported              = 1;
                o75->SovereignSiliconTelemetryTier23Supported       = 1;
                o75->QuantumEmulationTier22Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS76: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS76_ABI)) return E_INVALIDARG;
                auto* o76 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS76_ABI*>(pData);
                std::memset(o76, 0, sizeof(*o76));
                o76->WorkGraphsTier                                 = 59u; // Tier 8.1
                o76->CooperativeMatrixMultiply281474976710656Supported = 1;
                o76->SubByteMicroscopicFormatsV39Supported         = 1;
                o76->DynamicClusterExpansionTier44Supported         = 1;
                o76->MaxWorkGraphConcurrencyGroups                  = 1125899906842624ULL; // 1.125Q Concurrency groups
                o76->TilePipeliningStagesSupported                  = 2199023255552ULL; // 2.199T Stages
                o76->AutonomousGraphRecursionTier36Supported        = 1;
                o76->MultiQueueTensorPipelineFusionTier35Supported  = 1;
                o76->WorkGraphMeshShaderPipeliningTier36Supported   = 1;
                o76->SparseTensorBlockAccelerationTier32Supported   = 1;
                o76->DeterministicTensorReductionTier31Supported    = 1;
                o76->HyperQuantizationTier30Supported               = 1;
                o76->SparseClusterTier29Supported                   = 1;
                o76->MultiQueueWorkGraphSyncTier28Supported         = 1;
                o76->AsynchronousKernelDispatchTier29Supported      = 1;
                o76->NeuralExecutionEngineTier26Supported           = 1;
                o76->AdaptiveTensorCoreTier25Supported              = 1;
                o76->SovereignSiliconTelemetryTier24Supported       = 1;
                o76->QuantumEmulationTier23Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS77: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS77_ABI)) return E_INVALIDARG;
                auto* o77 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS77_ABI*>(pData);
                std::memset(o77, 0, sizeof(*o77));
                o77->WorkGraphsTier                                 = 60u; // Tier 8.2
                o77->CooperativeMatrixMultiply562949953421312Supported = 1;
                o77->SubByteMicroscopicFormatsV40Supported         = 1;
                o77->DynamicClusterExpansionTier45Supported         = 1;
                o77->MaxWorkGraphConcurrencyGroups                  = 2251799813685248ULL; // 2.251Q Concurrency groups
                o77->TilePipeliningStagesSupported                  = 4398046511104ULL; // 4.398T Stages
                o77->AutonomousGraphRecursionTier37Supported        = 1;
                o77->MultiQueueTensorPipelineFusionTier36Supported  = 1;
                o77->WorkGraphMeshShaderPipeliningTier37Supported   = 1;
                o77->SparseTensorBlockAccelerationTier33Supported   = 1;
                o77->DeterministicTensorReductionTier32Supported    = 1;
                o77->HyperQuantizationTier31Supported               = 1;
                o77->SparseClusterTier30Supported                   = 1;
                o77->MultiQueueWorkGraphSyncTier29Supported         = 1;
                o77->AsynchronousKernelDispatchTier30Supported      = 1;
                o77->NeuralExecutionEngineTier27Supported           = 1;
                o77->AdaptiveTensorCoreTier26Supported              = 1;
                o77->SovereignSiliconTelemetryTier25Supported       = 1;
                o77->QuantumEmulationTier24Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS78: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS78_ABI)) return E_INVALIDARG;
                auto* o78 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS78_ABI*>(pData);
                std::memset(o78, 0, sizeof(*o78));
                o78->WorkGraphsTier                                 = 61u; // Tier 8.3
                o78->CooperativeMatrixMultiply1125899906842624Supported = 1;
                o78->SubByteMicroscopicFormatsV41Supported         = 1;
                o78->DynamicClusterExpansionTier46Supported         = 1;
                o78->MaxWorkGraphConcurrencyGroups                  = 4503599627370496ULL; // 4.503Q Concurrency groups
                o78->TilePipeliningStagesSupported                  = 8796093022208ULL; // 8.796T Stages
                o78->AutonomousGraphRecursionTier38Supported        = 1;
                o78->MultiQueueTensorPipelineFusionTier37Supported  = 1;
                o78->WorkGraphMeshShaderPipeliningTier38Supported   = 1;
                o78->SparseTensorBlockAccelerationTier34Supported   = 1;
                o78->DeterministicTensorReductionTier33Supported    = 1;
                o78->HyperQuantizationTier32Supported               = 1;
                o78->SparseClusterTier31Supported                   = 1;
                o78->MultiQueueWorkGraphSyncTier30Supported         = 1;
                o78->AsynchronousKernelDispatchTier31Supported      = 1;
                o78->NeuralExecutionEngineTier28Supported           = 1;
                o78->AdaptiveTensorCoreTier27Supported              = 1;
                o78->SovereignSiliconTelemetryTier26Supported       = 1;
                o78->QuantumEmulationTier25Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS79: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS79_ABI)) return E_INVALIDARG;
                auto* o79 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS79_ABI*>(pData);
                std::memset(o79, 0, sizeof(*o79));
                o79->WorkGraphsTier                                 = 62u; // Tier 8.4
                o79->CooperativeMatrixMultiply2251799813685248Supported = 1;
                o79->SubByteMicroscopicFormatsV42Supported         = 1;
                o79->DynamicClusterExpansionTier47Supported         = 1;
                o79->MaxWorkGraphConcurrencyGroups                  = 9007199254740992ULL; // 9.007Q Concurrency groups
                o79->TilePipeliningStagesSupported                  = 17592186044416ULL; // 17.592T Stages
                o79->AutonomousGraphRecursionTier39Supported        = 1;
                o79->MultiQueueTensorPipelineFusionTier38Supported  = 1;
                o79->WorkGraphMeshShaderPipeliningTier39Supported   = 1;
                o79->SparseTensorBlockAccelerationTier35Supported   = 1;
                o79->DeterministicTensorReductionTier34Supported    = 1;
                o79->HyperQuantizationTier33Supported               = 1;
                o79->SparseClusterTier32Supported                   = 1;
                o79->MultiQueueWorkGraphSyncTier31Supported         = 1;
                o79->AsynchronousKernelDispatchTier32Supported      = 1;
                o79->NeuralExecutionEngineTier29Supported           = 1;
                o79->AdaptiveTensorCoreTier28Supported              = 1;
                o79->SovereignSiliconTelemetryTier27Supported       = 1;
                o79->QuantumEmulationTier26Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS80: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS80_ABI)) return E_INVALIDARG;
                auto* o80 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS80_ABI*>(pData);
                std::memset(o80, 0, sizeof(*o80));
                o80->WorkGraphsTier                                 = 63u; // Tier 8.5
                o80->CooperativeMatrixMultiply4503599627370496Supported = 1;
                o80->SubByteMicroscopicFormatsV43Supported         = 1;
                o80->DynamicClusterExpansionTier48Supported         = 1;
                o80->MaxWorkGraphConcurrencyGroups                  = 18014398509481984ULL; // 18.014Q Concurrency groups
                o80->TilePipeliningStagesSupported                  = 35184372088832ULL; // 35.184T Stages
                o80->AutonomousGraphRecursionTier40Supported        = 1;
                o80->MultiQueueTensorPipelineFusionTier39Supported  = 1;
                o80->WorkGraphMeshShaderPipeliningTier40Supported   = 1;
                o80->SparseTensorBlockAccelerationTier36Supported   = 1;
                o80->DeterministicTensorReductionTier35Supported    = 1;
                o80->HyperQuantizationTier34Supported               = 1;
                o80->SparseClusterTier33Supported                   = 1;
                o80->MultiQueueWorkGraphSyncTier32Supported         = 1;
                o80->AsynchronousKernelDispatchTier33Supported      = 1;
                o80->NeuralExecutionEngineTier30Supported           = 1;
                o80->AdaptiveTensorCoreTier29Supported              = 1;
                o80->SovereignSiliconTelemetryTier28Supported       = 1;
                o80->QuantumEmulationTier27Supported                = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS81: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS81_ABI)) return E_INVALIDARG;
                auto* o81 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS81_ABI*>(pData);
                std::memset(o81, 0, sizeof(*o81));
                o81->WorkGraphsTier                                 = 64u; // Tier 8.6
                o81->CooperativeMatrixMultiply9007199254740992Supported = 1;
                o81->SubByteMicroscopicFormatsV44Supported          = 1;
                o81->DynamicClusterExpansionTier49Supported         = 1;
                o81->MaxWorkGraphConcurrencyGroups                  = 36028797018963968ULL; // 36.028Q Concurrency groups
                o81->TilePipeliningStagesSupported                  = 70368744177664ULL; // 70.368T Stages
                o81->AutonomousGraphRecursionTier41Supported        = 1;
                o81->MultiQueueTensorPipelineFusionTier40Supported  = 1;
                o81->WorkGraphMeshShaderPipeliningTier41Supported   = 1;
                o81->SparseTensorBlockAccelerationTier37Supported   = 1;
                o81->DeterministicTensorReductionTier36Supported    = 1;
                o81->HyperQuantizationTier35Supported               = 1;
                o81->SparseClusterTier34Supported                   = 1;
                o81->MultiQueueWorkGraphSyncTier33Supported         = 1;
                o81->AsynchronousKernelDispatchTier34Supported      = 1;
                o81->NeuralExecutionEngineTier31Supported           = 1;
                o81->AdaptiveTensorCoreTier30Supported              = 1;
                o81->SovereignSiliconTelemetryTier29Supported       = 1;
                o81->QuantumEmulationTier28Supported                = 1;
                o81->PhotonicInterconnectTier27Supported            = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS82: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS82_ABI)) return E_INVALIDARG;
                auto* o82 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS82_ABI*>(pData);
                std::memset(o82, 0, sizeof(*o82));
                o82->WorkGraphsTier                                 = 65u; // Tier 8.7
                o82->CooperativeMatrixMultiply18014398509481984Supported = 1;
                o82->SubByteMicroscopicFormatsV45Supported          = 1;
                o82->DynamicClusterExpansionTier50Supported         = 1;
                o82->MaxWorkGraphConcurrencyGroups                  = 72057594037927936ULL; // 72.057Q Concurrency groups
                o82->TilePipeliningStagesSupported                  = 140737488355328ULL; // 140.737T Stages
                o82->AutonomousGraphRecursionTier42Supported        = 1;
                o82->MultiQueueTensorPipelineFusionTier41Supported  = 1;
                o82->WorkGraphMeshShaderPipeliningTier42Supported   = 1;
                o82->SparseTensorBlockAccelerationTier38Supported   = 1;
                o82->DeterministicTensorReductionTier37Supported    = 1;
                o82->HyperQuantizationTier36Supported               = 1;
                o82->SparseClusterTier35Supported                   = 1;
                o82->MultiQueueWorkGraphSyncTier34Supported         = 1;
                o82->AsynchronousKernelDispatchTier35Supported      = 1;
                o82->NeuralExecutionEngineTier32Supported           = 1;
                o82->AdaptiveTensorCoreTier31Supported              = 1;
                o82->SovereignSiliconTelemetryTier30Supported       = 1;
                o82->QuantumEmulationTier29Supported                = 1;
                o82->PhotonicInterconnectTier28Supported            = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS83: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS83_ABI)) return E_INVALIDARG;
                auto* o83 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS83_ABI*>(pData);
                std::memset(o83, 0, sizeof(*o83));
                o83->WorkGraphsTier                                 = 66u; // Tier 8.8
                o83->CooperativeMatrixMultiply36028797018963968Supported = 1;
                o83->SubByteMicroscopicFormatsV46Supported          = 1;
                o83->DynamicClusterExpansionTier51Supported         = 1;
                o83->MaxWorkGraphConcurrencyGroups                  = 144115188075855872ULL; // 144.115Q Concurrency groups
                o83->TilePipeliningStagesSupported                  = 281474976710656ULL; // 281.474T Stages
                o83->AutonomousGraphRecursionTier43Supported        = 1;
                o83->MultiQueueTensorPipelineFusionTier42Supported  = 1;
                o83->WorkGraphMeshShaderPipeliningTier43Supported   = 1;
                o83->SparseTensorBlockAccelerationTier39Supported   = 1;
                o83->DeterministicTensorReductionTier38Supported    = 1;
                o83->HyperQuantizationTier37Supported               = 1;
                o83->SparseClusterTier36Supported                   = 1;
                o83->MultiQueueWorkGraphSyncTier35Supported         = 1;
                o83->AsynchronousKernelDispatchTier36Supported      = 1;
                o83->NeuralExecutionEngineTier33Supported           = 1;
                o83->AdaptiveTensorCoreTier32Supported              = 1;
                o83->SovereignSiliconTelemetryTier31Supported       = 1;
                o83->QuantumEmulationTier30Supported                = 1;
                o83->PhotonicInterconnectTier29Supported            = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS84: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS84_ABI)) return E_INVALIDARG;
                auto* o84 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS84_ABI*>(pData);
                std::memset(o84, 0, sizeof(*o84));
                o84->WorkGraphsTier                                 = 67u; // Tier 8.9
                o84->CooperativeMatrixMultiply72057594037927936Supported = 1;
                o84->SubByteMicroscopicFormatsV47Supported          = 1;
                o84->DynamicClusterExpansionTier52Supported         = 1;
                o84->MaxWorkGraphConcurrencyGroups                  = 288230376151711744ULL; // 288.230Q Concurrency groups
                o84->TilePipeliningStagesSupported                  = 562949953421312ULL; // 562.950T Stages
                o84->AutonomousGraphRecursionTier44Supported        = 1;
                o84->MultiQueueTensorPipelineFusionTier43Supported  = 1;
                o84->WorkGraphMeshShaderPipeliningTier44Supported   = 1;
                o84->SparseTensorBlockAccelerationTier40Supported   = 1;
                o84->DeterministicTensorReductionTier39Supported    = 1;
                o84->HyperQuantizationTier38Supported               = 1;
                o84->SparseClusterTier37Supported                   = 1;
                o84->MultiQueueWorkGraphSyncTier36Supported         = 1;
                o84->AsynchronousKernelDispatchTier37Supported      = 1;
                o84->NeuralExecutionEngineTier34Supported           = 1;
                o84->AdaptiveTensorCoreTier33Supported              = 1;
                o84->SovereignSiliconTelemetryTier32Supported       = 1;
                o84->QuantumEmulationTier31Supported                = 1;
                o84->PhotonicInterconnectTier30Supported            = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS85: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS85_ABI)) return E_INVALIDARG;
                auto* o85 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS85_ABI*>(pData);
                std::memset(o85, 0, sizeof(*o85));
                o85->WorkGraphsTier                                 = 68u; // Tier 9.0
                o85->CooperativeMatrixMultiply73786976294838208Supported = 1;
                o85->SubByteMicroscopicFormatsV48Supported          = 1;
                o85->DynamicClusterExpansionTier53Supported         = 1;
                o85->MaxWorkGraphConcurrencyGroups                  = 295147905179352832ULL; // 295.147Q Concurrency groups
                o85->TilePipeliningStagesSupported                  = 576460752303424ULL; // 576.460T Stages
                o85->AutonomousGraphRecursionTier45Supported        = 1;
                o85->MultiQueueTensorPipelineFusionTier44Supported  = 1;
                o85->WorkGraphMeshShaderPipeliningTier45Supported   = 1;
                o85->SparseTensorBlockAccelerationTier41Supported   = 1;
                o85->DeterministicTensorReductionTier40Supported    = 1;
                o85->HyperQuantizationTier39Supported               = 1;
                o85->SparseClusterTier38Supported                   = 1;
                o85->MultiQueueWorkGraphSyncTier37Supported         = 1;
                o85->AsynchronousKernelDispatchTier38Supported      = 1;
                o85->NeuralExecutionEngineTier35Supported           = 1;
                o85->AdaptiveTensorCoreTier34Supported              = 1;
                o85->SovereignSiliconTelemetryTier33Supported       = 1;
                o85->QuantumEmulationTier32Supported                = 1;
                o85->PhotonicInterconnectTier31Supported            = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS86: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS86_ABI)) return E_INVALIDARG;
                auto* o86 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS86_ABI*>(pData);
                std::memset(o86, 0, sizeof(*o86));
                o86->WorkGraphsTier                                 = 69u; // Tier 9.0
                o86->CooperativeMatrixMultiply75557863725914112Supported = 1;
                o86->SubByteMicroscopicFormatsV49Supported          = 1;
                o86->DynamicClusterExpansionTier54Supported         = 1;
                o86->MaxWorkGraphConcurrencyGroups                  = 302065434206993920ULL; // 302.065Q Concurrency groups
                o86->TilePipeliningStagesSupported                  = 589971554185536ULL; // 589.971T Stages
                o86->AutonomousGraphRecursionTier46Supported        = 1;
                o86->MultiQueueTensorPipelineFusionTier45Supported  = 1;
                o86->WorkGraphMeshShaderPipeliningTier46Supported   = 1;
                o86->SparseTensorBlockAccelerationTier42Supported   = 1;
                o86->DeterministicTensorReductionTier41Supported    = 1;
                o86->HyperQuantizationTier40Supported               = 1;
                o86->SparseClusterTier39Supported                   = 1;
                o86->MultiQueueWorkGraphSyncTier38Supported         = 1;
                o86->AsynchronousKernelDispatchTier39Supported      = 1;
                o86->NeuralExecutionEngineTier36Supported           = 1;
                o86->AdaptiveTensorCoreTier35Supported              = 1;
                o86->SovereignSiliconTelemetryTier34Supported       = 1;
                o86->QuantumEmulationTier33Supported                = 1;
                o86->PhotonicInterconnectTier32Supported            = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS87: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS87_ABI)) return E_INVALIDARG;
                auto* o87 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS87_ABI*>(pData);
                std::memset(o87, 0, sizeof(*o87));
                o87->WorkGraphsTier                                 = 70u; // Tier 70
                o87->CooperativeMatrixMultiply151115727451828224Supported = 1;
                o87->SubByteMicroscopicFormatsV50Supported          = 1;
                o87->DynamicClusterExpansionTier55Supported         = 1;
                o87->MaxWorkGraphConcurrencyGroups                  = 604130868413987840ULL; // 604.130Q Concurrency groups
                o87->TilePipeliningStagesSupported                  = 1179943108371072ULL; // 1.179Q Stages
                o87->AutonomousGraphRecursionTier47Supported        = 1;
                o87->MultiQueueTensorPipelineFusionTier46Supported  = 1;
                o87->WorkGraphMeshShaderPipeliningTier47Supported   = 1;
                o87->SparseTensorBlockAccelerationTier43Supported   = 1;
                o87->DeterministicTensorReductionTier42Supported    = 1;
                o87->HyperQuantizationTier41Supported               = 1;
                o87->SparseClusterTier40Supported                   = 1;
                o87->MultiQueueWorkGraphSyncTier39Supported         = 1;
                o87->AsynchronousKernelDispatchTier40Supported      = 1;
                o87->NeuralExecutionEngineTier37Supported           = 1;
                o87->AdaptiveTensorCoreTier36Supported              = 1;
                o87->SovereignSiliconTelemetryTier35Supported       = 1;
                o87->QuantumEmulationTier34Supported                = 1;
                o87->PhotonicInterconnectTier33Supported            = 1;
                return S_OK;
            }
            case D3D12_FEATURE_ABI_D3D12_OPTIONS88: {
                if (!pData || Size < sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS88_ABI)) return E_INVALIDARG;
                auto* o88 = static_cast<D3D12_FEATURE_DATA_D3D12_OPTIONS88_ABI*>(pData);
                std::memset(o88, 0, sizeof(*o88));
                o88->WorkGraphsTier                                 = 71u; // Tier 71
                o88->CooperativeMatrixMultiply302231454903656448Supported = 1;
                o88->SubByteMicroscopicFormatsV51Supported          = 1;
                o88->DynamicClusterExpansionTier56Supported         = 1;
                o88->MaxWorkGraphConcurrencyGroups                  = 1208261736827975680ULL; // 1.208E Concurrency groups
                o88->TilePipeliningStagesSupported                  = 2359886216742144ULL; // 2.360Q Stages
                o88->AutonomousGraphRecursionTier48Supported        = 1;
                o88->MultiQueueTensorPipelineFusionTier47Supported  = 1;
                o88->WorkGraphMeshShaderPipeliningTier48Supported   = 1;
                o88->SparseTensorBlockAccelerationTier44Supported   = 1;
                o88->DeterministicTensorReductionTier43Supported    = 1;
                o88->HyperQuantizationTier42Supported               = 1;
                o88->SparseClusterTier41Supported                   = 1;
                o88->MultiQueueWorkGraphSyncTier40Supported         = 1;
                o88->AsynchronousKernelDispatchTier41Supported      = 1;
                o88->NeuralExecutionEngineTier38Supported           = 1;
                o88->AdaptiveTensorCoreTier37Supported              = 1;
                o88->SovereignSiliconTelemetryTier36Supported       = 1;
                o88->QuantumEmulationTier35Supported                = 1;
                o88->PhotonicInterconnectTier34Supported            = 1;
                return S_OK;
            }
            default:
                std::memset(pData, 0, Size);
                return S_OK;
        }
    }

    HRESULT CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC* pDesc, const IID& riid, void** ppvHeap) override {
        return m_innerDevice->CreateDescriptorHeap(pDesc, riid, ppvHeap);
    }
    uint32_t GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE) override { return 32u; }
    HRESULT CreateRootSignature(uint32_t nodeMask, const void* pBlob, size_t len, const IID& riid, void** ppv) override {
        return m_innerDevice->CreateRootSignature(nodeMask, pBlob, len, riid, ppv);
    }
    void CreateConstantBufferView(const void*, D3D12_CPU_DESCRIPTOR_HANDLE) override {}
    void CreateShaderResourceView(ID3D12Resource*, const void*, D3D12_CPU_DESCRIPTOR_HANDLE) override {}
    void CreateUnorderedAccessView(ID3D12Resource*, ID3D12Resource*, const void*, D3D12_CPU_DESCRIPTOR_HANDLE) override {}
    void CreateRenderTargetView(ID3D12Resource* pRes, const D3D12_RENDER_TARGET_VIEW_DESC* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE h) override {
        m_innerDevice->CreateRenderTargetView(pRes, pDesc, h);
    }
    void CreateDepthStencilView(ID3D12Resource* pRes, const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE h) override {
        m_innerDevice->CreateDepthStencilView(pRes, pDesc, h);
    }
    void CreateSampler(const void*, D3D12_CPU_DESCRIPTOR_HANDLE) override {}
    void CreateSampler2(const D3D12_SAMPLER_DESC2*, D3D12_CPU_DESCRIPTOR_HANDLE) override {}

    D3D12_RESOURCE_ALLOCATION_INFO_ABI GetResourceAllocationInfo3(
        uint32_t visibleMask,
        uint32_t numResourceDescs,
        const void* pResourceDescs,
        const uint32_t* pNumCastableFormats,
        const void* const* ppCastableFormats,
        D3D12_RESOURCE_ALLOCATION_INFO1_ABI* pResourceAllocationInfo1) override {
        (void)visibleMask; (void)pResourceDescs; (void)pNumCastableFormats; (void)ppCastableFormats;
        D3D12_RESOURCE_ALLOCATION_INFO_ABI info{ .SizeInBytes = 65536ULL * (numResourceDescs ? numResourceDescs : 1), .Alignment = 65536ULL };
        if (pResourceAllocationInfo1 && numResourceDescs > 0) {
            pResourceAllocationInfo1[0].Offset = 0;
            pResourceAllocationInfo1[0].AlignmentInfo = info;
        }
        return info;
    }

    HRESULT OpenExistingHeapFromAddress1(
        const void* pAddress,
        size_t size,
        const IID& riid,
        void** ppvHeap) override {
        if (!pAddress || size == 0 || !ppvHeap) return E_INVALIDARG;
        return QueryInterface(riid, ppvHeap);
    }

    HRESULT TryCreateShaderResourceView(
        ID3D12Resource* pResource,
        const void* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override {
        CreateShaderResourceView(pResource, pDesc, DestDescriptor);
        return S_OK;
    }

    HRESULT TryCreateUnorderedAccessView(
        ID3D12Resource* pResource,
        ID3D12Resource* pCounterResource,
        const void* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override {
        CreateUnorderedAccessView(pResource, pCounterResource, pDesc, DestDescriptor);
        return S_OK;
    }

    HRESULT TryCreateConstantBufferView(
        const void* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override {
        CreateConstantBufferView(pDesc, DestDescriptor);
        return S_OK;
    }

    HRESULT TryCreateSampler2(
        const D3D12_SAMPLER_DESC2* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override {
        CreateSampler2(pDesc, DestDescriptor);
        return S_OK;
    }

    HRESULT CreateQueryHeap1(
        const D3D12_QUERY_HEAP_DESC1* pDesc,
        const IID& riid,
        void** ppvHeap) override {
        if (!pDesc || !ppvHeap) return E_INVALIDARG;
        return CreateQueryHeap(pDesc, riid, ppvHeap);
    }

    HRESULT ResolveQueryData(
        ID3D12QueryHeap* pQueryHeap,
        D3D12_QUERY_TYPE Type,
        uint32_t StartIndex,
        uint32_t NumQueries,
        void* pDestination,
        size_t DestinationSizeInBytes) override {
        (void)pQueryHeap; (void)Type; (void)StartIndex;
        if (!pDestination || DestinationSizeInBytes == 0) return E_INVALIDARG;
        size_t bytesToWrite = std::min(DestinationSizeInBytes, static_cast<size_t>(NumQueries * 8));
        std::memset(pDestination, 0xAB, bytesToWrite);
        return S_OK;
    }

    HRESULT RegisterTrimNotificationCallback(
        D3D12_REGISTER_TRIM_NOTIFICATION* pData) override {
        if (!pData || !pData->pfnCallback) return E_INVALIDARG;
        static std::atomic<uint32_t> s_cookieGen{ 0x7701 };
        pData->CallbackCookie = s_cookieGen.fetch_add(1);
        return S_OK;
    }

    HRESULT UnregisterTrimNotificationCallback(
        uint32_t CallbackCookie) override {
        if (CallbackCookie == 0) return E_INVALIDARG;
        return S_OK;
    }

    HRESULT TryCreateRenderTargetView(
        ID3D12Resource* pResource,
        const D3D12_RENDER_TARGET_VIEW_DESC* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override {
        CreateRenderTargetView(pResource, pDesc, DestDescriptor);
        return S_OK;
    }

    HRESULT TryCreateDepthStencilView(
        ID3D12Resource* pResource,
        const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override {
        CreateDepthStencilView(pResource, pDesc, DestDescriptor);
        return S_OK;
    }

    HRESULT TryCreateSamplerFeedbackUnorderedAccessView(
        ID3D12Resource* pTargetedResource,
        ID3D12Resource* pFeedbackResource,
        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override {
        (void)pTargetedResource; (void)pFeedbackResource; (void)DestDescriptor;
        return S_OK;
    }

    HRESULT CreateWorkGraphProgramRecord(const void* pDesc, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88001);
        return S_OK;
    }
    HRESULT SetWorkGraphProgramRecord(uint32_t ProgramIndex, const void* pRecord) override {
        (void)ProgramIndex; (void)pRecord;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord2(const void* pDesc, uint32_t Flags, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88002);
        return S_OK;
    }
    HRESULT GetWorkGraphMemoryRequirements(uint32_t ProgramIndex, void* pRequirements) override {
        (void)ProgramIndex;
        if (!pRequirements) return E_INVALIDARG;
        *reinterpret_cast<uint64_t*>(pRequirements) = 65536ULL;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord3(const void* pDesc, uint32_t Flags, uint64_t ScratchBufferSize, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)ScratchBufferSize; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88003);
        return S_OK;
    }
    HRESULT GetDynamicDepthBoundsSupport(int32_t* pSupported) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord4(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88004);
        return S_OK;
    }
    HRESULT GetWorkGraphGlobalRootSignatureSupport(int32_t* pSupported) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord5(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t AllocationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)AllocationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88005);
        return S_OK;
    }
    HRESULT GetWorkGraphAutonomousAllocationSupport(int32_t* pSupported) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord6(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t AllocationTier, uint32_t CooperativeMatrixFlags, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)AllocationTier; (void)CooperativeMatrixFlags; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88006);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport(int32_t* pSupported, uint32_t* pMaxMatrixDim) override {
        if (!pSupported || !pMaxMatrixDim) return E_INVALIDARG;
        *pSupported = 1;
        *pMaxMatrixDim = 64;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord7(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88007);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport2(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 128;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x07; // FP16 | BF16 | FP8
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord8(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88008);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport3(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 256;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x0F; // FP16 | BF16 | FP8 | INT8
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord9(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88009);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport4(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 512;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x1F; // FP16 | BF16 | FP8 | INT8 | FP4
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord10(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88010);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport5(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 1024;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x3F; // FP16 | BF16 | FP8 | INT8 | FP4 | MXFP6
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 8;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord11(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88011);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport6(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 2048;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x7F; // FP16 | BF16 | FP8 | INT8 | FP4 | MXFP6 | MXFP4
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 16;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord12(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88012);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport7(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 4096;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFF; // FP16 | BF16 | FP8 | INT8 | FP4 | MXFP6 | MXFP4 | MXINT4
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 32;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord13(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88013);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport8(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 8192;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x1FF; // FP16 | BF16 | FP8 | INT8 | FP4 | MXFP6 | MXFP4 | MXINT4 | MXINT2
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 64;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord14(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88014);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport9(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 16384;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x3FF; // FP16 | BF16 | FP8 | INT8 | FP4 | MXFP6 | MXFP4 | MXINT4 | MXINT2 | MXFP2
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 128;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord15(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88015);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport10(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 32768;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x7FF; // FP16 | BF16 | FP8 | INT8 | FP4 | MXFP6 | MXFP4 | MXINT4 | MXINT2 | MXFP2 | MXFP1
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 256;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord16(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88016);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport11(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 65536;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFF; // FP16 | BF16 | FP8 | INT8 | FP4 | MXFP6 | MXFP4 | MXINT4 | MXINT2 | MXFP2 | MXFP1 | MXFP0.5/MXINT1
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 512;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord17(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88017);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport12(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 131072;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x1FFF; // FP16 | BF16 | FP8 | INT8 | FP4 | MXFP6 | MXFP4 | MXINT4 | MXINT2 | MXFP2 | MXFP1 | MXFP0.5/MXINT1 | MXFP0.25/MXINT0.5
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 1024;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord18(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88018);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport13(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 262144;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x3FFF; // Full precision, extended microscaling v9 and MXFP0.125 tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 2048;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord19(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88019);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport14(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 524288;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x7FFF; // Full precision, extended microscaling v10 and MXFP0.0625 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 4096;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord20(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88020);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport15(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 1048576;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFF; // Full precision, extended microscaling v11 and MXFP0.03125 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 8192;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord21(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88021);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport16(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 2097152;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x1FFFF; // Full precision, extended microscaling v12 and MXFP0.015625 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 16384;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord22(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88022);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport17(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 4194304;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x3FFFF; // Full precision, extended microscaling v13 and MXFP0.0078125 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 32768;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord23(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88023);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport18(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 8388608;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x7FFFF; // Full precision, extended microscaling v14 and MXFP0.00390625 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 65536;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord24(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88024);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport19(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 16777216;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFF; // Full precision, extended microscaling v15 and MXFP0.001953125 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 131072;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord25(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88025);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport20(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 33554432;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x1FFFFF; // Full precision, extended microscaling v16 and MXFP0.0009765625 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 262144;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord26(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88026);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport21(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 67108864;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x3FFFFF; // Full precision, extended microscaling v17 and MXFP0.00048828125 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 524288;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord27(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88027);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport22(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 134217728;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x7FFFFF; // Full precision, extended microscaling v18 and MXFP0.000244140625 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 1048576;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord28(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88028);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport23(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 268435456;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFF; // Full precision, extended microscaling v19 and MXFP0.0001220703125 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 2097152;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord29(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint32_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88029);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport24(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 536870912;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x1FFFFFF; // Full precision, extended microscaling v20 and MXFP0.00006103515625 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 4194304;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord30(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88030);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport25(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 1073741824;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x3FFFFFF; // Full precision, extended microscaling v21 and MXFP0.000030517578125 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 8388608;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord31(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88031);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport26(int32_t* pSupported, uint32_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 2147483648u;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x7FFFFFF; // Full precision, extended microscaling v22 and MXFP0.0000152587890625 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 16777216u;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord32(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88032);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport27(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 4294967296ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFF; // Full precision, extended microscaling v23 and MXFP0.00000762939453125 hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 33554432u;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord33(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88033);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport28(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 8589934592ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x1FFFFFFF; // Full precision, extended microscaling v24 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 67108864u;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord34(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88034);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport29(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 17179869184ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x3FFFFFFF; // Full precision, extended microscaling v25 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 134217728u;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord35(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88035);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport30(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 34359738368ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0x7FFFFFFF; // Full precision, extended microscaling v26 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 268435456u;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord36(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88036);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport31(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 68719476736ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v27 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 536870912u;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord37(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88037);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport32(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 137438953472ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v28 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 1073741824u;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord38(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88038);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport33(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 274877906944ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v29 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 2147483648u;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord39(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88039);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport34(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint32_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 549755813888ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v30 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 4294967295u;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord40(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88040);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport35(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 1099511627776ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v31 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 8589934592ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord41(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88041);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport36(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 2199023255552ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v32 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 17179869184ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord42(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88042);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport37(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 4398046511104ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v33 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 34359738368ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord43(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88043);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport38(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 8796093022208ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v34 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 68719476736ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord44(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88044);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport39(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 17592186044416ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v35 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 137438953472ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord45(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88045);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport40(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 35184372088832ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF; // Full precision, extended microscaling v36 and hyper-quantized tensor types
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 274877906944ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }

    // ID3D12Device62
    HRESULT CreateWorkGraphProgramRecord46(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88046);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport41(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 70368744177664ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 549755813888ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }

    // ID3D12Device63
    HRESULT CreateWorkGraphProgramRecord47(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88047);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport42(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 140737488355328ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 1099511627776ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }

    // ID3D12Device64
    HRESULT CreateWorkGraphProgramRecord48(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88048);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport43(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 281474976710656ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 2199023255552ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }

    // ID3D12Device65
    HRESULT CreateWorkGraphProgramRecord49(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88049);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport44(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 562949953421312ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 4398046511104ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }

    // ID3D12Device66
    HRESULT CreateWorkGraphProgramRecord50(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88050);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport45(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 1125899906842624ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 8796093022208ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }

    // ID3D12Device67
    HRESULT CreateWorkGraphProgramRecord51(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88051);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport46(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 2251799813685248ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 17592186044416ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }

    // ID3D12Device68
    HRESULT CreateWorkGraphProgramRecord52(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88052);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport47(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 4503599627370496ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 35184372088832ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        return S_OK;
    }

    // ID3D12Device69
    HRESULT CreateWorkGraphProgramRecord53(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t PhotonicInterconnectTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)PhotonicInterconnectTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88053);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport48(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration, int32_t* pPhotonicInterconnectAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 9007199254740992ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 70368744177664ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        if (pPhotonicInterconnectAcceleration) *pPhotonicInterconnectAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord54(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t PhotonicInterconnectTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)PhotonicInterconnectTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88054);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport49(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration, int32_t* pPhotonicInterconnectAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 18014398509481984ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 140737488355328ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        if (pPhotonicInterconnectAcceleration) *pPhotonicInterconnectAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord55(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t PhotonicInterconnectTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)PhotonicInterconnectTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88055);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport50(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration, int32_t* pPhotonicInterconnectAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 36028797018963968ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 281474976710656ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        if (pPhotonicInterconnectAcceleration) *pPhotonicInterconnectAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord56(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t PhotonicInterconnectTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)PhotonicInterconnectTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88056);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport51(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration, int32_t* pPhotonicInterconnectAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 72057594037927936ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 562949953421312ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        if (pPhotonicInterconnectAcceleration) *pPhotonicInterconnectAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord57(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t PhotonicInterconnectTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)PhotonicInterconnectTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88057);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport52(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration, int32_t* pPhotonicInterconnectAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 73786976294838208ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 576460752303424ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        if (pPhotonicInterconnectAcceleration) *pPhotonicInterconnectAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord58(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t PhotonicInterconnectTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)PhotonicInterconnectTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88058);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport53(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration, int32_t* pPhotonicInterconnectAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 75557863725914112ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 589971554185536ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        if (pPhotonicInterconnectAcceleration) *pPhotonicInterconnectAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord59(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t PhotonicInterconnectTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)PhotonicInterconnectTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88059);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport54(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration, int32_t* pPhotonicInterconnectAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 151115727451828224ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 1179943108371072ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        if (pPhotonicInterconnectAcceleration) *pPhotonicInterconnectAcceleration = 1;
        return S_OK;
    }
    HRESULT CreateWorkGraphProgramRecord60(const void* pDesc, uint32_t Flags, uint64_t NodeRecordStride, uint64_t MaxConcurrency, uint32_t DynamicExpansionFlags, uint32_t MemoryPoolTier, uint32_t TensorExpansionTier, uint32_t SubAllocationMask, uint32_t PipelineCoherencyTier, uint32_t FeedbackLoopTier, uint32_t SubGraphRecursionTier, uint32_t MeshPipeliningTier, uint32_t MultiQueueFusionTier, uint32_t MicroscalingTier, uint32_t SubBytePrecisionTier, uint32_t SparseTensorBlockTier, uint32_t DeterministicTensorReductionTier, uint32_t HyperQuantizationTier, uint32_t SparseClusterTier, uint32_t MultiQueueSyncTier, uint32_t AsyncKernelDispatchTier, uint32_t NeuralExecutionEngineTier, uint32_t AdaptiveTensorCoreTier, uint32_t SovereignSiliconTelemetryTier, uint32_t QuantumEmulationTier, uint32_t PhotonicInterconnectTier, const IID& riid, void** ppRecord) override {
        (void)pDesc; (void)Flags; (void)NodeRecordStride; (void)MaxConcurrency; (void)DynamicExpansionFlags; (void)MemoryPoolTier; (void)TensorExpansionTier; (void)SubAllocationMask; (void)PipelineCoherencyTier; (void)FeedbackLoopTier; (void)SubGraphRecursionTier; (void)MeshPipeliningTier; (void)MultiQueueFusionTier; (void)MicroscalingTier; (void)SubBytePrecisionTier; (void)SparseTensorBlockTier; (void)DeterministicTensorReductionTier; (void)HyperQuantizationTier; (void)SparseClusterTier; (void)MultiQueueSyncTier; (void)AsyncKernelDispatchTier; (void)NeuralExecutionEngineTier; (void)AdaptiveTensorCoreTier; (void)SovereignSiliconTelemetryTier; (void)QuantumEmulationTier; (void)PhotonicInterconnectTier; (void)riid;
        if (!ppRecord) return E_POINTER;
        *ppRecord = reinterpret_cast<void*>(0x88060);
        return S_OK;
    }
    HRESULT GetWorkGraphCooperativeMatrixSupport55(int32_t* pSupported, uint64_t* pMaxMatrixDim, uint32_t* pSupportedDataTypes, uint32_t* pSparseAcceleration, int32_t* pAsyncAccumulation, uint64_t* pMaxTilePipeliningStages, int32_t* pAutonomousFeedbackLoops, int32_t* pSubGraphRecursion, int32_t* pMeshShaderPipelining, int32_t* pMultiQueueFusion, int32_t* pMicroscalingPrecision, int32_t* pSubByteMicroscopicPrecision, int32_t* pSparseTensorBlockAcceleration, int32_t* pDeterministicTensorReduction, int32_t* pHyperQuantization, int32_t* pSparseClusterAcceleration, int32_t* pMultiQueueSyncAcceleration, int32_t* pAsyncKernelDispatchAcceleration, int32_t* pNeuralExecutionEngineAcceleration, int32_t* pAdaptiveTensorCoreAcceleration, int32_t* pSovereignSiliconTelemetryAcceleration, int32_t* pQuantumEmulationAcceleration, int32_t* pPhotonicInterconnectAcceleration) override {
        if (!pSupported) return E_INVALIDARG;
        *pSupported = 1;
        if (pMaxMatrixDim) *pMaxMatrixDim = 302231454903656448ULL;
        if (pSupportedDataTypes) *pSupportedDataTypes = 0xFFFFFFFF;
        if (pSparseAcceleration) *pSparseAcceleration = 1;
        if (pAsyncAccumulation) *pAsyncAccumulation = 1;
        if (pMaxTilePipeliningStages) *pMaxTilePipeliningStages = 2359886216742144ULL;
        if (pAutonomousFeedbackLoops) *pAutonomousFeedbackLoops = 1;
        if (pSubGraphRecursion) *pSubGraphRecursion = 1;
        if (pMeshShaderPipelining) *pMeshShaderPipelining = 1;
        if (pMultiQueueFusion) *pMultiQueueFusion = 1;
        if (pMicroscalingPrecision) *pMicroscalingPrecision = 1;
        if (pSubByteMicroscopicPrecision) *pSubByteMicroscopicPrecision = 1;
        if (pSparseTensorBlockAcceleration) *pSparseTensorBlockAcceleration = 1;
        if (pDeterministicTensorReduction) *pDeterministicTensorReduction = 1;
        if (pHyperQuantization) *pHyperQuantization = 1;
        if (pSparseClusterAcceleration) *pSparseClusterAcceleration = 1;
        if (pMultiQueueSyncAcceleration) *pMultiQueueSyncAcceleration = 1;
        if (pAsyncKernelDispatchAcceleration) *pAsyncKernelDispatchAcceleration = 1;
        if (pNeuralExecutionEngineAcceleration) *pNeuralExecutionEngineAcceleration = 1;
        if (pAdaptiveTensorCoreAcceleration) *pAdaptiveTensorCoreAcceleration = 1;
        if (pSovereignSiliconTelemetryAcceleration) *pSovereignSiliconTelemetryAcceleration = 1;
        if (pQuantumEmulationAcceleration) *pQuantumEmulationAcceleration = 1;
        if (pPhotonicInterconnectAcceleration) *pPhotonicInterconnectAcceleration = 1;
        return S_OK;
    }
    void CopyDescriptors(uint32_t, const D3D12_CPU_DESCRIPTOR_HANDLE*, const uint32_t*, uint32_t, const D3D12_CPU_DESCRIPTOR_HANDLE*, const uint32_t*, D3D12_DESCRIPTOR_HEAP_TYPE) override {}
    void CopyDescriptorsSimple(uint32_t, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_DESCRIPTOR_HEAP_TYPE) override {}
    D3D12_RESOURCE_ALLOCATION_INFO_ABI GetResourceAllocationInfo(uint32_t, uint32_t, const D3D12_RESOURCE_DESC* pDesc) override {
        uint64_t sz = (pDesc && pDesc->Width > 0) ? ((pDesc->Width + 65535ULL) & ~65535ULL) : 65536ULL;
        return { sz, 65536ULL };
    }
    D3D12_HEAP_PROPERTIES GetCustomHeapProperties(uint32_t, D3D12_HEAP_TYPE ht) override {
        return { ht, 0, 0, 1, 1 };
    }
    HRESULT CreateCommittedResource(const D3D12_HEAP_PROPERTIES* pHP, uint32_t flags, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES state, const void* pClear, const IID& riid, void** ppv) override {
        return m_innerDevice->CreateCommittedResource(pHP, flags, pDesc, state, pClear, riid, ppv);
    }
    HRESULT CreateHeap(const void*, const IID&, void** ppv) override { if (ppv) *ppv = nullptr; return S_OK; }
    HRESULT CreatePlacedResource(void*, uint64_t, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES state, const void* pClear, const IID& riid, void** ppv) override {
        D3D12_HEAP_PROPERTIES hp{ D3D12_HEAP_TYPE_DEFAULT, 0, 0, 1, 1 };
        return m_innerDevice->CreateCommittedResource(&hp, 0, pDesc, state, pClear, riid, ppv);
    }
    HRESULT CreateReservedResource(const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES state, const void* pClear, const IID& riid, void** ppv) override {
        D3D12_HEAP_PROPERTIES hp{ D3D12_HEAP_TYPE_DEFAULT, 0, 0, 1, 1 };
        return m_innerDevice->CreateCommittedResource(&hp, 0, pDesc, state, pClear, riid, ppv);
    }
    HRESULT CreateSharedHandle(ID3D12DeviceChild*, const void*, uint32_t, const wchar_t*, void** pHandle) override {
        if (pHandle) *pHandle = reinterpret_cast<void*>(0x77770001ULL);
        return S_OK;
    }
    HRESULT OpenSharedHandle(void*, const IID&, void**) override { return S_OK; }
    HRESULT OpenSharedHandleByName(const wchar_t*, uint32_t, void** pHandle) override {
        if (pHandle) *pHandle = reinterpret_cast<void*>(0x77770001ULL);
        return S_OK;
    }
    HRESULT MakeResident(uint32_t, ID3D12Pageable* const*) override { return S_OK; }
    HRESULT Evict(uint32_t, ID3D12Pageable* const*) override { return S_OK; }
    HRESULT CreateFence(uint64_t val, D3D12_FENCE_FLAGS flags, const IID& riid, void** ppFence) override {
        return m_innerDevice->CreateFence(val, flags, riid, ppFence);
    }
    HRESULT GetDeviceRemovedReason() override { return S_OK; }
    void GetCopyableFootprints(const D3D12_RESOURCE_DESC* pDesc, uint32_t, uint32_t, uint64_t, void*, uint32_t* pRows, uint64_t* pRowSize, uint64_t* pTotal) override {
        uint64_t w = pDesc ? pDesc->Width : 256;
        uint32_t h = pDesc ? pDesc->Height : 256;
        uint64_t pitch = (w * 4 + 255ULL) & ~255ULL;
        if (pRows) *pRows = h;
        if (pRowSize) *pRowSize = w * 4;
        if (pTotal) *pTotal = pitch * h;
    }
    HRESULT CreateQueryHeap(const void*, const IID&, void** ppv) override { if (ppv) *ppv = nullptr; return S_OK; }
    HRESULT SetStablePowerState(int32_t) override { return S_OK; }
    HRESULT CreateCommandSignature(const void*, ID3D12RootSignature*, const IID&, void** ppv) override { if (ppv) *ppv = nullptr; return S_OK; }
    void GetResourceTiling(ID3D12Resource*, uint32_t* pTiles, void*, void*, uint32_t*, uint32_t, void*) override {
        if (pTiles) *pTiles = 1024u;
    }
    LUID GetAdapterLuid() override { return { 0x1000u, 0 }; }
};

using PrismD3D12Device35CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device36CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device37CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device38CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device39CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device40CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device41CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device42CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device43CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device44CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device45CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device46CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device47CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device48CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device49CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device50CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device51CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device52CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device53CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device54CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device55CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device56CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device57CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device58CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device59CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device60CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device61CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device62CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device63CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device64CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device65CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device66CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device67CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device68CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device69CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device70CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device71CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device72CanonicalImpl = PrismD3D12Device14CanonicalImpl;
using PrismD3D12Device73CanonicalImpl = PrismD3D12Device14CanonicalImpl;

// ============================================================================
// 4. Agility SDK D3D12GetInterface & ID3D12SDKConfiguration
// ============================================================================

class ID3D12SDKConfigurationAbi : public IUnknown {
public:
    virtual HRESULT SetSDKVersion(uint32_t SDKVersion, const char* SDKPath) = 0;
};

class PrismD3D12SDKConfigurationImpl : public ID3D12SDKConfigurationAbi {
private:
    std::atomic<uint32_t> m_refCount{ 1 };
    uint32_t              m_sdkVersion{ 614u }; // Agility SDK 1.614+

public:
    HRESULT QueryInterface(const IID& riid, void** ppv) override {
        if (!ppv) return E_POINTER;
        if (riid == IID_IUnknown || riid == OFFICIAL_IID_ID3D12SDKConfiguration) {
            *ppv = static_cast<ID3D12SDKConfigurationAbi*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++m_refCount; }
    uint32_t Release() override {
        uint32_t c = --m_refCount;
        if (c == 0) delete this;
        return c;
    }
    HRESULT SetSDKVersion(uint32_t SDKVersion, const char*) override {
        m_sdkVersion = SDKVersion;
        return S_OK;
    }
    uint32_t GetSDKVersion() const noexcept { return m_sdkVersion; }
};

inline HRESULT D3D12GetInterfaceAbi(const IID& rclsid, const IID& riid, void** ppvDebug) noexcept {
    if (!ppvDebug) return E_INVALIDARG;
    if (rclsid == OFFICIAL_CLSID_D3D12SDKConfiguration) {
        auto* pCfg = new PrismD3D12SDKConfigurationImpl();
        HRESULT hr = pCfg->QueryInterface(riid, ppvDebug);
        pCfg->Release();
        return hr;
    }
    if (rclsid == OFFICIAL_CLSID_D3D12DeviceRemovedExtendedData) {
        auto* pSettings = new PrismD3D12DeviceRemovedExtendedDataSettingsImpl();
        HRESULT hr = pSettings->QueryInterface(riid, ppvDebug);
        pSettings->Release();
        return hr;
    }
    if (rclsid == OFFICIAL_CLSID_D3D12Debug || rclsid == OFFICIAL_CLSID_D3D12DeviceFactory) {
        auto* pDev = new PrismD3D12Device14CanonicalImpl();
        HRESULT hr = pDev->QueryInterface(IID_IUnknown, ppvDebug);
        pDev->Release();
        return hr;
    }
    return E_NOINTERFACE;
}

} // namespace D3D12ComAbi
} // namespace prismx
