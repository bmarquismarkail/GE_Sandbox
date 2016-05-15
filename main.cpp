#include <iostream>
#if defined(_MSC_VER)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <SDL2/SDL_mixer.h>
#include "utils/TMX/SDL/TMX_SDLClass.h"
#include "utils/SFF2/SDL/SDL_SFFWrapper.h"



int main(int argc, char** argv){
	//First we need to start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
    //Lets make global variables for the width and length of the application
    int winwidth = 1024;
    int winheight = 768;
	//Now create a window with title "Hello World" at 100, 100 on the screen with w:640 h:480 and show it
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, winwidth, winheight, SDL_WINDOW_SHOWN);
	//Make sure creating our window went ok
	if (win == NULL){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() <<   std::endl;
		return 1;
	}

	int mixRet = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096);
	if (mixRet != 0)
		return mixRet;
	mixRet = Mix_Init(MIX_INIT_MODPLUG);
	if (mixRet != MIX_INIT_MODPLUG)
	{
		cout << "SDLmixer Initiazation Error: " << Mix_GetError() << endl;
		return mixRet;
	}
	SDL_TMXMap Map("Resources/LTTP.tmx");
	Mix_Music *altSamba = Mix_LoadMUS(Map.getProperties(0).getProperty((unsigned) 0 ).getValue().c_str());
	if (!altSamba)
	{
		cout << "alternativesamba.mod is not loaded. Exiting..." << Mix_GetError() << endl;
		return 1;
	}
	Mix_PlayMusic(altSamba,-1);

	bool isRunning = true;
	SDL_Event gameLoop;

	SDL_Rect cameraRect;
	cameraRect.w = 256;
	cameraRect.h = 224;
	cameraRect.x = (140 * Map.getTileWidth()) - ( cameraRect.w / 2) ;
	cameraRect.y = (177 * Map.getTileHeight()) - ( cameraRect.h / 2 );
	int xVel = 0;
	int yVel = 0;
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL){
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	Map.Populate_Map(ren);
	SDL_SFFWrapper Sprite ("Resources/kakurinetest.sff");

	const float fGameRatioX = (float) winwidth / (float) cameraRect.w;
	const float fGameRatioY =  (float) winheight / (float) cameraRect.h;
	const unsigned int  iGameRatioX = (unsigned) fGameRatioX;
	const unsigned int  iGameRatioY = (unsigned) fGameRatioY;

	const int tAxisX = 8;
	const int tAxisY = 20;
	const int AxisX = tAxisX * iGameRatioX ; // a manual axis, located on the sprite's feet.
	const int AxisY = tAxisY * iGameRatioY ; //TODO: Make the Akis dynamic according to a file (Most likely a Binary Air File)
	// Note To Self: that means either put assignment in the loop or add a function in the loop that assigns.

    float fPosX = ( ( (float)cameraRect.w / 2)  * fGameRatioX );
	float fPosY = ( ( (float)cameraRect.h / 2)  * fGameRatioY );
	Sprite.setPosX( fPosX - AxisX );   //Sprite's position relative to the screen
    Sprite.setPosY( fPosY - AxisY ); //Sprite's position relative to the screen
	Sprite.setWidth( Sprite.GetSpriteNode(0)->GetWidth() * iGameRatioX );
	Sprite.setHeight( Sprite.GetSpriteNode(0)->GetHeight() * iGameRatioY );



	while (isRunning)
	{
	    int fTruePosX = ( (float)cameraRect.x  + ( ( (float)Sprite.getPosX() + (float)AxisX ) / fGameRatioX ) );
	    int fTruePosY = ( (float)cameraRect.y  + ( ( (float)Sprite.getPosY() + (float)AxisY ) / fGameRatioY ) );
//	    int iTruePosX = (int)fTruePosX; //Sprite's position relative to the map in pixels
//      int iTruePosY = (int)fTruePosY; //Sprite's position relative to the map in pixels
//      int iTilePosX = iTruePosX / Map.getTileWidth();
//      int iTilePosY = iTruePosY / Map.getTileHeight();

		while (SDL_PollEvent(&gameLoop))
		{
			if (gameLoop.type == SDL_QUIT)
				isRunning = false;
			if ( gameLoop.key.state == SDL_PRESSED )
				switch (gameLoop.key.keysym.sym){
                    case  SDLK_UP: yVel = -4;
                    break;
                    case SDLK_DOWN:	yVel = 4;
                    break;
                    case SDLK_LEFT: xVel = -6;
                    break;
                    case SDLK_RIGHT:xVel = 6;
                    break;
				}
            if ( gameLoop.key.state == SDL_RELEASED )
				switch (gameLoop.key.keysym.sym){
                    case  SDLK_UP:
                    case SDLK_DOWN:	yVel = 0;
                    break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT: xVel = 0;
                    break;
				}
		}
        bool isBoundCameraX = Sprite.getPosX() + xVel >= 0 && Sprite.getPosX() + xVel <= winwidth - Sprite.getWidth();
        bool isBoundCameraY = Sprite.getPosY() + yVel >= 0 && Sprite.getPosY() + yVel <= winheight - Sprite.getHeight();
        bool isBoundMapX = cameraRect.x + xVel >= 0 && ((unsigned)cameraRect.x + xVel <= ( ( Map.getWidth() * Map.getTileWidth() ) - (unsigned) cameraRect.w ) );
        bool isBoundMapY = cameraRect.y + yVel >= 0 && ((unsigned)cameraRect.y + yVel <= ( ( Map.getHeight() * Map.getTileHeight() ) - (unsigned) cameraRect.h ) );
        //TODO: Make variables that indicate the sprite's position to the edge of the screen
        if (xVel)
        {
            if( isBoundCameraX )
                Sprite.setPosX(Sprite.getPosX() + xVel);
            else if( isBoundMapX )
                cameraRect.x += xVel;
        }
        if (yVel)
        {
            if( isBoundCameraY )
                Sprite.setPosY(Sprite.getPosY() + yVel);
            else if( isBoundMapY )
                cameraRect.y += yVel;
        }




		SDL_SetRenderDrawColor(ren,255,0,255,SDL_ALPHA_OPAQUE);
		SDL_RenderClear(ren);
		Map.Render_Map(ren , &cameraRect);
		Sprite.Render(0,0,ren);
		SDL_RenderPresent(ren);
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();

	return 0;
}
