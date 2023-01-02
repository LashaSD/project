#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_texture);

	Vector2f& getPos();

	Vector2f& getAcceleration();
	void accelerate(float p_x, float p_y);

	SDL_Texture* getTexture();

	SDL_Rect getCurrentFrame();
private:
	Vector2f pos;
	Vector2f acceleration;
	SDL_Rect currentFrame;
	SDL_Texture* texture;
}; 