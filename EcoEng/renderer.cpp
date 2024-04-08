#include "renderer.h"
#include <iostream>
#include "SDL_thread.h"
#include "entity.h"
#include "interface.h"
/*
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_sdl3.h"
#include "vendor/imgui/imgui_impl_sdlrenderer3.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
*/

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


void renderer::renderUI(SDL_Renderer* renderer)
{

}

void renderer::renderCycle(SDL_Renderer* renderer)
{
	frames++;


}


void renderer::entry(std::shared_ptr<window>& _window)
{
	// obviously handle all render calls
	wClass = _window;
	this->render = SDL_CreateRenderer(wClass->getSDLWindow(),-1, SDL_RENDERER_ACCELERATED);
	if (_window != nullptr)
		this->wClass = _window;
	IMG_Init(IMG_INIT_PNG);
	/*
		image img;
		img.loadImage("./resources/charImage.png");

	*/

	/*
	Camera test below
	*/
	std::shared_ptr<entityManager> e = std::make_shared<entityManager>();
	int entity1Id = e->createEntity<entity>();
	e->addComponent<transform>(entity1Id);
	e->addComponent<rigidBody>(entity1Id);
	e->getComponent<rigidBody>(entity1Id)->force = 100;
	//std::cout << e->getComponent<rigidBody>(entity1Id)->force << std::endl;
	//std::cout << e->retCompIdentifier<transform>() << std::endl;

	uiFrame* uXFrame = new uiFrame;
	{ // Ui testing here
		uXFrame->setColor(100, 100, 100, 255);
		uXFrame->setPosition(100, 100, 300, 300);
	}
	
	std::shared_ptr<image> img(new image);
	img->loadImage("./resources/charImage.png");
	now = SDL_GetPerformanceCounter();
	// Imgui
	SDL_GLContext glContext = SDL_GL_CreateContext(_window->getSDLWindow());
	SDL_GL_MakeCurrent(_window->getSDLWindow(),glContext);
	while (wClass->on) // finish render cycle then quit
	{
		wClass->pollEvent();
		e->requestEntityUpdate<entity>(*render);
		last = now;
		now = SDL_GetPerformanceCounter();
		deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
		renderUI(render); // Ui rendering before 
		renderCycle(render); // Main graphics
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
	    img->renderTextureFromSurface(render, { 100,100,100,100 });
		uXFrame->renderFrame(render, this->wClass);
		// Create a input class for handling SDL_Event parameters
		SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
		SDL_RenderPresent(render);
		SDL_RenderClear(render);
	}
	SDL_Quit();
}