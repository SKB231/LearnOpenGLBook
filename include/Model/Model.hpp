#include <Mesh/mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <memory>
#include <set>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Model {
public:
  Model(string filePath, bool shouldFlipUVs = true) {
    loadModel(filePath, shouldFlipUVs);
    position = {0, 0, 0};
    // scale = {0.2, 0.2, 0.2};
    scale = {1, 1, 1};
  }
  void Draw(Shader &shader, Camera *camera);
  void DisplayWindow();
  string modelName = "empty";
  Shader *shader;

  // Transforms
  glm::vec3 position;
  glm::vec3 scale;
  bool hasOutline = true;

  void UpdateShaderTransforms(Camera *camera);
  void UpdateLightingData(); // DirectionalLight dirLight, vector<PointLight>
                             // pointLights

private:
  vector<Mesh> meshes; // to be filled when processing tree
  string directory;

  void loadModel(string filePath, bool shouldFlipUVs);
  void UpdateShaderTransforms(Camera *camera, Shader *shader);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  vector<Texture> loadedTextures;

  vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                       string typeName);
};