#include "engine.h"
#include "entity.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_sdl3.h"
#include "vendor/imgui/imgui_impl_sdlrenderer3.h"
engine* engine::instance = nullptr;
engine* engine::getInstance()
{
    if (instance != nullptr)
    {
        return nullptr;
    }
    else {
        instance = new engine;
        return instance;
    }
}

void engine::entry()
{
    // initialize memory for the window and renderer.
    _window.reset(new window);
    _renderer.reset(new renderer);


    // Usage -> e->addComponent<COMPONENT>(entity1Id) returns a integer for the identifier for the created entity.
    // renderer will focus on image loading ect.
    _window->createWindow("eCore", vec2(100, 100), vec2(800, 600), SDL_WINDOW_SHOWN);
    _renderer->entry(_window);
}