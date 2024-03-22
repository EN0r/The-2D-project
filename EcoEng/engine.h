#pragma once
#include <iostream>
#include <memory>
#include "window.h"
#include "renderer.h"

enum GAMESTATES
{
	PLAY = 1,
	PAUSE = 0,
	STOP = 2,
	FORCESTOP = -1
	
};

class engine
{
public:
	void entry(); // engine entrypoint
	static engine* getInstance();

	~engine() { }
private:
	engine() {}
	static engine* instance;
	// renderer class is derived from window. 
	// create pointers for renderer and window class
	std::shared_ptr<window> _window;
	std::unique_ptr<renderer> _renderer;
	
};

