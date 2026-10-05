// ============================================================================
// PrismX: Sovereign Graphics Ecosystem
// 
// Modern Pointer, Multi-Touch Gesture & Stylus Inking Geometry Subsystem
// (include/prismx/pointer_input.hpp)
// 
// Clean-Room Implementation in ISO C++23. Zero External Dependencies.
// Tribute to Dave Cutler's 1988 DEC PRISM Architecture.
// ============================================================================

#pragma once

#include <cstdint>
#include <vector>
#include <cmath>
#include <string>
#include <chrono>
#include <functional>
#include <memory>
#include <algorithm>
#include <array>
#include <unordered_map>

namespace prismx::input {

// ============================================================================
// 1. Pointer Types, Buttons & Events
// ============================================================================

enum class PointerDeviceType : uint32_t {
    Mouse    = 0,
    Touch    = 1,
    Pen      = 2,
    Touchpad = 3
};

enum class PointerButtonState : uint32_t {
    None      = 0,
    Left      = 1 << 0,
    Right     = 1 << 1,
    Middle    = 1 << 2,
    Barrel    = 1 << 3,
    Eraser    = 1 << 4
};

inline PointerButtonState operator|(PointerButtonState a, PointerButtonState b) {
    return static_cast<PointerButtonState>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline bool operator&(PointerButtonState a, PointerButtonState b) {
    return (static_cast<uint32_t>(a) & static_cast<uint32_t>(b)) != 0;
}

enum class PointerEventType : uint32_t {
    Down   = 0,
    Move   = 1,
    Up     = 2,
    Cancel = 3,
    Wheel  = 4,
    Hover  = 5
};

struct PointerPoint {
    uint32_t          pointerId{ 0 };
    PointerDeviceType deviceType{ PointerDeviceType::Touch };
    PointerEventType  eventType{ PointerEventType::Down };
    float             x{ 0.0f };
    float             y{ 0.0f };
    float             contactWidth{ 10.0f };
    float             contactHeight{ 10.0f };
    float             pressure{ 0.5f }; // Normalized 0.0f to 1.0f
    float             tiltX{ 0.0f };    // -90 to +90 degrees
    float             tiltY{ 0.0f };    // -90 to +90 degrees
    float             rotation{ 0.0f }; // 0 to 360 degrees
    PointerButtonState buttons{ PointerButtonState::None };
    uint64_t          timestampMs{ 0 };
    bool              isInContact{ true };
    bool              isPrimary{ true };
};

// ============================================================================
// 2. Gesture Recognizer Architecture
// ============================================================================

enum class GestureType : uint32_t {
    None        = 0,
    Tap         = 1,
    DoubleTap   = 2,
    LongPress   = 3,
    Pan         = 4,
    Pinch       = 5,
    Rotate      = 6,
    Swipe       = 7
};

enum class GestureState : uint32_t {
    Possible  = 0,
    Began     = 1,
    Changed   = 2,
    Ended     = 3,
    Cancelled = 4
};

struct GestureEvent {
    GestureType  type{ GestureType::None };
    GestureState state{ GestureState::Possible };
    float        focalX{ 0.0f };
    float        focalY{ 0.0f };
    float        deltaX{ 0.0f };
    float        deltaY{ 0.0f };
    float        scale{ 1.0f };         // For Pinch (1.0 = baseline)
    float        rotationDelta{ 0.0f }; // In radians
    float        velocityX{ 0.0f };     // Pixels / second
    float        velocityY{ 0.0f };
    uint32_t     tapCount{ 0 };
};

using GestureCallback = std::function<void(const GestureEvent&)>;

class GestureRecognizer {
private:
    struct ContactInfo {
        PointerPoint initialPoint;
        PointerPoint currentPoint;
        uint64_t     downTimeMs{ 0 };
        bool         hasMovedBeyondSlop{ false };
    };

    std::unordered_map<uint32_t, ContactInfo> m_contacts;
    std::vector<GestureCallback>              m_callbacks;

    // Dual-touch initial metrics
    float m_initialPinchDistance{ 0.0f };
    float m_initialRotateAngle{ 0.0f };
    bool  m_isPinching{ false };
    bool  m_isRotating{ false };
    bool  m_isPanning{ false };

    // Tap tracking
    uint64_t m_lastTapTimeMs{ 0 };
    float    m_lastTapX{ 0.0f };
    float    m_lastTapY{ 0.0f };

    static constexpr float TOUCH_SLOP = 8.0f; // Pixels
    static constexpr uint64_t DOUBLE_TAP_WINDOW_MS = 350;
    static constexpr uint64_t LONG_PRESS_THRESHOLD_MS = 500;

    void Dispatch(const GestureEvent& ev) {
        for (const auto& cb : m_callbacks) {
            if (cb) cb(ev);
        }
    }

    static float Distance(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }

    static float Angle(float x1, float y1, float x2, float y2) {
        return std::atan2(y2 - y1, x2 - x1);
    }

public:
    void AddCallback(GestureCallback cb) {
        m_callbacks.push_back(cb);
    }

    void ProcessPointerEvent(const PointerPoint& pt) {
        switch (pt.eventType) {
            case PointerEventType::Down: {
                ContactInfo ci;
                ci.initialPoint = pt;
                ci.currentPoint = pt;
                ci.downTimeMs = pt.timestampMs;
                ci.hasMovedBeyondSlop = false;
                m_contacts[pt.pointerId] = ci;

                if (m_contacts.size() == 2) {
                    auto it = m_contacts.begin();
                    const auto& c1 = it->second.currentPoint;
                    ++it;
                    const auto& c2 = it->second.currentPoint;
                    m_initialPinchDistance = Distance(c1.x, c1.y, c2.x, c2.y);
                    m_initialRotateAngle = Angle(c1.x, c1.y, c2.x, c2.y);
                    m_isPinching = true;
                    m_isRotating = true;

                    GestureEvent ge;
                    ge.type = GestureType::Pinch;
                    ge.state = GestureState::Began;
                    ge.focalX = (c1.x + c2.x) * 0.5f;
                    ge.focalY = (c1.y + c2.y) * 0.5f;
                    ge.scale = 1.0f;
                    Dispatch(ge);
                }
                break;
            }

            case PointerEventType::Move: {
                auto it = m_contacts.find(pt.pointerId);
                if (it == m_contacts.end()) return;

                float oldX = it->second.currentPoint.x;
                float oldY = it->second.currentPoint.y;
                it->second.currentPoint = pt;

                float distFromStart = Distance(it->second.initialPoint.x, it->second.initialPoint.y, pt.x, pt.y);
                if (distFromStart > TOUCH_SLOP) {
                    it->second.hasMovedBeyondSlop = true;
                }

                if (m_contacts.size() == 1) {
                    if (it->second.hasMovedBeyondSlop) {
                        GestureEvent ge;
                        ge.type = GestureType::Pan;
                        ge.state = m_isPanning ? GestureState::Changed : GestureState::Began;
                        ge.focalX = pt.x;
                        ge.focalY = pt.y;
                        ge.deltaX = pt.x - oldX;
                        ge.deltaY = pt.y - oldY;

                        float dt = std::max(1.0f, static_cast<float>(pt.timestampMs - it->second.downTimeMs) * 0.001f);
                        ge.velocityX = (pt.x - it->second.initialPoint.x) / dt;
                        ge.velocityY = (pt.y - it->second.initialPoint.y) / dt;

                        m_isPanning = true;
                        Dispatch(ge);
                    }
                } else if (m_contacts.size() >= 2 && m_isPinching) {
                    auto cIt = m_contacts.begin();
                    const auto& c1 = cIt->second.currentPoint;
                    ++cIt;
                    const auto& c2 = cIt->second.currentPoint;

                    float curDist = Distance(c1.x, c1.y, c2.x, c2.y);
                    float curAngle = Angle(c1.x, c1.y, c2.x, c2.y);

                    float scale = (m_initialPinchDistance > 1e-4f) ? (curDist / m_initialPinchDistance) : 1.0f;
                    float rotDelta = curAngle - m_initialRotateAngle;

                    GestureEvent gePinch;
                    gePinch.type = GestureType::Pinch;
                    gePinch.state = GestureState::Changed;
                    gePinch.focalX = (c1.x + c2.x) * 0.5f;
                    gePinch.focalY = (c1.y + c2.y) * 0.5f;
                    gePinch.scale = scale;
                    Dispatch(gePinch);

                    if (std::abs(rotDelta) > 0.02f) { // ~1.1 degrees threshold
                        GestureEvent geRot;
                        geRot.type = GestureType::Rotate;
                        geRot.state = GestureState::Changed;
                        geRot.focalX = gePinch.focalX;
                        geRot.focalY = gePinch.focalY;
                        geRot.rotationDelta = rotDelta;
                        Dispatch(geRot);
                    }
                }
                break;
            }

            case PointerEventType::Up: {
                auto it = m_contacts.find(pt.pointerId);
                if (it == m_contacts.end()) return;

                uint64_t holdDuration = pt.timestampMs - it->second.downTimeMs;
                float distFromStart = Distance(it->second.initialPoint.x, it->second.initialPoint.y, pt.x, pt.y);

                if (!it->second.hasMovedBeyondSlop && distFromStart <= TOUCH_SLOP) {
                    if (holdDuration >= LONG_PRESS_THRESHOLD_MS) {
                        GestureEvent ge;
                        ge.type = GestureType::LongPress;
                        ge.state = GestureState::Ended;
                        ge.focalX = pt.x;
                        ge.focalY = pt.y;
                        Dispatch(ge);
                    } else {
                        // Check for DoubleTap
                        uint64_t tapInterval = pt.timestampMs - m_lastTapTimeMs;
                        float tapDist = Distance(m_lastTapX, m_lastTapY, pt.x, pt.y);

                        if (tapInterval <= DOUBLE_TAP_WINDOW_MS && tapDist <= TOUCH_SLOP * 2.0f) {
                            GestureEvent ge;
                            ge.type = GestureType::DoubleTap;
                            ge.state = GestureState::Ended;
                            ge.focalX = pt.x;
                            ge.focalY = pt.y;
                            ge.tapCount = 2;
                            Dispatch(ge);
                            m_lastTapTimeMs = 0;
                        } else {
                            GestureEvent ge;
                            ge.type = GestureType::Tap;
                            ge.state = GestureState::Ended;
                            ge.focalX = pt.x;
                            ge.focalY = pt.y;
                            ge.tapCount = 1;
                            Dispatch(ge);
                            m_lastTapTimeMs = pt.timestampMs;
                            m_lastTapX = pt.x;
                            m_lastTapY = pt.y;
                        }
                    }
                }

                if (m_isPanning && m_contacts.size() == 1) {
                    GestureEvent ge;
                    ge.type = GestureType::Pan;
                    ge.state = GestureState::Ended;
                    ge.focalX = pt.x;
                    ge.focalY = pt.y;

                    float dt = std::max(0.01f, static_cast<float>(holdDuration) * 0.001f);
                    ge.velocityX = (pt.x - it->second.initialPoint.x) / dt;
                    ge.velocityY = (pt.y - it->second.initialPoint.y) / dt;
                    Dispatch(ge);

                    // High-velocity Swipe / Flick detection (> 500 px/s)
                    float speed = std::sqrt(ge.velocityX * ge.velocityX + ge.velocityY * ge.velocityY);
                    if (speed > 500.0f) {
                        GestureEvent geSwipe;
                        geSwipe.type = GestureType::Swipe;
                        geSwipe.state = GestureState::Ended;
                        geSwipe.focalX = pt.x;
                        geSwipe.focalY = pt.y;
                        geSwipe.velocityX = ge.velocityX;
                        geSwipe.velocityY = ge.velocityY;
                        Dispatch(geSwipe);
                    }
                    m_isPanning = false;
                }

                if (m_contacts.size() == 2 && m_isPinching) {
                    GestureEvent ge;
                    ge.type = GestureType::Pinch;
                    ge.state = GestureState::Ended;
                    ge.scale = 1.0f;
                    Dispatch(ge);
                    m_isPinching = false;
                    m_isRotating = false;
                }

                m_contacts.erase(it);
                break;
            }

            case PointerEventType::Cancel: {
                m_contacts.erase(pt.pointerId);
                m_isPanning = false;
                m_isPinching = false;
                m_isRotating = false;
                break;
            }

            default:
                break;
        }
    }

    size_t GetActiveContactCount() const {
        return m_contacts.size();
    }
};

// ============================================================================
// 3. Stylus Inking Stroke & GPU Geometry Spline Engine
// ============================================================================

enum class PressureCurve : uint32_t {
    Linear  = 0,
    Soft    = 1,
    Hard    = 2,
    Sigmoid = 3
};

struct InkPoint {
    float    x{ 0.0f };
    float    y{ 0.0f };
    float    pressure{ 0.5f }; // 0.0 to 1.0
    float    tiltX{ 0.0f };
    float    tiltY{ 0.0f };
    uint64_t timestampMs{ 0 };
};

struct InkVertex {
    float x{ 0.0f };
    float y{ 0.0f };
    float z{ 0.0f };
    float nx{ 0.0f }; // Normal vector
    float ny{ 0.0f };
    float r{ 0.0f };
    float g{ 0.0f };
    float b{ 0.0f };
    float a{ 1.0f };
    float strokeWidth{ 1.0f };
};

class InkStroke {
private:
    std::vector<InkPoint>  m_rawPoints;
    std::vector<InkPoint>  m_smoothedPoints;
    std::vector<InkVertex> m_triangleStrip;

    float         m_baseWidth{ 6.0f };
    PressureCurve m_curve{ PressureCurve::Soft };
    float         m_colorR{ 0.0f };
    float         m_colorG{ 0.47f };
    float         m_colorB{ 0.84f };
    float         m_colorA{ 1.0f };

    float CalibratePressure(float p) const {
        p = std::clamp(p, 0.01f, 1.0f);
        switch (m_curve) {
            case PressureCurve::Soft:
                return std::sqrt(p);
            case PressureCurve::Hard:
                return p * p;
            case PressureCurve::Sigmoid:
                return 1.0f / (1.0f + std::exp(-10.0f * (p - 0.5f)));
            case PressureCurve::Linear:
            default:
                return p;
        }
    }

    // Catmull-Rom parametric spline interpolation between P1 and P2
    static InkPoint EvaluateCatmullRom(const InkPoint& p0, const InkPoint& p1,
                                       const InkPoint& p2, const InkPoint& p3, float t) {
        float t2 = t * t;
        float t3 = t2 * t;

        InkPoint pt;
        pt.x = 0.5f * ((2.0f * p1.x) +
                       (-p0.x + p2.x) * t +
                       (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * t2 +
                       (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * t3);

        pt.y = 0.5f * ((2.0f * p1.y) +
                       (-p0.y + p2.y) * t +
                       (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * t2 +
                       (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * t3);

        pt.pressure = (1.0f - t) * p1.pressure + t * p2.pressure;
        pt.tiltX = (1.0f - t) * p1.tiltX + t * p2.tiltX;
        pt.tiltY = (1.0f - t) * p1.tiltY + t * p2.tiltY;
        pt.timestampMs = static_cast<uint64_t>((1.0f - t) * p1.timestampMs + t * p2.timestampMs);
        return pt;
    }

public:
    InkStroke(float baseWidth = 6.0f, PressureCurve curve = PressureCurve::Soft)
        : m_baseWidth(baseWidth), m_curve(curve) {}

    void SetColor(float r, float g, float b, float a = 1.0f) {
        m_colorR = r; m_colorG = g; m_colorB = b; m_colorA = a;
    }

    void AddPoint(const InkPoint& pt) {
        m_rawPoints.push_back(pt);
    }

    void FinalizeStroke() {
        if (m_rawPoints.empty()) return;

        m_smoothedPoints.clear();
        m_triangleStrip.clear();

        if (m_rawPoints.size() < 4) {
            m_smoothedPoints = m_rawPoints;
        } else {
            // Perform Catmull-Rom spline subdivision
            m_smoothedPoints.push_back(m_rawPoints.front());
            for (size_t i = 0; i < m_rawPoints.size() - 1; ++i) {
                const auto& p0 = (i == 0) ? m_rawPoints[i] : m_rawPoints[i - 1];
                const auto& p1 = m_rawPoints[i];
                const auto& p2 = m_rawPoints[i + 1];
                const auto& p3 = (i + 2 < m_rawPoints.size()) ? m_rawPoints[i + 2] : p2;

                constexpr int SUBDIVISIONS = 4;
                for (int s = 1; s <= SUBDIVISIONS; ++s) {
                    float t = static_cast<float>(s) / static_cast<float>(SUBDIVISIONS);
                    m_smoothedPoints.push_back(EvaluateCatmullRom(p0, p1, p2, p3, t));
                }
            }
        }

        // Tessellate into GPU Triangle Strip
        if (m_smoothedPoints.size() < 2) return;

        for (size_t i = 0; i < m_smoothedPoints.size(); ++i) {
            float tx = 0.0f, ty = 0.0f;
            if (i == 0) {
                tx = m_smoothedPoints[1].x - m_smoothedPoints[0].x;
                ty = m_smoothedPoints[1].y - m_smoothedPoints[0].y;
            } else if (i == m_smoothedPoints.size() - 1) {
                tx = m_smoothedPoints[i].x - m_smoothedPoints[i - 1].x;
                ty = m_smoothedPoints[i].y - m_smoothedPoints[i - 1].y;
            } else {
                tx = m_smoothedPoints[i + 1].x - m_smoothedPoints[i - 1].x;
                ty = m_smoothedPoints[i + 1].y - m_smoothedPoints[i - 1].y;
            }

            float len = std::sqrt(tx * tx + ty * ty);
            if (len < 1e-4f) len = 1.0f;
            tx /= len;
            ty /= len;

            // Normal orthogonal vector: (-ty, tx)
            float nx = -ty;
            float ny = tx;

            float calibP = CalibratePressure(m_smoothedPoints[i].pressure);
            float width = m_baseWidth * (0.35f + 1.3f * calibP);
            float halfW = width * 0.5f;

            // Left vertex
            InkVertex vLeft;
            vLeft.x = m_smoothedPoints[i].x + nx * halfW;
            vLeft.y = m_smoothedPoints[i].y + ny * halfW;
            vLeft.z = 0.0f;
            vLeft.nx = nx; vLeft.ny = ny;
            vLeft.r = m_colorR; vLeft.g = m_colorG; vLeft.b = m_colorB; vLeft.a = m_colorA;
            vLeft.strokeWidth = width;

            // Right vertex
            InkVertex vRight;
            vRight.x = m_smoothedPoints[i].x - nx * halfW;
            vRight.y = m_smoothedPoints[i].y - ny * halfW;
            vRight.z = 0.0f;
            vRight.nx = -nx; vRight.ny = -ny;
            vRight.r = m_colorR; vRight.g = m_colorG; vRight.b = m_colorB; vRight.a = m_colorA;
            vRight.strokeWidth = width;

            m_triangleStrip.push_back(vLeft);
            m_triangleStrip.push_back(vRight);
        }
    }

    const std::vector<InkPoint>& GetRawPoints() const { return m_rawPoints; }
    const std::vector<InkPoint>& GetSmoothedPoints() const { return m_smoothedPoints; }
    const std::vector<InkVertex>& GetTriangleStrip() const { return m_triangleStrip; }
    size_t GetTriangleCount() const {
        return (m_triangleStrip.size() >= 3) ? (m_triangleStrip.size() - 2) : 0;
    }
};

} // namespace prismx::input
