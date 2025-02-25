#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

struct Vector2
{
	float x, y; // The components of a vector

	// Constructor
	Vector2(float x = 0, float y = 0) : x(x), y(y) {}

	// Addition
	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	// Subtraction
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	// Scalar multiplication
	friend Vector2 operator*(const Vector2& vector, float scalar)
	{
		return Vector2(vector.x * scalar, vector.y * scalar);
	}

	// Scalar division
	friend Vector2 operator/(const Vector2& vector, float scalar)
	{
		return Vector2(vector.x / scalar, vector.y / scalar);
	}

	// Magnitude (Length of the vector)
	float magnitude() const
	{
		return std::sqrt(x * x + y * y);
	}

	// Normalize the vector (make its length 1)
	Vector2 normalized() const
	{
		float mag = magnitude();
		return (mag > 0) ? *this / mag : Vector2(0, 0);
	}

	// Dot product (measures similarity between two vectors)
	float dot(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}
};

#endif