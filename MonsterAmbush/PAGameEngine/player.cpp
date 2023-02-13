#include "player.h"
void Player::up() {	
	this->setPos(this->getPos() + Vector3D (0, 0.3, 0));
	this->setRot(Vector3D(90, 180, 0));
}
void Player::down() {	
	this->setPos(this->getPos() + Vector3D (0, -0.3, 0));
	this->setRot(Vector3D(90, 0, 0));
}
void Player::left() {	
	this->setPos(this->getPos() + Vector3D (-0.3, 0, 0));
	this->setRot(Vector3D(90, -90, 0));
}
void Player::right() {	
	this->setPos(this->getPos() + Vector3D (0.3, 0, 0));
	this->setRot(Vector3D(90, 90, 0));
}
void Player::collidePj(Solid* enemy) {
	if (
		((enemy->getPos().getX() + enemy->getSize() ) >= (this->getPos().getX())) && (this->getPos().getX() >= (enemy->getPos().getX() - enemy->getSize()) &&
			((enemy->getPos().getY() + enemy->getSize() ) >= (this->getPos().getY())) && (this->getPos().getY() >= (enemy->getPos().getY() - (enemy->getSize() )))
			)
		)
	{
		this->setCollide(true);
	}
}