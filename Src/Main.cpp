#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "EntityHandler.hpp"
#include "PositionComponent.hpp"
#include "Math.hpp"
#include "Utils.hpp"


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("Couldn't Initialize SDL, SDL_ERROR: %s\n", SDL_GetError());

	if (!(IMG_Init(IMG_INIT_PNG)))
		printf("Couldn't initialize SDL_Image, SDL_ERROR %s\n", IMG_GetError());
	
	RenderWindow window("Program V1.0.0", 1280, 720);

	printf("FPS: %d\n", window.getRefreshRate());

	SDL_Texture* grassTexture = window.loadTexture("Res/gfx/ground_grass.png");

	EntityHandler handler;

	Entity* entity1 = handler.createEntity();
	handler.addComponent(entity1, PositionComponent()); //todo: make position component on the heap 

	window.addToQueue(entity1);

	bool appRunning = true;
	SDL_Event e;

	float beginTicks = SDL_GetTicks();
	int frames = 0;

	while (appRunning)
	{

		frames++;
		float start = utils::hireTimeInSeconds();

		window.clear();

		// Event Loop
		while(SDL_PollEvent(&e) != 0) 
		{
			{
				if (e.type == SDL_QUIT)
					appRunning = false;
			}
		}

		// Physics Loop

		// Render Loop
		window.renderQueue();
		window.display();

		float elapsedMs = utils::hireTimeInSeconds() - startTicks;

		if (elapsedMs < 0.1666)
			SDL_Delay(16 - elapsedMs);

		printf("FPS: %f\n", (float)frames / ((SDL_GetTicks() - beginTicks) / 1000));
	}
	window.cleanUp();
	SDL_Quit();
	return 0; 
}
