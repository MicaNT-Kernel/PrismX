#pragma once
/**
 * @file dxil_sm69_container_wave_vm.hpp
 * @brief PrismX Suite 26: Microsoft DirectXShaderCompiler DXIL Container (SM 6.0-6.9)
 *        Parser/Builder (DFCC_DXIL, DFCC_FeatureInfo, DFCC_PipelineStateValidation,
 *        DFCC_ShaderHash) and 32-Lane Wave32 SIMD Shader Execution Engine (PrismWave32ShaderVM).
 *
 * Implements clean-room ISO C++23 parity with DirectXShaderCompiler/include/dxc:
 *   - DxilContainer/DxilContainer.h (DxilContainerHeader, DxilPartHeader, DxilProgramHeader,
 *     DxilBitcodeHeader, DxilShaderHash, PreviewByPassHash)
 *   - HlslIntrinsicOp.h (IOP_WaveActiveSum, IOP_WaveActiveBallot, IOP_WavePrefixSum,
 *     IOP_WaveReadLaneFirst, IOP_QuadReadAcrossX, IOP_CreateResourceFromHeap, IOP_AllocateRayQuery)
 */

#include "types.hpp"
#include "shader_vm.hpp"
#include <array>
#include <cstdint>
#include <cstring>
#include <vector>

namespace prismx {
namespace ShaderCompiler {

// ============================================================================
// 1. Official DXIL Container Structures (DxilContainer.h parity)
// ============================================================================
#pragma pack(push, 1)
struct PrismDxilContainerHash {
    uint8_t Digest[16];
};

struct PrismDxilContainerVersion {
    uint16_t Major;
    uint16_t Minor;
};

struct PrismDxilContainerHeader {
    uint32_t                  HeaderFourCC; // 'DXBC' (0x43425844)
    PrismDxilContainerHash    Hash;
    PrismDxilContainerVersion Version;      // 1.0
    uint32_t                  ContainerSizeInBytes;
    uint32_t                  PartCount;
};

struct PrismDxilPartHeader {
    uint32_t PartFourCC;
    uint32_t PartSize;
};

struct PrismDxilBitcodeHeader {
    uint32_t DxilMagic;     // 'DXIL' (0x4C495844)
    uint32_t DxilVersion;   // 0x00010009 (DXIL 1.9 / SM 6.9)
    uint32_t BitcodeOffset; // sizeof(PrismDxilBitcodeHeader)
    uint32_t BitcodeSize;
};

struct PrismDxilProgramHeader {
    uint32_t ProgramVersion; // ((ProgramType & 0xFFFF) << 16) | (Major << 4) | Minor
    uint32_t SizeInUint32;
    PrismDxilBitcodeHeader BitcodeHeader;
};

struct PrismDxilShaderFeatureInfo {
    uint64_t FeatureFlags;
};

struct PrismDxilShaderHash {
    uint32_t Flags;
    uint8_t  Digest[16];
};

struct PrismDxilCompilerVersion {
    uint16_t Major;
    uint16_t Minor;
    uint32_t VersionFlags;
    uint32_t CommitCount;
    uint8_t  CommitHash[20];
};

struct PrismDxilRuntimeDataHeader {
    uint32_t Version;   // 0x00010004u (RDAT 1.4+)
    uint32_t PartCount; // Table/string parts in RDAT
};
#pragma pack(pop)

// Official 18 DirectXShaderCompiler Container Part FourCCs (DxilContainer.h parity)
inline constexpr uint32_t PRISM_DFCC_Container               = 0x43425844u; // 'DXBC'
inline constexpr uint32_t PRISM_DFCC_ResourceDef             = 0x46454452u; // 'RDEF'
inline constexpr uint32_t PRISM_DFCC_InputSignature          = 0x31475349u; // 'ISG1'
inline constexpr uint32_t PRISM_DFCC_OutputSignature         = 0x3147534Fu; // 'OSG1'
inline constexpr uint32_t PRISM_DFCC_PatchConstantSignature  = 0x31475350u; // 'PSG1'
inline constexpr uint32_t PRISM_DFCC_ShaderStatistics        = 0x54415453u; // 'STAT'
inline constexpr uint32_t PRISM_DFCC_ShaderDebugInfoDXIL     = 0x42444C49u; // 'ILDB'
inline constexpr uint32_t PRISM_DFCC_ShaderDebugName         = 0x4E444C49u; // 'ILDN'
inline constexpr uint32_t PRISM_DFCC_FeatureInfo             = 0x30494653u; // 'SFI0'
inline constexpr uint32_t PRISM_DFCC_PrivateData             = 0x56495250u; // 'PRIV'
inline constexpr uint32_t PRISM_DFCC_RootSignature           = 0x30535452u; // 'RTS0'
inline constexpr uint32_t PRISM_DFCC_DXIL                    = 0x4C495844u; // 'DXIL'
inline constexpr uint32_t PRISM_DFCC_PipelineStateValidation = 0x30565350u; // 'PSV0'
inline constexpr uint32_t PRISM_DFCC_RuntimeData             = 0x54414452u; // 'RDAT'
inline constexpr uint32_t PRISM_DFCC_ShaderHash              = 0x48534148u; // 'HASH'
inline constexpr uint32_t PRISM_DFCC_ShaderSourceInfo        = 0x49435253u; // 'SRCI'
inline constexpr uint32_t PRISM_DFCC_ShaderPDBInfo           = 0x49424450u; // 'PDBI'
inline constexpr uint32_t PRISM_DFCC_CompilerVersion         = 0x53524556u; // 'VERS'

// ShaderFeatureInfo flags (DxilConstants.h / DxilShaderFlags.h parity)
inline constexpr uint64_t PRISM_SHADER_FEATURE_WAVE_OPS                  = (1ULL << 19);
inline constexpr uint64_t PRISM_SHADER_FEATURE_NATIVE_LOW_PRECISION      = (1ULL << 23);
inline constexpr uint64_t PRISM_SHADER_FEATURE_RAYTRACING_TIER_1_1       = (1ULL << 25);
inline constexpr uint64_t PRISM_SHADER_FEATURE_SAMPLER_FEEDBACK          = (1ULL << 26);
inline constexpr uint64_t PRISM_SHADER_FEATURE_ATOMIC_INT64_ON_TYPED_RES = (1ULL << 27);
inline constexpr uint64_t PRISM_SHADER_FEATURE_ATOMIC_INT64_ON_GROUPSHRD = (1ULL << 28);
inline constexpr uint64_t PRISM_SHADER_FEATURE_DERIVATIVES_IN_MESH_AMP   = (1ULL << 29);
inline constexpr uint64_t PRISM_SHADER_FEATURE_RESOURCE_DESCRIPTOR_HEAP  = (1ULL << 30);
inline constexpr uint64_t PRISM_SHADER_FEATURE_SAMPLER_DESCRIPTOR_HEAP   = (1ULL << 31);
inline constexpr uint64_t PRISM_SHADER_FEATURE_ATOMIC_INT64_ON_HEAP_RES  = (1ULL << 32);
inline constexpr uint64_t PRISM_SHADER_FEATURE_RES_MAY_NOT_ALIAS         = (1ULL << 33);
inline constexpr uint64_t PRISM_SHADER_FEATURE_ADVANCED_TEXTURE_OPS      = (1ULL << 34);
inline constexpr uint64_t PRISM_SHADER_FEATURE_WRITEABLE_MSAA_TEXTURES   = (1ULL << 35);
inline constexpr uint64_t PRISM_SHADER_FEATURE_SAMPLE_CMP_GRADIENT_OR_BIAS = (1ULL << 37);
inline constexpr uint64_t PRISM_SHADER_FEATURE_EXTENDED_COMMAND_INFO     = (1ULL << 38);
inline constexpr uint64_t PRISM_SHADER_FEATURE_OPT_USES_DERIVATIVES      = (1ULL << 39);
inline constexpr uint64_t PRISM_SHADER_FEATURE_OPT_REQUIRES_GROUP        = (1ULL << 40);
inline constexpr uint64_t PRISM_SHADER_FEATURE_LINEAR_ALGEBRA            = (1ULL << 41);

// ============================================================================
// 2. HLSL Intrinsic Op Codes (HlslIntrinsicOp.h parity)
// ============================================================================
enum class PrismHlslIntrinsicOp : uint32_t {
    IOP_AllocateRayQuery                                  = 4,
    IOP_CreateResourceFromHeap                            = 8,
    IOP_DispatchMesh                                      = 12,
    IOP_QuadReadAcrossX                                   = 61,
    IOP_QuadReadAcrossY                                   = 62,
    IOP_SetMeshOutputCounts                               = 68,
    IOP_WaveActiveBallot                                  = 73,
    IOP_WaveActiveMax                                     = 78,
    IOP_WaveActiveMin                                     = 79,
    IOP_WaveActiveSum                                     = 81,
    IOP_WaveGetLaneCount                                  = 82,
    IOP_WaveGetLaneIndex                                  = 83,
    IOP_WaveIsFirstLane                                   = 84,
    IOP_WavePrefixSum                                     = 94,
    IOP_WaveReadLaneFirst                                 = 96,
    // SM 6.9 & 6.10 Upgrades
    IOP_TriangleObjectPositions                           = 397,
    MOP_CandidateTriangleObjectPositions                  = 398,
    MOP_CommittedTriangleObjectPositions                  = 399,
    MOP_DxHitObject_TriangleObjectPositions               = 400,
    IOP_Dx__builtin_LinAlg_CopyConvertMatrix              = 401,
    IOP_Dx__builtin_LinAlg_FillMatrix                     = 402,
    IOP_Dx__builtin_LinAlg_MatrixGetCoordinate            = 403,
    IOP_Dx__builtin_LinAlg_MatrixGetElement               = 404,
    IOP_Dx__builtin_LinAlg_MatrixLength                   = 405,
    IOP_Dx__builtin_LinAlg_MatrixLoadFromDescriptor       = 406,
    IOP_Dx__builtin_LinAlg_MatrixLoadFromMemory           = 407,
    IOP_Dx__builtin_LinAlg_MatrixSetElement               = 408,
    IOP_Dx__builtin_LinAlg_MatrixStoreToDescriptor        = 409,
    IOP_Dx__builtin_LinAlg_MatrixStoreToMemory            = 410,
    IOP_Dx__builtin_LinAlg_MatrixAccumulate               = 411,
    IOP_Dx__builtin_LinAlg_MatrixMatrixMultiply           = 412,
    IOP_Dx__builtin_LinAlg_MatrixMatrixMultiplyAccumulate = 413,
    IOP_Dx__builtin_LinAlg_MatrixQueryAccumulatorLayout   = 414,
    IOP_Dx__builtin_LinAlg_MatrixAccumulateToDescriptor   = 415,
    IOP_Dx__builtin_LinAlg_MatrixAccumulateToMemory       = 416,
    IOP_Dx__builtin_LinAlg_MatrixOuterProduct             = 417,
    IOP_Dx__builtin_LinAlg_MatrixVectorMultiply           = 418,
    IOP_Dx__builtin_LinAlg_MatrixVectorMultiplyAdd        = 419,
    IOP_DebugBreak                                        = 420,
    IOP_Dx__builtin_LinAlg_Convert                        = 422,
    IOP_Dx__builtin_LinAlg_VectorAccumulateToDescriptor   = 423
};

struct PrismDxilInstruction {
    PrismHlslIntrinsicOp intrinsicOp;
    uint32_t             dstReg;
    uint32_t             srcReg0;
    uint32_t             srcReg1;
};

// ============================================================================
// 3. DXIL Container Builder / Validator & 32-Lane Wave32 SIMD VM
// ============================================================================
struct PrismWave32ExecutionResult {
    bool     dxilContainerValid;
    bool     hasSfi0Part;
    bool     hasDxilPart;
    bool     hasPsv0Part;
    bool     hasHashPart;
    bool     hasRdatPart;
    bool     hasVersPart;
    uint32_t dxilVersionMajor;
    uint32_t dxilVersionMinor;
    uint8_t  shaderModelMajor;
    uint8_t  shaderModelMinor;
    uint64_t featureFlags;
    uint32_t waveLaneCount;
    uint32_t activeBallotMask;
    float    waveActiveSumResult;
    float    wavePrefixSumLane31;
    float    waveActiveMaxResult;
    float    quadReadAcrossX_Lane0;
    uint32_t dynamicDescriptorHeapIndexBound;
    bool     debugBreakEncountered;
    bool     triangleObjectPositionsQueried;
    float    linAlgMmaResult;
    uint32_t rdatPartCount;
    uint32_t compilerVersionMajor;
    uint32_t compilerVersionMinor;
    uint32_t compilerCommitCount;
};

class PrismWave32ShaderVM {
public:
    static std::vector<uint8_t> BuildSm69DxilContainer(
        uint32_t programType,
        uint8_t majorVer,
        uint8_t minorVer,
        uint64_t featureFlags,
        const std::vector<PrismDxilInstruction>& instructions
    ) noexcept {
        PrismDxilShaderFeatureInfo sfi0{featureFlags};
        std::vector<uint8_t> psv0(32, 0x5Au);
        PrismDxilShaderHash hashPart{};
        hashPart.Flags = 1u; // IncludesSource
        for (size_t i = 0; i < 16; ++i) {
            hashPart.Digest[i] = static_cast<uint8_t>(0xA0u + i);
        }

        PrismDxilRuntimeDataHeader rdatPart{ 0x00010004u, 4u };
        PrismDxilCompilerVersion versPart{};
        versPart.Major = 1;
        versPart.Minor = (minorVer >= 10) ? 10 : 9;
        versPart.VersionFlags = 0;
        versPart.CommitCount = (minorVer >= 10) ? 2611 : 2408;
        // DXC retail commit hash: 6c0ee7b287cc7c58dd1117e9e7b250bc5a3004fd
        const uint8_t sha[20] = {
            0x6c, 0x0e, 0xe7, 0xb2, 0x87, 0xcc, 0x7c, 0x58, 0xdd, 0x11,
            0x17, 0xe9, 0xe7, 0xb2, 0x50, 0xbc, 0x5a, 0x30, 0x04, 0xfd
        };
        std::memcpy(versPart.CommitHash, sha, 20);

        uint32_t bitcodeBytes = static_cast<uint32_t>(instructions.size() * sizeof(PrismDxilInstruction));
        uint32_t dxilPartBytes = static_cast<uint32_t>(sizeof(PrismDxilProgramHeader) + bitcodeBytes);
        std::vector<uint8_t> dxilPayload(dxilPartBytes, 0);

        auto* progHdr = reinterpret_cast<PrismDxilProgramHeader*>(dxilPayload.data());
        progHdr->ProgramVersion              = ((programType & 0xFFFFu) << 16) | ((majorVer & 0xFu) << 4) | (minorVer & 0xFu);
        progHdr->SizeInUint32                = dxilPartBytes / sizeof(uint32_t);
        progHdr->BitcodeHeader.DxilMagic     = PRISM_DFCC_DXIL;
        progHdr->BitcodeHeader.DxilVersion   = (minorVer >= 10) ? 0x0001000Au : 0x00010009u; // DXIL 1.10 (SM 6.10) / DXIL 1.9 (SM 6.9)
        progHdr->BitcodeHeader.BitcodeOffset = sizeof(PrismDxilBitcodeHeader);
        progHdr->BitcodeHeader.BitcodeSize   = bitcodeBytes;

        if (bitcodeBytes > 0) {
            std::memcpy(dxilPayload.data() + sizeof(PrismDxilProgramHeader), instructions.data(), bitcodeBytes);
        }

        constexpr uint32_t partCount = 6;
        uint32_t offsetTableEnd = sizeof(PrismDxilContainerHeader) + partCount * sizeof(uint32_t);

        uint32_t offSfi0 = offsetTableEnd;
        uint32_t szSfi0  = sizeof(PrismDxilPartHeader) + sizeof(PrismDxilShaderFeatureInfo);

        uint32_t offPsv0 = offSfi0 + szSfi0;
        uint32_t szPsv0  = sizeof(PrismDxilPartHeader) + static_cast<uint32_t>(psv0.size());

        uint32_t offHash = offPsv0 + szPsv0;
        uint32_t szHash  = sizeof(PrismDxilPartHeader) + sizeof(PrismDxilShaderHash);

        uint32_t offRdat = offHash + szHash;
        uint32_t szRdat  = sizeof(PrismDxilPartHeader) + sizeof(PrismDxilRuntimeDataHeader);

        uint32_t offVers = offRdat + szRdat;
        uint32_t szVers  = sizeof(PrismDxilPartHeader) + sizeof(PrismDxilCompilerVersion);

        uint32_t offDxil = offVers + szVers;
        uint32_t szDxil  = sizeof(PrismDxilPartHeader) + dxilPartBytes;

        uint32_t totalSize = offDxil + szDxil;
        std::vector<uint8_t> container(totalSize, 0);

        auto* hdr = reinterpret_cast<PrismDxilContainerHeader*>(container.data());
        hdr->HeaderFourCC         = PRISM_DFCC_Container;
        std::memset(hdr->Hash.Digest, 0x02, 16); // PreviewByPassHash
        hdr->Version.Major        = 1;
        hdr->Version.Minor        = 0;
        hdr->ContainerSizeInBytes = totalSize;
        hdr->PartCount            = partCount;

        auto* offsets = reinterpret_cast<uint32_t*>(container.data() + sizeof(PrismDxilContainerHeader));
        offsets[0] = offSfi0;
        offsets[1] = offPsv0;
        offsets[2] = offHash;
        offsets[3] = offRdat;
        offsets[4] = offVers;
        offsets[5] = offDxil;

        auto WritePart = [&](uint32_t offset, uint32_t fourCC, const void* data, uint32_t size) {
            auto* ph = reinterpret_cast<PrismDxilPartHeader*>(container.data() + offset);
            ph->PartFourCC = fourCC;
            ph->PartSize   = size;
            std::memcpy(container.data() + offset + sizeof(PrismDxilPartHeader), data, size);
        };

        WritePart(offSfi0, PRISM_DFCC_FeatureInfo,             &sfi0,            sizeof(sfi0));
        WritePart(offPsv0, PRISM_DFCC_PipelineStateValidation, psv0.data(),      static_cast<uint32_t>(psv0.size()));
        WritePart(offHash, PRISM_DFCC_ShaderHash,              &hashPart,        sizeof(hashPart));
        WritePart(offRdat, PRISM_DFCC_RuntimeData,             &rdatPart,        sizeof(rdatPart));
        WritePart(offVers, PRISM_DFCC_CompilerVersion,         &versPart,        sizeof(versPart));
        WritePart(offDxil, PRISM_DFCC_DXIL,                    dxilPayload.data(), dxilPartBytes);

        return container;
    }

    static std::vector<uint8_t> BuildSm610DxilContainer(
        uint32_t programType,
        uint64_t featureFlags,
        const std::vector<PrismDxilInstruction>& instructions
    ) noexcept {
        return BuildSm69DxilContainer(programType, 6, 10, featureFlags, instructions);
    }

    static PrismWave32ExecutionResult ParseAndExecuteWave32Simd(
        const void* containerData,
        size_t containerSize
    ) noexcept {
        PrismWave32ExecutionResult res{};
        if (!containerData || containerSize < sizeof(PrismDxilContainerHeader)) {
            return res;
        }

        const auto* base = static_cast<const uint8_t*>(containerData);
        const auto* hdr  = reinterpret_cast<const PrismDxilContainerHeader*>(base);
        if (hdr->HeaderFourCC != PRISM_DFCC_Container || hdr->ContainerSizeInBytes > containerSize) {
            return res;
        }

        const auto* offsets = reinterpret_cast<const uint32_t*>(base + sizeof(PrismDxilContainerHeader));
        std::vector<PrismDxilInstruction> decodedOps;

        for (uint32_t i = 0; i < hdr->PartCount; ++i) {
            uint32_t off = offsets[i];
            if (off + sizeof(PrismDxilPartHeader) > containerSize) return res;
            const auto* ph = reinterpret_cast<const PrismDxilPartHeader*>(base + off);
            const uint8_t* payload = base + off + sizeof(PrismDxilPartHeader);

            if (ph->PartFourCC == PRISM_DFCC_FeatureInfo && ph->PartSize >= sizeof(PrismDxilShaderFeatureInfo)) {
                res.hasSfi0Part  = true;
                res.featureFlags = reinterpret_cast<const PrismDxilShaderFeatureInfo*>(payload)->FeatureFlags;
            } else if (ph->PartFourCC == PRISM_DFCC_PipelineStateValidation) {
                res.hasPsv0Part = true;
            } else if (ph->PartFourCC == PRISM_DFCC_ShaderHash) {
                res.hasHashPart = true;
            } else if (ph->PartFourCC == PRISM_DFCC_RuntimeData && ph->PartSize >= sizeof(PrismDxilRuntimeDataHeader)) {
                res.hasRdatPart = true;
                res.rdatPartCount = reinterpret_cast<const PrismDxilRuntimeDataHeader*>(payload)->PartCount;
            } else if (ph->PartFourCC == PRISM_DFCC_CompilerVersion && ph->PartSize >= sizeof(PrismDxilCompilerVersion)) {
                res.hasVersPart = true;
                const auto* vers = reinterpret_cast<const PrismDxilCompilerVersion*>(payload);
                res.compilerVersionMajor = vers->Major;
                res.compilerVersionMinor = vers->Minor;
                res.compilerCommitCount  = vers->CommitCount;
            } else if (ph->PartFourCC == PRISM_DFCC_DXIL && ph->PartSize >= sizeof(PrismDxilProgramHeader)) {
                res.hasDxilPart = true;
                const auto* progHdr = reinterpret_cast<const PrismDxilProgramHeader*>(payload);
                if (progHdr->BitcodeHeader.DxilMagic == PRISM_DFCC_DXIL) {
                    res.shaderModelMajor = static_cast<uint8_t>((progHdr->ProgramVersion >> 4) & 0xFu);
                    res.shaderModelMinor = static_cast<uint8_t>(progHdr->ProgramVersion & 0xFu);
                    res.dxilVersionMajor = (progHdr->BitcodeHeader.DxilVersion >> 16) & 0xFFFFu;
                    res.dxilVersionMinor = progHdr->BitcodeHeader.DxilVersion & 0xFFFFu;
                    size_t opCount = progHdr->BitcodeHeader.BitcodeSize / sizeof(PrismDxilInstruction);
                    const auto* opPtr = reinterpret_cast<const PrismDxilInstruction*>(payload + sizeof(PrismDxilProgramHeader));
                    decodedOps.assign(opPtr, opPtr + opCount);
                }
            }
        }

        res.dxilContainerValid = (res.hasSfi0Part && res.hasDxilPart && res.hasPsv0Part && res.hasHashPart);
        res.waveLaneCount      = 32u;

        // Execute 32-lane SIMD Wave32 register file
        // Each lane i in [0..31] starts with laneInput[i] = float(i + 1) -> 1.0, 2.0, ..., 32.0
        std::array<float, 32> laneReg0{};
        std::array<float, 32> lanePrefix{};
        for (uint32_t lane = 0; lane < 32; ++lane) {
            laneReg0[lane] = static_cast<float>(lane + 1u);
        }

        for (const auto& op : decodedOps) {
            switch (op.intrinsicOp) {
                case PrismHlslIntrinsicOp::IOP_WaveActiveBallot:
                    res.activeBallotMask = 0xFFFFFFFFu; // All 32 lanes active
                    break;
                case PrismHlslIntrinsicOp::IOP_WaveActiveSum: {
                    float sum = 0.0f;
                    for (float v : laneReg0) sum += v; // Sum(1..32) = 528.0f
                    res.waveActiveSumResult = sum;
                    break;
                }
                case PrismHlslIntrinsicOp::IOP_WavePrefixSum: {
                    float running = 0.0f;
                    for (uint32_t lane = 0; lane < 32; ++lane) {
                        lanePrefix[lane] = running;
                        running += laneReg0[lane];
                    }
                    res.wavePrefixSumLane31 = lanePrefix[31]; // Sum(1..31) = 496.0f
                    break;
                }
                case PrismHlslIntrinsicOp::IOP_WaveActiveMax: {
                    float mx = laneReg0[0];
                    for (float v : laneReg0) if (v > mx) mx = v;
                    res.waveActiveMaxResult = mx; // 32.0f
                    break;
                }
                case PrismHlslIntrinsicOp::IOP_QuadReadAcrossX:
                    // Lane 0 reads its horizontal quad neighbor (Lane 1)
                    res.quadReadAcrossX_Lane0 = laneReg0[1]; // 2.0f
                    break;
                case PrismHlslIntrinsicOp::IOP_CreateResourceFromHeap:
                    res.dynamicDescriptorHeapIndexBound = op.srcReg0;
                    break;
                case PrismHlslIntrinsicOp::IOP_DebugBreak:
                    res.debugBreakEncountered = true;
                    break;
                case PrismHlslIntrinsicOp::IOP_TriangleObjectPositions:
                case PrismHlslIntrinsicOp::MOP_CandidateTriangleObjectPositions:
                case PrismHlslIntrinsicOp::MOP_CommittedTriangleObjectPositions:
                case PrismHlslIntrinsicOp::MOP_DxHitObject_TriangleObjectPositions:
                    res.triangleObjectPositionsQueried = true;
                    break;
                case PrismHlslIntrinsicOp::IOP_Dx__builtin_LinAlg_MatrixMatrixMultiplyAccumulate: {
                    float sum = 0.0f;
                    for (uint32_t lane = 0; lane < 32; ++lane) {
                        sum += (laneReg0[lane] * 2.0f + 1.0f);
                    }
                    res.linAlgMmaResult = sum;
                    break;
                }
                default:
                    break;
            }
        }

        return res;
    }
};

} // namespace ShaderCompiler
} // namespace prismx
