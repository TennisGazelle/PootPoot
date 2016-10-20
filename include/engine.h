#ifndef __ENGINE_H_
#define __ENGINE_H_

#include <sys/time.h>
#include <assert.h>

#include "graphics_headers.h"

#include "window.h"
#include "graphics.h"

class Engine {
public:
    Engine(string name, int width = 800, int height = 800);
    Engine(string name);
    ~Engine();

    bool Initialize();
    void Run();
    void Keyboard();
    unsigned int getDT();
    long long GetCurrentTimeMillis();

private:
    // Window related variables
    Window *m_window;    
    string m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    SDL_Event m_event;

    // Main Game Engine variables
    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    SDL_Joystick *m_joystick;

    // Master Run of Game
    bool m_running;
};

#endif // ENGINE_H
