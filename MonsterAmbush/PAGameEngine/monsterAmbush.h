#pragma once
#include "game.h"
#include "projectile.h"
#include "player.h"
#include "enemy.h"
#include "button.h"
class MonsterAmbush :
	public Game
{
	seconds initialSeconds;
	long lastUpdateTimeSec;

	Camera currentCamera;
	Camera secondaryCamera;
	bool alternativeCamera = false;

	vector<Projectile*> balas;
	vector<Enemy*> enemigos;
	Player* pj = new Player();
	Button* jugar = new Button();
	Button* salir = new Button();

	vector<string> puntuacionesPila;
	vector<Text*> puntuacionesMuestra ={new Text ("1"),new Text("2") ,new Text("3") ,new Text("4") ,new Text("5"), new Text("6") };
	bool puntuacionRegistrada=false;

public:
	MonsterAmbush(): lastUpdateTimeSec(0),Game(){}

	//void readScore(string file);

	void init();
	void render();
	void update();
	void processKeyPressed(unsigned char key, int x, int y);
	void processMouseMovement(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
};

