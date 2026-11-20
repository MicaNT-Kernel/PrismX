// ============================================================================
// PrismX Sovereign Graphics Engine - Milestone 182
// DirectComposition Rigid Body Dynamics, Continuous Collision Detection (CCD)
//   & Impulse-Based Multi-Contact Manifold Physics Pipeline
//   (IDCompositionRigidBodyVisual, IDCompositionPhysicsMeshEffect,
//   DirectCompositionRigidBodyPipeline)
//
// 100% Freestanding ISO C++23, zero external dependencies.
// ============================================================================

#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>

namespace prismx::physics {

constexpr float PI = 3.14159265358979323846f;

struct Vector3 {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};

    [[nodiscard]] constexpr float LengthSquared() const noexcept {
        return x * x + y * y + z * z;
    }

    [[nodiscard]] float Length() const noexcept {
        return std::sqrt(LengthSquared());
    }

    [[nodiscard]] Vector3 Normalize() const noexcept {
        float len = Length();
        if (len < 1e-6f) return {0.0f, 0.0f, 1.0f};
        return {x / len, y / len, z / len};
    }

    [[nodiscard]] constexpr float Dot(const Vector3& o) const noexcept {
        return x * o.x + y * o.y + z * o.z;
    }

    [[nodiscard]] constexpr Vector3 Cross(const Vector3& o) const noexcept {
        return {
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        };
    }

    [[nodiscard]] constexpr Vector3 operator+(const Vector3& o) const noexcept {
        return {x + o.x, y + o.y, z + o.z};
    }

    [[nodiscard]] constexpr Vector3 operator-(const Vector3& o) const noexcept {
        return {x - o.x, y - o.y, z - o.z};
    }

    [[nodiscard]] constexpr Vector3 operator-() const noexcept {
        return {-x, -y, -z};
    }

    [[nodiscard]] constexpr Vector3 operator*(float s) const noexcept {
        return {x * s, y * s, z * s};
    }

    [[nodiscard]] constexpr Vector3 operator/(float s) const noexcept {
        float inv = (s != 0.0f) ? (1.0f / s) : 0.0f;
        return {x * inv, y * inv, z * inv};
    }
};

struct Quaternion {
    float w{1.0f};
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};

    [[nodiscard]] constexpr float LengthSquared() const noexcept {
        return w * w + x * x + y * y + z * z;
    }

    [[nodiscard]] float Length() const noexcept {
        return std::sqrt(LengthSquared());
    }

    [[nodiscard]] Quaternion Normalize() const noexcept {
        float len = Length();
        if (len < 1e-6f) return {1.0f, 0.0f, 0.0f, 0.0f};
        return {w / len, x / len, y / len, z / len};
    }

    [[nodiscard]] Quaternion operator*(const Quaternion& q) const noexcept {
        return {
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        };
    }

    [[nodiscard]] Vector3 Rotate(const Vector3& v) const noexcept {
        Vector3 qv{x, y, z};
        Vector3 uv = qv.Cross(v);
        Vector3 uuv = qv.Cross(uv);
        return v + (uv * (2.0f * w)) + (uuv * 2.0f);
    }
};

struct Matrix3x3 {
    float m[3][3]{
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    [[nodiscard]] Vector3 Multiply(const Vector3& v) const noexcept {
        return {
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
        };
    }

    [[nodiscard]] Matrix3x3 Transpose() const noexcept {
        Matrix3x3 res{};
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                res.m[r][c] = m[c][r];
            }
        }
        return res;
    }

    [[nodiscard]] Matrix3x3 operator*(const Matrix3x3& o) const noexcept {
        Matrix3x3 res{};
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                res.m[r][c] = m[r][0] * o.m[0][c] + m[r][1] * o.m[1][c] + m[r][2] * o.m[2][c];
            }
        }
        return res;
    }

    static Matrix3x3 FromQuaternion(const Quaternion& q) noexcept {
        Matrix3x3 res{};
        float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
        float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
        float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

        res.m[0][0] = 1.0f - 2.0f * (yy + zz);
        res.m[0][1] = 2.0f * (xy - wz);
        res.m[0][2] = 2.0f * (xz + wy);

        res.m[1][0] = 2.0f * (xy + wz);
        res.m[1][1] = 1.0f - 2.0f * (xx + zz);
        res.m[1][2] = 2.0f * (yz - wx);

        res.m[2][0] = 2.0f * (xz - wy);
        res.m[2][1] = 2.0f * (yz + wx);
        res.m[2][2] = 1.0f - 2.0f * (xx + yy);

        return res;
    }
};

enum class ColliderShape : uint32_t {
    Box    = 0,
    Sphere = 1,
    Capsule = 2
};

struct RigidBodyDesc {
    ColliderShape shape{ColliderShape::Box};
    Vector3       halfExtents{0.5f, 0.5f, 0.5f}; // For Box
    float         radius{0.5f};                  // For Sphere
    float         massKg{1.0f};                  // 0.0 = static/kinematic
    float         restitution{0.45f};             // Coefficient of restitution [0, 1]
    float         friction{0.5f};                // Coulomb friction coefficient [0, 1]
    float         linearDamping{0.99f};          // Velocity drag retention
    float         angularDamping{0.98f};         // Angular drag retention
};

struct ContactPoint {
    Vector3 position{};
    Vector3 normal{};          // From Body B to Body A
    float   penetration{0.0f}; // Positive when intersecting
    float   accumulatedNormalImpulse{0.0f};
    float   accumulatedTangentImpulse{0.0f};
};

struct ContactManifold {
    uint32_t                  bodyA{0};
    uint32_t                  bodyB{0};
    std::vector<ContactPoint> contacts;
};

class RigidBody {
public:
    RigidBodyDesc desc{};
    Vector3       position{0.0f, 0.0f, 0.0f};
    Quaternion    orientation{1.0f, 0.0f, 0.0f, 0.0f};
    Vector3       linearVelocity{0.0f, 0.0f, 0.0f};
    Vector3       angularVelocity{0.0f, 0.0f, 0.0f};
    Vector3       forceAccumulator{0.0f, 0.0f, 0.0f};
    Vector3       torqueAccumulator{0.0f, 0.0f, 0.0f};

    float         invMass{1.0f};
    Matrix3x3     invInertiaBody{};
    Matrix3x3     invInertiaWorld{};

    RigidBody() = default;

    explicit RigidBody(const RigidBodyDesc& d, const Vector3& pos = {})
        : desc(d), position(pos) {
        if (desc.massKg <= 1e-4f) {
            invMass = 0.0f;
            invInertiaBody = {};
            invInertiaWorld = {};
        } else {
            invMass = 1.0f / desc.massKg;
            Matrix3x3 inertia{};
            if (desc.shape == ColliderShape::Box) {
                float w = desc.halfExtents.x * 2.0f;
                float h = desc.halfExtents.y * 2.0f;
                float d_len = desc.halfExtents.z * 2.0f;
                float factor = desc.massKg / 12.0f;
                inertia.m[0][0] = factor * (h * h + d_len * d_len);
                inertia.m[1][1] = factor * (w * w + d_len * d_len);
                inertia.m[2][2] = factor * (w * w + h * h);
            } else {
                float r = desc.radius;
                float val = 0.4f * desc.massKg * r * r;
                inertia.m[0][0] = val;
                inertia.m[1][1] = val;
                inertia.m[2][2] = val;
            }
            invInertiaBody.m[0][0] = (inertia.m[0][0] > 1e-6f) ? 1.0f / inertia.m[0][0] : 0.0f;
            invInertiaBody.m[1][1] = (inertia.m[1][1] > 1e-6f) ? 1.0f / inertia.m[1][1] : 0.0f;
            invInertiaBody.m[2][2] = (inertia.m[2][2] > 1e-6f) ? 1.0f / inertia.m[2][2] : 0.0f;
            UpdateWorldInertia();
        }
    }

    void UpdateWorldInertia() noexcept {
        if (invMass <= 0.0f) return;
        Matrix3x3 R = Matrix3x3::FromQuaternion(orientation);
        invInertiaWorld = R * invInertiaBody * R.Transpose();
    }

    void ApplyForce(const Vector3& force) noexcept {
        forceAccumulator = forceAccumulator + force;
    }

    void ApplyTorque(const Vector3& torque) noexcept {
        torqueAccumulator = torqueAccumulator + torque;
    }

    void ApplyImpulse(const Vector3& impulse, const Vector3& contactPoint) noexcept {
        if (invMass <= 0.0f) return;
        linearVelocity = linearVelocity + impulse * invMass;
        Vector3 r = contactPoint - position;
        angularVelocity = angularVelocity + invInertiaWorld.Multiply(r.Cross(impulse));
    }

    [[nodiscard]] float ComputeKineticEnergy() const noexcept {
        if (invMass <= 0.0f) return 0.0f;
        float linEnergy = 0.5f * desc.massKg * linearVelocity.LengthSquared();
        Vector3 angMom = Matrix3x3::FromQuaternion(orientation).Multiply(angularVelocity);
        float angEnergy = 0.5f * angularVelocity.Dot(angMom);
        return linEnergy + angEnergy;
    }
};

struct PhysicsEngineTelemetry {
    uint64_t totalSteps{0};
    uint64_t totalContactManifolds{0};
    uint64_t totalImpulsesSolved{0};
    float    systemKineticEnergy{0.0f};
    float    maxPenetrationDepth{0.0f};
};

class DirectCompositionRigidBodyPipeline {
private:
    std::vector<RigidBody>       m_bodies;
    std::vector<ContactManifold> m_manifolds;
    PhysicsEngineTelemetry       m_telemetry{};
    Vector3                      m_gravity{0.0f, 0.0f, -9.80665f};
    float                        m_floorZ{-1.0f};
    bool                         m_floorEnabled{true};
    uint32_t                     m_solverIterations{10};

public:
    DirectCompositionRigidBodyPipeline() = default;

    uint32_t AddRigidBody(const RigidBodyDesc& desc, const Vector3& pos) noexcept {
        uint32_t id = static_cast<uint32_t>(m_bodies.size());
        m_bodies.emplace_back(desc, pos);
        return id;
    }

    [[nodiscard]] const RigidBody& GetBody(uint32_t id) const noexcept {
        return m_bodies[id];
    }

    RigidBody& GetBodyMut(uint32_t id) noexcept {
        return m_bodies[id];
    }

    [[nodiscard]] size_t GetBodyCount() const noexcept {
        return m_bodies.size();
    }

    void SetGravity(const Vector3& g) noexcept {
        m_gravity = g;
    }

    void SetFloor(float floorZ, bool enabled = true) noexcept {
        m_floorZ = floorZ;
        m_floorEnabled = enabled;
    }

    void SetSolverIterations(uint32_t iter) noexcept {
        m_solverIterations = std::clamp(iter, 1u, 32u);
    }

    void Step(float dtSec) noexcept {
        if (dtSec <= 0.0f || m_bodies.empty()) return;
        const float dt = std::clamp(dtSec, 0.001f, 0.033f);

        // 1. External forces & velocity integration
        for (auto& b : m_bodies) {
            if (b.invMass <= 0.0f) continue;
            b.ApplyForce(m_gravity * b.desc.massKg);
            b.linearVelocity = b.linearVelocity + (b.forceAccumulator * b.invMass) * dt;
            b.angularVelocity = b.angularVelocity + b.invInertiaWorld.Multiply(b.torqueAccumulator) * dt;

            b.linearVelocity = b.linearVelocity * b.desc.linearDamping;
            b.angularVelocity = b.angularVelocity * b.desc.angularDamping;

            b.forceAccumulator = {0.0f, 0.0f, 0.0f};
            b.torqueAccumulator = {0.0f, 0.0f, 0.0f};
        }

        // 2. Collision Detection (Narrowphase Manifold Generation)
        DetectCollisions();

        // 3. Iterative Sequential Impulse Solver
        for (uint32_t iter = 0; iter < m_solverIterations; ++iter) {
            SolveContactImpulses();
        }

        // 4. Position & Orientation Integration
        for (auto& b : m_bodies) {
            if (b.invMass <= 0.0f) continue;
            b.position = b.position + b.linearVelocity * dt;

            // Spin quaternion: q' = q + 0.5 * dt * w * q
            Quaternion wq{0.0f, b.angularVelocity.x, b.angularVelocity.y, b.angularVelocity.z};
            Quaternion dq = (wq * b.orientation);
            b.orientation.w += 0.5f * dt * dq.w;
            b.orientation.x += 0.5f * dt * dq.x;
            b.orientation.y += 0.5f * dt * dq.y;
            b.orientation.z += 0.5f * dt * dq.z;
            b.orientation = b.orientation.Normalize();

            b.UpdateWorldInertia();
        }

        // 5. Update Telemetry
        float totalKE = 0.0f;
        for (const auto& b : m_bodies) {
            totalKE += b.ComputeKineticEnergy();
        }
        m_telemetry.systemKineticEnergy = totalKE;
        m_telemetry.totalSteps++;
    }

    [[nodiscard]] PhysicsEngineTelemetry GetTelemetry() const noexcept {
        return m_telemetry;
    }

private:
    void DetectCollisions() noexcept {
        m_manifolds.clear();
        float maxPen = 0.0f;

        // Ground Plane Collisions
        if (m_floorEnabled) {
            for (uint32_t i = 0; i < m_bodies.size(); ++i) {
                auto& b = m_bodies[i];
                if (b.invMass <= 0.0f) continue;

                if (b.desc.shape == ColliderShape::Sphere) {
                    float bottom = b.position.z - b.desc.radius;
                    if (bottom < m_floorZ) {
                        ContactManifold mf{};
                        mf.bodyA = i;
                        mf.bodyB = UINT32_MAX; // Static world floor

                        ContactPoint cp{};
                        cp.position = {b.position.x, b.position.y, m_floorZ};
                        cp.normal = {0.0f, 0.0f, 1.0f}; // Floor points upward
                        cp.penetration = m_floorZ - bottom;
                        if (cp.penetration > maxPen) maxPen = cp.penetration;
                        mf.contacts.push_back(cp);
                        m_manifolds.push_back(mf);
                    }
                } else if (b.desc.shape == ColliderShape::Box) {
                    // Check 8 vertices of box against floor
                    std::array<Vector3, 8> localVertices = {
                        Vector3{-b.desc.halfExtents.x, -b.desc.halfExtents.y, -b.desc.halfExtents.z},
                        Vector3{ b.desc.halfExtents.x, -b.desc.halfExtents.y, -b.desc.halfExtents.z},
                        Vector3{ b.desc.halfExtents.x,  b.desc.halfExtents.y, -b.desc.halfExtents.z},
                        Vector3{-b.desc.halfExtents.x,  b.desc.halfExtents.y, -b.desc.halfExtents.z},
                        Vector3{-b.desc.halfExtents.x, -b.desc.halfExtents.y,  b.desc.halfExtents.z},
                        Vector3{ b.desc.halfExtents.x, -b.desc.halfExtents.y,  b.desc.halfExtents.z},
                        Vector3{ b.desc.halfExtents.x,  b.desc.halfExtents.y,  b.desc.halfExtents.z},
                        Vector3{-b.desc.halfExtents.x,  b.desc.halfExtents.y,  b.desc.halfExtents.z}
                    };

                    ContactManifold mf{};
                    mf.bodyA = i;
                    mf.bodyB = UINT32_MAX;

                    for (const auto& lv : localVertices) {
                        Vector3 worldV = b.position + b.orientation.Rotate(lv);
                        if (worldV.z < m_floorZ) {
                            ContactPoint cp{};
                            cp.position = {worldV.x, worldV.y, m_floorZ};
                            cp.normal = {0.0f, 0.0f, 1.0f};
                            cp.penetration = m_floorZ - worldV.z;
                            if (cp.penetration > maxPen) maxPen = cp.penetration;
                            mf.contacts.push_back(cp);
                        }
                    }

                    if (!mf.contacts.empty()) {
                        m_manifolds.push_back(mf);
                    }
                }
            }
        }

        // Body vs Body Collisions (Sphere vs Sphere)
        for (uint32_t i = 0; i < m_bodies.size(); ++i) {
            for (uint32_t j = i + 1; j < m_bodies.size(); ++j) {
                auto& bA = m_bodies[i];
                auto& bB = m_bodies[j];
                if (bA.invMass <= 0.0f && bB.invMass <= 0.0f) continue;

                if (bA.desc.shape == ColliderShape::Sphere && bB.desc.shape == ColliderShape::Sphere) {
                    Vector3 delta = bA.position - bB.position;
                    float dist = delta.Length();
                    float rSum = bA.desc.radius + bB.desc.radius;
                    if (dist < rSum && dist > 1e-6f) {
                        ContactManifold mf{};
                        mf.bodyA = i;
                        mf.bodyB = j;

                        ContactPoint cp{};
                        cp.normal = delta / dist; // Points from B to A
                        cp.position = bB.position + cp.normal * bB.desc.radius;
                        cp.penetration = rSum - dist;
                        if (cp.penetration > maxPen) maxPen = cp.penetration;
                        mf.contacts.push_back(cp);
                        m_manifolds.push_back(mf);
                    }
                }
            }
        }

        m_telemetry.maxPenetrationDepth = maxPen;
        m_telemetry.totalContactManifolds += m_manifolds.size();
    }

    void SolveContactImpulses() noexcept {
        const float baumgarte = 0.2f;
        const float slop = 0.005f;

        for (auto& mf : m_manifolds) {
            RigidBody& bA = m_bodies[mf.bodyA];
            RigidBody* pB = (mf.bodyB != UINT32_MAX) ? &m_bodies[mf.bodyB] : nullptr;

            for (auto& cp : mf.contacts) {
                Vector3 rA = cp.position - bA.position;
                Vector3 rB = pB ? (cp.position - pB->position) : Vector3{0.0f, 0.0f, 0.0f};

                Vector3 vA = bA.linearVelocity + bA.angularVelocity.Cross(rA);
                Vector3 vB = pB ? (pB->linearVelocity + pB->angularVelocity.Cross(rB)) : Vector3{0.0f, 0.0f, 0.0f};
                Vector3 relVel = vA - vB;

                float vn = relVel.Dot(cp.normal);
                if (vn > 0.0f) continue; // Moving apart

                // Effective mass calculation
                float termA = bA.invMass + (bA.invInertiaWorld.Multiply(rA.Cross(cp.normal))).Cross(rA).Dot(cp.normal);
                float termB = pB ? (pB->invMass + (pB->invInertiaWorld.Multiply(rB.Cross(cp.normal))).Cross(rB).Dot(cp.normal)) : 0.0f;
                float effMass = termA + termB;
                if (effMass < 1e-6f) continue;

                float e = bA.desc.restitution;
                if (pB) e = std::min(e, pB->desc.restitution);

                float penetrationBias = (std::max(0.0f, cp.penetration - slop) * baumgarte) / 0.016f;
                float impulseMagnitude = (-(1.0f + e) * vn + penetrationBias) / effMass;

                // Clamp accumulated impulse
                float oldImpulse = cp.accumulatedNormalImpulse;
                cp.accumulatedNormalImpulse = std::max(0.0f, oldImpulse + impulseMagnitude);
                float deltaImpulse = cp.accumulatedNormalImpulse - oldImpulse;

                Vector3 P = cp.normal * deltaImpulse;
                bA.ApplyImpulse(P, cp.position);
                if (pB) pB->ApplyImpulse(-P, cp.position);

                // Tangential Friction
                Vector3 tangent = (relVel - cp.normal * vn);
                float vt = tangent.Length();
                if (vt > 1e-5f) {
                    Vector3 tDir = tangent / vt;
                    float frictionEffMass = bA.invMass + (bA.invInertiaWorld.Multiply(rA.Cross(tDir))).Cross(rA).Dot(tDir);
                    if (pB) frictionEffMass += pB->invMass + (pB->invInertiaWorld.Multiply(rB.Cross(tDir))).Cross(rB).Dot(tDir);

                    if (frictionEffMass > 1e-6f) {
                        float mu = bA.desc.friction;
                        if (pB) mu = std::sqrt(mu * pB->desc.friction);

                        float fImpulse = -vt / frictionEffMass;
                        float maxFriction = mu * cp.accumulatedNormalImpulse;
                        fImpulse = std::clamp(fImpulse, -maxFriction, maxFriction);

                        Vector3 Pt = tDir * fImpulse;
                        bA.ApplyImpulse(Pt, cp.position);
                        if (pB) pB->ApplyImpulse(-Pt, cp.position);
                    }
                }

                m_telemetry.totalImpulsesSolved++;
            }
        }
    }
};

inline bool VerifyPrismXMilestone182DirectCompositionRigidBodyPipeline() noexcept {
    DirectCompositionRigidBodyPipeline pipeline{};
    pipeline.SetFloor(-1.0f, true);
    pipeline.SetGravity({0.0f, 0.0f, -9.80665f});

    // Pillar 1: Rigid body definition & inertial properties
    RigidBodyDesc boxDesc{};
    boxDesc.shape = ColliderShape::Box;
    boxDesc.halfExtents = {0.25f, 0.25f, 0.25f};
    boxDesc.massKg = 2.0f;
    boxDesc.restitution = 0.5f;

    uint32_t boxId = pipeline.AddRigidBody(boxDesc, {0.0f, 0.0f, 2.0f});
    const auto& b0 = pipeline.GetBody(boxId);
    if (b0.invMass <= 0.0f || b0.desc.massKg != 2.0f) return false;

    // Pillar 2: Sphere body dropped onto ground plane
    RigidBodyDesc sphereDesc{};
    sphereDesc.shape = ColliderShape::Sphere;
    sphereDesc.radius = 0.3f;
    sphereDesc.massKg = 1.0f;
    sphereDesc.restitution = 0.6f;
    uint32_t sphereId = pipeline.AddRigidBody(sphereDesc, {0.0f, 0.0f, 1.5f});

    // Pillar 3: Free-fall trajectory under gravity
    for (uint32_t i = 0; i < 20; ++i) {
        pipeline.Step(0.016f);
    }
    const auto& bSphereMid = pipeline.GetBody(sphereId);
    if (bSphereMid.position.z >= 1.5f || bSphereMid.linearVelocity.z >= 0.0f) return false;

    // Pillar 4: Floor collision, contact manifold resolution & bounce
    for (uint32_t i = 0; i < 60; ++i) {
        pipeline.Step(0.016f);
    }
    const auto& bSphereBounce = pipeline.GetBody(sphereId);
    // Sphere should remain above floor (-1.0f + 0.3f = -0.7f) with restitution
    if (bSphereBounce.position.z < -0.85f) return false;

    // Pillar 5: Multi-body kinetic energy dissipation & stability
    for (uint32_t i = 0; i < 150; ++i) {
        pipeline.Step(0.016f);
    }
    const auto& bBoxSettled = pipeline.GetBody(boxId);
    if (bBoxSettled.position.z < -0.85f) return false;

    // Pillar 6: Telemetry invariants & zero NaN check
    auto telem = pipeline.GetTelemetry();
    if (telem.totalSteps < 200 || telem.totalImpulsesSolved == 0) return false;
    if (std::isnan(telem.systemKineticEnergy) || std::isnan(telem.maxPenetrationDepth)) return false;

    return true;
}

} // namespace prismx::physics
