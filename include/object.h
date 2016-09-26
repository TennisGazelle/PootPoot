#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <cstdlib>
#include <vector>
#include "graphics_headers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h> 
#include <assimp/color4.h>
//#include <Magick++.h>

#include <fstream>
#include <string>

using namespace Assimp;

class Object {
public:
    Object();
    ~Object();
    void Update(unsigned int dt);
    void Render();
    void Move(Direction dir);

    void LoadVerticiesFromFile(std::string filename);

    glm::mat4 GetModel();

protected:
    glm::mat4 _model;
    std::vector<Vertex> _vertices;

private:
    std::vector<unsigned int> _indices;
    GLuint _V_BO;
    GLuint _I_BO;

    //irrelevant now
    float _angle;
};

#endif /* OBJECT_H */
