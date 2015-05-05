#ifndef TMX_SDLCLASS_H_INCLUDED
#define TMX_SDLCLASS_H_INCLUDED

#include <SDL2/SDL.h>

#include "TMX_Map.h"


class SDL_TMXMap : public TMX_Map
{
public:
    SDL_TMXMap();
    SDL_TMXMap(const char *Filename);
    ~SDL_TMXMap();
    SDL_Surface *getMapSurface();
    void Populate_Map(SDL_Renderer *Render);
    void Render_Map(SDL_Renderer *Render, SDL_Rect *Clip);
private:
    SDL_Surface *MapSurf;
    SDL_Texture *MapTex;
    vector<SDL_Surface*> LayerSurf;
};

#endif // TMX_SDLCLASS_H_INCLUDED
