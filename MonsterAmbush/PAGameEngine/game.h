#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glut.h>
#include "vector3d.h"
#include "cube.h"
#include "sphere.h"
#include "teapot.h"
#include "scene.h"
#include "camera.h"
#include "camera_fly.h"
#include "cylinder.h"
#include "triangle.h"
#include "model_mesh_triangles.h"
#include "loader_obj.h"
#include "light.h"
#include "cuboid.h"
#include "text.h"

#include <chrono>

using namespace std::chrono;
using namespace std;
class Game {
	const double TIME_INCREMENT = 0.07; //ms tiempo en el juego
	const int UPDATE_PERIOD = 10; //ms tiempo en el mundo real

	milliseconds initialMilliseconds;
	long lastUpdatedTime;

	
	Scene* activeScene;
	vector<Scene*> scenes;
	


	

public:

	Game() : activeScene(nullptr), initialMilliseconds(duration_cast<milliseconds>(system_clock::now().time_since_epoch())), lastUpdatedTime(0) {}

	void init();
	void init(const string& file);
	void render();
	void update();
	void processKeyPressed(unsigned char key, int x, int y);
	void processMouseMovement(int x, int y);
	void processMouseClick(int button, int state, int x, int y);

	//getters
	inline double getTIME_INCREMENT() { return TIME_INCREMENT; }
	inline int getUPDATE_PERIOD() { return UPDATE_PERIOD; }
	inline milliseconds getInitialMilliseconds() { return initialMilliseconds; }
	inline long getLastUpdatedTime() { return lastUpdatedTime; }
	inline Scene* getActiveScene() { return activeScene; }
	inline vector<Scene*> getScenes() { return scenes; }
	inline Scene* getScene(int i) { return scenes[i]; }

	//setters
	inline void setActiveScene(Scene* as) { activeScene=as; }
	inline void setLastUpdatedTime(long lut) { lastUpdatedTime = lut; }
	void addScene(Scene* s) { scenes.push_back(s); }


};

