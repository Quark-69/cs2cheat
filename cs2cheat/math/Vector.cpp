#include "Vector.h"

const Vector& Vector::operator+(const Vector& vec) const
{
	return Vector(x + vec.x, y + vec.y, z + vec.z);
}

const Vector& Vector::operator-(const Vector& vec) const
{
	return Vector(x - vec.x, y - vec.y, z - vec.z);
}

const Vector& Vector::operator*(const float factor) const
{
	return Vector(x * factor, y * factor, z * factor);
}

const Vector& Vector::operator/(const float factor) const
{
	return Vector(x / factor, y / factor, z / factor);
}

float Vector::distance(const Vector& vec) const
{
	return (float)sqrt(pow(x - vec.x, 2) + pow(y - vec.y, 2) + pow(z - vec.z, 2));
}

const Vector& Vector::RelativeAngle() const
{
	return {
		std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
		std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
		0.0f
	};
}
