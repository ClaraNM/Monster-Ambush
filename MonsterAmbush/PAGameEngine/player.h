#pragma once
#include "cube.h"
class Player :
	public Cube
{
	int kills;
	int score;
	bool collided;
public:
	Player(double d = 0.5, Vector3D p = Vector3D(0, 0, 0), Vector3D c = Vector3D(0, 0, 1),int k=0, int s =0, bool cd=false) :kills(k),score(s), collided(cd),Cube (d,p,c) {	}
	void up();
	void down();
	void right();
	void left();
	inline int getKills() { return kills; }
	inline void setKills(int k) { kills = k; }
	inline int getScore() { return score; }
	inline void setScore(int s) { score = s; }
	inline bool getCollide() { return collided; }
	inline void setCollide(bool cd) { collided = cd; }
	void collidePj(Solid* enemy);
};

