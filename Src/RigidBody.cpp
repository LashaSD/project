#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"
#include "Entity.hpp"
#include "RigidBody.hpp"

Rigidbody::Rigidbody(int p_id, Vector2f p_pos, SDL_Texture* p_texture, float p_mass)
: Entity(p_id, p_pos, p_texture), mass(p_mass)
{
	
}

Rigidbody::~Rigidbody()
{ }

void Rigidbody::update(float p_dt)
{
	pos.x += velocity.x * p_dt;
	pos.y += velocity.y * p_dt;
	rotation += angularVelocity * p_dt;
}

void Rigidbody::setVelocity(float p_x, float p_y)
{
	velocity.x = p_x;
	velocity.y = p_y;
}

void Rigidbody::calculateValues()
{
	centerOfMass.x = pos.x + 16;
	centerOfMass.y = pos.y + 16;
}
