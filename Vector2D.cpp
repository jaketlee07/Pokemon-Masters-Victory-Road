#include <cmath>
#include <iostream>

#include "Vector2D.h"

// Default Constructor
Vector2D::Vector2D()
{
    x = 0.0;
    y = 0.0;
}

// Create a new Vector2D Object
Vector2D::Vector2D(double in_x, double in_y)
{
    x = in_x;
    y = in_y;
}

// Nonmember Overloaded Operators
Vector2D operator*(Vector2D v1, double d)
{
    Vector2D multVector2D;
	multVector2D.x = v1.x*d;
	multVector2D.y = v1.y*d;
	return multVector2D;
}
Vector2D operator/(Vector2D v1, double d)
{
    Vector2D divVector2D;
    if (d == 0)
    {
        divVector2D.x = v1.x;
        divVector2D.y = v1.y;
    }
    else
    {
        divVector2D.x = v1.x / d;
        divVector2D.y = v1.y / d;
    }

    return divVector2D;
}
ostream& operator<<(ostream& outstream, Vector2D& v1)
{
    outstream << "<" << v1.x << ", " << v1.y << ">";
    return outstream;
}

