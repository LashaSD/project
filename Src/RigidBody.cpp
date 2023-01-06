#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"
#include "Entity.hpp"
#include "RigidBody.hpp"

Rigidbody::Rigidbody(Vector2f p_pos, SDL_Texture* p_texture, float p_mass)
: Entity(p_pos, p_texture), mass(p_mass)
{ }

Rigidbody::~Rigidbody()
{ }

void Rigidbody::update(float p_dt)
{
	// figure out
}

void Rigidbody::updatePhysics(float p_dt)
{
	// Linear Motion
	if (velocity.x != 0 && velocity.y != 0)
	{
		float val = (p_dt * velocity.x) + (p_dt * velocity.y);
		momentum.x += val;
		momentum.y += val;
		pos.x += momentum.x;
		pos.y += momentum.y;
	}
	
	// Angular Velocity
	if (angularVelocity.x != 0 && angularVelocity.y != 0)
	{
		float val1 = (p_dt * angularVelocity.x) + (p_dt * angularVelocity.y);
		angle += val1;
	}	
}

void Rigidbody::setVelocity(float p_x, float p_y)
{
	velocity.x = p_x;
	velocity.y = p_y;
	momentum.x = mass * velocity.x;
	momentum.y = mass * velocity.y;
}
