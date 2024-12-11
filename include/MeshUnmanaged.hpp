// #ifndef RAYLIB_CPP_INCLUDE_MESHUNMANAGED_HPP_
// #define RAYLIB_CPP_INCLUDE_MESHUNMANAGED_HPP_
#pragma once

#include <string>
#include <vector>

#include "./BoundingBox.hpp"
#include "./Matrix.hpp"
#include "./Model.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {

/**
 * 定义网格的顶点数据，不受C++ RAII管理。
 *
 * 如果需要，请确保调用Unload()，否则请使用raylib::Mesh。
 *
 * @see raylib::Mesh
 */
class MeshUnmanaged : public ::Mesh {
public:
    /**
     * 默认构造函数。
     */
    MeshUnmanaged() {
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
        vaoId = 0;
        vboId = nullptr;
    }

    MeshUnmanaged(const ::Mesh& mesh) { set(mesh); }

    MeshUnmanaged(::Mesh&& mesh) { set(mesh); }

    /**
     * 从模型文件加载网格
     */
    // static std::vector<Mesh> Load(const std::string& fileName) {
    //    int count = 0;
    //    ::Mesh* meshes = LoadMeshes(fileName.c_str(), &count);
    //    return std::vector<Mesh>(meshes, meshes + count);
    // }

    /**
     * 生成多边形网格
     */
    static ::Mesh Poly(int sides, float radius) { return ::GenMeshPoly(sides, radius); }

    /**
     * 生成平面网格（带细分）
     */
    static ::Mesh Plane(float width, float length, int resX, int resZ) {
        return ::GenMeshPlane(width, length, resX, resZ);
    }

    /**
     * 生成立方体网格
     */
    static ::Mesh Cube(float width, float height, float length) { return ::GenMeshCube(width, height, length); }

    /**
     * 生成球体网格（标准球体）
     */
    static ::Mesh Sphere(float radius, int rings, int slices) { return ::GenMeshSphere(radius, rings, slices); }

    /**
     * 生成半球体网格（无底部盖子）
     */
    static ::Mesh HemiSphere(float radius, int rings, int slices) { return ::GenMeshHemiSphere(radius, rings, slices); }

    /**
     * 生成圆柱体网格
     */
    static ::Mesh Cylinder(float radius, float height, int slices) { return ::GenMeshCylinder(radius, height, slices); }

    /**
     * 生成圆锥/棱锥网格
     */
    static ::Mesh Cone(float radius, float height, int slices) { return ::GenMeshCone(radius, height, slices); }

    /**
     * 生成圆环网格
     */
    static ::Mesh Torus(float radius, float size, int radSeg, int sides) {
        return ::GenMeshTorus(radius, size, radSeg, sides);
    }

    /**
     * 生成三叶结网格
     */
    static ::Mesh Knot(float radius, float size, int radSeg, int sides) {
        return ::GenMeshKnot(radius, size, radSeg, sides);
    }

    /**
     * 从图像数据生成高度图网格
     */
    static ::Mesh Heightmap(const ::Image& heightmap, ::Vector3 size) { return ::GenMeshHeightmap(heightmap, size); }

    /**
     * 从图像数据生成基于立方体的地图网格
     */
    static ::Mesh Cubicmap(const ::Image& cubicmap, ::Vector3 cubeSize) {
        return ::GenMeshCubicmap(cubicmap, cubeSize);
    }

    GETTERSETTER(int, VertexCount, vertexCount)
    GETTERSETTER(int, TriangleCount, triangleCount)
    GETTERSETTER(float*, Vertices, vertices)
    GETTERSETTER(float*, TexCoords, texcoords)
    GETTERSETTER(float*, TexCoords2, texcoords2)
    GETTERSETTER(float*, Normals, normals)
    GETTERSETTER(float*, Tangents, tangents)
    GETTERSETTER(unsigned char*, Colors, colors)
    GETTERSETTER(unsigned short*, Indices, indices) // NOLINT
    GETTERSETTER(float*, AnimVertices, animVertices)
    GETTERSETTER(float*, AnimNormals, animNormals)
    GETTERSETTER(unsigned char*, BoneIds, boneIds)
    GETTERSETTER(float*, BoneWeights, boneWeights)
    GETTERSETTER(unsigned int, VaoId, vaoId)
    GETTERSETTER(unsigned int*, VboId, vboId)

    MeshUnmanaged& operator=(const ::Mesh& mesh) {
        set(mesh);
        return *this;
    }

    /**
     * 从内存中卸载网格（RAM和/或VRAM）
     */
    void Unload() {
        if (vboId != nullptr) {
            ::UnloadMesh(*this);
            vboId = nullptr;
        }
    }

    /**
     * 将网格顶点数据上传到GPU（VRAM）
     */
    void Upload(bool dynamic = false) { ::UploadMesh(this, dynamic); }

    /**
     * 更新网格缓冲区数据
     */
    void UpdateBuffer(int index, void* data, int dataSize, int offset = 0) {
        ::UpdateMeshBuffer(*this, index, data, dataSize, offset);
    }

    /**
     * 使用材质和变换矩阵绘制3D网格
     */
    void Draw(const ::Material& material, const ::Matrix& transform) const { ::DrawMesh(*this, material, transform); }

    /**
     * 使用材质和不同的变换矩阵绘制多个网格实例
     */
    void Draw(const ::Material& material, ::Matrix* transforms, int instances) const {
        ::DrawMeshInstanced(*this, material, transforms, instances);
    }

    /**
     * 将网格数据导出到文件
     *
     * @throws raylib::RaylibException 如果导出网格失败，则抛出异常。
     */
    void Export(const std::string& fileName) {
        if (!::ExportMesh(*this, fileName.c_str())) {
            throw RaylibException("Failed to export the Mesh");
        }
    }

    /**
     * 将网格导出为代码文件（.h），定义多个顶点属性数组
     *
     * @throws raylib::RaylibException 如果导出网格失败，则抛出异常。
     */
    void ExportCode(const std::string& fileName) {
        if (!::ExportMeshAsCode(*this, fileName.c_str())) {
            throw RaylibException("Failed to export the Mesh");
        }
    }

    /**
     * 计算网格的包围盒限制
     */
    raylib::BoundingBox BoundingBox() const { return ::GetMeshBoundingBox(*this); }

    /**
     * 计算网格的包围盒限制
     */
    operator raylib::BoundingBox() { return BoundingBox(); }

    /**
     * 计算网格的切线
     */
    Mesh& GenTangents() {
        ::GenMeshTangents(this);
        return *this;
    }

    /**
     * 从生成的网格加载模型
     */
    raylib::Model LoadModelFrom() const { return ::LoadModelFromMesh(*this); }

    /**
     * 从生成的网格加载模型
     */
    operator raylib::Model() { return ::LoadModelFromMesh(*this); }

    /**
     * 返回网格是否有效
     */
    bool IsValid() { return ::IsModelValid(*this); }
protected:
    void set(const ::Mesh& mesh) {
        vertexCount = mesh.vertexCount;
        triangleCount = mesh.triangleCount;
        vertices = mesh.vertices;
        texcoords = mesh.texcoords;
        texcoords2 = mesh.texcoords2;
        normals = mesh.normals;
        tangents = mesh.tangents;
        colors = mesh.colors;
        indices = mesh.indices;
        animVertices = mesh.animVertices;
        animNormals = mesh.animNormals;
        boneIds = mesh.boneIds;
        boneWeights = mesh.boneWeights;
        boneMatrices = mesh.boneMatrices;
        vaoId = mesh.vaoId;
        vboId = mesh.vboId;
    }
};
} // namespace raylib

using RMeshUnmanaged = raylib::MeshUnmanaged;

// #endif // RAYLIB_CPP_INCLUDE_MESHUNMANAGED_HPP_