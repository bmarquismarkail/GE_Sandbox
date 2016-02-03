#ifndef SDL_SFFWRAPPER_H
#define SDL_SFFWRAPPER_H

#include <fstream>

#include <SDL2/SDL.h>

#include "SFF2File.h"
#include "types/enums.h"

class SDL_SFFWrapper : public SFF2File
{
public:
    /** Default constructor */
    SDL_SFFWrapper(SDL_Renderer* Renderer);
    SDL_SFFWrapper(const char *Filename);
    SDL_SFFWrapper(std::ifstream *in, SDL_Renderer* Renderer);
    SDL_SFFWrapper(SDL_RWops *in, SDL_Renderer* Renderer);
    /** Default destructor */
    ~SDL_SFFWrapper();
    void setPosX(int value);
    void setPosY(int value);
    void setWidth(int value);
    void setHeight(int value);
    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();
    void Render(unsigned long SprNo, unsigned long PalNo, SDL_Renderer* Renderer);
protected:
private:
    SDL_Rect ClipRect;
    SDL_Texture *RenderTex;
};

#endif // SDL_SFFWRAPPER_H
