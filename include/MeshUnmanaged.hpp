// #ifndef RAYLIB_CPP_INCLUDE_MESHUNMANAGED_HPP_
// #define RAYLIB_CPP_INCLUDE_MESHUNMANAGED_HPP_
#pragma once

#include <string>
#include <vector>

#include "./BoundingBox.hpp"
#include "./Matrix.hpp"
#include "./Model.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {

/**
 * 定义网格的顶点数据，不受C++ RAII管理。
 *
 * 如果需要，请确保调用Unload()，否则请使用raylib::Mesh。
 *
 * @see raylib::Mesh
 */
class 非托管网格 : public ::Mesh {
public:
  /**
   * 默认构造函数。
   */
  非托管网格() {
    vertexCount = 0;
    triangleCount = 0;
    vertices = nullptr;
    texcoords = nullptr;
    texcoords2 = nullptr;
    normals = nullptr;
    tangents = nullptr;
    colors = nullptr;
    indices = nullptr;
    animVertices = nullptr;
    animNormals = nullptr;
    boneIds = nullptr;
    boneWeights = nullptr;
    boneMatrices = nullptr;
    boneCount = 0;
    vaoId = 0;
    vboId = nullptr;
  }

  非托管网格(const ::Mesh &网格) { 设(网格); }

  非托管网格(::Mesh &&网格) { 设(网格); }

  /**
   * 从模型文件加载网格
   */
  // static std::vector<Mesh> Load(const std::string& fileName) {
  //    int count = 0;
  //    ::Mesh* meshes = LoadMeshes(fileName.c_str(), &count);
  //    return std::vector<Mesh>(meshes, meshes + count);
  // }

  static ::Mesh 生成多边形网格(int 边数, float 半径) {
    return ::GenMeshPoly(边数, 半径);
  }

  static ::Mesh 生成平面网格(float 宽, float 长, int 行分段数, int 列分段数) {
    return ::GenMeshPlane(宽, 长, 行分段数, 列分段数);
  }

  static ::Mesh 生成立方体网格(float 宽, float 高, float 长) {
    return ::GenMeshCube(宽, 高, 长);
  }

  /**
   * （标准球体）
   */
  static ::Mesh 生成球体网格(float 半径, int 环数, int 段数) {
    return ::GenMeshSphere(半径, 环数, 段数);
  }

  /**
   * （无底部盖子）
   */
  static ::Mesh 生成半球体网格(float 半径, int 环数, int 段数) {
    return ::GenMeshHemiSphere(半径, 环数, 段数);
  }

  static ::Mesh 生成圆柱体网格(float 半径, float 高, int 段数) {
    return ::GenMeshCylinder(半径, 高, 段数);
  }

  /**
   * 生成圆锥/棱锥网格
   */
  static ::Mesh 生成圆锥网格(float 半径, float 高, int 段数) {
    return ::GenMeshCone(半径, 高, 段数);
  }

  static ::Mesh 生成圆环网格(float 半径, float 大小, int 半径段数, int 段数) {
    return ::GenMeshTorus(半径, 大小, 半径段数, 段数);
  }

  static ::Mesh 生成三叶结网格(float 半径, float 大小, int 半径段数, int 段数) {
    return ::GenMeshKnot(半径, 大小, 半径段数, 段数);
  }

  /**
   * 从图像数据生成高度图网格
   */
  static ::Mesh 生成高度图网格(const ::Image &高度图, ::Vector3 大小) {
    return ::GenMeshHeightmap(高度图, 大小);
  }

  /**
   * 从图像数据生成基于立方体的地图网格
   * https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/06%20Cubemaps/
   */
  static ::Mesh 生成立方体贴图网格(const ::Image &立方体贴图,
                                   ::Vector3 立方体尺寸) {
    return ::GenMeshCubicmap(立方体贴图, 立方体尺寸);
  }

  GETTERSETTER(int, 顶点数量, vertexCount)
  GETTERSETTER(int, 三角形数量, triangleCount)
  // 顶点属性数据
  GETTERSETTER(float *, 顶点位置, vertices)
  GETTERSETTER(float *, 顶点纹理坐标, texcoords)
  GETTERSETTER(float *, 顶点纹理坐标2, texcoords2)
  GETTERSETTER(float *, 顶点法线, normals)
  GETTERSETTER(float *, 顶点切线, tangents)
  GETTERSETTER(unsigned char *, 顶点颜色, colors)
  GETTERSETTER(unsigned short *, 顶点索引, indices)
  // 动画顶点数据
  GETTERSETTER(float *, 动画顶点位置, animVertices)
  GETTERSETTER(float *, 动画法线, animNormals)
  GETTERSETTER(unsigned char *, 顶点骨骼ID, boneIds)
  GETTERSETTER(float *, 顶点骨骼权重, boneWeights)
  GETTERSETTER(unsigned int, VaoId, vaoId) // OpenGL顶点数组对象id
  GETTERSETTER(unsigned int *, VboId,
               vboId) // OpenGL顶点缓冲对象id（默认顶点数据）

  非托管网格 &operator=(const ::Mesh &网格) {
    设(网格);
    return *this;
  }

  /**
   * 从内存中卸载网格（RAM和/或VRAM）
   */
  void 卸载网格() {
    if (vboId != nullptr) {
      ::UnloadMesh(*this);
      vboId = nullptr;
    }
  }

  /**
   * 将网格顶点数据上传到GPU（VRAM）
   */
  void 上传网格数据到GPU(bool 动态 = false) { ::UploadMesh(this, 动态); }

  /**
   * 更新网格缓冲区数据
   */
  void 更新网格缓存(int 索引, void *数据, int 数据大小, int 偏移 = 0) {
    ::UpdateMeshBuffer(*this, 索引, 数据, 数据大小, 偏移);
  }

  /**
   * 使用材质和变换矩阵绘制3D网格
   */
  void 绘制(const ::Material &材质, const ::Matrix &变换矩阵) const {
    ::DrawMesh(*this, 材质, 变换矩阵);
  }

  /**
   * 使用材质和不同的变换矩阵绘制多个网格实例
   */
  void 绘制(const ::Material &材质, ::Matrix *变换矩阵数组,
            int 实例个数) const {
    ::DrawMeshInstanced(*this, 材质, 变换矩阵数组, 实例个数);
  }

  /**
   * 将网格数据导出到文件
   *
   * @throws raylib::RaylibException 如果导出网格失败，则抛出异常。
   */
  void 导出到文件(const std::string &文件路径) {
    if (!::ExportMesh(*this, 文件路径.c_str())) {
      throw Raylib异常("导出网格失败");
    }
  }

  /**
   * 将网格导出为代码文件（.h），定义多个顶点属性数组
   *
   * @throws raylib::RaylibException 如果导出网格失败，则抛出异常。
   */
  void 导出到代码文件(const std::string &文件路径) {
    if (!::ExportMeshAsCode(*this, 文件路径.c_str())) {
      throw Raylib异常("导出网格失败");
    }
  }

  /**
   * 计算网格的包围盒限制
   */
  [[nodiscard]] R包围盒 包围盒() const { return ::GetMeshBoundingBox(*this); }

  /**
   * 计算网格的包围盒限制
   */
  operator R包围盒() const { return 包围盒(); }

  /**
   * 计算网格的切线
   */
  Mesh &生成切线() {
    ::GenMeshTangents(this);
    return *this;
  }

  /**
   * 从生成的网格加载模型
   */
  [[nodiscard]] raylib::模型 从网格加载模型() const {
    return ::LoadModelFromMesh(*this);
  }

  /**
   * 从生成的网格加载模型
   */
  operator raylib::模型() { return ::LoadModelFromMesh(*this); }

  /**
   * 返回网格是否有效
   */
  bool 检查可用性() { return ::IsModelValid(*this); }

protected:
  void 设(const ::Mesh &网格) {
    vertexCount = 网格.vertexCount;
    triangleCount = 网格.triangleCount;
    vertices = 网格.vertices;
    texcoords = 网格.texcoords;
    texcoords2 = 网格.texcoords2;
    normals = 网格.normals;
    tangents = 网格.tangents;
    colors = 网格.colors;
    indices = 网格.indices;
    animVertices = 网格.animVertices;
    animNormals = 网格.animNormals;
    boneIds = 网格.boneIds;
    boneWeights = 网格.boneWeights;
    boneMatrices = 网格.boneMatrices;
    vaoId = 网格.vaoId;
    vboId = 网格.vboId;
  }
};
} // namespace raylib

using R非托管网格 = raylib::非托管网格;

// #endif // RAYLIB_CPP_INCLUDE_MESHUNMANAGED_HPP_