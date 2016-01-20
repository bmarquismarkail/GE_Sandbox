#include "SFF2_SDLClass.h"

SFF2_SDLClass::SFF2_SDLClass()
{
    SFF2Surf = NULL;
}

SFF2_SDLClass::SFF2_SDLClass(std::ifstream *in)
{
    SFF2Surf = NULL;
}

SFF2_SDLClass::~SFF2_SDLClass()
{
    SDL_DestroyTexture(SFF2Tex);
    for(vector<SDL_Surface*>::iterator it = SpriteSurf.begin(); it != SpriteSurf.end(); ++it)
        SDL_FreeSurface(*it);
}

void SFF2_SDLClass::Populate_SpriteSheet(SDL_Renderer* Render)
{
    //load all the sprites in SpriteSurf.

}

void SFF2_SDLClass::Render_Sprite(SDL_Renderer* Render, SDL_Rect* Clip)
{

}
