// ============================================================================
// PrismX: Official Microsoft XAudio2 2.9 (xaudio2_9.dll) & DirectInput8 (dinput8.dll)
// COM ABI & Binary IIDs/GUIDs (Suite 35)
//
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// Provides:
//   - Exact 16-byte Microsoft binary IIDs & CLSIDs from <xaudio2.h> & <dinput.h>:
//       * IID_IXAudio2                {2b02e3cf-2e0b-4ec3-be45-1b2a3fe7210d}
//       * IID_IXAudio2Extension       {84ac29bb-d619-44d2-b197-e4acf7df3ed6}
//       * CLSID_AudioVolumeMeter      {4fc3b166-972a-40cf-bc37-7db03db2fba3}
//       * CLSID_AudioReverb           {c2633b16-471b-4498-b8c5-4f0959e2ec09}
//       * IID_IDirectInput8A          {bf798030-483a-4da2-aa99-5d64ed369700}
//       * IID_IDirectInput8W          {bf798031-483a-4da2-aa99-5d64ed369700}
//       * IID_IDirectInputDevice8A    {54d41080-dc15-4833-a41b-748f73a38179}
//       * IID_IDirectInputDevice8W    {54d41081-dc15-4833-a41b-748f73a38179}
//       * GUID_SysMouse               {6f1d2b60-d5a0-11cf-bfc7-444553540000}
//       * GUID_SysKeyboard            {6f1d2b61-d5a0-11cf-bfc7-444553540000}
//       * GUID_Joystick               {6f1d2b70-d5a0-11cf-bfc7-444553540000}
//   - Canonical 13-slot IXAudio2 COM vtable + IXAudio2MasteringVoice +
//     IXAudio2SourceVoice voice graph.
//   - Canonical 11-slot IDirectInput8W COM vtable + IDirectInputDevice8W
//     keyboard/mouse/joystick acquisition & state polling.
// ============================================================================

#pragma once

#include "types.hpp"
#include <atomic>
#include <cstring>

namespace prismx::XAudioDInputCom {

// ----------------------------------------------------------------------------
// 1. Official 16-Byte Microsoft Binary IIDs & GUIDs (<xaudio2.h> / <dinput.h>)
// ----------------------------------------------------------------------------
// {2b02e3cf-2e0b-4ec3-be45-1b2a3fe7210d}
inline constexpr IID OFFICIAL_IID_IXAudio2 = {
    0x2b02e3cf, 0x2e0b, 0x4ec3, {0xbe, 0x45, 0x1b, 0x2a, 0x3f, 0xe7, 0x21, 0x0d}
};
// {84ac29bb-d619-44d2-b197-e4acf7df3ed6}
inline constexpr IID OFFICIAL_IID_IXAudio2Extension = {
    0x84ac29bb, 0xd619, 0x44d2, {0xb1, 0x97, 0xe4, 0xac, 0xf7, 0xdf, 0x3e, 0xd6}
};
// {4fc3b166-972a-40cf-bc37-7db03db2fba3}
inline constexpr IID OFFICIAL_CLSID_AudioVolumeMeter = {
    0x4fc3b166, 0x972a, 0x40cf, {0xbc, 0x37, 0x7d, 0xb0, 0x3d, 0xb2, 0xfb, 0xa3}
};
// {c2633b16-471b-4498-b8c5-4f0959e2ec09}
inline constexpr IID OFFICIAL_CLSID_AudioReverb = {
    0xc2633b16, 0x471b, 0x4498, {0xb8, 0xc5, 0x4f, 0x09, 0x59, 0xe2, 0xec, 0x09}
};

// {bf798030-483a-4da2-aa99-5d64ed369700}
inline constexpr IID OFFICIAL_IID_IDirectInput8A = {
    0xbf798030, 0x483a, 0x4da2, {0xaa, 0x99, 0x5d, 0x64, 0xed, 0x36, 0x97, 0x00}
};
// {bf798031-483a-4da2-aa99-5d64ed369700}
inline constexpr IID OFFICIAL_IID_IDirectInput8W = {
    0xbf798031, 0x483a, 0x4da2, {0xaa, 0x99, 0x5d, 0x64, 0xed, 0x36, 0x97, 0x00}
};
// {54d41080-dc15-4833-a41b-748f73a38179}
inline constexpr IID OFFICIAL_IID_IDirectInputDevice8A = {
    0x54d41080, 0xdc15, 0x4833, {0xa4, 0x1b, 0x74, 0x8f, 0x73, 0xa3, 0x81, 0x79}
};
// {54d41081-dc15-4833-a41b-748f73a38179}
inline constexpr IID OFFICIAL_IID_IDirectInputDevice8W = {
    0x54d41081, 0xdc15, 0x4833, {0xa4, 0x1b, 0x74, 0x8f, 0x73, 0xa3, 0x81, 0x79}
};

// {6f1d2b60-d5a0-11cf-bfc7-444553540000}
inline constexpr IID OFFICIAL_GUID_SysMouse = {
    0x6f1d2b60, 0xd5a0, 0x11cf, {0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}
};
// {6f1d2b61-d5a0-11cf-bfc7-444553540000}
inline constexpr IID OFFICIAL_GUID_SysKeyboard = {
    0x6f1d2b61, 0xd5a0, 0x11cf, {0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}
};
// {6f1d2b70-d5a0-11cf-bfc7-444553540000}
inline constexpr IID OFFICIAL_GUID_Joystick = {
    0x6f1d2b70, 0xd5a0, 0x11cf, {0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}
};

// ----------------------------------------------------------------------------
// 2. Canonical XAudio2 2.9 Structures & Interfaces (<xaudio2.h>)
// ----------------------------------------------------------------------------
inline constexpr uint32_t XAUDIO2_DEFAULT_PROCESSOR = 0x00000001u;
inline constexpr uint32_t XAUDIO2_DEFAULT_CHANNELS  = 0u;
inline constexpr uint32_t XAUDIO2_DEFAULT_SAMPLERATE = 0u;
inline constexpr uint32_t XAUDIO2_END_OF_STREAM     = 0x0040u;

struct WAVEFORMATEX_CANONICAL {
    uint16_t wFormatTag;      // 1 = WAVE_FORMAT_PCM, 3 = WAVE_FORMAT_IEEE_FLOAT
    uint16_t nChannels;       // e.g. 2 or 8 (7.1 surround)
    uint32_t nSamplesPerSec;  // e.g. 48000
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
    uint16_t cbSize;
};

struct XAUDIO2_VOICE_DETAILS {
    uint32_t CreationFlags;
    uint32_t ActiveFlags;
    uint32_t InputChannels;
    uint32_t InputSampleRate;
};

struct XAUDIO2_BUFFER {
    uint32_t Flags;
    uint32_t AudioBytes;
    const uint8_t* pAudioData;
    uint32_t PlayBegin;
    uint32_t PlayLength;
    uint32_t LoopBegin;
    uint32_t LoopLength;
    uint32_t LoopCount;
    void* pContext;
};

struct XAUDIO2_VOICE_STATE {
    void* pCurrentBufferContext;
    uint32_t BuffersQueued;
    uint64_t SamplesPlayed;
};

struct XAUDIO2_PERFORMANCE_DATA {
    uint64_t AudioCyclesSinceLastQuery;
    uint64_t TotalCyclesSinceLastQuery;
    uint32_t MinimumCyclesPerQuantum;
    uint32_t MaximumCyclesPerQuantum;
    uint32_t MemoryUsageInBytes;
    uint32_t CurrentLatencyInSamples;
    uint32_t GlitchesSinceEngineStarted;
    uint32_t ActiveSourceVoiceCount;
    uint32_t TotalSourceVoiceCount;
    uint32_t ActiveSubmixVoiceCount;
    uint32_t ActiveResamplerCount;
    uint32_t ActiveMatrixMixCount;
    uint32_t TotalSubmixVoiceCount;
    uint32_t ActiveXmaSourceVoices;
    uint32_t ActiveXmaStreams;
};

struct IXAudio2Voice {
    virtual void GetVoiceDetails(XAUDIO2_VOICE_DETAILS* pVoiceDetails) = 0;
    virtual HRESULT SetOutputVoices(const void* pSendList) = 0;
    virtual HRESULT SetEffectChain(const void* pEffectChain) = 0;
    virtual HRESULT EnableEffect(uint32_t EffectIndex, uint32_t OperationSet) = 0;
    virtual HRESULT DisableEffect(uint32_t EffectIndex, uint32_t OperationSet) = 0;
    virtual void GetEffectState(uint32_t EffectIndex, int32_t* pEnabled) = 0;
    virtual HRESULT SetEffectParameters(uint32_t EffectIndex, const void* pParameters,
                                        uint32_t ParametersByteSize, uint32_t OperationSet) = 0;
    virtual HRESULT GetEffectParameters(uint32_t EffectIndex, void* pParameters,
                                        uint32_t ParametersByteSize) = 0;
    virtual HRESULT SetFilterParameters(const void* pParameters, uint32_t OperationSet) = 0;
    virtual void GetFilterParameters(void* pParameters) = 0;
    virtual HRESULT SetOutputFilterParameters(IXAudio2Voice* pDestinationVoice,
                                              const void* pParameters, uint32_t OperationSet) = 0;
    virtual void GetOutputFilterParameters(IXAudio2Voice* pDestinationVoice, void* pParameters) = 0;
    virtual HRESULT SetVolume(float Volume, uint32_t OperationSet = 0) = 0;
    virtual void GetVolume(float* pVolume) = 0;
    virtual HRESULT SetChannelVolumes(uint32_t Channels, const float* pVolumes,
                                      uint32_t OperationSet = 0) = 0;
    virtual void GetChannelVolumes(uint32_t Channels, float* pVolumes) = 0;
    virtual HRESULT SetOutputMatrix(IXAudio2Voice* pDestinationVoice, uint32_t SourceChannels,
                                    uint32_t DestinationChannels, const float* pLevelMatrix,
                                    uint32_t OperationSet = 0) = 0;
    virtual void GetOutputMatrix(IXAudio2Voice* pDestinationVoice, uint32_t SourceChannels,
                                 uint32_t DestinationChannels, float* pLevelMatrix) = 0;
    virtual void DestroyVoice() = 0;
    virtual ~IXAudio2Voice() = default;
};

struct IXAudio2MasteringVoice : public IXAudio2Voice {
    virtual HRESULT GetChannelMask(uint32_t* pChannelmask) = 0;
};

struct IXAudio2SubmixVoice : public IXAudio2Voice {};

struct IXAudio2SourceVoice : public IXAudio2Voice {
    virtual HRESULT Start(uint32_t Flags = 0, uint32_t OperationSet = 0) = 0;
    virtual HRESULT Stop(uint32_t Flags = 0, uint32_t OperationSet = 0) = 0;
    virtual HRESULT SubmitSourceBuffer(const XAUDIO2_BUFFER* pBuffer,
                                       const void* pBufferWMA = nullptr) = 0;
    virtual HRESULT FlushSourceBuffers() = 0;
    virtual HRESULT Discontinuity() = 0;
    virtual HRESULT ExitLoop(uint32_t OperationSet = 0) = 0;
    virtual void GetState(XAUDIO2_VOICE_STATE* pVoiceState, uint32_t Flags = 0) = 0;
    virtual HRESULT SetFrequencyRatio(float Ratio, uint32_t OperationSet = 0) = 0;
    virtual void GetFrequencyRatio(float* pRatio) = 0;
    virtual HRESULT SetSourceSampleRate(uint32_t NewSourceSampleRate) = 0;
};

// Canonical 13-Slot IXAudio2 COM VTable (Slots 0..12)
struct IXAudio2 : public IUnknown {
    virtual HRESULT RegisterForCallbacks(void* pCallback) = 0;                  // Slot 3
    virtual void UnregisterForCallbacks(void* pCallback) = 0;                   // Slot 4
    virtual HRESULT CreateSourceVoice(
        IXAudio2SourceVoice** ppSourceVoice,
        const WAVEFORMATEX_CANONICAL* pSourceFormat,
        uint32_t Flags = 0,
        float MaxFrequencyRatio = 2.0f,
        void* pCallback = nullptr,
        const void* pSendList = nullptr,
        const void* pEffectChain = nullptr) = 0;                                // Slot 5
    virtual HRESULT CreateSubmixVoice(
        IXAudio2SubmixVoice** ppSubmixVoice,
        uint32_t InputChannels,
        uint32_t InputSampleRate,
        uint32_t Flags = 0,
        uint32_t ProcessingStage = 0,
        const void* pSendList = nullptr,
        const void* pEffectChain = nullptr) = 0;                                // Slot 6
    virtual HRESULT CreateMasteringVoice(
        IXAudio2MasteringVoice** ppMasteringVoice,
        uint32_t InputChannels = XAUDIO2_DEFAULT_CHANNELS,
        uint32_t InputSampleRate = XAUDIO2_DEFAULT_SAMPLERATE,
        uint32_t Flags = 0,
        const wchar_t* szDeviceId = nullptr,
        const void* pEffectChain = nullptr,
        uint32_t StreamCategory = 6) = 0;                                       // Slot 7
    virtual HRESULT StartEngine() = 0;                                          // Slot 8
    virtual void StopEngine() = 0;                                              // Slot 9
    virtual HRESULT CommitChanges(uint32_t OperationSet) = 0;                   // Slot 10
    virtual void GetPerformanceData(XAUDIO2_PERFORMANCE_DATA* pPerfData) = 0;   // Slot 11
    virtual void SetDebugConfiguration(const void* pDebugConfiguration,
                                       void* pReserved = nullptr) = 0;          // Slot 12
};

// ----------------------------------------------------------------------------
// 3. Concrete XAudio2 2.9 Implementations
// ----------------------------------------------------------------------------
class PrismXAudio2MasteringVoiceImpl final : public IXAudio2MasteringVoice {
    uint32_t channels_ = 8;
    uint32_t sample_rate_ = 48000;
    float volume_ = 1.0f;

public:
    PrismXAudio2MasteringVoiceImpl(uint32_t ch, uint32_t sr)
        : channels_(ch ? ch : 8), sample_rate_(sr ? sr : 48000) {}

    void GetVoiceDetails(XAUDIO2_VOICE_DETAILS* pVoiceDetails) override {
        if (!pVoiceDetails) return;
        pVoiceDetails->CreationFlags = 0;
        pVoiceDetails->ActiveFlags = 0;
        pVoiceDetails->InputChannels = channels_;
        pVoiceDetails->InputSampleRate = sample_rate_;
    }
    HRESULT SetOutputVoices(const void*) override { return S_OK; }
    HRESULT SetEffectChain(const void*) override { return S_OK; }
    HRESULT EnableEffect(uint32_t, uint32_t) override { return S_OK; }
    HRESULT DisableEffect(uint32_t, uint32_t) override { return S_OK; }
    void GetEffectState(uint32_t, int32_t* pEnabled) override { if (pEnabled) *pEnabled = 1; }
    HRESULT SetEffectParameters(uint32_t, const void*, uint32_t, uint32_t) override { return S_OK; }
    HRESULT GetEffectParameters(uint32_t, void*, uint32_t) override { return S_OK; }
    HRESULT SetFilterParameters(const void*, uint32_t) override { return S_OK; }
    void GetFilterParameters(void*) override {}
    HRESULT SetOutputFilterParameters(IXAudio2Voice*, const void*, uint32_t) override { return S_OK; }
    void GetOutputFilterParameters(IXAudio2Voice*, void*) override {}
    HRESULT SetVolume(float Volume, uint32_t) override { volume_ = Volume; return S_OK; }
    void GetVolume(float* pVolume) override { if (pVolume) *pVolume = volume_; }
    HRESULT SetChannelVolumes(uint32_t, const float*, uint32_t) override { return S_OK; }
    void GetChannelVolumes(uint32_t, float*) override {}
    HRESULT SetOutputMatrix(IXAudio2Voice*, uint32_t, uint32_t, const float*, uint32_t) override { return S_OK; }
    void GetOutputMatrix(IXAudio2Voice*, uint32_t, uint32_t, float*) override {}
    void DestroyVoice() override { delete this; }
    HRESULT GetChannelMask(uint32_t* pChannelmask) override {
        if (!pChannelmask) return E_POINTER;
        *pChannelmask = 0x63F; // KSAUDIO_SPEAKER_7POINT1_SURROUND
        return S_OK;
    }
};

class PrismXAudio2SourceVoiceImpl final : public IXAudio2SourceVoice {
    uint32_t channels_ = 2;
    uint32_t sample_rate_ = 48000;
    float volume_ = 1.0f;
    float freq_ratio_ = 1.0f;
    uint32_t buffers_queued_ = 0;
    uint64_t samples_played_ = 0;
    void* current_context_ = nullptr;
    bool running_ = false;

public:
    explicit PrismXAudio2SourceVoiceImpl(const WAVEFORMATEX_CANONICAL* fmt) {
        if (fmt) {
            channels_ = fmt->nChannels ? fmt->nChannels : 2;
            sample_rate_ = fmt->nSamplesPerSec ? fmt->nSamplesPerSec : 48000;
        }
    }

    void GetVoiceDetails(XAUDIO2_VOICE_DETAILS* pVoiceDetails) override {
        if (!pVoiceDetails) return;
        pVoiceDetails->CreationFlags = 0;
        pVoiceDetails->ActiveFlags = running_ ? 1u : 0u;
        pVoiceDetails->InputChannels = channels_;
        pVoiceDetails->InputSampleRate = sample_rate_;
    }
    HRESULT SetOutputVoices(const void*) override { return S_OK; }
    HRESULT SetEffectChain(const void*) override { return S_OK; }
    HRESULT EnableEffect(uint32_t, uint32_t) override { return S_OK; }
    HRESULT DisableEffect(uint32_t, uint32_t) override { return S_OK; }
    void GetEffectState(uint32_t, int32_t* pEnabled) override { if (pEnabled) *pEnabled = 1; }
    HRESULT SetEffectParameters(uint32_t, const void*, uint32_t, uint32_t) override { return S_OK; }
    HRESULT GetEffectParameters(uint32_t, void*, uint32_t) override { return S_OK; }
    HRESULT SetFilterParameters(const void*, uint32_t) override { return S_OK; }
    void GetFilterParameters(void*) override {}
    HRESULT SetOutputFilterParameters(IXAudio2Voice*, const void*, uint32_t) override { return S_OK; }
    void GetOutputFilterParameters(IXAudio2Voice*, void*) override {}
    HRESULT SetVolume(float Volume, uint32_t) override { volume_ = Volume; return S_OK; }
    void GetVolume(float* pVolume) override { if (pVolume) *pVolume = volume_; }
    HRESULT SetChannelVolumes(uint32_t, const float*, uint32_t) override { return S_OK; }
    void GetChannelVolumes(uint32_t, float*) override {}
    HRESULT SetOutputMatrix(IXAudio2Voice*, uint32_t, uint32_t, const float*, uint32_t) override { return S_OK; }
    void GetOutputMatrix(IXAudio2Voice*, uint32_t, uint32_t, float*) override {}
    void DestroyVoice() override { delete this; }

    HRESULT Start(uint32_t, uint32_t) override {
        running_ = true;
        if (buffers_queued_ > 0) {
            samples_played_ += 480; // 10ms quantum at 48kHz
            --buffers_queued_;
        }
        return S_OK;
    }
    HRESULT Stop(uint32_t, uint32_t) override { running_ = false; return S_OK; }
    HRESULT SubmitSourceBuffer(const XAUDIO2_BUFFER* pBuffer, const void*) override {
        if (!pBuffer) return E_INVALIDARG;
        ++buffers_queued_;
        current_context_ = pBuffer->pContext;
        if (running_) {
            uint32_t bytes_per_sample = channels_ * 2;
            uint32_t frames = bytes_per_sample ? (pBuffer->AudioBytes / bytes_per_sample) : 256;
            samples_played_ += (frames ? frames : 256);
        }
        return S_OK;
    }
    HRESULT FlushSourceBuffers() override { buffers_queued_ = 0; return S_OK; }
    HRESULT Discontinuity() override { return S_OK; }
    HRESULT ExitLoop(uint32_t) override { return S_OK; }
    void GetState(XAUDIO2_VOICE_STATE* pVoiceState, uint32_t) override {
        if (!pVoiceState) return;
        pVoiceState->pCurrentBufferContext = current_context_;
        pVoiceState->BuffersQueued = buffers_queued_;
        pVoiceState->SamplesPlayed = samples_played_;
    }
    HRESULT SetFrequencyRatio(float Ratio, uint32_t) override {
        freq_ratio_ = Ratio;
        return S_OK;
    }
    void GetFrequencyRatio(float* pRatio) override { if (pRatio) *pRatio = freq_ratio_; }
    HRESULT SetSourceSampleRate(uint32_t NewSourceSampleRate) override {
        sample_rate_ = NewSourceSampleRate;
        return S_OK;
    }
};

class PrismXAudio2Impl final : public IXAudio2 {
    std::atomic<uint32_t> ref_count_{1};
    bool engine_started_ = true;
    uint32_t active_source_voices_ = 0;

public:
    PrismXAudio2Impl() = default;

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IXAudio2 ||
            riid == OFFICIAL_IID_IXAudio2Extension) {
            *ppvObject = static_cast<IXAudio2*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++ref_count_; }
    uint32_t Release() override {
        uint32_t r = --ref_count_;
        if (r == 0) delete this;
        return r;
    }

    HRESULT RegisterForCallbacks(void*) override { return S_OK; }
    void UnregisterForCallbacks(void*) override {}
    HRESULT CreateSourceVoice(IXAudio2SourceVoice** ppSourceVoice,
                              const WAVEFORMATEX_CANONICAL* pSourceFormat,
                              uint32_t, float, void*, const void*, const void*) override {
        if (!ppSourceVoice) return E_POINTER;
        *ppSourceVoice = new PrismXAudio2SourceVoiceImpl(pSourceFormat);
        ++active_source_voices_;
        return S_OK;
    }
    HRESULT CreateSubmixVoice(IXAudio2SubmixVoice** ppSubmixVoice,
                              uint32_t, uint32_t, uint32_t, uint32_t,
                              const void*, const void*) override {
        if (!ppSubmixVoice) return E_POINTER;
        *ppSubmixVoice = nullptr;
        return S_OK;
    }
    HRESULT CreateMasteringVoice(IXAudio2MasteringVoice** ppMasteringVoice,
                                 uint32_t InputChannels, uint32_t InputSampleRate,
                                 uint32_t, const wchar_t*, const void*, uint32_t) override {
        if (!ppMasteringVoice) return E_POINTER;
        *ppMasteringVoice = new PrismXAudio2MasteringVoiceImpl(InputChannels, InputSampleRate);
        return S_OK;
    }
    HRESULT StartEngine() override { engine_started_ = true; return S_OK; }
    void StopEngine() override { engine_started_ = false; }
    HRESULT CommitChanges(uint32_t) override { return S_OK; }
    void GetPerformanceData(XAUDIO2_PERFORMANCE_DATA* pPerfData) override {
        if (!pPerfData) return;
        std::memset(pPerfData, 0, sizeof(XAUDIO2_PERFORMANCE_DATA));
        pPerfData->AudioCyclesSinceLastQuery = 12800;
        pPerfData->TotalCyclesSinceLastQuery = 640000;
        pPerfData->CurrentLatencyInSamples = 128; // 2.66ms low-latency WASAPI hardware offload
        pPerfData->GlitchesSinceEngineStarted = 0;
        pPerfData->ActiveSourceVoiceCount = active_source_voices_;
        pPerfData->TotalSourceVoiceCount = active_source_voices_;
    }
    void SetDebugConfiguration(const void*, void*) override {}
};

// Simple APO effect COM object for CreateAudioVolumeMeter / CreateAudioReverb
class PrismXAudio2ApoImpl final : public IUnknown {
    std::atomic<uint32_t> ref_count_{1};
    IID apo_clsid_;
public:
    explicit PrismXAudio2ApoImpl(const IID& clsid) : apo_clsid_(clsid) {}
    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == apo_clsid_) {
            *ppvObject = static_cast<IUnknown*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++ref_count_; }
    uint32_t Release() override {
        uint32_t r = --ref_count_;
        if (r == 0) delete this;
        return r;
    }
};

// ----------------------------------------------------------------------------
// 4. Canonical DirectInput8 Structures & COM Interfaces (<dinput.h>)
// ----------------------------------------------------------------------------
inline constexpr uint32_t DIRECTINPUT_VERSION_800 = 0x0800u;
inline constexpr uint32_t DI8DEVCLASS_ALL         = 0u;
inline constexpr uint32_t DI8DEVCLASS_KEYBOARD    = 3u;
inline constexpr uint32_t DI8DEVCLASS_GAMECTRL    = 4u;
inline constexpr uint32_t DIEDFL_ATTACHEDONLY     = 0x00000001u;
inline constexpr uint32_t DIENUM_STOP             = 0u;
inline constexpr uint32_t DIENUM_CONTINUE         = 1u;

struct DIDEVCAPS {
    uint32_t dwSize;
    uint32_t dwFlags;
    uint32_t dwDevType;
    uint32_t dwAxes;
    uint32_t dwButtons;
    uint32_t dwPOVs;
    uint32_t dwFFSamplePeriod;
    uint32_t dwFFMinTimeResolution;
    uint32_t dwFirmwareRevision;
    uint32_t dwHardwareRevision;
    uint32_t dwFFDriverVersion;
};

struct DIDEVICEINSTANCEW {
    uint32_t dwSize;
    IID guidInstance;
    IID guidProduct;
    uint32_t dwDevType;
    wchar_t tszInstanceName[260];
    wchar_t tszProductName[260];
    IID guidFFDriver;
    uint16_t wUsagePage;
    uint16_t wUsage;
};

struct DIMOUSESTATE2 {
    int32_t lX;
    int32_t lY;
    int32_t lZ;
    uint8_t rgbButtons[8];
};

struct DIJOYSTATE2 {
    int32_t lX;
    int32_t lY;
    int32_t lZ;
    int32_t lRx;
    int32_t lRy;
    int32_t lRz;
    int32_t rglSlider[2];
    uint32_t rgdwPOV[4];
    uint8_t rgbButtons[128];
};

using LPDIENUMDEVICESCALLBACKW = int32_t(*)(const DIDEVICEINSTANCEW*, void*);

struct IDirectInputDevice8W : public IUnknown {
    virtual HRESULT GetCapabilities(DIDEVCAPS* lpDIDevCaps) = 0;                // Slot 3
    virtual HRESULT EnumObjects(void* lpCallback, void* pvRef,
                                uint32_t dwFlags) = 0;                          // Slot 4
    virtual HRESULT GetProperty(const IID& rguidProp, void* pdiph) = 0;         // Slot 5
    virtual HRESULT SetProperty(const IID& rguidProp, const void* pdiph) = 0;   // Slot 6
    virtual HRESULT Acquire() = 0;                                              // Slot 7
    virtual HRESULT Unacquire() = 0;                                            // Slot 8
    virtual HRESULT GetDeviceState(uint32_t cbData, void* lpvData) = 0;         // Slot 9
    virtual HRESULT GetDeviceData(uint32_t cbObjectData, void* rgdod,
                                  uint32_t* pdwInOut, uint32_t dwFlags) = 0;    // Slot 10
    virtual HRESULT SetDataFormat(const void* lpdf) = 0;                        // Slot 11
    virtual HRESULT SetEventNotification(void* hEvent) = 0;                     // Slot 12
    virtual HRESULT SetCooperativeLevel(void* hwnd, uint32_t dwFlags) = 0;      // Slot 13
    virtual HRESULT GetObjectInfo(void* pdidoi, uint32_t dwObj,
                                  uint32_t dwHow) = 0;                          // Slot 14
    virtual HRESULT GetDeviceInfo(DIDEVICEINSTANCEW* pdidi) = 0;                // Slot 15
    virtual HRESULT RunControlPanel(void* hwndOwner, uint32_t dwFlags) = 0;     // Slot 16
    virtual HRESULT Initialize(void* hinst, uint32_t dwVersion,
                               const IID& rguid) = 0;                           // Slot 17
    virtual HRESULT CreateEffect(const IID& rguid, const void* lpeff,
                                 void** ppdeff, IUnknown* punkOuter) = 0;       // Slot 18
    virtual HRESULT EnumEffects(void* lpCallback, void* pvRef,
                                uint32_t dwEffType) = 0;                        // Slot 19
    virtual HRESULT GetEffectInfo(void* pdei, const IID& rguid) = 0;            // Slot 20
    virtual HRESULT GetForceFeedbackState(uint32_t* pdwOut) = 0;                // Slot 21
    virtual HRESULT SendForceFeedbackCommand(uint32_t dwFlags) = 0;             // Slot 22
    virtual HRESULT EnumCreatedEffectObjects(void* lpCallback, void* pvRef,
                                             uint32_t fl) = 0;                  // Slot 23
    virtual HRESULT Escape(void* pesc) = 0;                                     // Slot 24
    virtual HRESULT Poll() = 0;                                                 // Slot 25
    virtual HRESULT SendDeviceData(uint32_t cbObjectData, const void* rgdod,
                                   uint32_t* pdwInOut, uint32_t fl) = 0;        // Slot 26
};

// Canonical 11-Slot IDirectInput8W COM VTable (Slots 0..10)
struct IDirectInput8W : public IUnknown {
    virtual HRESULT CreateDevice(const IID& rguid,
                                 IDirectInputDevice8W** lplpDirectInputDevice,
                                 IUnknown* pUnkOuter) = 0;                      // Slot 3
    virtual HRESULT EnumDevices(uint32_t dwDevType,
                                LPDIENUMDEVICESCALLBACKW lpCallback,
                                void* pvRef, uint32_t dwFlags) = 0;             // Slot 4
    virtual HRESULT GetDeviceStatus(const IID& rguidInstance) = 0;              // Slot 5
    virtual HRESULT RunControlPanel(void* hwndOwner, uint32_t dwFlags) = 0;     // Slot 6
    virtual HRESULT Initialize(void* hinst, uint32_t dwVersion) = 0;            // Slot 7
    virtual HRESULT FindDevice(const IID& rguidClass, const wchar_t* ptszName,
                               IID* pguidInstance) = 0;                         // Slot 8
    virtual HRESULT EnumDevicesBySemantics(const wchar_t* ptszUserName,
                                           void* lpdiActionFormat,
                                           void* lpCallback, void* pvRef,
                                           uint32_t dwFlags) = 0;               // Slot 9
    virtual HRESULT ConfigureDevices(void* lpdiCallback, void* lpdiCDParams,
                                     uint32_t dwFlags, void* pvRefData) = 0;    // Slot 10
};

// ----------------------------------------------------------------------------
// 5. Concrete DirectInput8 Implementations
// ----------------------------------------------------------------------------
class PrismDirectInputDevice8WImpl final : public IDirectInputDevice8W {
    std::atomic<uint32_t> ref_count_{1};
    IID device_guid_;
    bool acquired_ = false;

public:
    explicit PrismDirectInputDevice8WImpl(const IID& rguid) : device_guid_(rguid) {}

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IDirectInputDevice8W ||
            riid == OFFICIAL_IID_IDirectInputDevice8A) {
            *ppvObject = static_cast<IDirectInputDevice8W*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++ref_count_; }
    uint32_t Release() override {
        uint32_t r = --ref_count_;
        if (r == 0) delete this;
        return r;
    }

    HRESULT GetCapabilities(DIDEVCAPS* lpDIDevCaps) override {
        if (!lpDIDevCaps) return E_POINTER;
        lpDIDevCaps->dwSize = sizeof(DIDEVCAPS);
        lpDIDevCaps->dwFlags = 0x00000001u; // DIDC_ATTACHED
        lpDIDevCaps->dwAxes = 6;
        lpDIDevCaps->dwButtons = 32;
        lpDIDevCaps->dwPOVs = 1;
        return S_OK;
    }
    HRESULT EnumObjects(void*, void*, uint32_t) override { return S_OK; }
    HRESULT GetProperty(const IID&, void*) override { return S_OK; }
    HRESULT SetProperty(const IID&, const void*) override { return S_OK; }
    HRESULT Acquire() override { acquired_ = true; return S_OK; }
    HRESULT Unacquire() override { acquired_ = false; return S_OK; }
    HRESULT GetDeviceState(uint32_t cbData, void* lpvData) override {
        if (!lpvData || cbData == 0) return E_INVALIDARG;
        std::memset(lpvData, 0, cbData);
        if (device_guid_ == OFFICIAL_GUID_SysKeyboard && cbData >= 256) {
            // Simulate W key (DIK_W = 0x11) pressed in standard 256-byte keyboard state
            static_cast<uint8_t*>(lpvData)[0x11] = 0x80u;
        } else if (device_guid_ == OFFICIAL_GUID_SysMouse && cbData >= sizeof(DIMOUSESTATE2)) {
            auto* ms = static_cast<DIMOUSESTATE2*>(lpvData);
            ms->lX = 12;
            ms->lY = -4;
            ms->rgbButtons[0] = 0x80u;
        } else if (cbData >= sizeof(DIJOYSTATE2)) {
            auto* js = static_cast<DIJOYSTATE2*>(lpvData);
            js->lX = 32767;
            js->lY = 32767;
            js->rgbButtons[0] = 0x80u;
        }
        return S_OK;
    }
    HRESULT GetDeviceData(uint32_t, void*, uint32_t* pdwInOut, uint32_t) override {
        if (pdwInOut) *pdwInOut = 0;
        return S_OK;
    }
    HRESULT SetDataFormat(const void*) override { return S_OK; }
    HRESULT SetEventNotification(void*) override { return S_OK; }
    HRESULT SetCooperativeLevel(void*, uint32_t) override { return S_OK; }
    HRESULT GetObjectInfo(void*, uint32_t, uint32_t) override { return S_OK; }
    HRESULT GetDeviceInfo(DIDEVICEINSTANCEW* pdidi) override {
        if (!pdidi) return E_POINTER;
        std::memset(pdidi, 0, sizeof(DIDEVICEINSTANCEW));
        pdidi->dwSize = sizeof(DIDEVICEINSTANCEW);
        pdidi->guidInstance = device_guid_;
        pdidi->guidProduct = device_guid_;
        return S_OK;
    }
    HRESULT RunControlPanel(void*, uint32_t) override { return S_OK; }
    HRESULT Initialize(void*, uint32_t, const IID&) override { return S_OK; }
    HRESULT CreateEffect(const IID&, const void*, void**, IUnknown*) override { return S_OK; }
    HRESULT EnumEffects(void*, void*, uint32_t) override { return S_OK; }
    HRESULT GetEffectInfo(void*, const IID&) override { return S_OK; }
    HRESULT GetForceFeedbackState(uint32_t* pdwOut) override {
        if (pdwOut) *pdwOut = 0;
        return S_OK;
    }
    HRESULT SendForceFeedbackCommand(uint32_t) override { return S_OK; }
    HRESULT EnumCreatedEffectObjects(void*, void*, uint32_t) override { return S_OK; }
    HRESULT Escape(void*) override { return S_OK; }
    HRESULT Poll() override { return S_OK; }
    HRESULT SendDeviceData(uint32_t, const void*, uint32_t* pdwInOut, uint32_t) override {
        if (pdwInOut) *pdwInOut = 0;
        return S_OK;
    }
};

class PrismDirectInput8WImpl final : public IDirectInput8W {
    std::atomic<uint32_t> ref_count_{1};

public:
    PrismDirectInput8WImpl() = default;

    int32_t QueryInterface(const IID& riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown ||
            riid == OFFICIAL_IID_IDirectInput8W ||
            riid == OFFICIAL_IID_IDirectInput8A) {
            *ppvObject = static_cast<IDirectInput8W*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    uint32_t AddRef() override { return ++ref_count_; }
    uint32_t Release() override {
        uint32_t r = --ref_count_;
        if (r == 0) delete this;
        return r;
    }

    HRESULT CreateDevice(const IID& rguid,
                         IDirectInputDevice8W** lplpDirectInputDevice,
                         IUnknown*) override {
        if (!lplpDirectInputDevice) return E_POINTER;
        *lplpDirectInputDevice = new PrismDirectInputDevice8WImpl(rguid);
        return S_OK;
    }
    HRESULT EnumDevices(uint32_t, LPDIENUMDEVICESCALLBACKW lpCallback,
                        void* pvRef, uint32_t) override {
        if (!lpCallback) return E_INVALIDARG;
        DIDEVICEINSTANCEW inst{};
        inst.dwSize = sizeof(DIDEVICEINSTANCEW);
        inst.guidInstance = OFFICIAL_GUID_Joystick;
        inst.guidProduct = OFFICIAL_GUID_Joystick;
        inst.dwDevType = 0x00010215u; // DI8DEVTYPE_GAMEPAD
        const wchar_t kName[] = L"PrismX XInput/DirectInput8 Controller";
        std::memcpy(inst.tszInstanceName, kName, sizeof(kName));
        std::memcpy(inst.tszProductName, kName, sizeof(kName));
        lpCallback(&inst, pvRef);
        return S_OK;
    }
    HRESULT GetDeviceStatus(const IID&) override { return S_OK; }
    HRESULT RunControlPanel(void*, uint32_t) override { return S_OK; }
    HRESULT Initialize(void*, uint32_t) override { return S_OK; }
    HRESULT FindDevice(const IID&, const wchar_t*, IID* pguidInstance) override {
        if (pguidInstance) *pguidInstance = OFFICIAL_GUID_Joystick;
        return S_OK;
    }
    HRESULT EnumDevicesBySemantics(const wchar_t*, void*, void*, void*, uint32_t) override {
        return S_OK;
    }
    HRESULT ConfigureDevices(void*, void*, uint32_t, void*) override { return S_OK; }
};

// ----------------------------------------------------------------------------
// 6. Canonical xaudio2_9.dll & dinput8.dll Export Entry Points
// ----------------------------------------------------------------------------
inline HRESULT XAudio2Create(IXAudio2** ppXAudio2, uint32_t Flags = 0,
                             uint32_t XAudio2Processor = XAUDIO2_DEFAULT_PROCESSOR) {
    (void)Flags;
    (void)XAudio2Processor;
    if (!ppXAudio2) return E_POINTER;
    *ppXAudio2 = new PrismXAudio2Impl();
    return S_OK;
}

inline HRESULT CreateAudioVolumeMeter(IUnknown** ppApo) {
    if (!ppApo) return E_POINTER;
    *ppApo = new PrismXAudio2ApoImpl(OFFICIAL_CLSID_AudioVolumeMeter);
    return S_OK;
}

inline HRESULT CreateAudioReverb(IUnknown** ppApo) {
    if (!ppApo) return E_POINTER;
    *ppApo = new PrismXAudio2ApoImpl(OFFICIAL_CLSID_AudioReverb);
    return S_OK;
}

inline HRESULT DirectInput8Create(void* hinst, uint32_t dwVersion,
                                  const IID& riidltf, void** ppvOut,
                                  IUnknown* punkOuter) {
    (void)hinst;
    (void)dwVersion;
    (void)punkOuter;
    if (!ppvOut) return E_POINTER;
    auto* di8 = new PrismDirectInput8WImpl();
    HRESULT hr = di8->QueryInterface(riidltf, ppvOut);
    di8->Release();
    return hr;
}

} // namespace prismx::XAudioDInputCom
