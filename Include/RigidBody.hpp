#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"
#include "Entity.hpp"

class Rigidbody : public Entity
{
public:
	Rigidbody(int p_id, Vector2f p_pos, SDL_Texture* p_texture, float p_mass);
	~Rigidbody();

	void update(float p_dt);

	void setVelocity(float p_x, float p_y);
	Vector2f& getVelocity() { return velocity; }

	Vector2f& getCenterOfMass() { return centerOfMass; }

	float getMass() { return mass; }

	float getMomentOfInertia() { return momentOfInertia; }

	float& getAngularVel() { return angularVelocity; }

	void calculateValues();

private:
	Vector2f velocity;
	Vector2f centerOfMass;
	float mass = 2.0f;
	float momentOfInertia = 87381.3333333;
	float angularVelocity = 0.0f;
};