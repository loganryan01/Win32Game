#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <array>

struct Matrix3x3
{
	std::array<std::array<int, 3>, 3> m;

	// Constructor
	Matrix3x3()
	{
		identity();
	}

	// Set matrix to identity
	void identity()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m[i][j] = (i == j) ? 1 : 0;
			}
		}
	}

	// Matrix multiplication
	friend Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				result.m[i][j] = 0;
				for (int k = 0; k < 3; k++)
				{
					result.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
				}
			}
		}
		return result;
	}

	// Transform a 2D point using the matrix
	std::pair<int, int> transformPoint(int x, int y) const
	{
		int newX = m[0][0] * x + m[0][1] * y + m[0][2] * 1;
		int newY = m[1][0] * x + m[1][1] * y + m[1][2] * 1;
		return { newX, newY };
	}

	// Create a translation matrix
	static Matrix3x3 translate(int tx, int ty)
	{
		Matrix3x3 mat;
		mat.m[0][2] = tx;
		mat.m[1][2] = ty;
		return mat;
	}

	// Create a scaling matrix
	static Matrix3x3 scale(int sx, int sy)
	{
		Matrix3x3 mat;
		mat.m[0][0] = sx;
		mat.m[1][1] = sy;
		return mat;
	}

	// Create a rotation matrix (angle in radians)
	static Matrix3x3 rotate(int angle)
	{
		Matrix3x3 mat;
		int c = static_cast<int>(cos(angle));
		int s = static_cast<int>(sin(angle));
		mat.m[0][0] = c; mat.m[0][1] = -s;
		mat.m[1][0] = s; mat.m[1][1] = c;
		return mat;
	}
};

#endif
