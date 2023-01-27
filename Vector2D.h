#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>

using namespace std;

// Vector2D Class Definition
class Vector2D
{
	public: 
        // Public Members
		double x, y;
        
        // Constructors
		Vector2D();
		Vector2D(double, double);
};		

// Nonmember Overloaded Operators
Vector2D operator*(Vector2D, double);
Vector2D operator/(Vector2D, double);
ostream& operator<<(ostream& outstream, Vector2D& cv);

#endif