#ifndef __GAME_H_
#define __GAME_H_ 

#include "../graphics.h"

class Game : public Graphics {
public:
	Game();
	~Game();

	/* data */
};

class ShootingGame : public Graphics {
public:
	bool UpdatePlayers(unsigned int dt);
	bool UpdateAIOpponent(unsigned int dt);
	bool UpdateScore(unsigned int dt);
	/* data */
};

class AvoidanceGame : public Graphics {

};

class ColorClashGame: public Graphics {

};

/*
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
*/
#endif