#pragma once
#include <math.h>

const double pi = 3.1415926535897;

class MathUtilities
{
public:
	MathUtilities();
	int getNearestInt(float x);
	int getNearestEvenInt(float x);

	//Returns the maximum of any two, three or four values. Uses variadic templates/function templates http://www.cplusplus.com/articles/EhvU7k9E/
	template<class T>
	T maxValue(T x, T y) //The informally called base case; the maximum between two numbers
	{
		T maxVal = x;
		if (y > maxVal)
			maxVal = y;
		return maxVal;
	}

	template<class T, class... fArguments>
	T maxValue(T x, T y, fArguments... otherValues) //The actual function. fArguments stands for function arguments
	{
		return maxValue(maxValue(x, y), otherValues...);
	}

	//Returns the minimum of any two, three or four values. Uses variadic templates/function templates http://www.cplusplus.com/articles/EhvU7k9E/
	template<class T>
	T minValue(T x, T y) //The informally called base case; the minimum between two numbers
	{
		T minVal = x;
		if (y < minVal)
			minVal = y;
		return minVal;
	}

	template<class T, class... fArguments>
	T minValue(T x, T y, fArguments... otherValues) //The actual function. fArguments stands for function arguments
	{
		return minValue(minValue(x, y), otherValues...);
	}

	//Clamps a float (or an int) to be within a specified range (merely moves the point to the nearest available value)
	template<class T>
	T clamp(T x, T min, T max)
	{
		if (x < min)
			x = min;
		else if (x > max)
			x = max;
		return x;
	}

	//Converts an angle in degrees to radians
	template<class T>
	double toRadians(T angle)
	{
		return angle * (pi / 180);
	}

	//Converts an angle in radians to degrees
	template<class T>
	double toDegrees(T angle)
	{
		return angle * (180 / pi);
	}

	//Calculates angular distance from angle A to angle B
	template<class T>
	T getAngularDistance(T angleA, T angleB)
	{
		return abs(angleA - angleB);
	}

	bool isPowerOfTwo(int x);

	//Interpolates a float (or an int) between a start value and an end value, 
	//at a fraction specified from start (0.0) to end (1.0).
	template<class T>
	T interpolate(T min, T max, float fraction)
	{
		T range = max - min;
		return min + (range * fraction);
	}

	~MathUtilities();
};

