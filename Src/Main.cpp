#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("Couldn't Initialize SDL, SDL_ERROR: %s\n", SDL_GetError());

	if (!(IMG_Init(IMG_INIT_PNG)))
		printf("Couldn't initialize SDL_Image, SDL_ERROR %s\n", IMG_GetError());
	
	RenderWindow window("Program V1.0.0", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("Res/gfx/ground_grass.png");

	Entity platform0(100, 100, grassTexture);

	bool appRunning = true;
	SDL_Event e;

	while (appRunning)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				appRunning = false;
		}
		window.clear();
		window.render(platform0);
		window.display();
	}
	window.cleanUp();
	SDL_Quit();
	return 0; 
}
