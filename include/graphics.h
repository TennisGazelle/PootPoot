#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

#include <iostream>
#include <SDL2/SDL.h>

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "flyers/player.h"
#include "flyers/bullet_holder.h"

using namespace std;

class Graphics {
public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    
    // master function that will call all appropriate subfuncitons
    bool Update(unsigned int dt);
    virtual bool UpdatePlayers(unsigned int dt);
    virtual bool UpdateAIOpponent(unsigned int dt);
    virtual bool UpdateScore(unsigned int dt);

    void Render();
    void ShiftCamera(Direction dir);
    void Keyboard(SDL_Event sdl_event);
    void CheckBounds();
    int hasPlayerBeenShot();

protected:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    // things to give the shader
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_preMultipliedMVPMatrix;

    // game object (will be changed out)
    Player *m_player;
    Player *m_opponent;

    BulletHolder *bulletHolder;

    //field area size
    int boundarySize;
    Object *m_boundary;

    enum GameState {
        MAIN_MENU, SCOREBOARD, RUNNING, EXIT
    } gameState = RUNNING;
};

#endif /* GRAPHICS_H */
