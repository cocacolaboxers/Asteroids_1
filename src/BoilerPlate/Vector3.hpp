#pragma once
#ifndef _Vector3_H_
#define _Vector3_H_

struct Vector3
{
	/*STATIC*/
	static Vector3 Origin;

	/*MEMBERS*/
	float x;
	float y;
	float z; 
	float length;

	/*CTOR*/
	Vector3();
	Vector3(float, float, float);
	Vector3(float);

	/*PUBLIC FUNCTIONS*/
	float Length() const;
	float SquaredLength() const;
	float Normalize();

	/*OPERATORS*/
	Vector3& operator= (const Vector3&);
	Vector3& operator+= (const Vector3&);
	Vector3& operator-= (const Vector3&);
	Vector3& operator*= (const Vector3&);
	Vector3& operator/= (const Vector3&);
	Vector3 operator+ (const Vector3&)const;
	Vector3 operator- (const Vector3&)const;
	Vector3 operator* (const Vector3&)const;
	Vector3 operator/ (const Vector3&)const;
	bool operator== (const Vector3&)const;
	bool operator!= (const Vector3&)const;
	friend Vector3 operator*(float, const Vector3&);
	friend Vector3 operator*(const Vector3&, float);
};

#endif // !_Vector3_H_