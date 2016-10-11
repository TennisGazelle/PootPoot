#include "camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

bool Camera::Initialize(int w, int h) {
  _focusPoint = glm::vec3(0.0);
  _cameraPosition = glm::vec3(0.0, 8.0, -16.0);

  this->recalc(); 		//for the view matrix

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 100.0f); //Distance to the far plane, 

  return true;
}

glm::mat4 Camera::GetProjection() {
  return projection;
}

glm::mat4 Camera::GetView() {
  return view;
}

void Camera::goToFrontView() {
  _cameraPosition = glm::vec3(0.0, 0.0, -16.0);
  this->recalc();
}

void Camera::goToSideView() {
  _cameraPosition = glm::vec3(-16.0, 0.0, 0.0);
  this->recalc();
}

void Camera::goToTopView() {
  _cameraPosition = glm::vec3(0.0, 20.0, -0.5);
  this->recalc();
}

void Camera::zoomIn() {
  _cameraPosition *= 0.9;
  this->recalc();
}

void Camera::zoomOut() {
  _cameraPosition *= 1.1;
  this->recalc();
}

void Camera::updateFocusPoint(const glm::vec3 pFocusPoint) {
  static const float dampingFactor = 0.1f;
  _focusPoint = (dampingFactor * _focusPoint) + ((1-dampingFactor) * pFocusPoint);
  
  _cameraPosition = (dampingFactor * _cameraPosition) + ((1-dampingFactor) * (glm::vec3(0.0, 20.0, -0.5)+_focusPoint));

  recalc();
}

void Camera::recalc(){
  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine
  view = glm::lookAt( _cameraPosition, //Eye Position
                      _focusPoint, //Focus point
                      GLOBAL_UP); //Positive Y is up
}