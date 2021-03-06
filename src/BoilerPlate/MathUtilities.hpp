#pragma once
#include <cmath>

class MathUtilities
{
public:
	MathUtilities();
	int GetNearestInt(float x);
	int GetNearestEvenInt(float x);

	//Constant member
	const float PI = 3.1415f;

	//Returns the maximum of any two, three or four values. Uses variadic templates/function templates http://www.cplusplus.com/articles/EhvU7k9E/
	template<class T>
	T MaxValue(T x, T y) //The informally called base case; the maximum between two numbers
	{
		T maxValue = x;
		if (y > maxValue)
			maxValue = y;
		return maxValue;
	}

	template<class T, class... fArguments>
	T MaxValue(T x, T y, fArguments... otherValues) //The actual function. fArguments stands for function arguments
	{
		return MaxValue(MaxValue(x, y), otherValues...);
	}

	//Returns the minimum of any two, three or four values. Uses variadic templates/function templates http://www.cplusplus.com/articles/EhvU7k9E/
	template<class T>
	T MinValue(T x, T y) //The informally called base case; the minimum between two numbers
	{
		T minValue = x;
		if (y < minValue)
			minValue = y;
		return minValue;
	}

	template<class T, class... fArguments>
	T MinValue(T x, T y, fArguments... otherValues) //The actual function. fArguments stands for function arguments
	{
		return MinValue(MinValue(x, y), otherValues...);
	}

	//Clamps a float (or an int) to be within a specified range (merely moves the point to the nearest available value)
	template<class T>
	T Clamp(T x, T min, T max)
	{
		if (x < min)
			x = min;
		else if (x > max)
			x = max;
		return x;
	}

	//Converts an angle in degrees to radians
	template<class T>
	float ToRadians(T angle)
	{
		return angle * (PI / 180);
	}

	//Converts an angle in radians to degrees
	template<class T>
	float ToDegrees(T angle)
	{
		return angle * (180 / PI);
	}

	//Calculates angular distance from angle A to angle B
	template<class T>
	T GetAngularDistance(T angleA, T angleB)
	{
		return abs(angleA - angleB);
	}

	bool IsPowerOfTwo(int x);

	//Interpolates a float (or an int) between a start value and an end value, 
	//at a fraction specified from start (0.0) to end (1.0).
	template<class T>
	T Interpolate(T min, T max, float fraction)
	{
		T range = max - min;
		return min + (range * fraction);
	}

	~MathUtilities();
};