#include "Vector2.hpp"
#include <cmath>

/*Default constructor*/
Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
	length = 0.0f;
}

/*Parameterized constructor. Sets the x and y values to the specified ones*/
Vector2::Vector2(float xVal, float yVal)
{
	x = xVal;
	y = yVal;
	length = Length();
}

/*Parameterized constructor. Sets the x and y values to the same specified value*/
Vector2::Vector2(float val) 
{
	x = val;
	y = val;
	length = Length();
}

/*Returns vector's length*/
float Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

/*Returns length raised to the power of 2*/
float Vector2::SquaredLength() const
{
	return (x * x + y * y);
}

/*Divides x and y values by vector's length*/
float Vector2::Normalize()
{
	float inverseScale = 1.0f / length;
	x *= inverseScale;
	y *= inverseScale;

	//Calculate new length
	length = Length();
	
	return length;
}

Vector2& Vector2::operator=(const Vector2& aVector2)
{
	//Prevent self assignment
	if (this == &aVector2) 
		return *this;

	x = aVector2.x;
	y = aVector2.y;

	//Calculate new length
	length = Length();

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& aVector2)
{
	x = x + aVector2.x;
	y = y + aVector2.y;

	//Calculate new length
	length = Length();

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& aVector2)
{
	x = x - aVector2.x;
	y = y - aVector2.y;

	//Calculate new length
	length = Length();

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& aVector2)
{
	x = x * aVector2.x;
	y = y * aVector2.y;

	//Calculate new length
	length = Length();

	return *this;
}

Vector2& Vector2::operator/=(const Vector2& aVector2)
{
	if (aVector2.x == 0) throw "Can't divide by zero";
	if (aVector2.y == 0) throw "Can't divide by zero";
	
	x = x / aVector2.x;
	y = y / aVector2.y;

	//Calculate new length
	length = Length();

	return *this;
}

/*Calculates resulting coordinates of the addition and returns them as a new vector*/
Vector2 Vector2::operator+(const Vector2& aVector2) const
{
	float resultingXvalue = x + aVector2.x;
	float resultingYvalue = y + aVector2.y;
	
	return Vector2(resultingXvalue, resultingYvalue);
}

/*Calculates resulting coordinates of the subtraction and returns them as a new vector*/
Vector2 Vector2::operator-(const Vector2& aVector2) const
{
	float resultingXvalue = x - aVector2.x;
	float resultingYvalue = y - aVector2.y;

	return Vector2(resultingXvalue, resultingYvalue);
}

/*Calculates resulting coordinates of the multiplication and returns them as a new vector*/
Vector2 Vector2::operator*(const Vector2& aVector2) const
{
	float resultingXvalue = x * aVector2.x;
	float resultingYvalue = y * aVector2.y;

	return Vector2(resultingXvalue, resultingYvalue);
}

/*Calculates resulting coordinates of the division and returns them as a new vector*/
Vector2 Vector2::operator/(const Vector2& aVector2) const
{
	if (aVector2.x == 0) throw "Can't divide by zero";
	if (aVector2.y == 0) throw "Can't divide by zero";
	
	float resultingXvalue = x / aVector2.x;
	float resultingYvalue = y / aVector2.y;

	return Vector2(resultingXvalue, resultingYvalue);
}

bool Vector2::operator==(const Vector2& aVector2)const
{
	return x == aVector2.x && y == aVector2.y;
}

bool Vector2::operator!=(const Vector2& aVector2)const
{
	return x != aVector2.x || y != aVector2.y;
}

/*Calculates resulting coordinates of the multiplication by a value and returns them as a new vector*/
Vector2 operator*(float value, const Vector2& aVector2)
{
	float resultingXvalue = value * aVector2.x;
	float resultingYvalue = value * aVector2.y;

	return Vector2(resultingXvalue, resultingYvalue);
}

/*Calculates resulting coordinates of the multiplication by a value and returns them as a new vector*/
Vector2 operator*(const Vector2& aVector2, float value)
{
	float resultingXvalue = value * aVector2.x;
	float resultingYvalue = value * aVector2.y;

	return Vector2(resultingXvalue, resultingYvalue);
}