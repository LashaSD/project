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

	SDL_Texture* grassTexture = window.loadTexture("Res/gfx/ground_grass.png");

	Rigidbody rb(1, Vector2f(64, 128), grassTexture, 5.0f);
	Rigidbody rb1(2, Vector2f(128, 128), grassTexture, 5.0f);
	// rb.setVelocity(0, 9.8f);
	// rb1.setVelocity(0, 9.8f);

	std::vector<Rigidbody> entities = { rb, rb1 };

	window.addToScene(entities);

	float windowRefreshRate = window.getRefreshRate();

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
			for (Rigidbody& rb : window.getScene())
			{
				if (entity.getId() != rb.getId())
				{
					Vector2f& rbPos = rb.getPos();
					Vector2f& entPos = entity.getPos();
					bool x_overlap = (rbPos.x + 32 >= entPos.x && rbPos.x <= entPos.x + 32) || (entPos.x + 32 >= rbPos.x && entPos.x <= rbPos.x + 32);
					bool y_overlap = (rbPos.y + 32 >= entPos.y && rbPos.y <= entPos.y + 32) || (entPos.y + 32 >= rbPos.y && entPos.y <= rbPos.y + 32);

					bool colliding = x_overlap && y_overlap;

					if (colliding)
					{
						const float friction = 0.1f;
						const float restitutionCoeff = 0.4f;

						Vector2f collisionNormal = (rbPos - entPos).normalize();
						Vector2f relativeVelocity = rb.getVelocity() - entity.getVelocity();

						float impulse = -(1 / restitutionCoeff) * relativeVelocity.dot(collisionNormal) / (collisionNormal.dot(collisionNormal) * (1.0f / rb.getMass() + 1.0f / entity.getMass()));

						rb.getVelocity() = rb.getVelocity() + (impulse / rb.getMass()) * collisionNormal;
						entity.getVelocity() = entity.getVelocity() - (impulse / entity.getMass()) * collisionNormal;

						float relativeAngularVelocity = rb.getAngularVel() - entity.getAngularVel();
						Vector2f r1 = rbPos - rb.getCenterOfMass();
						Vector2f r2 = entPos - entity.getCenterOfMass();
						float torque = -(1 + restitutionCoeff) * relativeAngularVelocity * (r1.cross(collisionNormal) + r2.cross(collisionNormal)) / (r1.cross(collisionNormal) * r1.cross(collisionNormal) / rb.getMomentOfInertia() + r2.cross(collisionNormal) * r2.cross(collisionNormal) / entity.getMomentOfInertia());
						rb.getAngularVel() = rb.getAngularVel() + torque / rb.getMomentOfInertia();
						entity.getAngularVel() = entity.getAngularVel() - torque / entity.getMomentOfInertia();

						rb.getVelocity() = rb.getVelocity() * (1.0f - friction);
						entity.getVelocity() = entity.getVelocity() * (1.0f - friction);
					}
				}
			}
			float dt = utils::hireTimeInSeconds() - start;
			entity.update(dt);
		}

		// Render Loop
		window.renderScene();
		window.display();

		float elapsed = utils::hireTimeInSeconds() - start;
		if (elapsed < 1 / windowRefreshRate)
			SDL_Delay(1000/75 - (elapsed*1000));

		printf("FPS: %f\n", (float)frames / ((SDL_GetTicks() - beginTicks) / 1000));
	}
	window.cleanUp();
	SDL_Quit();
	return 0; 
}
