#include "MathUtilities.hpp"


MathUtilities::MathUtilities()
{
}

//Returns the value of x rounded downward
int MathUtilities::getNearestInt(float x)
{
	return floorf(x);
}

//Gets the value of x rounded downward and returns (whatever it returns)
int MathUtilities::getNearestEvenInt(float x)
{
	int roundedX = floorf(x);

	if (roundedX % 2 != 0)
		return ++roundedX;
	else
		return roundedX;
}

//Determines if an number is a power of two
bool MathUtilities::isPowerOfTwo(int x)
{
	while ((x % 2 == 0) && x > 1)
		x /= 2;
	return (x == 1);
}

MathUtilities::~MathUtilities()
{

}
