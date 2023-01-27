#include <cmath>
#include <iostream>

#include "Point2D.h"
#include "Vector2D.h"

// Default Constructor
Point2D::Point2D()
{
    x = 0.0;
    y = 0.0;
}

// Construct A New Point2D Object
Point2D::Point2D(double in_x, double in_y)
{
    x = in_x;
    y = in_y;
}

// Nonmember Functions
double GetDistanceBetween(Point2D p1, Point2D p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Nonmember Overloaded Operators
ostream& operator<<(ostream& outstream, Point2D& p1)
{
    outstream << "(" << p1.x << ", " << p1.y << ")";
    return outstream;
}

Point2D operator+(Point2D p1, Vector2D v1)
{
    double x = p1.x + v1.x;
    double y = p1.y + v1.y;
    
    Point2D addPoint(x, y);
    return addPoint;
}

Vector2D operator-(Point2D p1, Point2D p2)
{
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    
    Vector2D subPoint(x, y);
    return subPoint;
}


