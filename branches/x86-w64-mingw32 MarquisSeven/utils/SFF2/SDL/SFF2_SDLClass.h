#ifndef SFF2_SDLCLASS_H
#define SFF2_SDLCLASS_H

#include <vector>
using namespace std;

#include <SDL2/SDL.h>

#include "SFF2File.h"

class SFF2_SDLClass : public SFF2File
{
    public:
        SFF2_SDLClass();
        SFF2_SDLClass(std::ifstream *in);
        ~SFF2_SDLClass();
        void Populate_SpriteSheet(SDL_Renderer *Render);
        void Render_Sprite(SDL_Renderer *Render, SDL_Rect *Clip);
    private:
    SDL_Surface *SFF2Surf;
    SDL_Texture *SFF2Tex;
    vector<SDL_Surface*> SpriteSurf;
};

#endif // SFF2_SDLCLASS_H
