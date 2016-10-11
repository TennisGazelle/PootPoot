#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "graphics_headers.h"

class Camera {
public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    
    void goToFrontView();
    void goToSideView();
    void goToTopView();

    void zoomIn();
    void zoomOut();

    void recalc();

    void updateFocusPoint(const glm::vec3 pFocusPoint);

private:
    glm::mat4 projection;
    glm::mat4 view;

    glm::vec3 _focusPoint, _cameraPosition;

    
};

#endif /* CAMERA_H */
