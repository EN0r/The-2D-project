#include "engine.h"
#include "entity.h"
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

    std::shared_ptr<entityManager> e = std::make_shared<entityManager>();
    int entity1Id = e->createEntity<entity>();
    e->addComponent<transform>(entity1Id);
    e->addComponent<rigidBody>(entity1Id);
    e->getComponent<rigidBody>(entity1Id)->force = 100;
    std::cout << "Done" << std::endl;
    // Usage -> e->addComponent<COMPONENT>(entity1Id) returns a integer for the identifier for the created entity.

    std::cout << e->getComponent<rigidBody>(entity1Id)->force << std::endl;
    std::cout << e->retCompIdentifier<transform>() << std::endl;



    // renderer will focus on image loading ect.
    _window->createWindow("eCore", vec2(100, 100), vec2(800, 600), SDL_WINDOW_SHOWN);
    _renderer->entry(_window);


    /*
    sandBox
    
    
    VVVVVVVVVVVVVVV
    */






}