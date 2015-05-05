#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;

#include <rapidxml.hpp>
using namespace rapidxml;


#include "Tiled_Editor.h"
#include "TMX_Utils.h"

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_ConvertSurfaceFormat( loadedImage , SDL_PIXELFORMAT_RGBA8888, 0);

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_TRUE, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}


