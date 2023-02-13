#pragma once
#include "cube.h"
class Enemy :
	public Cube
{
private:
	int life;
	int points;
	bool collided;
	int enemyVel;

public:	
	Enemy(double d = 1.0, Vector3D p = Vector3D(0, 0, 0), Vector3D c = Vector3D(1, 0, 0), int pt=0,int l = 0, bool cd=false) :points(pt),collided(cd),life(l), Cube(d, p, c) {		}
	inline int getLife() { return life; }
	inline void setLife(int l) { life = l; }
	inline bool getCollide() { return collided; }
	inline void setCollide(bool cd) { collided = cd; }
	inline int getPoints() { return points; }
	inline void setPoints(int dP) { points = dP; }
	inline int getEnemyVel() { return enemyVel; }
	inline void setEnemyVel(int v) { enemyVel = v; }

	void persue(Vector3D pjPos);
	Enemy* clone(Vector3D randomPos);
	void collideEnemy(Solid* bullet, int damage);
	
};

