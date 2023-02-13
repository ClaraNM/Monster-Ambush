#pragma once
#include "composite.h"
#include "camera.h"

using namespace std;
class Scene :public Composite {
	Vector3D size;
	Camera* camera;
	double mx, my;
public:
	Scene() : size(Vector3D(10, 10, 10)), Composite()
	{
		this->camera = new Camera(Vector3D(size.getX() / 2, size.getY() / 2, size.getZ() * 2));
	}
	inline Vector3D getSize() const { return this->size; }
	inline void setSize(const Vector3D& sizeToSet) { this->size = sizeToSet; this->camera->setPos(Vector3D(size.getX()/2, size.getY()/2, size.getZ()*2)); }
	void update(const double& dt);
	void render();
	void processKeyPressed(unsigned char key, int x, int y);
	void processMouseMovement(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	Scene* clone();

};

