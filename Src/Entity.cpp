#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"
#include "Math.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_texture)
:pos(p_pos), texture(p_texture), acceleration(Vector2f(4.0f, 4.0f))
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32; 
};

Vector2f& Entity::getPos()
{
	return pos;
}

Vector2f& Entity::getAcceleration()
{
	return acceleration;
}

void Entity::accelerate(float p_x, float p_y)
{
	acceleration.x += p_x;
	acceleration.y += p_y;
}

SDL_Texture* Entity::getTexture()
{
	return texture;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}


