#include <iostream>
#include "window.h"


bool window::createWindow(const char* title, vec2 position, vec2 size, Uint32 flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow(title,position.x,position.y,size.x,size.y, flags);

    if (_window != nullptr)
        return true;
    return false;
}

int window::pollEvent()
{
    using namespace std;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            cout << "Quit requested!" << std::endl;
            on = false;
            break;
        }
    }
    return 0;
}
