#pragma once
#include "cuboid.h"
#include <GL/glut.h>
class Button :
    public Cuboid
{
    bool collided;

public:
    Button(int i = 0, double d = 1.0, Vector3D p = Vector3D(0, 0, 0), Vector3D c = Vector3D(1, 1, 0), bool cd = false) : collided(cd), Cuboid() {}
    inline bool getCollide() { return collided; }
    inline void setCollide(bool cd) { collided = cd; }
    void collideButton(double x, double y);
};
