#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
	Entity(int p_id, Vector2f p_pos, SDL_Texture* p_texture);

	int getId() { return id; }

	Vector2f& getPos() { return pos; }

	SDL_Texture* getTexture() { return texture; }

	SDL_Rect getCurrentFrame() { return currentFrame; }
protected:
	int id;
	Vector2f pos;
	float rotation;
	SDL_Rect currentFrame;
	SDL_Texture* texture;
}; 