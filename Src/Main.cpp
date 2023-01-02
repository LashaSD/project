#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
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

	std::vector<Entity> entities = {Entity(Vector2f(0, 96),grassTexture),
									Entity(Vector2f(32, 96),grassTexture),
									Entity(Vector2f(64, 96),grassTexture),
									Entity(Vector2f(96, 96),grassTexture),
									Entity(Vector2f(128, 96),grassTexture),};
	window.addToQueue(entities);

	bool appRunning = true;
	SDL_Event e;

	float totalFrameTicks = 0;
	float totalFrames = 0;

	while (appRunning)
	{

		totalFrames++;
		float startTicks = SDL_GetTicks();
		float startPerf = SDL_GetPerformanceCounter();

		window.clear();

		// Event Loop
		while(SDL_PollEvent(&e) != 0) 
		{
			{
				if (e.type == SDL_QUIT)
					appRunning = false;
			}
		}

		// Render Loop
		window.renderQueue();
		window.display();

		float endTicks = SDL_GetTicks();
		float endPerf = SDL_GetPerformanceCounter();
		float framePerf = endPerf - startPerf;
		float frameTime = (endTicks - startTicks) / 1000.0f;
		totalFrameTicks += endTicks - startTicks;

		printf("FPS: %f, AvgFPS: %f, framePerformance: %f\n", (1.0f / frameTime), (1000.0f / (totalFrameTicks / totalFrames)), framePerf);
	}
	window.cleanUp();
	SDL_Quit();
	return 0; 
}
