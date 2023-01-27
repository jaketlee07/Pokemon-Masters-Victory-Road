#ifndef POINT2D_H
#define POINT2D_H
#include <iostream>

#include "Point2D.h"
#include "Vector2D.h"

using namespace std;

// Point2D Class Definition
class Point2D
{
	public: 
        // Public Members
		double x, y;
        
        // Constructors
		Point2D();
		Point2D(double, double);
};		

// Nonmember Functions
double GetDistanceBetween(Point2D, Point2D);

// Nonmember Overloaded Operators
ostream& operator<<(ostream& out, Point2D& point);
Point2D operator+(Point2D, Vector2D);
Vector2D operator-(Point2D, Point2D);


#endif