#pragma once

#include <cmath>

struct Vector2f
{
	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	: x(p_x), y(p_y)
	{}

	Vector2f operator+(const Vector2f& vec) const 
	{
		return Vector2f(x + vec.x, y + vec.y);
	}

	Vector2f operator-(const Vector2f& vec) const 
	{
		return Vector2f(x - vec.x, y - vec.y);
	}

	Vector2f operator*(const Vector2f& vec) const 
	{
		return Vector2f(x * vec.x, y * vec.y);
	}

	Vector2f operator*(float val) const 
	{
		return Vector2f(x * val, y * val);
	}

	Vector2f operator/(float val) const 
	{
		return Vector2f(x / val, y / val);
	}

	Vector2f normalize() const 
	{
		double length = std::sqrt(x*x + y*y);
		return Vector2f(x / length, y / length);
	}

	float dot(const Vector2f& vec) const 
	{
		return x * vec.x + y * vec.y;
	}

	float cross(const Vector2f& vec) const 
	{
		return x * vec.y - y * vec.x;
	}
	void print() const 
	{
		printf("x: %f, y: %f\n", x, y);
	}

	float x, y;
};


