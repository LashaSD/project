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

struct Vector2 
{
	Vector2() 
	:x(0), y(0)
	{ }

	Vector2(int p_x, int p_y) 
	:x(p_x), y(p_y)
	{ }

	void print()
	{
		printf("x: %d, y: %d\n", x, y);
	}

	int x, y;
};