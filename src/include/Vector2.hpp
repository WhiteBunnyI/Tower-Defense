#pragma once

#include <cmath>

struct Vector2
{
	float x;
	float y;

	Vector2() = default;

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2& operator-(const Vector2& other)
	{
		Vector2 temp(*this);
		temp -= other;
		return temp;
	}

	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& operator/(float num)
	{
		Vector2 temp(*this);
		temp /= num;
		return temp;
	}

	Vector2& operator/=(float num)
	{
		x /= num;
		y /= num;
		return *this;
	}

	Vector2& Normalize()
	{
		float len = std::sqrt(x * x + y * y);
		x /= len;
		y /= len;
		return *this;
	}

	static float Dot(Vector2 a, Vector2 b)
	{
		return a.x * b.x + a.y * b.y;
	}
};