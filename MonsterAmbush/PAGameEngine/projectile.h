#pragma once
#include "sphere.h"

class Projectile :
	public Sphere
{
private: 
	
	int damage=2;
	bool collided;

public:
	Projectile(double d = 0.2, Vector3D p = Vector3D(0, 0, 0), Vector3D c = Vector3D(0.8, 0.8, 0.8),bool cd=false) :collided(cd), Sphere(d, p, c) {};
	Projectile* setDirUp();
	Projectile* setDirDown();
	Projectile* setDirRight();
	Projectile* setDirLeft();
	inline int getDamage() { return damage; };
	inline bool getCollide() { return collided; }
	inline void setCollide(bool cd) { collided = cd; }
	void collideBullet(Vector3D limits);
};

