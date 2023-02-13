#include "button.h"

void Button::collideButton(double x, double y) {
	if (x <= this->getPos().getX() + (this->getLength()/2)
		&& x >= this->getPos().getX() - (this->getLength()/2)
		&& y <= this->getPos().getY() + (this->getHeight()/2)
		&& y >= this->getPos().getY() - (this->getHeight()/2)
		)
	{
		this->setCollide(true);
	}
}