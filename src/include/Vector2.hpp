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

	Vector2& operator+(const Vector2& other)
	{
		Vector2 temp(*this);
		temp += other;
		return temp;
	}

	Vector2& operator+=(const Vector2& other)
	{
		x += other.y;
		y += other.y;
		return *this;
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

	Vector2& operator*(float num)
	{
		Vector2 temp(*this);
		temp *= num;
		return temp;
	}

	Vector2& operator*=(float num)
	{
		x *= num;
		y *= num;
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

struct Vector2I
{
	int x;
	int y;

	Vector2I() = default;

	Vector2I(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2I& operator-(const Vector2I& other)
	{
		Vector2I temp(*this);
		temp -= other;
		return temp;
	}

	Vector2I& operator-=(const Vector2I& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2I& operator/(int num)
	{
		Vector2I temp(*this);
		temp /= num;
		return temp;
	}

	Vector2I& operator/=(int num)
	{
		x /= num;
		y /= num;
		return *this;
	}

	Vector2I& Normalize()
	{
		float len = std::sqrt(x * x + y * y);
		x /= len;
		y /= len;
		return *this;
	}

	static float Dot(Vector2I a, Vector2I b)
	{
		return a.x * b.x + a.y * b.y;
	}
};