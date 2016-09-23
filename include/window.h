#ifndef __WINDOW_H_
#define __WINDOW_H_

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Window {
public:
    Window();
    ~Window();
    bool Initialize(const string &name, int* width, int* height);
    void Swap();

private:
    SDL_Window* gWindow;
    SDL_GLContext gContext;
};

#endif /* WINDOW_H */
