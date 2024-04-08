#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <memory>
#include <unordered_map>
#include "entity.h"

/*
	in regards to scene i will need to implement features which i can
	use to make scenes.
	Scenes will have entities inside.
*/

class sceneManager
{
	/*
	What i want:
	Need an array of some sorts to store all scenes
	I should have them stored as void* pointers
	Every frame call the scenemanager needs to refresh the current loaded scene.

	*/
public:
	sceneManager* getInstance();

	void updateScene();
	// Load a scene.
	template <typename world>
	bool loadScene(world _world);
	// Create a scene
	template<typename world>
	int createScene();

	template<typename world>
	std::shared_ptr<world> getScene(int sceneID);

	template<typename world>
	bool saveScene(int sceneID);

	template<typename world>
	std::shared_ptr<world> loadSavedScene(const char* savedScenePath);



	~sceneManager() {}
private:
	std::unordered_multimap<int, std::shared_ptr<void> > sceneList; // list for all scenes.
	int loadedScene = -1;
	int totalScenes = 0; // use this for assigning scene identifiers
	static sceneManager* instance;
	sceneManager(){} // irrelevant.
};

class scene : public sceneManager // scene will always be called through manager as i don't want to make copies of it as its super resource heavy with all the arrays
{
public:
	void render(SDL_Renderer* renderer);
	void start(SDL_Renderer* renderer);

private:
	std::shared_ptr<entityManager> sceneEntityManager = std::make_shared<entityManager>(new entityManager);
};

