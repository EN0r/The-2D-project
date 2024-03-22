#pragma once
#include "SDL.h"
#include "SDL_image.h"

/*
	in regards to scene i will need to implement features which i can
	use to make scenes.
	Scenes will have entities inside.
*/

class scene
{
public:
	virtual void render(SDL_Renderer* renderer);
	virtual void start(SDL_Renderer* renderer);

private:

};

