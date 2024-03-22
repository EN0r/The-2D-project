#include "renderer.h"
#include <iostream>
#include "SDL_thread.h"

bool image::loadImage(const char* filepath)
{
	surface = IMG_Load(filepath);
	if (surface == nullptr)
		return false;
	return true;
}

void image::renderTextureFromSurface(SDL_Renderer* render, SDL_Rect size)
{
		if (texture == nullptr)
		{
			texture = SDL_CreateTextureFromSurface(render, surface);
			SDL_RenderCopy(render, texture, NULL, &size);
		}
		else { SDL_RenderCopy(render, texture, NULL, &size); } 
}

void renderer::entry(std::shared_ptr<window>& window)
{
	// obviously handle all render calls
	wClass = window;
	this->render = SDL_CreateRenderer(wClass->getSDLWindow(),-1, SDL_RENDERER_ACCELERATED);
	if (window != nullptr)
		this->wClass = window;

	IMG_Init(IMG_INIT_PNG);
	/*
		image img;
		img.loadImage("./resources/charImage.png");

	*/
	std::cout << SDL_GetError() << std::endl;
	while (wClass->on) // finish render cycle then quit
	{
		wClass->pollEvent();
		/*
		todo:
			Have specific threads for:
				Mathematical Calculation
				PostProcessing
			Also, Need to create a quick camera system
			Also Particle system would be nice.
			Need serialization to save levels.
			Collision using AABB.
			Circle circle collision.
		
		*/
	    //img.renderTextureFromSurface(render, { 100,100,100,100 });

		SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
		SDL_RenderPresent(render);
		SDL_RenderClear(render);
	}
	SDL_Quit();
}

