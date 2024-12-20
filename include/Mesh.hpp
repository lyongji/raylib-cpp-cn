// #ifndef RAYLIB_CPP_INCLUDE_MESH_HPP_
// #define RAYLIB_CPP_INCLUDE_MESH_HPP_
#pragma once

#include <string>
#include <vector>

#include "./MeshUnmanaged.hpp"
#include "./Model.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 定义网格的顶点数据
 *
 * 网格将在对象销毁时自动卸载。
 *
 * @see raylib::MeshUnmanaged
 */
class Mesh : public MeshUnmanaged {
public:
    using MeshUnmanaged::MeshUnmanaged;

    /**
     * 显式禁止复制构造函数。
     */
    Mesh(const Mesh&) = delete;

    /**
     * 显式禁止复制赋值。
     */
    Mesh& operator=(const Mesh&) = delete;

    /**
     * 移动构造函数。
     */
    Mesh(Mesh&& other) noexcept {
        set(other);

        other.vertexCount = 0;
        other.triangleCount = 0;
        other.vertices = nullptr;
        other.texcoords = nullptr;
        other.texcoords2 = nullptr;
        other.normals = nullptr;
        other.tangents = nullptr;
        other.colors = nullptr;
        other.indices = nullptr;
        other.animVertices = nullptr;
        other.animNormals = nullptr;
        other.boneIds = nullptr;
        other.boneWeights = nullptr;
        other.vaoId = 0;
        other.vboId = nullptr;
    }

    Mesh& operator=(Mesh&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.vertexCount = 0;
        other.triangleCount = 0;
        other.vertices = nullptr;
        other.texcoords = nullptr;
        other.texcoords2 = nullptr;
        other.normals = nullptr;
        other.tangents = nullptr;
        other.colors = nullptr;
        other.indices = nullptr;
        other.animVertices = nullptr;
        other.animNormals = nullptr;
        other.boneIds = nullptr;
        other.boneWeights = nullptr;
        other.vaoId = 0;
        other.vboId = nullptr;

        return *this;
    }

    ~Mesh() { Unload(); }
};
} // namespace raylib

using RMesh = raylib::Mesh;

// #endif // RAYLIB_CPP_INCLUDE_MESH_HPP_