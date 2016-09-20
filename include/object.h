#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h> 
#include <assimp/color4.h>
//#include <Magick++.h>

#include <fstream>
//#include <stream>
#include <string>

using namespace Assimp;

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt);
    void Render();
    void Move(Direction dir);

    void LoadVerticiesFromFile(std::string filename);

    glm::mat4 GetModel();

  private:
    glm::mat4 _model;
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    GLuint _V_BO;
    GLuint _I_BO;

    //assimp
    //Assimp::Importer _importer;
    //const aiScene* _aiScene;

    //irrelevant now
    float _angle;
};

#endif /* OBJECT_H */
