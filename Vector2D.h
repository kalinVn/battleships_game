#ifndef _Vector2D_H
#define _Vector2D_H

#include "math.h"

using std::sqrt;
using std::pow;

class Vector2D {

    double x, y;

    public:
        Vector2D();

        Vector2D(double, double);

        double getX () {
            return x;
        }

        double getY () {
            return y;
        }

        Vector2D middlePoint (Vector2D v1, Vector2D v2) {
            return Vector2D(v1.getX() + v2.getX() / 2,  (v1.getY() + v2.getY()) / 2);
        }

        double length () {
            return sqrt(pow(x, 2) + pow(y, 2));
        } 
        
        double getDistance (Vector2D v) {
            return sqrt(pow(y - v.getY(), 2) + pow(x - v.getX(), 2));
        } 
};

Vector2D::Vector2D () {
    x = 0;
    y = 0;
}

Vector2D::Vector2D (double i, double j) {
    x = i;
    y = j;
}

#endif
