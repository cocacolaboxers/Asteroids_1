#include "Vector2.hpp"
#include "Vector3.hpp"
#include <cmath>

/*Default constructor*/
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	length = 0.0f;
}

/*Parameterized constructor. Sets the x, y and z values to the specified ones*/
Vector3::Vector3(float xVal, float yVal, float zVal)
{
	x = xVal;
	y = yVal;
	z = zVal;
	length = Length();
}

/*Parameterized constructor. Sets the x, y and z values to the same specified value*/
Vector3::Vector3(float val)
{
	x = val;
	y = val;
	z = val;
	length = Length();
}

Vector3::Vector3(const Vector2& vector2)
{
	x = vector2.x;
	y = vector2.y;
	z = 0.0f;
	length = Length();
}

/*Returns vector's length*/
float Vector3::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

/*Returns length raised to the power of 2*/
float Vector3::SquaredLength() const
{
	return (x * x + y * y + z * z);
}

/*Divides x, y and z values by vector's length*/
float Vector3::Normalize()
{
	float inverseScale = 1.0f / length;
	x *= inverseScale;
	y *= inverseScale;
	z *= inverseScale;

	//Calculate new length
	length = Length();

	return length;
}

Vector3& Vector3::operator=(const Vector3& aVector3)
{
	//Prevent self assignment
	if (this == &aVector3)
		return *this;

	x = aVector3.x;
	y = aVector3.y;
	z = aVector3.z;

	//Calculate new length
	length = Length();

	return *this;
}

Vector3& Vector3::operator+=(const Vector3& aVector3)
{
	x = x + aVector3.x;
	y = y + aVector3.y;
	z = z + aVector3.z;

	//Calculate new length
	length = Length();

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& aVector3)
{
	x = x - aVector3.x;
	y = y - aVector3.y;
	z = z - aVector3.z;

	//Calculate new length
	length = Length();

	return *this;
}

Vector3& Vector3::operator*=(const Vector3& aVector3)
{
	x = x * aVector3.x;
	y = y * aVector3.y;
	z = z * aVector3.z;

	//Calculate new length
	length = Length();

	return *this;
}

Vector3& Vector3::operator/=(const Vector3& aVector3)
{
	if (aVector3.x == 0) throw "Can't divide by zero";
	if (aVector3.y == 0) throw "Can't divide by zero";

	x = x / aVector3.x;
	y = y / aVector3.y;
	z = z / aVector3.z;

	//Calculate new length
	length = Length();

	return *this;
}

/*Calculates resulting coordinates of the addition and returns them as a new vector*/
Vector3 Vector3::operator+(const Vector3& aVector3) const
{
	float resultingXvalue = x + aVector3.x;
	float resultingYvalue = y + aVector3.y;
	float resultingZvalue = z + aVector3.z;

	return Vector3(resultingXvalue, resultingYvalue, resultingZvalue);
}

/*Calculates resulting coordinates of the subtraction and returns them as a new vector*/
Vector3 Vector3::operator-(const Vector3& aVector3) const
{
	float resultingXvalue = x - aVector3.x;
	float resultingYvalue = y - aVector3.y;
	float resultingZvalue = z - aVector3.z;

	return Vector3(resultingXvalue, resultingYvalue, resultingZvalue);
}

/*Calculates resulting coordinates of the multiplication and returns them as a new vector*/
Vector3 Vector3::operator*(const Vector3& aVector3) const
{
	float resultingXvalue = x * aVector3.x;
	float resultingYvalue = y * aVector3.y;
	float resultingZvalue = z * aVector3.z;

	return Vector3(resultingXvalue, resultingYvalue, resultingZvalue);
}

/*Calculates resulting coordinates of the division and returns them as a new vector*/
Vector3 Vector3::operator/(const Vector3& aVector3) const
{
	if (aVector3.x == 0) throw "Can't divide by zero";
	if (aVector3.y == 0) throw "Can't divide by zero";

	float resultingXvalue = x / aVector3.x;
	float resultingYvalue = y / aVector3.y;
	float resultingZvalue = z / aVector3.z;

	return Vector3(resultingXvalue, resultingYvalue, resultingZvalue);
}

bool Vector3::operator==(const Vector3& aVector3)const
{
	return x == aVector3.x && y == aVector3.y && z == aVector3.z;
}

bool Vector3::operator!=(const Vector3& aVector3)const
{
	return x != aVector3.x || y != aVector3.y || z != aVector3.z;
}

/*Calculates resulting coordinates of the multiplication by a value and returns them as a new vector*/
Vector3 operator*(float value, const Vector3& aVector3)
{
	float resultingXvalue = value * aVector3.x;
	float resultingYvalue = value * aVector3.y;
	float resultingZvalue = value * aVector3.z;

	return Vector3(resultingXvalue, resultingYvalue, resultingZvalue);
}

/*Calculates resulting coordinates of the multiplication by a value and returns them as a new vector*/
Vector3 operator*(const Vector3& aVector3, float value)
{
	float resultingXvalue = value * aVector3.x;
	float resultingYvalue = value * aVector3.y;
	float resultingZvalue = value * aVector3.z;

	return Vector3(resultingXvalue, resultingYvalue, resultingZvalue);
}