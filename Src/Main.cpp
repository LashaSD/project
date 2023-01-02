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

	while (appRunning)
	{

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

		for (Entity& entity : window.getQueue())
		{
			entity.getPos().x += entity.getAcceleration().x;
			entity.getPos().y += entity.getAcceleration().y;
			if (entity.getPos().x >= 1248 || entity.getPos().x <= 0)
			{
				// Collision with the Wall on the X-Axis
				entity.accelerate(((entity.getAcceleration().x)*-2), 0);
				entity.getAcceleration().x -= 1.0f;
			}
			if (entity.getPos().y >= 688 || entity.getPos().y <= 0)
			{
				// Collision with the Wall on the Y-Axis
				entity.accelerate(0, ((entity.getAcceleration().y)*-2));
				entity.getAcceleration().y += 1.0f;
			}
		}

		// Render Loop
		window.renderQueue();
		window.display();
	}
	window.cleanUp();
	SDL_Quit();
	return 0; 
}
