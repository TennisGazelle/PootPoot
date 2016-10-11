#include "object.h"

Object::Object()
{  

}

Object::~Object()
{
  _vertices.clear();
  _indices.clear();
}

void Object::Init(const std::string& filename) {
  LoadVerticiesFromFile(filename);

  glGenBuffers(1, &_V_BO);
  glBindBuffer(GL_ARRAY_BUFFER, _V_BO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &_I_BO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _I_BO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _indices.size(), &_indices[0], GL_STATIC_DRAW);
}

void Object::Update(unsigned int dt)
{

}

glm::mat4 Object::GetModel()
{
  return _model;
}

void Object::setPosition(glm::vec3 pPosition) {
  _model[3] = glm::vec4(pPosition, _model[3][3]);
}

void Object::resize(glm::vec3 pResizingFactor) {
  _model = glm::scale(_model, pResizingFactor);
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, _V_BO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position)); //should be 0
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));  //should be one glm::vec off

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _I_BO);

  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
  //glDrawElements(GL_LINES, _indices.size(), GL_UNSIGNED_INT, 0);

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
		case RIGHT:
			transformationVector.x = -distance;
			break;
		case LEFT:
			transformationVector.x = distance;
			break;
	}
	_model = glm::translate(_model, transformationVector);
}

void Object::LoadVerticiesFromFile(const std::string& filename) {
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
          tempVert.position[j] = _aiScene->mMeshes[meshIndex]->mVertices[vertice_index][j];
          tempVert.color[j]=  float(rand()%100) / 100.0f;
        }

        //add to the final vec
        _vertices.push_back(tempVert);
        _indices.push_back(vertice_index);
      }
    }
  }
  /*
  std::vector<unsigned int> line_indices;
  for (int i = 0; i < _indices.size(); i++) {
    line_indices.push_back(_indices[i]);
    if (i%3 == 2) {
      line_indices.push_back(_indices[i-1]);
      line_indices.push_back(_indices[i]);
      line_indices.push_back(_indices[i-2]);
      line_indices.push_back(_indices[i]);
    }
  }
  _indices = line_indices;
  */
}

bool hasTwoObjectsHit(Object* first, Object* second) {
  glm::vec3 distanceBetweenTwo = glm::vec3(first->GetModel()[3] - second->GetModel()[3]);
  return abs(distanceBetweenTwo.length()) <= 2.0;
}
