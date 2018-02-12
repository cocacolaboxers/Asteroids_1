#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include <cmath>

/*Default constructor*/
Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
	length = 0.0f;
}

/*Parameterized constructor. Sets the x, y, z and values to the specified ones*/
Vector4::Vector4(float xValue, float yValue, float zValue, float wValue)
{
	x = xValue;
	y = yValue;
	z = zValue;
	w = wValue;
	length = Length();
}

/*Parameterized constructor. Sets the x, y, z and w values to the same specified value*/
Vector4::Vector4(float value)
{
	x = value;
	y = value;
	z = value;
	w = value;
	length = Length();
}

Vector4::Vector4(const Vector2& vector2)
{
	x = vector2.x;
	y = vector2.y;
	z = 0.0f;
	w = 0.0f;
	length = Length();
}

Vector4::Vector4(const Vector3& vector3)
{
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;
	w = 0.0f;
	length = Length();
}

/*Returns vector's length*/
float Vector4::Length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

/*Returns length raised to the power of 2*/
float Vector4::SquaredLength() const
{
	return (x * x + y * y + z * z + w * w);
}

/*Divides x, y and z values by vector's length*/
float Vector4::Normalize()
{
	float inverseScale = 1.0f / length;
	x *= inverseScale;
	y *= inverseScale;
	z *= inverseScale;
	w *= inverseScale;

	//Calculate new length
	length = Length();

	return length;
}

Vector4& Vector4::operator=(const Vector4& aVector4)
{
	//Prevent self assignment
	if (this == &aVector4)
		return *this;

	x = aVector4.x;
	y = aVector4.y;
	z = aVector4.z;
	w = aVector4.w;

	//Calculate new length
	length = Length();

	return *this;
}

Vector4& Vector4::operator+=(const Vector4& aVector4)
{
	x = x + aVector4.x;
	y = y + aVector4.y;
	z = z + aVector4.z;
	w = w + aVector4.w;

	//Calculate new length
	length = Length();

	return *this;
}

Vector4& Vector4::operator-=(const Vector4& aVector4)
{
	x = x - aVector4.x;
	y = y - aVector4.y;
	z = z - aVector4.z;
	w = w - aVector4.w;

	//Calculate new length
	length = Length();

	return *this;
}

Vector4& Vector4::operator*=(const Vector4& aVector4)
{
	x = x * aVector4.x;
	y = y * aVector4.y;
	z = z * aVector4.z;
	w = w * aVector4.w;

	//Calculate new length
	length = Length();

	return *this;
}

Vector4& Vector4::operator/=(const Vector4& aVector4)
{
	if (aVector4.x == 0) throw "Can't divide by zero";
	if (aVector4.y == 0) throw "Can't divide by zero";
	if (aVector4.z == 0) throw "Can't divide by zero";
	if (aVector4.w == 0) throw "Can't divide by zero";

	x = x / aVector4.x;
	y = y / aVector4.y;
	z = z / aVector4.z;
	w = w / aVector4.w;

	//Calculate new length
	length = Length();

	return *this;
}

/*Calculates resulting coordinates of the addition and returns them as a new vector*/
Vector4 Vector4::operator+(const Vector4& aVector4) const
{
	float resultingXvalue = x + aVector4.x;
	float resultingYvalue = y + aVector4.y;
	float resultingZvalue = z + aVector4.z;
	float resultingWvalue = w + aVector4.w;

	return Vector4(resultingXvalue, resultingYvalue, resultingZvalue, resultingWvalue);
}

/*Calculates resulting coordinates of the subtraction and returns them as a new vector*/
Vector4 Vector4::operator-(const Vector4& aVector4) const
{
	float resultingXvalue = x - aVector4.x;
	float resultingYvalue = y - aVector4.y;
	float resultingZvalue = z - aVector4.z;
	float resultingWvalue = w - aVector4.w;

	return Vector4(resultingXvalue, resultingYvalue, resultingZvalue, resultingWvalue);
}

/*Calculates resulting coordinates of the multiplication and returns them as a new vector*/
Vector4 Vector4::operator*(const Vector4& aVector4) const
{
	float resultingXvalue = x * aVector4.x;
	float resultingYvalue = y * aVector4.y;
	float resultingZvalue = z * aVector4.z;
	float resultingWvalue = w * aVector4.w;

	return Vector4(resultingXvalue, resultingYvalue, resultingZvalue, resultingWvalue);
}

/*Calculates resulting coordinates of the division and returns them as a new vector*/
Vector4 Vector4::operator/(const Vector4& aVector4) const
{
	if (aVector4.x == 0) throw "Can't divide by zero";
	if (aVector4.y == 0) throw "Can't divide by zero";
	if (aVector4.z == 0) throw "Can't divide by zero";
	if (aVector4.w == 0) throw "Can't divide by zero";

	float resultingXvalue = x / aVector4.x;
	float resultingYvalue = y / aVector4.y;
	float resultingZvalue = z / aVector4.z;
	float resultingWvalue = w / aVector4.w;

	return Vector4(resultingXvalue, resultingYvalue, resultingZvalue, resultingWvalue);
}

bool Vector4::operator==(const Vector4& aVector4)const
{
	return x == aVector4.x && y == aVector4.y && z == aVector4.z && w == aVector4.z;
}

bool Vector4::operator!=(const Vector4& aVector4)const
{
	return x != aVector4.x || y != aVector4.y || z != aVector4.z || w != aVector4.w;
}

/*Calculates resulting coordinates of the multiplication by a value and returns them as a new vector*/
Vector4 operator*(float value, const Vector4& aVector4)
{
	float resultingXvalue = value * aVector4.x;
	float resultingYvalue = value * aVector4.y;
	float resultingZvalue = value * aVector4.z;
	float resultingWvalue = value * aVector4.w;

	return Vector4(resultingXvalue, resultingYvalue, resultingZvalue, resultingWvalue);
}

/*Calculates resulting coordinates of the multiplication by a value and returns them as a new vector*/
Vector4 operator*(const Vector4& aVector4, float value)
{
	float resultingXvalue = value * aVector4.x;
	float resultingYvalue = value * aVector4.y;
	float resultingZvalue = value * aVector4.z;
	float resultingWvalue = value * aVector4.w;

	return Vector4(resultingXvalue, resultingYvalue, resultingZvalue, resultingWvalue);
}