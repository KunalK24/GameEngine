#pragma once

#include<math.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern const float pi;

double GetCurrentTimeSeconds();

float DegreesToRadians(float degrees);

struct Vector2f 
{
	float x;
	float y;

	Vector2f();
	Vector2f(float rhs);
	Vector2f(float xVar, float yVar);
	void operator+=(const Vector2f& rhs);
	void operator-=(const Vector2f& rhs);
	const Vector2f operator+(const Vector2f& rhs) const;
	const Vector2f operator-(const Vector2f& rhs) const;
	const Vector2f operator*(const Vector2f& rhs) const;

	float magnitude() const;
	Vector2f normal() const;
};

float DistanceFormula(Vector2f& a, Vector2f& b);