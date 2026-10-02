// ============================================================================
// PrismX: Sovereign 3D Math Engine (DirectXMath / SimpleMath Parity)
//
// Strict Clean-Room Implementation in modern ISO C++23. Zero External Dependencies.
// Compatible with Microsoft DirectXMath and DirectXTK SimpleMath conventions.
// Left-Handed Coordinate System (+X Right, +Y Up, +Z Forward).
// ============================================================================

#pragma once

#include <cmath>
#include <array>
#include <algorithm>
#include <numbers>

namespace prismx::math {

// ============================================================================
// 1. Vector2
// ============================================================================

struct Vector2 {
    float x{0.0f};
    float y{0.0f};

    constexpr Vector2() = default;
    constexpr Vector2(float x_, float y_) : x(x_), y(y_) {}
    explicit constexpr Vector2(float s) : x(s), y(s) {}

    constexpr Vector2 operator+(const Vector2& o) const noexcept { return {x + o.x, y + o.y}; }
    constexpr Vector2 operator-(const Vector2& o) const noexcept { return {x - o.x, y - o.y}; }
    constexpr Vector2 operator*(float s) const noexcept { return {x * s, y * s}; }
    constexpr Vector2 operator/(float s) const noexcept { return {x / s, y / s}; }

    float Length() const noexcept { return std::sqrt(x * x + y * y); }
    float LengthSquared() const noexcept { return x * x + y * y; }
    float Dot(const Vector2& o) const noexcept { return x * o.x + y * o.y; }

    Vector2 Normalized() const noexcept {
        float len = Length();
        return (len > 0.00001f) ? (*this / len) : Vector2{0.0f, 0.0f};
    }
};

// ============================================================================
// 2. Vector3
// ============================================================================

struct Vector3 {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};

    constexpr Vector3() = default;
    constexpr Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    explicit constexpr Vector3(float s) : x(s), y(s), z(s) {}

    constexpr Vector3 operator+(const Vector3& o) const noexcept { return {x + o.x, y + o.y, z + o.z}; }
    constexpr Vector3 operator-(const Vector3& o) const noexcept { return {x - o.x, y - o.y, z - o.z}; }
    constexpr Vector3 operator*(float s) const noexcept { return {x * s, y * s, z * s}; }
    constexpr Vector3 operator/(float s) const noexcept { return {x / s, y / s, z / s}; }

    Vector3& operator+=(const Vector3& o) noexcept { x += o.x; y += o.y; z += o.z; return *this; }
    Vector3& operator-=(const Vector3& o) noexcept { x -= o.x; y -= o.y; z -= o.z; return *this; }
    Vector3& operator*=(float s) noexcept { x *= s; y *= s; z *= s; return *this; }
    Vector3& operator/=(float s) noexcept { x /= s; y /= s; z /= s; return *this; }

    constexpr bool operator==(const Vector3& o) const noexcept {
        return x == o.x && y == o.y && z == o.z;
    }

    float Length() const noexcept { return std::sqrt(x * x + y * y + z * z); }
    float LengthSquared() const noexcept { return x * x + y * y + z * z; }
    float Dot(const Vector3& o) const noexcept { return x * o.x + y * o.y + z * o.z; }

    Vector3 Cross(const Vector3& o) const noexcept {
        return {
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        };
    }

    Vector3 Normalized() const noexcept {
        float len = Length();
        return (len > 0.00001f) ? (*this / len) : Vector3{0.0f, 0.0f, 0.0f};
    }

    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t) noexcept {
        return a + (b - a) * t;
    }

    static float Distance(const Vector3& a, const Vector3& b) noexcept {
        return (a - b).Length();
    }

    static const Vector3 Zero;
    static const Vector3 One;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
    static const Vector3 Up;
    static const Vector3 Forward;
};

inline constexpr Vector3 Vector3::Zero{0.0f, 0.0f, 0.0f};
inline constexpr Vector3 Vector3::One{1.0f, 1.0f, 1.0f};
inline constexpr Vector3 Vector3::UnitX{1.0f, 0.0f, 0.0f};
inline constexpr Vector3 Vector3::UnitY{0.0f, 1.0f, 0.0f};
inline constexpr Vector3 Vector3::UnitZ{0.0f, 0.0f, 1.0f};
inline constexpr Vector3 Vector3::Up{0.0f, 1.0f, 0.0f};
inline constexpr Vector3 Vector3::Forward{0.0f, 0.0f, 1.0f};

// ============================================================================
// 3. Vector4
// ============================================================================

struct Vector4 {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
    float w{0.0f};

    constexpr Vector4() = default;
    constexpr Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
    constexpr Vector4(const Vector3& v, float w_) : x(v.x), y(v.y), z(v.z), w(w_) {}

    constexpr Vector4 operator+(const Vector4& o) const noexcept { return {x + o.x, y + o.y, z + o.z, w + o.w}; }
    constexpr Vector4 operator-(const Vector4& o) const noexcept { return {x - o.x, y - o.y, z - o.z, w - o.w}; }
    constexpr Vector4 operator*(float s) const noexcept { return {x * s, y * s, z * s, w * s}; }

    float Dot(const Vector4& o) const noexcept { return x * o.x + y * o.y + z * o.z + w * o.w; }
};

// ============================================================================
// 4. Matrix 4x4 (Row-Major Storage, Left-Handed DirectX Conventions)
// ============================================================================

struct Matrix {
    float m[4][4]{
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    constexpr Matrix() = default;

    constexpr Matrix(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
    ) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
        m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }

    static constexpr Matrix Identity() noexcept {
        return Matrix();
    }

    static constexpr Matrix Zero() noexcept {
        return Matrix(
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        );
    }

    static Matrix CreateTranslation(float x, float y, float z) noexcept {
        Matrix r = Identity();
        r.m[3][0] = x;
        r.m[3][1] = y;
        r.m[3][2] = z;
        return r;
    }

    static Matrix CreateTranslation(const Vector3& pos) noexcept {
        return CreateTranslation(pos.x, pos.y, pos.z);
    }

    static Matrix CreateScale(float sx, float sy, float sz) noexcept {
        Matrix r = Identity();
        r.m[0][0] = sx;
        r.m[1][1] = sy;
        r.m[2][2] = sz;
        return r;
    }

    static Matrix CreateScale(float s) noexcept {
        return CreateScale(s, s, s);
    }

    static Matrix CreateRotationX(float radians) noexcept {
        Matrix r = Identity();
        float c = std::cos(radians);
        float s = std::sin(radians);
        r.m[1][1] = c;
        r.m[1][2] = s;
        r.m[2][1] = -s;
        r.m[2][2] = c;
        return r;
    }

    static Matrix CreateRotationY(float radians) noexcept {
        Matrix r = Identity();
        float c = std::cos(radians);
        float s = std::sin(radians);
        r.m[0][0] = c;
        r.m[0][2] = -s;
        r.m[2][0] = s;
        r.m[2][2] = c;
        return r;
    }

    static Matrix CreateRotationZ(float radians) noexcept {
        Matrix r = Identity();
        float c = std::cos(radians);
        float s = std::sin(radians);
        r.m[0][0] = c;
        r.m[0][1] = s;
        r.m[1][0] = -s;
        r.m[1][1] = c;
        return r;
    }

    /**
     * @brief Creates a Left-Handed LookAt View Matrix.
     */
    static Matrix CreateLookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up) noexcept {
        Vector3 zAxis = (target - eye).Normalized();
        Vector3 xAxis = up.Cross(zAxis).Normalized();
        Vector3 yAxis = zAxis.Cross(xAxis);

        Matrix r = Identity();
        r.m[0][0] = xAxis.x; r.m[0][1] = yAxis.x; r.m[0][2] = zAxis.x;
        r.m[1][0] = xAxis.y; r.m[1][1] = yAxis.y; r.m[1][2] = zAxis.y;
        r.m[2][0] = xAxis.z; r.m[2][1] = yAxis.z; r.m[2][2] = zAxis.z;

        r.m[3][0] = -xAxis.Dot(eye);
        r.m[3][1] = -yAxis.Dot(eye);
        r.m[3][2] = -zAxis.Dot(eye);
        return r;
    }

    /**
     * @brief Creates a Left-Handed Perspective Field of View Matrix.
     */
    static Matrix CreatePerspectiveFovLH(float fovY, float aspectRatio, float nearZ, float farZ) noexcept {
        float yScale = 1.0f / std::tan(fovY * 0.5f);
        float xScale = yScale / aspectRatio;

        Matrix r = Zero();
        r.m[0][0] = xScale;
        r.m[1][1] = yScale;
        r.m[2][2] = farZ / (farZ - nearZ);
        r.m[2][3] = 1.0f;
        r.m[3][2] = (-nearZ * farZ) / (farZ - nearZ);
        return r;
    }

    // DirectXTK / SimpleMath compatibility aliases
    static Matrix Translation(float x, float y, float z) noexcept { return CreateTranslation(x, y, z); }
    static Matrix Translation(const Vector3& pos) noexcept { return CreateTranslation(pos); }
    static Matrix Scale(float sx, float sy, float sz) noexcept { return CreateScale(sx, sy, sz); }
    static Matrix Scale(float s) noexcept { return CreateScale(s); }
    static Matrix RotationX(float radians) noexcept { return CreateRotationX(radians); }
    static Matrix RotationY(float radians) noexcept { return CreateRotationY(radians); }
    static Matrix RotationZ(float radians) noexcept { return CreateRotationZ(radians); }
    static Matrix LookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up) noexcept { return CreateLookAtLH(eye, target, up); }
    static Matrix PerspectiveFovLH(float fovY, float aspectRatio, float nearZ, float farZ) noexcept { return CreatePerspectiveFovLH(fovY, aspectRatio, nearZ, farZ); }
    static Matrix Multiply(const Matrix& a, const Matrix& b) noexcept { return a * b; }

    Matrix operator*(const Matrix& o) const noexcept {
        Matrix r{};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                r.m[i][j] = m[i][0] * o.m[0][j] +
                            m[i][1] * o.m[1][j] +
                            m[i][2] * o.m[2][j] +
                            m[i][3] * o.m[3][j];
            }
        }
        return r;
    }

    Vector4 Transform(const Vector4& v) const noexcept {
        return {
            v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + v.w * m[3][0],
            v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + v.w * m[3][1],
            v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + v.w * m[3][2],
            v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + v.w * m[3][3]
        };
    }

    Vector3 TransformCoord(const Vector3& v) const noexcept {
        Vector4 res = Transform(Vector4(v, 1.0f));
        if (std::abs(res.w) > 0.00001f) {
            return { res.x / res.w, res.y / res.w, res.z / res.w };
        }
        return { res.x, res.y, res.z };
    }

    Matrix Transpose() const noexcept {
        Matrix r{};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                r.m[i][j] = m[j][i];
            }
        }
        return r;
    }
};

// ============================================================================
// 5. Color (RGBA Float)
// ============================================================================

struct Color {
    float r{0.0f};
    float g{0.0f};
    float b{0.0f};
    float a{1.0f};

    constexpr Color() = default;
    constexpr Color(float r_, float g_, float b_, float a_ = 1.0f) : r(r_), g(g_), b(b_), a(a_) {}

    uint32_t ToBgra8888() const noexcept {
        uint32_t ur = static_cast<uint32_t>(std::clamp(r * 255.0f, 0.0f, 255.0f));
        uint32_t ug = static_cast<uint32_t>(std::clamp(g * 255.0f, 0.0f, 255.0f));
        uint32_t ub = static_cast<uint32_t>(std::clamp(b * 255.0f, 0.0f, 255.0f));
        uint32_t ua = static_cast<uint32_t>(std::clamp(a * 255.0f, 0.0f, 255.0f));
        return (ua << 24) | (ur << 16) | (ug << 8) | ub;
    }
};

} // namespace prismx::math
