#pragma once
#include <SDL.h>
#include <memory>
#include "vec2.h"
static class window
{
public:
	bool on = true; // if this is false quit.
	bool createWindow(const char* title, vec2 position, vec2 size, Uint32 flags);
	int pollEvent(); // should be called each frame.

	SDL_Window* getSDLWindow() { return _window; };
private:

	SDL_Window* _window = nullptr;
	SDL_Event event;
};

