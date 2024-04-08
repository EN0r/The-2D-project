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
	void getMousePosition(int& x, int& y) { x = mouseX; y = mouseY; };
	const Uint8*& getKeyState() { return keyState; } // returns a Rvalue of the keyState
	Uint32 getMouseState() { return mouseState;  }
	SDL_Window* getSDLWindow() { return _window; };
	SDL_Event event;
private:
	Uint32 mouseState;
	const Uint8* keyState;
	int mouseX, mouseY;
	SDL_Window* _window = nullptr;
};

