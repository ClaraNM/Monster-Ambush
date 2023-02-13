#include "enemy.h"

void Enemy::persue(Vector3D pjPos) {
	Vector3D newDir = pjPos - (this->getPos());
	int modulo = sqrt(pow(newDir.getX(),2)+pow(newDir.getY(),2));
	this->setVel(Vector3D(newDir.getX()/modulo, newDir.getY() / modulo,0)/ this->getEnemyVel()); 
}
Enemy* Enemy::clone(Vector3D randomPos) {
	Enemy* another = new Enemy();
	another->setSize(this->getSize());
	another->setColor(this->getColor());
	another->setEnemyVel(this->getEnemyVel());
	another->setPoints(this->getPoints());
	another->setLife(this->getLife());
	another->setPos(randomPos);
	another->setCollide(false);
	return another;

}
void Enemy::collideEnemy(Solid* bullet, int damage) {
	if (bullet->getPos().getX() <= this->getPos().getX() + (this->getSize() / 2)
		&& bullet->getPos().getX() >= this->getPos().getX() - (this->getSize() / 2)
		&& bullet->getPos().getY() <= this->getPos().getY() + (this->getSize() / 2)
		&& bullet->getPos().getY() >= this->getPos().getY() - (this->getSize() / 2)
		)
	{
		this->setCollide(true);
		this->setLife(this->getLife() - damage);
		this->setColor(Vector3D(this->getColor().getX()-0.1, this->getColor().getY() - 0.1, this->getColor().getZ() - 0.1));

	}
}