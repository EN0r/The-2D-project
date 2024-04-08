#include "interface.h"
#include <iostream>

bool game_Text::init(SDL_Renderer* renderer, const char* text, unsigned int size, int x,int y, SDL_Color color, const char* path)
{
    this->defaultColor = color;
    this->defaultPath = path;
    this->font = TTF_OpenFont(path, size);
    this->surface = TTF_RenderText_Solid(font, text, defaultColor);
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->size = { (int)x,(int)y,surface->w,surface->h };
    if (texture == NULL)
        return false;

    return true;
}

void game_Text::renderText(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, this->texture, NULL, &this->size, NULL, NULL, SDL_FLIP_NONE);
}

void game_Text::changeText(SDL_Renderer* renderer, const char* text)
{
    // i dont like this. Massive circle of functions...
    // also copying memory every frame. This is not fun.
    this->surface = TTF_RenderText_Solid(font, text, defaultColor);
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopyEx(renderer, this->texture, NULL, &this->size, NULL, NULL, SDL_FLIP_NONE);
    SDL_FreeSurface(this->surface);
    SDL_DestroyTexture(this->texture);
}
/*
bool uiCore::AABB(int mouseX,int mouseY)
{
    if (mouseX < thisSize.x + thisSize.w &&
        mouseX + mouseClickboxSize > thisSize.x &&
        mouseY < thisSize.y + thisSize.h &&
        mouseY + mouseClickboxSize > thisSize.y
        )
        return true;
    return false;
}
*/

void uiFrame::renderFrame(SDL_Renderer* renderer,std::shared_ptr<window> window)
{
    if (thisSize.h == 0 && thisSize.w == 0)
        return;
    if (hasTitle == true) // can move has title into either U or parameters for this function to be fair
        //if (!titleDebounce) return;
            //title.init(renderer,titleText,10,);  will be finished once i finish calculations for frameSize and title bar size
    //titleBar Calculations
    {
        if (!titleBarInit) // make sure that sdl rect doesnt get copied and using up vital RAM
        {
            titleBarInit = true;
            titleBarPosition = { thisSize.x,thisSize.y - titleBarSizeY,thisSize.w,titleBarSizeY};
        }
    }

    SDL_SetRenderDrawColor(renderer, u.r, u.g, u.b, u.a);
    SDL_RenderFillRect(renderer,&thisSize);
    if (titleBarPosition.w != 0 && titleBarPosition.h != 0)
    {
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer, &titleBarPosition);
        int x, y;
        (void)window->getMousePosition(x, y);
        bool onclicked = false;
        if (SDL_BUTTON(window->getMouseState()) == SDL_BUTTON_LEFT)
        {
            onclicked = true;
        }
        if (AABB(titleBarPosition, { x,y,titleBarSizeY,titleBarSizeY }) && onclicked == true)
        {
            titleBarPosition.x = x;
            titleBarPosition.y = y;
            thisSize.x = x;
            thisSize.y = y;
        }
    }
    /*
    TODO:
    Add text to frame
    Change textBar when hovered
    Add minimize and maximise to the frame.
    More ui components at some point
    */



            
}
