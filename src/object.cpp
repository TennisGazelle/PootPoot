#include "object.h"

Object::Object()
{  
  /*
  _vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  _indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < _indices.size(); i++) {
    _indices[i] = _indices[i] - 1;
  }
  */

  LoadVerticiesFromFile("../models/Torus Knot.obj");

  _angle = 0.0f;

  glGenBuffers(1, &_V_BO);
  glBindBuffer(GL_ARRAY_BUFFER, _V_BO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &_I_BO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _I_BO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _indices.size(), &_indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  _vertices.clear();
  _indices.clear();
}

void Object::Update(unsigned int dt)
{
  //_angle = dt * M_PI/1000;
  //_model = glm::rotate(_model, (_angle), glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Object::GetModel()
{
  return _model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, _V_BO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _I_BO);

  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void Object::Move(Direction dir) {
	static const float distance = 0.5f;
	
	glm::vec3 transformationVector(0.0f);
	
	switch (dir) {
		case UP:
			transformationVector.z = distance;
			break;
		case DOWN:
		default:
			transformationVector.z = -distance;
			break;
	}
	_model = glm::translate(_model, transformationVector);
}

void Object::LoadVerticiesFromFile(std::string filename) {
  //declare incoming variables stuff
  Assimp::Importer _importer;
  const aiScene* _aiScene = _importer.ReadFile(filename, aiProcess_Triangulate);
  if (_aiScene == NULL) {
    std::cerr << "File contents had problmes but was successfully opened." << std::endl;
    return;
  }

    // iterate through the meshes and go through
  for( int meshIndex = 0; meshIndex < _aiScene->mNumMeshes; meshIndex++ ){
    int numFacesInMesh = _aiScene->mMeshes[meshIndex]->mNumFaces;
    //iterate through faces
    for( int faceIndex = 0; faceIndex < numFacesInMesh; faceIndex++ ){
      //helper
      Vertex tempVert(glm::vec3(0.0), glm::vec3(0.0));

      //get val from faces' mIndeces array
      for( int i = 0; i < 3; i++ ){
        //go to aiMesh's mVertices Array
        int vertice_index = _aiScene->mMeshes[meshIndex]->mFaces[faceIndex].mIndices[i];
        
        //get position 
        for (int j = 0; j < 3; ++j){
          tempVert.vertex[j] = _aiScene->mMeshes[meshIndex]->mVertices[vertice_index][j];
        }

        //add to the final vec
        _vertices.push_back(tempVert);
        _indices.push_back(vertice_index);
      }
    }
  }
}