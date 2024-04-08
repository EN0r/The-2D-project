#include "renderer.h"
#include "SDL_ttf.h"
/*
Ui will not use transform just x,y width height as theyre in window positions and not ingame
Ui core will handle events e.g. Button clicks etcetera -- Will it though?
I shall use AABB to register button clicks.
The design of UI will be very rudamentary mainly for debug purposes
I will also require text rendering
*/
struct uiProperties
{
	int r, g, b;
	int a = 255;
};
class game_Text
{
public:
	bool init(SDL_Renderer* renderer, const char* text, unsigned int size, int x, int y, SDL_Color color = { 0,0,0,255 }, const char* path = "./resources/comicSans/COMIC.TTF");
	void renderText(SDL_Renderer* renderer);
	void changeText(SDL_Renderer* renderer, const char* text);
	~game_Text()
	{
		if (font != nullptr)
			TTF_CloseFont(font);
		delete this->surface;
		delete this->texture;
		delete this->defaultPath;
		delete this->font;
	}
	SDL_Rect size = { 0,0,0,0 };
private:
	int x, y;
	SDL_Color color = { 0,0,0,255 };
	const char* cPath = "NULL";
	unsigned int textSize = 0;
	TTF_Font* font = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Color defaultColor = { 0,0,0,255 };
	const char* defaultPath = "./resources/comicSans/COMIC.TTF";
};


class uiCore
{
public:
	bool init();
	//bool AABB(int mouseX,int mouseY);
private:
	SDL_Rect thisSize = {0,0,0,0};
	int mouseClickboxSize = 5; // mouse clickbox has a exterior size of 5x5 in pixels.
	bool buttonClicked();
	bool buttonHeld();

};
// basic create Rect
class uiFrame : public uiCore
{
public:
	bool hasTitle = true;
	void renderFrame(SDL_Renderer* renderer, std::shared_ptr<window> window);
	void setColor(int r, int g, int b, int a) { u.r = r;u.g = g;u.b = b;u.a = a;}
	void setPosition(int x, int y, int w, int h) { thisSize.x = x; thisSize.y = y;thisSize.w = w;thisSize.h = h; }
	const char* titleText = "Untitled";
private:
	bool AABB(SDL_Rect rect1, SDL_Rect rect2)
	{
		if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x && rect1.y < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y)
			return true;
		return false;
	}
	uiProperties u;
	SDL_Rect thisSize = { 0,0,0,0 };
	game_Text title;
	bool titleDebounce = false; // irelevant
	bool moved = false;
	bool titleBarInit = false;
	int titleBarSizeY = 5;
	SDL_Rect titleBarPosition;
};

class uiButton
{
public:
	uiButton();

private:
	SDL_Rect size = { 0,0,0,0 };
	SDL_Rect position = { 0,0,0,0 };
	uiFrame assignedFrame;

};