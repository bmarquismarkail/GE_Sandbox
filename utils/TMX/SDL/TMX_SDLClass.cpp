#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <stdlib.h> // For the exit function
#include "TMX_SDLClass.h"
#include "../TMX_Utils.h"

#include <SDL2/SDL_image.h>


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
	amask = 0x000000ff;
#else
    #define	rmask 0x000000ff
    #define	gmask 0x0000ff00
    #define	bmask 0x00ff0000
    #define	amask 0xff000000
#endif

SDL_TMXMap::SDL_TMXMap()
    : TMX_Map()
{
    MapSurf = NULL;
}

SDL_TMXMap::SDL_TMXMap(const char *Filename)
    :TMX_Map(Filename)
{
    MapSurf = SDL_CreateRGBSurface(0, getWidth()*getTileWidth(), getHeight()*getTileHeight(), 32, rmask, gmask, bmask, amask);
}

SDL_TMXMap::~SDL_TMXMap()
{
    SDL_DestroyTexture(MapTex);
    for(vector<SDL_Surface*>::iterator it = LayerSurf.begin(); it != LayerSurf.end(); ++it )
        SDL_FreeSurface(*it);
}

SDL_Surface* SDL_TMXMap::getMapSurface()
{
    return MapSurf;
}

void SDL_TMXMap::Populate_Map(SDL_Renderer *Render)
{
    if( MapSurf || getMapFile().length())
    {
        if (!MapSurf)
        {
            std::ifstream *in_xml = new ifstream(getMapFile().c_str(), ifstream::in);
            if(!in_xml->is_open())
            {
                std::cout << "No way to Populate Map. Quitting..." <<endl;
                return;
            }
            std::stringstream *ss_xml = new std::stringstream;
            *ss_xml << in_xml->rdbuf();
            char *xml_data = new char[ss_xml->str().length()+1]();
            strcpy(xml_data, ss_xml->str().c_str());
            in_xml->close();
            delete ss_xml;
            Load_Map(xml_data);
            MapSurf = SDL_CreateRGBSurface(0, getWidth()*getTileWidth(), getHeight()*getTileHeight(), 32, rmask, gmask, bmask, amask);
        }

        string ResDir = "Resources\\";
        SDL_Surface **TileSurf = new SDL_Surface*[getNumTilesets()];
        for ( unsigned int fn = 0; fn < getNumTilesets(); fn++)
        {
            //eventually, there will be a means to load multiple images per tileset. TODO: Make a loop that allows it.
            //TODO: Write it so that it also works with
            string Filenname = ResDir + getTileset(fn).getImage(0).getFilename();
            TileSurf[fn] = IMG_Load(Filenname.c_str());
            if (!TileSurf[fn]) return;
        }

        unsigned long color = getTileset(0).getImage(0).getTrans();
        SDL_Color CKey;
        CKey.r = (color & 0xFF0000)   >> 16;
        CKey.g = (color & 0x00FF00)   >> 8 ;
        CKey.b = (color & 0x0000FF)        ;
        SDL_SetColorKey( MapSurf , SDL_TRUE , SDL_MapRGB(TileSurf[0]->format , CKey.r , CKey.g , CKey.b));
        SDL_Rect SrcRect;
        SDL_Rect DstRect;
        DstRect.h = getTileHeight();
        DstRect.w = getTileWidth();
        unsigned char **in_data  = new unsigned char* [getNumLayers()];
        unsigned char **out_data = new unsigned char* [getNumLayers()];
        unsigned long **tiledata = new unsigned long* [getNumLayers()];
        for(unsigned i = 0; i < getNumLayers(); i++)
        {
            in_data[i]  = new unsigned char [getLayer(i).getData().getData().size()];
            out_data[i] = new unsigned char [getWidth()*getHeight()*4];
            memcpy( in_data[i] , getLayer(i).getData().getData().c_str() , getLayer(i).getData().getData().size() );
            unsigned char *dec_data = new unsigned char[( getLayer(i).getData().getData().size()* 3/4 )];
            TMX_Decode( in_data[i] , dec_data , getLayer(i).getData().getData().size() );
            TMX_Uncompress( dec_data , out_data[i] , ( getLayer(i).getData().getData().size() * 3/4 ), getWidth() * getHeight() * 4, getLayer(i).getData().getCompression().c_str());
            tiledata[i] = (unsigned long*) out_data[i];
			// TODO: For loop to determine if code is working correctly.
        }

        delete[]in_data;

        for (unsigned l = 0; l < TMX_Map::getNumLayers(); l++)
        {
            if(!getLayer(l).isVisible())
                continue;

            LayerSurf.push_back(SDL_CreateRGBSurface(0, getWidth()*getTileWidth(), getHeight()*getTileHeight(), 32, rmask, gmask, bmask, amask));
            SDL_SetSurfaceAlphaMod(LayerSurf[l], getLayer(l).getOpacity() * 255);
            for(unsigned int y = 0; y < getHeight(); y++)
            {
                DstRect.y = y * getTileHeight();
                for (unsigned int x = 0; x  < getWidth(); x++)
                {
                    if(tiledata[l][y*getWidth()+x])
                    {
                        DstRect.x = x * getTileWidth();
                        unsigned tilesetindex = findTileset(tiledata[l][y*getWidth()+x]);
                        unsigned srcindex = tiledata[l][y*getWidth()+x] - getTileset(tilesetindex).getGID();
                        SrcRect.h = getTileset(tilesetindex).getTileHeight();
                        SrcRect.w = getTileset(tilesetindex).getTileWidth();
                        float Float_TPL = (float) getTileset(tilesetindex).getImage(0).getWidth() / (getTileset(tilesetindex).getTileWidth() + getTileset(tilesetindex).getSpacing());
                        unsigned long Tiles_Per_Line = (long) ceil(Float_TPL);
                        SrcRect.x = srcindex % Tiles_Per_Line * (getTileset(tilesetindex).getTileWidth() + getTileset(tilesetindex).getSpacing());
                        SrcRect.y = srcindex / Tiles_Per_Line * (getTileset(tilesetindex).getTileWidth() + getTileset(tilesetindex).getSpacing());
                        if( SDL_BlitSurface(TileSurf[tilesetindex], &SrcRect, LayerSurf[l], &DstRect) )
						{
							cout << "SDL_BlitSurface Failed: " << SDL_GetError() << endl; // if for some reason the application does not implode and instead run this code, we need to know why it crapped us.
							exit (-2);
						}
                    }
                }
            }
            SDL_BlitSurface(LayerSurf[l],NULL, MapSurf, NULL);
        }

        delete[] out_data;
        delete[] tiledata;
        for (unsigned l = 0; l < getNumTilesets(); l++)
            SDL_FreeSurface(TileSurf[l]);

        MapTex = SDL_CreateTextureFromSurface(Render, MapSurf);
        SDL_FreeSurface(MapSurf);
    }
    else std::cout << "No way to Populate Map. Quitting..." << endl;
}

void  SDL_TMXMap::Render_Map(SDL_Renderer *Render, SDL_Rect *Clip)
{
    SDL_RenderCopy(Render, MapTex, Clip, NULL);
}
