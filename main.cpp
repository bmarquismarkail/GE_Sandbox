#include <iostream>
#if defined(_MSC_VER)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <SDL2/SDL_mixer.h>
#include "utils/TMX/SDL/TMX_SDLClass.h"
#include "../SFF2ViewerRedux/src/SDL_SFFWrapper.h"



int main(int argc, char** argv){
	//First we need to start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Now create a window with title "Hello World" at 100, 100 on the screen with w:640 h:480 and show it
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
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
	Mix_Music *altSamba = Mix_LoadMUS("Resources\\music\\alternativesamba.mod");
	if (!altSamba)
	{
		cout << "alternativesamba.mod is not loaded. Exiting..." << Mix_GetError() << endl;
		return 1987;
	}
	Mix_PlayMusic(altSamba,-1);

	bool isRunning = true;
	SDL_Event gameLoop;

	SDL_Rect cameraRect;
	cameraRect.x = 0;
	cameraRect.y = 0;
	cameraRect.w = 800;
	cameraRect.h = 600;
	int xVel = 0;
	int yVel = 0;
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL){
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_TMXMap Map("Resources\\Test.tmx");
	Map.Populate_Map(ren);

	SDL_SFFWrapper Sprite ("Resources\\kakurinetest.sff");
	while (isRunning)
	{
		while (SDL_PollEvent(&gameLoop))
		{
			if (gameLoop.type == SDL_QUIT)
				isRunning = false;
			if ( gameLoop.key.state == SDL_PRESSED )
				switch (gameLoop.key.keysym.sym){
			case  SDLK_UP:
				yVel = -16;
				break;
			case SDLK_DOWN:
				yVel = 16;
				break;
			case SDLK_LEFT:
				xVel = -16;
				break;
			case SDLK_RIGHT:
				xVel = 16;
				break;
				}
		}
		cameraRect.x +=xVel;
		if (cameraRect.x < 0) cameraRect.x = 0;
		else if (cameraRect.x > (Map.getWidth() * Map.getTileWidth()) - cameraRect.w)
				cameraRect.x = (Map.getWidth() * Map.getTileWidth()) - cameraRect.w;
		cameraRect.y +=yVel;
		if (cameraRect.y < 0) cameraRect.y = 0;
		else if (cameraRect.y >= (Map.getHeight() * Map.getTileHeight()) - cameraRect.h)
			cameraRect.y = (Map.getHeight() * Map.getTileHeight()) - cameraRect.h;
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
