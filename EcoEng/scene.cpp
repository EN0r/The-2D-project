#include "scene.h"

sceneManager* sceneManager::instance = nullptr;
sceneManager* sceneManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new sceneManager;
        return instance;
    }
    return instance;
}
void scene::start(SDL_Renderer* renderer)
{
}

void scene::render(SDL_Renderer* renderer)
{
}

