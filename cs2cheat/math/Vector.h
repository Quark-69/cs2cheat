#pragma once
#include <cmath>
#include <numbers>

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


