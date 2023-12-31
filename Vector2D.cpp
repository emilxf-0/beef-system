﻿#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vector2D::normalize()
{
	float length = std::sqrt(x * x + y * y);

	if (length != 0.0f)
	{
		x /= length;
		y /= length;
	}
}

Vector2D& Vector2D::Add(const Vector2D& vector)
{
	this->x += vector.x;
	this->y += vector.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vector)
{
	this->x -= vector.x;
	this->y -= vector.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vector)
{
	this->x *= vector.x;
	this->y *= vector.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vector)
{
	this->x /= vector.x;
	this->y /= vector.y;

	return *this;
}

Vector2D& operator+(Vector2D& vector1, const Vector2D& vector2)
{
	return vector1.Add(vector2);
}

Vector2D& operator-(Vector2D& vector1, const Vector2D& vector2)
{
	return vector1.Subtract(vector2);
}

Vector2D& operator*(Vector2D& vector1, const Vector2D& vector2)
{
	return vector1.Multiply(vector2);
}

Vector2D& operator/(Vector2D& vector1, const Vector2D& vector2)
{
	return vector1.Divide(vector2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vector)
{
	return this->Add(vector);
}

Vector2D& Vector2D::operator-=(const Vector2D& vector)
{
	return this->Subtract(vector);
}

Vector2D& Vector2D::operator*=(const Vector2D& vector)
{
	return this->Multiply(vector);
}

Vector2D& Vector2D::operator/=(const Vector2D& vector)
{
	return this->Divide(vector);
}







