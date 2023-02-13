#include "projectile.h"
Projectile* Projectile::setDirUp() {
	Projectile* balaUp = new Projectile();
	balaUp->setSize(this->getSize());
	balaUp->setPos(this->getPos());
	balaUp->setColor(this->getColor());
	balaUp->setVel(Vector3D(0, 0.6, 0));
	return balaUp;
};
 Projectile* Projectile::setDirDown() { 
	Projectile* balaDown = new Projectile();
	balaDown->setSize(this->getSize());
	balaDown->setPos(this->getPos());
	balaDown->setColor(this->getColor());
	balaDown->setVel( Vector3D(0, -0.6, 0)); 
	return balaDown;
 };
Projectile* Projectile::setDirRight() { 
	Projectile* balaRight = new Projectile();
	balaRight->setSize(this->getSize());
	balaRight->setPos(this->getPos());
	balaRight->setColor(this->getColor());
	balaRight->setVel(Vector3D(0.6, 0, 0)); 
	return balaRight;
};
Projectile* Projectile::setDirLeft() { 
	Projectile* balaLeft = new Projectile();
	balaLeft->setSize(this->getSize());
	balaLeft->setPos(this->getPos());
	balaLeft->setColor(this->getColor());
	balaLeft->setVel( Vector3D(-0.6, 0, 0));
	return balaLeft;
};
void Projectile::collideBullet(Vector3D limits) {
	if (this->getPos().getY() < 0.1) {
		this->setCollide(true);
	}
	if (this->getPos().getY() > limits.getY()-0.1) {
		this->setCollide(true);

	}
	if (this->getPos().getX() > limits.getX()-0.1) {
		this->setCollide(true);

	}
	if (this->getPos().getX() < 0.1) {
		this->setCollide(true);

	}
	
}