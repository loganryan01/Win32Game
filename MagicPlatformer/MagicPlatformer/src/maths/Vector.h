#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

struct Vector2
{
	int x, y; // The components of a vector

	// Constructor
	Vector2(int x = 0, int y = 0) : x(x), y(y) {}

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
	friend Vector2 operator*(const Vector2& vector, int scalar)
	{
		return Vector2(vector.x * scalar, vector.y * scalar);
	}

	// Scalar division
	friend Vector2 operator/(const Vector2& vector, int scalar)
	{
		return Vector2(vector.x / scalar, vector.y / scalar);
	}

	// Magnitude (Length of the vector)
	int magnitude() const
	{
		return static_cast<int>(std::sqrt(x * x + y * y));
	}

	// Normalize the vector (make its length 1)
	Vector2 normalized() const
	{
		int mag = magnitude();
		return (mag > 0) ? *this / mag : Vector2(0, 0);
	}

	// Dot product (measures similarity between two vectors)
	int dot(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}
};

#endif