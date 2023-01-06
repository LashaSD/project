#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "RigidBody.hpp"
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

	Rigidbody rb(Vector2f(0, 96), grassTexture, 5.0f);
	rb.setVelocity(1.0f, 1.0f);

	std::vector<Rigidbody> entities = { rb };

	window.addToScene(entities);

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

		for (auto& entity : window.getScene())
		{
			Vector2f oldVelocity = entity.getVelocity();
			if (entity.getPos().x >= 1248 || entity.getPos().x <= 0)
			{
				// Collision with the Wall on the X-Axis
				entity.setVelocity(-(oldVelocity.x), oldVelocity.y);
				
			}
			if (entity.getPos().y >= 688 || entity.getPos().y <= 0)
			{
				// Collision with the Roof on the Y-Axis
				entity.setVelocity(oldVelocity.x, -(oldVelocity.y));
			}
			float dt = utils::hireTimeInSeconds() - start;
			entity.updatePhysics(dt);
		}

		// Render Loop
		window.renderScene();
		window.display();

		float elapsedMs = utils::hireTimeInSeconds() - start;

		if (elapsedMs < 0.1666)
			SDL_Delay(16 - elapsedMs);

		// printf("FPS: %f\n", (float)frames / ((SDL_GetTicks() - beginTicks) / 1000));
	}
	window.cleanUp();
	SDL_Quit();
	return 0; 
}
