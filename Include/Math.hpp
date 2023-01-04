#pragma once

struct Vector2f
{
	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	: x(p_x), y(p_y)
	{}

	void print()
	{
		printf("x: %f, y: %f\n", x, y);
	}

	float x, y;
};