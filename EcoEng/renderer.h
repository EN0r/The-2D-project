#pragma once
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "window.h"

struct image {
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	// function definitions
	bool loadImage(const char* filepath);
	void renderTextureFromSurface(SDL_Renderer* render, SDL_Rect size);
	~image()
	{
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
};
class renderer 
{
public:
	void entry(std::shared_ptr<window>& window);
	bool pause = false;
	void renderUI(SDL_Renderer* renderer);
	void renderCycle(SDL_Renderer* renderer); // Can directly grab the pointer for wClass from inside this class for keystate handling
private:
	unsigned int frames = 0;
	Uint64 now = 0;
	Uint64 last = 0;
	double deltaTime = 0; // deltatime in MS
	SDL_Renderer* render;
	std::shared_ptr<window> wClass;
};

