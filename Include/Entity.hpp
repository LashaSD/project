#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_texture);

	Vector2f& getPos() { return pos; }

	SDL_Texture* getTexture() { return texture; }

	SDL_Rect getCurrentFrame() { return currentFrame; }
protected:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* texture;
}; 