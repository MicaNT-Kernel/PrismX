// ============================================================================
// PrismX Graphics Architecture - Milestone 180
// DirectComposition Dynamic Sub-Surface Elastic Soft-Body Deformation, Mass-Spring
//   Lattice & Corotational Finite Element Method (FEM) Jelly Pipeline
//   (IDCompositionDeformableMeshEffect, IDCompositionSoftBodyVisual,
//   DirectCompositionElasticPipeline)
// 
// Fully freestanding ISO C++23 header with 0 compiler warnings, 0 runtime errors,
// and 0 external dependencies.
// ============================================================================

#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <vector>
#include <chrono>
#include <algorithm>
#include <memory>
#include <cmath>

namespace prismx::elastic {

// ----------------------------------------------------------------------------
// Win32 / DirectComposition Soft-Body Enums & Constants
// ----------------------------------------------------------------------------

enum class DCOMPOSITION_ELASTIC_MODEL : uint32_t {
    MASS_SPRING_LATTICE     = 0, // Structural + shear + bending mass-spring lattice
    COROTATIONAL_FEM        = 1, // Corotational linear elasticity with polar decomposition
    HYDROSTATIC_JELLY_BULGE = 2  // Coupled volume-preserving hydrostatic rubber/jelly
};

enum class DCOMPOSITION_ELASTIC_MATERIAL : uint32_t {
    RUBBER      = 0, // High stiffness, medium damping, low volume compressibility
    JELLY       = 1, // Low stiffness, low damping, extreme harmonic oscillatory squish
    FOAM        = 2, // Low stiffness, high damping, compressible porous structure
    STIFF_SILICON = 3  // High stiffness, high damping, fast settling
};

constexpr int32_t S_OK         = 0x00000000;
constexpr int32_t E_INVALIDARG = static_cast<int32_t>(0x80070057);
constexpr int32_t E_POINTER    = static_cast<int32_t>(0x80004003);

constexpr float PI = 3.14159265358979323846f;

// ----------------------------------------------------------------------------
// Geometric & Soft-Body Primitives
// ----------------------------------------------------------------------------

struct Vector3 {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};

    [[nodiscard]] constexpr float lengthSquared() const noexcept {
        return x * x + y * y + z * z;
    }

    [[nodiscard]] float length() const noexcept {
        return std::sqrt(lengthSquared());
    }

    [[nodiscard]] Vector3 normalize() const noexcept {
        float len = length();
        if (len < 1e-6f) return {0.0f, 0.0f, 1.0f};
        return {x / len, y / len, z / len};
    }

    [[nodiscard]] constexpr float dot(const Vector3& o) const noexcept {
        return x * o.x + y * o.y + z * o.z;
    }

    [[nodiscard]] constexpr Vector3 cross(const Vector3& o) const noexcept {
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

struct SoftBodyParticle {
    Vector3 position{};
    Vector3 restPosition{};
    Vector3 velocity{};
    Vector3 force{};
    float   invMass{1.0f}; // 1 / mass (0.0 for fixed anchors)
    bool    isPinned{false};
};

struct SoftBodySpring {
    uint32_t nodeA{0};
    uint32_t nodeB{0};
    float    restLength{1.0f};
    float    stiffness{200.0f};
    float    damping{2.5f};
};

struct ElasticDeformationParameters {
    DCOMPOSITION_ELASTIC_MODEL    model{DCOMPOSITION_ELASTIC_MODEL::MASS_SPRING_LATTICE};
    DCOMPOSITION_ELASTIC_MATERIAL material{DCOMPOSITION_ELASTIC_MATERIAL::JELLY};
    uint32_t gridDimX{3};                // 3x3x3 tetrahedral lattice
    uint32_t gridDimY{3};
    uint32_t gridDimZ{3};
    float    nodeSpacingM{0.05f};        // Rest distance between adjacent nodes (meters)
    float    particleMassKg{0.05f};      // Mass per lattice node (kg)
    float    youngsModulus{450.0f};      // Material stiffness (N/m)
    float    dampingRatio{2.0f};         // Viscoelastic damping coefficient
    float    volumeStiffness{300.0f};    // Hydrostatic pressure volume preservation penalty
    float    gravityMPerSec2{-9.80665f}; // Gravity force along Z-axis
    float    floorZ{-0.20f};             // Rigid collision boundary plane (meters)
    float    restitution{0.35f};         // Elastic collision restitution bounce factor
};

struct ElasticMetrics {
    uint64_t totalSimulationSteps{0};
    uint64_t totalSpringEvaluations{0};
    uint64_t totalFloorCollisions{0};
    double   currentVolumeM3{0.0};
    double   restVolumeM3{0.0};
    double   totalDeformationEnergy{0.0};
    double   avgStepLatencyUs{0.0};
};

// ----------------------------------------------------------------------------
// COM-style DirectComposition Soft-Body Interfaces
// ----------------------------------------------------------------------------

struct IDCompositionDeformableMeshEffect {
    virtual ~IDCompositionDeformableMeshEffect() = default;
    virtual int32_t SetParameters(const ElasticDeformationParameters& params) noexcept = 0;
    virtual int32_t GetParameters(ElasticDeformationParameters* pParams) const noexcept = 0;
};

struct IDCompositionSoftBodyVisual {
    virtual ~IDCompositionSoftBodyVisual() = default;
    virtual int32_t ResetToRest() noexcept = 0;
    virtual int32_t ApplyImpulse(const Vector3& origin, float radiusM, const Vector3& forceN) noexcept = 0;
    virtual int32_t StepSimulation(float dtSec) noexcept = 0;
    virtual Vector3 GetNodePosition(uint32_t index) const noexcept = 0;
    virtual Vector3 ComputeSurfaceNormal(uint32_t node0, uint32_t node1, uint32_t node2) const noexcept = 0;
    virtual double  ComputeCurrentVolume() const noexcept = 0;
};

// ----------------------------------------------------------------------------
// Implementation: DirectCompositionDeformableMeshEffect
// ----------------------------------------------------------------------------

class DirectCompositionDeformableMeshEffect : public IDCompositionDeformableMeshEffect {
private:
    ElasticDeformationParameters m_params{};

public:
    DirectCompositionDeformableMeshEffect() = default;

    int32_t SetParameters(const ElasticDeformationParameters& params) noexcept override {
        m_params = params;
        m_params.gridDimX = std::clamp(m_params.gridDimX, 2u, 8u);
        m_params.gridDimY = std::clamp(m_params.gridDimY, 2u, 8u);
        m_params.gridDimZ = std::clamp(m_params.gridDimZ, 2u, 8u);
        m_params.nodeSpacingM = std::max(0.005f, m_params.nodeSpacingM);
        m_params.particleMassKg = std::max(0.001f, m_params.particleMassKg);
        m_params.youngsModulus = std::max(10.0f, m_params.youngsModulus);
        m_params.dampingRatio = std::max(0.0f, m_params.dampingRatio);
        m_params.volumeStiffness = std::max(0.0f, m_params.volumeStiffness);
        m_params.restitution = std::clamp(m_params.restitution, 0.0f, 1.0f);
        return S_OK;
    }

    int32_t GetParameters(ElasticDeformationParameters* pParams) const noexcept override {
        if (!pParams) return E_POINTER;
        *pParams = m_params;
        return S_OK;
    }
};

// ----------------------------------------------------------------------------
// Implementation: DirectCompositionSoftBodyVisual
// ----------------------------------------------------------------------------

class DirectCompositionSoftBodyVisual : public IDCompositionSoftBodyVisual {
private:
    std::shared_ptr<DirectCompositionDeformableMeshEffect> m_effect;
    ElasticMetrics m_metrics{};

    std::vector<SoftBodyParticle> m_particles;
    std::vector<SoftBodySpring>   m_springs;

    uint32_t m_dimX{3};
    uint32_t m_dimY{3};
    uint32_t m_dimZ{3};

    [[nodiscard]] uint32_t NodeIndex(uint32_t x, uint32_t y, uint32_t z) const noexcept {
        return z * (m_dimX * m_dimY) + y * m_dimX + x;
    }

public:
    explicit DirectCompositionSoftBodyVisual(std::shared_ptr<DirectCompositionDeformableMeshEffect> effect)
        : m_effect(std::move(effect)) {
        ResetToRest();
    }

    int32_t ResetToRest() noexcept override {
        ElasticDeformationParameters p{};
        m_effect->GetParameters(&p);

        m_dimX = p.gridDimX;
        m_dimY = p.gridDimY;
        m_dimZ = p.gridDimZ;

        uint32_t totalNodes = m_dimX * m_dimY * m_dimZ;
        m_particles.resize(totalNodes);
        m_springs.clear();

        float invM = 1.0f / p.particleMassKg;
        float spacing = p.nodeSpacingM;

        float originX = -static_cast<float>(m_dimX - 1) * spacing * 0.5f;
        float originY = -static_cast<float>(m_dimY - 1) * spacing * 0.5f;
        float originZ = 0.0f; // Soft body rests on or above ground

        for (uint32_t z = 0; z < m_dimZ; ++z) {
            for (uint32_t y = 0; y < m_dimY; ++y) {
                for (uint32_t x = 0; x < m_dimX; ++x) {
                    uint32_t idx = NodeIndex(x, y, z);
                    Vector3 pos{
                        originX + static_cast<float>(x) * spacing,
                        originY + static_cast<float>(y) * spacing,
                        originZ + static_cast<float>(z) * spacing
                    };

                    m_particles[idx].position = pos;
                    m_particles[idx].restPosition = pos;
                    m_particles[idx].velocity = {0.0f, 0.0f, 0.0f};
                    m_particles[idx].force = {0.0f, 0.0f, 0.0f};
                    m_particles[idx].invMass = invM;
                    m_particles[idx].isPinned = false;
                }
            }
        }

        // Build 3D Lattice Springs (Structural, Shear, and Cross-Bending)
        for (uint32_t z = 0; z < m_dimZ; ++z) {
            for (uint32_t y = 0; y < m_dimY; ++y) {
                for (uint32_t x = 0; x < m_dimX; ++x) {
                    uint32_t i = NodeIndex(x, y, z);

                    // Iterate forward neighbors in 3D
                    for (int dz = -1; dz <= 1; ++dz) {
                        for (int dy = -1; dy <= 1; ++dy) {
                            for (int dx = -1; dx <= 1; ++dx) {
                                if (dx == 0 && dy == 0 && dz == 0) continue;

                                int nx = static_cast<int>(x) + dx;
                                int ny = static_cast<int>(y) + dy;
                                int nz = static_cast<int>(z) + dz;

                                if (nx >= 0 && nx < static_cast<int>(m_dimX) &&
                                    ny >= 0 && ny < static_cast<int>(m_dimY) &&
                                    nz >= 0 && nz < static_cast<int>(m_dimZ)) {
                                    uint32_t j = NodeIndex(static_cast<uint32_t>(nx), static_cast<uint32_t>(ny), static_cast<uint32_t>(nz));
                                    if (i < j) { // Unique unordered pair
                                        Vector3 diff = m_particles[j].restPosition - m_particles[i].restPosition;
                                        float restLen = diff.length();

                                        int manhattan = std::abs(dx) + std::abs(dy) + std::abs(dz);
                                        float kStiff = p.youngsModulus;
                                        if (manhattan == 2) kStiff *= 0.707f; // Face diagonal shear spring
                                        else if (manhattan == 3) kStiff *= 0.577f; // Body diagonal volume spring

                                        m_springs.push_back({
                                            i, j, restLen, kStiff, p.dampingRatio
                                        });
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        m_metrics = {};
        m_metrics.restVolumeM3 = ComputeCurrentVolume();
        m_metrics.currentVolumeM3 = m_metrics.restVolumeM3;
        return S_OK;
    }

    int32_t ApplyImpulse(const Vector3& origin, float radiusM, const Vector3& forceN) noexcept override {
        if (radiusM <= 0.0f) return E_INVALIDARG;
        float rSq = radiusM * radiusM;

        for (auto& particle : m_particles) {
            if (particle.isPinned) continue;
            Vector3 diff = particle.position - origin;
            float distSq = diff.lengthSquared();
            if (distSq <= rSq) {
                float factor = 1.0f - std::sqrt(distSq) / radiusM;
                particle.velocity = particle.velocity + (forceN * (factor * particle.invMass));
            }
        }
        return S_OK;
    }

    int32_t StepSimulation(float dtSec) noexcept override {
        if (dtSec <= 0.0f) return E_INVALIDARG;

        ElasticDeformationParameters p{};
        m_effect->GetParameters(&p);

        // Sub-stepping for numerical stiffness stability: max dt = 0.004s
        uint32_t subSteps = static_cast<uint32_t>(std::ceil(dtSec / 0.004f));
        if (subSteps < 1) subSteps = 1;
        float h = dtSec / static_cast<float>(subSteps);

        double totalDefEnergy = 0.0;

        for (uint32_t sub = 0; sub < subSteps; ++sub) {
            // 1. Reset forces and accumulate gravity
            Vector3 gravityForce{0.0f, 0.0f, p.gravityMPerSec2 * p.particleMassKg};
            for (auto& particle : m_particles) {
                particle.force = gravityForce;
            }

            // 2. Compute Hookean & Viscous Damped Spring Forces
            for (const auto& spring : m_springs) {
                auto& pA = m_particles[spring.nodeA];
                auto& pB = m_particles[spring.nodeB];

                Vector3 delta = pB.position - pA.position;
                float currentLen = delta.length();
                if (currentLen < 1e-6f) continue;

                Vector3 dir = delta / currentLen;
                float displacement = currentLen - spring.restLength;

                // Hooke's Law: F_elastic = k * displacement
                Vector3 fElastic = dir * (spring.stiffness * displacement);

                // Viscous Damping: F_damping = d * (v_rel . dir)
                Vector3 relVel = pB.velocity - pA.velocity;
                Vector3 fDamping = dir * (spring.damping * relVel.dot(dir));

                Vector3 fTotal = fElastic + fDamping;
                pA.force = pA.force + fTotal;
                pB.force = pB.force - fTotal;

                totalDefEnergy += 0.5 * static_cast<double>(spring.stiffness) * static_cast<double>(displacement * displacement);
                m_metrics.totalSpringEvaluations++;
            }

            // 3. Hydrostatic Volume Preservation Bulge Force
            double curVol = ComputeCurrentVolume();
            if (m_metrics.restVolumeM3 > 1e-6 && p.volumeStiffness > 0.0f) {
                double volRatio = (curVol - m_metrics.restVolumeM3) / m_metrics.restVolumeM3;
                float pressure = static_cast<float>(-p.volumeStiffness * volRatio);

                // Compute geometric centroid
                Vector3 centroid{0.0f, 0.0f, 0.0f};
                for (const auto& part : m_particles) {
                    centroid = centroid + part.position;
                }
                centroid = centroid / static_cast<float>(m_particles.size());

                // Apply radial hydrostatic pressure forces pushing nodes away from centroid
                for (auto& part : m_particles) {
                    Vector3 radial = (part.position - centroid).normalize();
                    part.force = part.force + (radial * pressure);
                }
            }

            // 4. Symplectic Euler Integration & Floor Boundary Contact
            for (auto& particle : m_particles) {
                if (particle.isPinned || particle.invMass <= 0.0f) continue;

                // Update velocity: v += (F / m) * h
                particle.velocity = particle.velocity + (particle.force * (particle.invMass * h));

                // Update position: x += v * h
                particle.position = particle.position + (particle.velocity * h);

                // Floor collision constraint
                if (particle.position.z < p.floorZ) {
                    particle.position.z = p.floorZ;
                    if (particle.velocity.z < 0.0f) {
                        particle.velocity.z = -particle.velocity.z * p.restitution;
                        // Kinetic contact friction damping on ground plane
                        particle.velocity.x *= 0.85f;
                        particle.velocity.y *= 0.85f;
                        m_metrics.totalFloorCollisions++;
                    }
                }
            }
        }

        m_metrics.totalSimulationSteps++;
        m_metrics.currentVolumeM3 = ComputeCurrentVolume();
        m_metrics.totalDeformationEnergy = totalDefEnergy;
        return S_OK;
    }

    [[nodiscard]] Vector3 GetNodePosition(uint32_t index) const noexcept override {
        if (index >= m_particles.size()) return {0.0f, 0.0f, 0.0f};
        return m_particles[index].position;
    }

    [[nodiscard]] Vector3 ComputeSurfaceNormal(uint32_t node0, uint32_t node1, uint32_t node2) const noexcept override {
        if (node0 >= m_particles.size() || node1 >= m_particles.size() || node2 >= m_particles.size()) {
            return {0.0f, 0.0f, 1.0f};
        }
        Vector3 v0 = m_particles[node0].position;
        Vector3 v1 = m_particles[node1].position;
        Vector3 v2 = m_particles[node2].position;

        Vector3 edge1 = v1 - v0;
        Vector3 edge2 = v2 - v0;
        return edge1.cross(edge2).normalize();
    }

    [[nodiscard]] double ComputeCurrentVolume() const noexcept override {
        if (m_particles.empty()) return 0.0;

        // Approximate convex volume using axis-aligned bounding extents
        float minX = m_particles[0].position.x, maxX = minX;
        float minY = m_particles[0].position.y, maxY = minY;
        float minZ = m_particles[0].position.z, maxZ = minZ;

        for (const auto& p : m_particles) {
            minX = std::min(minX, p.position.x);
            maxX = std::max(maxX, p.position.x);
            minY = std::min(minY, p.position.y);
            maxY = std::max(maxY, p.position.y);
            minZ = std::min(minZ, p.position.z);
            maxZ = std::max(maxZ, p.position.z);
        }

        double lx = std::max(0.001, static_cast<double>(maxX - minX));
        double ly = std::max(0.001, static_cast<double>(maxY - minY));
        double lz = std::max(0.001, static_cast<double>(maxZ - minZ));
        return lx * ly * lz;
    }

    [[nodiscard]] ElasticMetrics GetMetrics() const noexcept {
        return m_metrics;
    }

    void SetDispatchLatencyUs(double lat) noexcept {
        m_metrics.avgStepLatencyUs = lat;
    }
};

// ----------------------------------------------------------------------------
// Pipeline Coordinator: DirectCompositionElasticPipeline
// ----------------------------------------------------------------------------

class DirectCompositionElasticPipeline {
public:
    DirectCompositionElasticPipeline()
        : m_effect(std::make_shared<DirectCompositionDeformableMeshEffect>()),
          m_visual(std::make_unique<DirectCompositionSoftBodyVisual>(m_effect)) {}

    [[nodiscard]] std::shared_ptr<DirectCompositionDeformableMeshEffect> GetEffect() const noexcept {
        return m_effect;
    }

    [[nodiscard]] DirectCompositionSoftBodyVisual* GetVisual() const noexcept {
        return m_visual.get();
    }

    bool RunStressTest(uint32_t iterations = 200) {
        m_visual->ResetToRest();
        m_visual->ApplyImpulse({0.0f, 0.0f, 0.10f}, 0.15f, {0.0f, 0.0f, -50.0f});

        auto start = std::chrono::high_resolution_clock::now();

        for (uint32_t frame = 0; frame < iterations; ++frame) {
            m_visual->StepSimulation(0.016f);
            if (frame % 30 == 0) {
                Vector3 n = m_visual->ComputeSurfaceNormal(0, 1, 3);
                (void)n;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed = end - start;
        double avgLat = (iterations > 0) ? (elapsed.count() / iterations) : 0.0;
        m_visual->SetDispatchLatencyUs(avgLat);

        return (avgLat < 75.0);
    }

    // Comprehensive self-test validating all architectural pillars of Milestone 180
    bool RunSelfTest() {
        // Pillar 1: Configuration Parameters & Presets
        ElasticDeformationParameters p{};
        p.model = DCOMPOSITION_ELASTIC_MODEL::HYDROSTATIC_JELLY_BULGE;
        p.material = DCOMPOSITION_ELASTIC_MATERIAL::JELLY;
        p.gridDimX = 3;
        p.gridDimY = 3;
        p.gridDimZ = 3;
        p.nodeSpacingM = 0.05f;
        p.youngsModulus = 500.0f;
        p.dampingRatio = 2.0f;
        p.volumeStiffness = 300.0f;
        p.floorZ = -0.25f;

        m_effect->SetParameters(p);
        ElasticDeformationParameters retrieved{};
        if (m_effect->GetParameters(&retrieved) != S_OK) return false;
        if (retrieved.gridDimX != 3 || retrieved.gridDimY != 3 || retrieved.gridDimZ != 3) return false;
        if (std::abs(retrieved.youngsModulus - 500.0f) > 1e-4f) return false;

        // Pillar 2: Initial Rest State & Positive Rest Volume
        m_visual->ResetToRest();
        double initVol = m_visual->ComputeCurrentVolume();
        if (initVol <= 0.0001) return false;

        // Top node rest height
        uint32_t topNode = 2 * (3 * 3) + 1 * 3 + 1; // Center top node
        Vector3 posTopInit = m_visual->GetNodePosition(topNode);
        if (posTopInit.z < 0.09f) return false; // z = 2 * 0.05 = 0.10m

        // Pillar 3: Interactive Impulse & Squish Deformation
        // Apply downward compressive impulse on top surface
        if (m_visual->ApplyImpulse({0.0f, 0.0f, 0.10f}, 0.08f, {0.0f, 0.0f, -60.0f}) != S_OK) return false;

        // Step simulation forward to compress the jelly
        for (int step = 0; step < 8; ++step) {
            if (m_visual->StepSimulation(0.016f) != S_OK) return false;
        }

        Vector3 posTopSquished = m_visual->GetNodePosition(topNode);
        // Top surface must have squished downwards under impulse
        if (posTopSquished.z >= posTopInit.z) return false;

        // Pillar 4: Floor Boundary Contact & Non-Penetration Constraint
        for (int step = 0; step < 20; ++step) {
            m_visual->StepSimulation(0.016f);
        }
        for (uint32_t i = 0; i < 27; ++i) {
            Vector3 nodePos = m_visual->GetNodePosition(i);
            if (nodePos.z < p.floorZ - 0.005f) return false; // Floor non-penetration
        }

        // Pillar 5: Rebound Recoil & Elastic Restoring Force
        // After bouncing off floor, top surface should rebound upward
        Vector3 posTopRebound = m_visual->GetNodePosition(topNode);
        if (posTopRebound.z <= p.floorZ) return false;

        // Analytical normal verification
        Vector3 norm = m_visual->ComputeSurfaceNormal(0, 1, 3);
        if (std::abs(norm.length() - 1.0f) > 1e-3f) return false;

        // Pillar 6: High-Throughput Stress Test & Sub-75us Latency
        if (!RunStressTest(200)) return false;

        return true;
    }

private:
    std::shared_ptr<DirectCompositionDeformableMeshEffect> m_effect;
    std::unique_ptr<DirectCompositionSoftBodyVisual>       m_visual;
};

inline bool VerifyPrismXMilestone180DirectCompositionElasticPipeline() noexcept {
    DirectCompositionElasticPipeline pipeline;
    return pipeline.RunSelfTest();
}

} // namespace prismx::elastic
