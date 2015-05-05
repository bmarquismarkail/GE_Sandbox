#ifndef TILED_EDITOR_H_INCLUDED
#define TILED_EDITOR_H_INCLUDED

#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TMX_Map.h"
//loads the file and returns a string. If the file is not present, returns NULL
SDL_Texture* Load_Tmx(TMX_Map *Map, const char *fn, SDL_Renderer *Render);


#endif // TILED_EDITOR_H_INCLUDED
