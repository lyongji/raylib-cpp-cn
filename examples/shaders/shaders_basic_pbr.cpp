/*******************************************************************************************
 *
 *   raylib [shaders] example - Basic PBR
 *
 *   Example originally created with raylib 5.0, last time updated with
 *raylib 5.1-dev
 *
 *   Example contributed by Afan OLOVCIC (@_DevDad) and reviewed by Ramon
 *Santamaria (@raysan5)
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an
 *OSI-certified, BSD-like license that allows static linking with closed source
 *software
 *
 *   Copyright (c) 2023-2024 Afan OLOVCIC (@_DevDad)
 *
 *   Model: "Old Rusty Car" (https://skfb.ly/LxRy) by Renafox,
 *   licensed under Creative Commons Attribution-NonCommercial
 *   (http://creativecommons.org/licenses/by-nc/4.0/)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 120
#endif

#include <array>

static const int MAX_LIGHTS = 4; // Max dynamic lights supported by shader

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

// Light type
enum class LightType { DIRECTIONAL = 0, POINT, SPOT };

// Light data
struct Light {
  LightType type;
  int enabled;
  raylib::Vector3 position;
  raylib::Vector3 target;
  std::array<float, 4> color;
  float intensity;

  // Shader light parameters locations
  int typeLoc;
  int enabledLoc;
  int positionLoc;
  int targetLoc;
  int colorLoc;
  int intensityLoc;
};

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
static int 光源数量 =
    0; // Current number of dynamic lights that have been created

//----------------------------------------------------------------------------------
// Module specific Functions Declaration
//----------------------------------------------------------------------------------
// Create a light and get shader locations
static Light CreateLight(size_t index, LightType type, Vector3 position,
                         Vector3 target, Color color, float intensity,
                         Shader shader);

// Update light properties on shader
// NOTE: Light shader locations should be available
static void UpdateLight(Shader shader, const Light &light);

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int 屏幕宽 = 800;
  const int 屏幕高 = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(屏幕宽, 屏幕高, "raylib [shaders] example - basic pbr");

  // Define the camera to look into our 3d world
  R相机 相机;
  相机.position = {2.0f, 2.0f, 6.0f}; // Camera position
  相机.target = {0.0f, 0.5f, 0.0f};   // Camera looking at point
  相机.up = {0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  相机.fovy = 45.0f;            // Camera field-of-view Y
  相机.projection = CAMERA_PERSPECTIVE; // Camera projection type

  // Load PBR shader and setup all required locations
  R着色器 着色器(TextFormat("resources/shaders/glsl%i/pbr.vs", GLSL_VERSION),
                 TextFormat("resources/shaders/glsl%i/pbr.fs", GLSL_VERSION));
  着色器.locs[SHADER_LOC_MAP_ALBEDO] = GetShaderLocation(着色器, "albedoMap");
  // WARNING: Metalness, roughness, and ambient occlusion are all packed into a
  // MRA R   // They are passed as to the SHADER_LOC_MAP_METALNESS location for
  // convenience, shader already takes care of it accordingly
  着色器.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(着色器, "mraMap");
  着色器.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(着色器, "normalMap");
  // WARNING: Similar to the MRA map, the emissive map packs different
  // information into a single texture: it stores height and emission data It is
  // binded to SHADER_LOC_MAP_EMISSION location an properly processed on shader
  着色器.locs[SHADER_LOC_MAP_EMISSION] =
      GetShaderLocation(着色器, "emissiveMap");
  着色器.locs[SHADER_LOC_COLOR_DIFFUSE] =
      GetShaderLocation(着色器, "albedoColor");

  // Setup additional required shader locations, including lights data
  着色器.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(着色器, "viewPos");
  int lightCountLoc = GetShaderLocation(着色器, "numOfLights");
  int maxLightCount = MAX_LIGHTS;
  着色器.设统一变量值(lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

  // Setup ambient color and intensity parameters
  float ambientIntensity = 0.02f;
  R颜色 ambientColor = {26, 32, 135, 255};
  raylib::Vector3 ambientColorNormalized = {ambientColor.r / 255.0f,
                                            ambientColor.g / 255.0f,
                                            ambientColor.b / 255.0f};
  着色器.设统一变量值(着色器.取统一变量位置("ambientColor"),
                      &ambientColorNormalized, SHADER_UNIFORM_VEC3);
  着色器.设统一变量值(着色器.取统一变量位置("ambient"), &ambientIntensity,
                      SHADER_UNIFORM_FLOAT);

  // Get location for shader parameters that can be modified in real time
  int emissiveIntensityLoc = 着色器.取统一变量位置("emissivePower");
  int emissiveColorLoc = 着色器.取统一变量位置("emissiveColor");
  int textureTilingLoc = 着色器.取统一变量位置("tiling");

  // Load old car model using PBR maps and shader
  // WARNING: We know this model consists of a single model.meshes[0] and
  // that model.materials[0] is by default assigned to that mesh
  // There could be more complex models consisting of multiple meshes and
  // multiple materials defined for those meshes... but always 1 mesh = 1
  // material
  R模型 车("resources/models/old_car_new.glb");

  // Assign already setup PBR shader to model.materials[0], used by
  // models.meshes[0]
  车.materials[0].shader = 着色器;

  // Setup materials[0].maps default parameters
  车.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
  车.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0.0f;
  车.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
  车.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
  车.materials[0].maps[MATERIAL_MAP_EMISSION].color = {255, 162, 0, 255};

  // Setup materials[0].maps default textures
  车.materials[0].maps[MATERIAL_MAP_ALBEDO].texture =
      LoadTexture("resources/old_car_d.png");
  车.materials[0].maps[MATERIAL_MAP_METALNESS].texture =
      LoadTexture("resources/old_car_mra.png");
  车.materials[0].maps[MATERIAL_MAP_NORMAL].texture =
      LoadTexture("resources/old_car_n.png");
  车.materials[0].maps[MATERIAL_MAP_EMISSION].texture =
      LoadTexture("resources/old_car_e.png");

  // Load floor model mesh and assign material parameters
  // NOTE: A basic plane shape can be generated instead of being loaded from a
  // model file
  R模型 地("resources/models/plane.glb");
  // Mesh floorMesh = GenMeshPlane(10, 10, 10, 10);
  // GenMeshTangents(&floorMesh);      // TODO: Review tangents generation
  // Model floor = LoadModelFromMesh(floorMesh);

  // Assign material shader for our floor model, same PBR shader
  地.materials[0].shader = 着色器;

  地.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
  地.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0.0f;
  地.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
  地.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
  地.materials[0].maps[MATERIAL_MAP_EMISSION].color = BLACK;

  地.materials[0].maps[MATERIAL_MAP_ALBEDO].texture =
      LoadTexture("resources/road_a.png");
  地.materials[0].maps[MATERIAL_MAP_METALNESS].texture =
      LoadTexture("resources/road_mra.png");
  地.materials[0].maps[MATERIAL_MAP_NORMAL].texture =
      LoadTexture("resources/road_n.png");

  // Models texture tiling parameter can be stored in the Material struct if
  // required (CURRENTLY NOT USED) NOTE: Material.params[4] are available for
  // generic parameters storage (float)
  Vector2 carTextureTiling = {0.5f, 0.5f};
  Vector2 floorTextureTiling = {0.5f, 0.5f};

  // Create some lights
  std::array<Light, MAX_LIGHTS> lights = {
      CreateLight(0, LightType::POINT, {-1.0f, 1.0f, -2.0f}, {0.0f, 0.0f, 0.0f},
                  YELLOW, 4.0f, 着色器),
      CreateLight(1, LightType::POINT, {2.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f},
                  GREEN, 3.3f, 着色器),
      CreateLight(2, LightType::POINT, {-2.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f},
                  RED, 8.3f, 着色器),
      CreateLight(3, LightType::POINT, {1.0f, 1.0f, -2.0f}, {0.0f, 0.0f, 0.0f},
                  BLUE, 2.0f, 着色器),
  };

  // Setup material texture maps usage in shader
  // NOTE: By default, the texture maps are always used
  int usage = 1;
  SetShaderValue(着色器, GetShaderLocation(着色器, "useTexAlbedo"), &usage,
                 SHADER_UNIFORM_INT);
  SetShaderValue(着色器, GetShaderLocation(着色器, "useTexNormal"), &usage,
                 SHADER_UNIFORM_INT);
  SetShaderValue(着色器, GetShaderLocation(着色器, "useTexMRA"), &usage,
                 SHADER_UNIFORM_INT);
  SetShaderValue(着色器, GetShaderLocation(着色器, "useTexEmissive"), &usage,
                 SHADER_UNIFORM_INT);

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //---------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    相机.更新(CAMERA_ORBITAL);

    // Update the shader with the camera view vector (points towards { 0.0f,
    // 0.0f, 0.0f })
    std::array<float, 3> cameraPos = {相机.position.x, 相机.position.y,
                                      相机.position.z};
    SetShaderValue(着色器, 着色器.locs[SHADER_LOC_VECTOR_VIEW],
                   cameraPos.data(), SHADER_UNIFORM_VEC3);

    // Check key inputs to enable/disable lights
    if (IsKeyPressed(KEY_ONE)) {
      lights[2].enabled = !lights[2].enabled;
    }
    if (IsKeyPressed(KEY_TWO)) {
      lights[1].enabled = !lights[1].enabled;
    }
    if (IsKeyPressed(KEY_THREE)) {
      lights[3].enabled = !lights[3].enabled;
    }
    if (IsKeyPressed(KEY_FOUR)) {
      lights[0].enabled = !lights[0].enabled;
    }

    // Update light values on shader (actually, only enable/disable them)
    for (int i = 0; i < MAX_LIGHTS; i++)
      UpdateLight(着色器, lights[i]);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode3D(相机);

    // Set floor model texture tiling and emissive color parameters on shader
    SetShaderValue(着色器, textureTilingLoc, &floorTextureTiling,
                   SHADER_UNIFORM_VEC2);
    raylib::Vector4 floorEmissiveColor =
        ColorNormalize(地.materials[0].maps[MATERIAL_MAP_EMISSION].color);
    SetShaderValue(着色器, emissiveColorLoc, &floorEmissiveColor,
                   SHADER_UNIFORM_VEC4);

    DrawModel(地, {0.0f, 0.0f, 0.0f}, 5.0f, WHITE); // Draw floor model

    // Set old car model texture tiling, emissive color and emissive intensity
    // parameters on shader
    SetShaderValue(着色器, textureTilingLoc, &carTextureTiling,
                   SHADER_UNIFORM_VEC2);
    raylib::Vector4 carEmissiveColor =
        ColorNormalize(车.materials[0].maps[MATERIAL_MAP_EMISSION].color);
    SetShaderValue(着色器, emissiveColorLoc, &carEmissiveColor,
                   SHADER_UNIFORM_VEC4);
    float emissiveIntensity = 0.01f;
    SetShaderValue(着色器, emissiveIntensityLoc, &emissiveIntensity,
                   SHADER_UNIFORM_FLOAT);

    车.绘制模型({0.0f, 0.0f, 0.0f}, 0.005f, WHITE); // Draw car model

    // Draw spheres to show the lights positions
    for (const auto &light : lights) {
      Color lightColor = {static_cast<unsigned char>(light.color[0] * 255),
                          static_cast<unsigned char>(light.color[1] * 255),
                          static_cast<unsigned char>(light.color[2] * 255),
                          static_cast<unsigned char>(light.color[3] * 255)};

      if (light.enabled)
        DrawSphereEx(light.position, 0.2f, 8, 8, lightColor);
      else
        DrawSphereWires(light.position, 0.2f, 8, 8,
                        ColorAlpha(lightColor, 0.3f));
    }

    EndMode3D();

    DrawText("Toggle lights: [1][2][3][4]", 10, 40, 20, LIGHTGRAY);

    DrawText("(c) Old Rusty Car model by Renafox (https://skfb.ly/LxRy)",
             屏幕宽 - 320, 屏幕高 - 20, 10, LIGHTGRAY);

    DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  // Unbind (disconnect) shader from car.material[0]
  // to avoid UnloadMaterial() trying to unload it automatically
  车.materials[0].shader = {0};
  UnloadMaterial(车.materials[0]);
  车.materials[0].maps = nullptr;
  // UnloadModel(car);

  地.materials[0].shader = {0};
  UnloadMaterial(地.materials[0]);
  地.materials[0].maps = nullptr;
  // UnloadModel(floor);

  // UnloadShader(shader);       // Unload Shader

  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

// Create light with provided data
// NOTE: It updated the global lightCount and it's limited to MAX_LIGHTS
static Light CreateLight(size_t index, LightType type, Vector3 position,
                         Vector3 target, Color color, float intensity,
                         Shader shader) {
  Light light;

  light.enabled = 1;
  light.type = type;
  light.position = position;
  light.target = target;
  light.color[0] = (float)color.r / 255.0f;
  light.color[1] = (float)color.g / 255.0f;
  light.color[2] = (float)color.b / 255.0f;
  light.color[3] = (float)color.a / 255.0f;
  light.intensity = intensity;

  // NOTE: Shader parameters names for lights must match the requested ones
  light.enabledLoc =
      GetShaderLocation(shader, TextFormat("lights[%i].enabled", index));
  light.typeLoc =
      GetShaderLocation(shader, TextFormat("lights[%i].type", index));
  light.positionLoc =
      GetShaderLocation(shader, TextFormat("lights[%i].position", index));
  light.targetLoc =
      GetShaderLocation(shader, TextFormat("lights[%i].target", index));
  light.colorLoc =
      GetShaderLocation(shader, TextFormat("lights[%i].color", index));
  light.intensityLoc =
      GetShaderLocation(shader, TextFormat("lights[%i].intensity", index));

  UpdateLight(shader, light);

  return light;
}

// Send light properties to shader
// NOTE: Light shader locations should be available
static void UpdateLight(Shader shader, const Light &light) {
  SetShaderValue(shader, light.enabledLoc, &light.enabled, SHADER_UNIFORM_INT);
  SetShaderValue(shader, light.typeLoc, &light.type, SHADER_UNIFORM_INT);

  // Send to shader light position values
  std::array<float, 3> position = {light.position.x, light.position.y,
                                   light.position.z};
  SetShaderValue(shader, light.positionLoc, position.data(),
                 SHADER_UNIFORM_VEC3);

  // Send to shader light target position values
  std::array<float, 3> target = {light.target.x, light.target.y,
                                 light.target.z};
  SetShaderValue(shader, light.targetLoc, target.data(), SHADER_UNIFORM_VEC3);
  SetShaderValue(shader, light.colorLoc, light.color.data(),
                 SHADER_UNIFORM_VEC4);
  SetShaderValue(shader, light.intensityLoc, &light.intensity,
                 SHADER_UNIFORM_FLOAT);
}