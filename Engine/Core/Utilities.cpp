#include "Engine/Core/Utilities.h"

const float pi = 3.14159f;

//-------------------------------------------------------------------------------------------------
Vector2f::Vector2f()
{
	x = 0.0f;
	y = 0.0f;
}

//-------------------------------------------------------------------------------------------------
Vector2f::Vector2f(float rhs)
	: x(rhs)
	, y(rhs)
{
}

//-------------------------------------------------------------------------------------------------
Vector2f::Vector2f(float xVar, float yVar)
{
	x = xVar;
	y = yVar;
}

//-------------------------------------------------------------------------------------------------
void Vector2f::operator+=(const Vector2f& rhs)
{
	x = x + rhs.x;
	y = y + rhs.y;
}

//-------------------------------------------------------------------------------------------------
void Vector2f::operator-=(const Vector2f& rhs)
{
	x = x - rhs.x;
	y = y - rhs.y;
}

//-------------------------------------------------------------------------------------------------
const Vector2f Vector2f::operator+(const Vector2f& rhs) const
{
	Vector2f result = *this;
	result += rhs;

	return result;
}

//-------------------------------------------------------------------------------------------------
const Vector2f Vector2f::operator-(const Vector2f& rhs) const
{
	Vector2f result = *this;
	result -= rhs;

	return result;
}

//-------------------------------------------------------------------------------------------------
const Vector2f Vector2f::operator*(const Vector2f& rhs) const
{
	Vector2f result;
	result.x = x * rhs.x;
	result.y = y * rhs.y;

	return result;
}

//-------------------------------------------------------------------------------------------------
float Vector2f::magnitude() const
{
	return sqrt(x*x + y*y);
}

//-------------------------------------------------------------------------------------------------
Vector2f Vector2f::normal() const
{
	float mag = magnitude();
	float xVal = x / mag;
	float yVal = y / mag;
	return Vector2f(xVal, yVal);
}

//-------------------------------------------------------------------------------------------------
double InitializeTime(LARGE_INTEGER& out_initialTime)
{
	LARGE_INTEGER countsPerSecond;
	QueryPerformanceFrequency(&countsPerSecond);
	QueryPerformanceCounter(&out_initialTime);
	return(1.0 / static_cast<double>(countsPerSecond.QuadPart));
}


//-----------------------------------------------------------------------------------------------
// A simple high-precision time utility function for Windows
double GetCurrentTimeSeconds()
{
	static LARGE_INTEGER initialTime;
	static double secondsPerCount = InitializeTime(initialTime);
	LARGE_INTEGER currentCount;
	QueryPerformanceCounter(&currentCount);
	LONGLONG elapsedCountsSinceInitialTime = currentCount.QuadPart - initialTime.QuadPart;

	double currentSeconds = static_cast<double>(elapsedCountsSinceInitialTime) * secondsPerCount;
	return currentSeconds;
}

float DegreesToRadians(float degrees)
{
	return (pi / 180.0f) * degrees;
}

float DistanceFormula(Vector2f& a, Vector2f& b)
{
	float x = a.x - b.x;
	float y = a.y - b.y;
	return sqrt(x*x + y*y);
}
