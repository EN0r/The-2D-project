#pragma once
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
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
		delete texture;
		delete surface;
	}
};

class renderer 
{
public:
	void entry(std::shared_ptr<window>& window);
	bool pause = false;
private:
	SDL_Renderer* render;
	std::shared_ptr<window> wClass;
};

