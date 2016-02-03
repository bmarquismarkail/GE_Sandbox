#include "SDL_SFFWrapper.h"
#include <stdio.h>



SDL_SFFWrapper::SDL_SFFWrapper(SDL_Renderer* Renderer) : SFF2File()
{
    RenderTex = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,0,0);
    ClipRect.x = 0;
    ClipRect.y = 0;
}

SDL_SFFWrapper::SDL_SFFWrapper(const char *Filename) : SFF2File(Filename)
{
    RenderTex = NULL;
    ClipRect.x = 0;
    ClipRect.y = 0;
}

SDL_SFFWrapper::SDL_SFFWrapper(std::ifstream *in, SDL_Renderer* Renderer) : SFF2File(in)
{
    RenderTex = NULL;
    ClipRect.x = 0;
    ClipRect.y = 0;
}

SDL_SFFWrapper::SDL_SFFWrapper(SDL_RWops *in, SDL_Renderer* Renderer)
{
    //RenderTex = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ARGB8888);
    //ClipRect.x = 0;
    //ClipRect.y = 0;
}

SDL_SFFWrapper::~SDL_SFFWrapper()
{
    //dtor
}

void SDL_SFFWrapper::setPosX(int value) { ClipRect.x = value;}
void SDL_SFFWrapper::setPosY(int value) {ClipRect.y = value;}
void SDL_SFFWrapper::setWidth(int value) {ClipRect.w = value;}
void SDL_SFFWrapper::setHeight(int value) {ClipRect.h = value;}
int SDL_SFFWrapper::getPosX(){return ClipRect.x;}
int SDL_SFFWrapper::getPosY(){return ClipRect.y;}
int SDL_SFFWrapper::getWidth(){return ClipRect.w;}
int SDL_SFFWrapper::getHeight(){return ClipRect.h;}

void SDL_SFFWrapper::Render(unsigned long SprNo, unsigned long PalNo, SDL_Renderer* Renderer)
{
    if (RenderTex)
        SDL_DestroyTexture(RenderTex);
    //Populate the First Sprite
   if (GetSprData(SprNo)->GetLength() != (SFF32_u)(GetSpriteNode(SprNo)->GetWidth() * GetSpriteNode(SprNo)->GetHeight()))
        GetSprData(SprNo)->TranslateData(GetSprData(SprNo)->GetLength(), (GetSpriteNode(SprNo)->GetWidth() * GetSpriteNode(SprNo)->GetHeight()), GetSpriteNode(SprNo)->GetFmt());
    SDL_Surface *temp = SDL_CreateRGBSurfaceFrom((void*)GetSprData(SprNo)->GetData(),
                                                 GetSpriteNode(SprNo)->GetWidth(),
                                                 GetSpriteNode(SprNo)->GetHeight(),
                                                 (GetSpriteNode(SprNo)->GetColdepth() == 5 ? 8 : GetSpriteNode(SprNo)->GetColdepth()),
                                                 GetSpriteNode(SprNo)->GetWidth(),
                                                 0,0,0,0);

    if (!temp)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return;
    }
    //Populate the rectangles
    //ClipRect.w = GetSpriteNode(SprNo)->GetWidth();
    //ClipRect.h = GetSpriteNode(SprNo)->GetHeight();
    //Populate the Palette
    SDL_Palette *Palette = SDL_AllocPalette(GetPalNode(PalNo)->GetNumCols());
    for (int c = 0; c < GetPalNode(PalNo)->GetNumCols(); c++)
    {
        Palette->colors[c].r = GetPalData(PalNo)->GetData()[c*4];
        Palette->colors[c].g = GetPalData(PalNo)->GetData()[c*4+1];
        Palette->colors[c].b = GetPalData(PalNo)->GetData()[c*4+2];
        //Palette->colors[c].a = GetPalData(PalNo)->GetData()[c*4+3]; //Adding an Alpha value makes SDL use Alpha Blending!!!
    }
    SDL_SetPaletteColors(temp->format->palette,Palette->colors,0,GetPalNode(PalNo)->GetNumCols());
    SDL_SetColorKey(temp,SDL_TRUE,SDL_MapRGB(temp->format,Palette->colors[0].r , Palette->colors[0].g , Palette->colors[0].b ));
    RenderTex = SDL_CreateTextureFromSurface(Renderer,temp);
    SDL_FreeSurface(temp);
    SDL_FreePalette(Palette);
    SDL_RenderCopy(Renderer,RenderTex,NULL,&ClipRect);

}

