#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"
#include "Entity.hpp"

class Rigidbody : public Entity
{
public:
	Rigidbody(Vector2f p_pos, SDL_Texture* p_texture, float mass);
	~Rigidbody();

	void update(float p_dt);
	void updatePhysics(float p_dt);

	void setVelocity(float p_x, float p_y);
	Vector2f& getVelocity() { return velocity; }
	Vector2f& getMomentum() { return momentum; }

private:
	Vector2f velocity;
	Vector2f momentum;
	float mass;

	float angle;
	Vector2f angularVelocity;
	// MomentOfInertia
};