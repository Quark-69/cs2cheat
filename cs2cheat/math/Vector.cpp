#include "Vector.h"

const Vector& Vector::operator+(const Vector& vec) const
{
	return { x + vec.x, y + vec.y, z + vec.z };
}

const Vector& Vector::operator-(const Vector& vec) const
{
	return { x - vec.x, y - vec.y, z - vec.z };
}

const Vector& Vector::operator*(const float factor) const
{
	return { x * factor, y * factor, z * factor };
}

const Vector& Vector::operator/(const float factor) const
{
	return { x / factor, y / factor, z / factor };
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

const Vector2& Vector2::WorldToScreen(ViewMatrix& viewMatrix, const Vector& pos, int width, int height)
{
	Vector2 screen;
	float w = viewMatrix[3][0] * pos.x + viewMatrix[3][1] * pos.y + viewMatrix[3][2] * pos.z + viewMatrix[3][3];
	if (w < 0.01f)
		return screen;

	float screenX = (viewMatrix[0][0] * pos.x + viewMatrix[0][1] * pos.y + viewMatrix[0][2] * pos.z + viewMatrix[0][3]);
	float screenY = (viewMatrix[1][0] * pos.x + viewMatrix[1][1] * pos.y + viewMatrix[1][2] * pos.z + viewMatrix[1][3]);


	float camX = width / 2.0f;
	float camY = height / 2.0f;

	screen.x = camX + (camX * screenX / w);
	screen.y = camY - (camY * screenY / w);

	return screen;
}

float Vector2::distance(const Vector2& vec) const
{
	return (float)sqrt(pow(x - vec.x, 2) + pow(y - vec.y, 2));
}

const Vector2& Vector2::operator*(const float factor) const
{
	return { x * factor, y * factor};
}
