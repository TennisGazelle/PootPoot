#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <cstdlib>
#include <vector>
#include "graphics_headers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h> 
#include <assimp/color4.h>
#include <glm/gtx/vector_angle.hpp>
//#include <Magick++.h>

#include <fstream>
#include <string>

using namespace Assimp;

class Object {
public:
    Object();
    ~Object();
    void Init(const std::string& filename);
    void Update(unsigned int dt);
    void Render();
    void Move(Direction dir);

    void LoadVerticiesFromFile(const std::string& filename);

    glm::mat4 GetModel();
    void setPosition(glm::vec3 pPosition);
    void resize(glm::vec3 pResizingFactor);
    void setModel(const glm::mat4& pModel);

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

bool hasTwoObjectsHit(Object* first, Object* second);

#endif /* OBJECT_H */
