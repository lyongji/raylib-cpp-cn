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
class 网格 : public 非托管网格 {
public:
  using 非托管网格::非托管网格;

  /**
   * 显式禁止复制构造函数。
   */
  网格(const 网格 &) = delete;

  /**
   * 显式禁止复制赋值。
   */
  网格 &operator=(const 网格 &) = delete;

  /**
   * 移动构造函数。
   */
  网格(网格 &&other) noexcept {
    设(other);

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

  网格 &operator=(网格 &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    卸载网格();
    设(other);

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

  ~网格() { 卸载网格(); }
};
} // namespace raylib

using R网格 = raylib::网格;

// #endif // RAYLIB_CPP_INCLUDE_MESH_HPP_