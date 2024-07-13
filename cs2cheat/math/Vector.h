#pragma once
#include <cmath>
#include <numbers>
#include <array>


struct ViewMatrix
{

	float* operator[](int index) noexcept
	{
		return matrix[index];
	}

	float matrix[4][4];
};

class Vector
{

public:
	float x, y, z;


public:
	Vector(float x, float y, float z) noexcept
		:x(x), y(y), z(z) { }


	Vector() noexcept
		:x(0), y(0), z(0) { }

	const Vector& operator+(const Vector& vec) const;
	

	const Vector& operator-(const Vector& vec) const;
	

	const Vector& operator*(const float factor) const;
	

	const Vector& operator/(const float factor) const;
	
	float distance(const Vector& vec) const;

	const Vector& RelativeAngle() const;
	
};


class Vector2
{
	public:
	float x, y;

	Vector2(float x, float y) noexcept
		:x(x), y(y) { }

	Vector2() noexcept
		:x(0), y(0) { }

	static const Vector2& WorldToScreen(ViewMatrix& viewMatrix, const Vector& pos, int width, int height);

	float distance(const Vector2& vec) const;
};



class Vector4
{
	public:
	float x, y, z, w;

	Vector4(float x, float y, float z, float w) noexcept
		:x(x), y(y), z(z), w(w) { }

	Vector4() noexcept
		:x(0), y(0), z(0), w(0) { }

};