#include "monsterAmbush.h"
inline double getRand(double min, double max) {
	static const int PRECISION = 10000;
	double n = max - min;
	int ir = rand() % PRECISION;
	double r = min + (double)ir / PRECISION * n;
	return r;
}

inline double getRand(double max = 1) { return getRand(0, max); }


void MonsterAmbush::init() {
	srand(13); //semilla
	currentCamera.setPos(Vector3D(0, 0, 10));
	currentCamera.setRot(Vector3D(0, 0, 0));
	secondaryCamera.setPos(Vector3D(0, -15, 10));
	secondaryCamera.setRot(Vector3D(-55, 0, 0));
	Light* light = new Light(Vector3D(1, 5, 5));

////ESCENA MENU//////////////////////////////////////////////////////////////////////////
	Scene* menuScene = new(nothrow) Scene();
	menuScene->setSize(Vector3D(30, 20, 7));

	menuScene->add(light);

	Text* tituloTxt = new Text("MONSTER AMBUSH");
	tituloTxt->setPos(Vector3D(menuScene->getSize().getX() / 2 - 3.5, menuScene->getSize().getY() / 2 + 8, 0));

	jugar->setPos(Vector3D(menuScene->getSize().getX() / 2, menuScene->getSize().getY() / 2 + 3, 0));
	jugar->setColor(Vector3D(0, 1, 0));
	jugar->setLength(7);
	jugar->setHeight(3);

	Text* jugarTxt = new Text("JUGAR");
	jugarTxt->setPos(Vector3D(jugar->getPos().getX() - 1, jugar->getPos().getY() - 0.8, 3));

	salir->setPos(Vector3D(menuScene->getSize().getX() / 2, (menuScene->getSize().getY() / 2) - 3, 0));
	salir->setColor(Vector3D(1, 0, 0));
	salir->setLength(7);
	salir->setHeight(3);

	Text* salirTxt = new Text("SALIR");
	salirTxt->setPos(Vector3D(salir->getPos().getX() - 1, salir->getPos().getY(), 3));

	menuScene->add(tituloTxt);
	menuScene->add(jugarTxt);
	menuScene->add(jugar);
	menuScene->add(salirTxt);
	menuScene->add(salir);

	this->addScene(menuScene);

////ESCENA JUEGO//////////////////////////////////////////////////////////////////////////
	Scene* mainScene = new(nothrow) Scene();
	mainScene->setSize(Vector3D(40, 30, 7));
	mainScene->add(light);

	////PERSONAJE EN CUBO///////////////////////////////
	pj->setSize(1.0);
	pj->setPos(Vector3D(mainScene->getSize().getX() / 2, mainScene->getSize().getY() / 2, 0));
	pj->setColor(Vector3D(0, 0, 0.8));

	mainScene->add(pj);

	////ENEMIGOS////////////////////////////////////////
	//Murcielago
	Enemy* bat = new Enemy();
	bat->setColor(Vector3D(0, 0, 0));
	bat->setSize(1);
	bat->setLife(2);
	bat->setEnemyVel(2);

	bat->setPoints(50);
	this->enemigos.push_back(bat);
	//Esqueleto
	Enemy* skeleton = new Enemy();
	skeleton->setColor(Vector3D(1, 1, 1));
	skeleton->setSize(1.5);
	skeleton->setLife(6);
	skeleton->setEnemyVel(5);

	skeleton->setPoints(60);
	this->enemigos.push_back(skeleton);
	////BALA ORIGEN/////////////////////////////
	Projectile* balaOrigen = new Projectile();
	balaOrigen->setSize(0.1);
	balaOrigen->setColor(Vector3D(1, 0, 0));
	balas.push_back(balaOrigen);
	mainScene->add(balas[0]);

	this->addScene(mainScene);
////VARIABLES PARA MOSTRAR LA PUNTUACION////////////////////
	Vector3D tamañoEscena = Vector3D(30, 20, 7);

	Text* puntuacionText = new Text("Tu puntuacion:");
	puntuacionText->setPos(Vector3D(tamañoEscena.getX() / 2 - 3, (tamañoEscena.getY() / 2) + 4, 0));

	puntuacionesMuestra[0]->setPos(Vector3D(tamañoEscena.getX() / 2, tamañoEscena.getY() / 2 + 3, 0));

	Text* rankingText = new Text("Ranking:");
	rankingText->setPos(Vector3D(tamañoEscena.getX() / 2 -1.5, (tamañoEscena.getY() / 2 ), 0));

	for (int i = 1; i < puntuacionesMuestra.size(); i++)
	{
		puntuacionesMuestra[i]->setText("No hay puntuacion");
		puntuacionesMuestra[i]->setPos(Vector3D(tamañoEscena.getX() / 2-1, tamañoEscena.getY() / 2 - (i), 0));

	}

////ESCENA DERROTA//////////////////////////////////////////////////////////////////////////
	Scene* deathScene = new(nothrow) Scene();
	deathScene->setSize(tamañoEscena);

	deathScene->add(light);

	Text* finaleText = new Text("Fin de la partida");
	finaleText->setPos(Vector3D(deathScene->getSize().getX() / 2 - 4, (deathScene->getSize().getY() / 2) + 6, 0));
	deathScene->add(finaleText);
	deathScene->add(rankingText);
	deathScene->add(puntuacionText);
	for (int i = 0; i < puntuacionesMuestra.size(); i++)
	{
		deathScene->add(puntuacionesMuestra[i]);
	}

	this->addScene(deathScene);

////ESCENA VICTORIA//////////////////////////////////////////////////////////////////////////
	Scene* victoryScene = new(nothrow) Scene();
	victoryScene->setSize(tamañoEscena);

	victoryScene->add(light);

	Text* victoryText = new Text("¡Felicidades, ganaste la partida!");
	victoryText->setPos(Vector3D(victoryScene->getSize().getX() / 2 - 6, (victoryScene->getSize().getY() / 2) + 6, 0));
	victoryScene->add(victoryText);
	victoryScene->add(rankingText);
	victoryScene->add(puntuacionText);


	for (int i = 0; i < puntuacionesMuestra.size(); i++)
	{
		victoryScene->add(puntuacionesMuestra[i]);
	}


	this->addScene(victoryScene);


////ESCENA ACTIVA///////////////
	this->setActiveScene(menuScene);
}
void MonsterAmbush::render() {
	if (alternativeCamera == true)
	{
		secondaryCamera.render();

	}
	else {
		currentCamera.render();

	}
	this->getActiveScene()->render();

}
void MonsterAmbush::update() {

	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	seconds enemyAppearTime = duration_cast<seconds>(system_clock::now().time_since_epoch());

	//Acciones si se colisionan los botones
	if (jugar->getCollide() == true)
	{
		this->setActiveScene(this->getScene(1));
		jugar->setCollide(false);
	}
	
	if (salir->getCollide() == true)
	{
		exit(0);
	}
	//Acciones si se colisiona el personaje o si cumple las condiciones para ganar
	if ((pj->getCollide() == true || pj->getKills() == 25)&& puntuacionRegistrada==false)
	{
		if (pj->getCollide() == true)
		{
			this->setActiveScene(this->getScene(2));
		}
		if (pj->getKills() == 25)
		{
			this->setActiveScene(this->getScene(3));
		}
	//Registro de la puntuacion
		ofstream fScore("score.txt", ios_base::app);
		if (fScore.is_open())
		{
			fScore <<this->pj->getScore() << endl;
			fScore.close();
		}
		else
		{
			cout << "Error al abrir el fichero de salida" << endl;
		}
		//Lectura del fichero
		string line;
		ifstream fScoreEntrada("score.txt");
		if (fScoreEntrada.is_open()) {
			while (getline(fScoreEntrada, line)) {
				puntuacionesPila.push_back(line);
				
			}
			fScoreEntrada.close();
		}
		else {
			cout << "El fichero parece que no existe" << endl;
		}
			//Ultima puntuacion
		puntuacionesMuestra[0]->setText(puntuacionesPila.back());
		//Creación del Ranking (las mejores 5 puntuaciones)
		for (int j = 1; j < puntuacionesMuestra.size(); j++)
		{
			int comparar = 0;
			int indice = 0;
			string MaxPtaux;
			for (int i = 0; i <puntuacionesPila.size() ; i++)
			{
				if (stoi(puntuacionesPila[i])>comparar)
				{
					MaxPtaux = puntuacionesPila[i];
					indice = i;
					comparar = stoi(MaxPtaux);
				}
			}
			puntuacionesMuestra[j]->setText(to_string(j)+": "+MaxPtaux);
			puntuacionesPila.erase(puntuacionesPila.begin()+indice);
		}
		puntuacionesPila.clear();
		puntuacionRegistrada = true;

	}

	if ((currentTime.count() - this->getInitialMilliseconds().count()) - this->getLastUpdatedTime() > this->getUPDATE_PERIOD())
	{
		this->getActiveScene()->update(this->getTIME_INCREMENT());
		this->balas[0]->setPos(pj->getPos()); //la bala original actualiza su posicion para seguir al pj

		//for que actualiza el persguimiento de los enemigos y checkea activa las colisiones de las balas con los enemigos
		for (int i = 1; i < enemigos.size(); i++)
		{
			this->enemigos[i]->persue(pj->getPos());
			this->pj->collidePj(enemigos[i]);
			for (int j = 1; j < balas.size(); j++)
			{
				this->balas[j]->collideBullet(Vector3D(this->getScene(1)->getSize().getX(), this->getScene(1)->getSize().getY(), this->getScene(1)->getSize().getZ()));
				this->enemigos[i]->collideEnemy(balas[j], balas[j]->getDamage());

				if (this->balas[j]->getCollide() == true)
				{
					this->getActiveScene()->removeSolid(this->balas[j]);
					this->balas.erase(balas.begin() + j);
				}


				if (this->enemigos[i]->getCollide() == true)
				{
					this->getActiveScene()->removeSolid(this->balas[j]);
					this->balas.erase(balas.begin() + j);

					this->enemigos[i]->setCollide(false);

					if (enemigos[i]->getLife() <= 0)
					{
						this->pj->setScore(pj->getScore() + this->enemigos[i]->getPoints());
						this->pj->setKills(pj->getKills() + 1);

						this->getActiveScene()->removeSolid(this->enemigos[i]);
						this->enemigos.erase(enemigos.begin() + i);

					}

				}
			}

		}
		this->setLastUpdatedTime(currentTime.count() - this->getInitialMilliseconds().count());

	}
	if (this->getActiveScene() == this->getScene(1))
	{

		//Generación aleatoria de enemigos cada 10 seg
		if ((enemyAppearTime.count() - this->initialSeconds.count() - this->lastUpdateTimeSec) > 10) 
		{
			//top
			this->enemigos.push_back(enemigos[(int)getRand(0, 2)]->clone(Vector3D(getRand((this->getScene(1)->getSize().getX() / 2) - 10, (this->getScene(1)->getSize().getX() / 2) + 10),
				getRand(this->getScene(1)->getSize().getY() - 2, this->getScene(1)->getSize().getY()), 0)));
			this->getScene(1)->add(enemigos[enemigos.size() - 1]);

			//bottom
			this->enemigos.push_back(enemigos[(int)getRand(0, 2)]->clone(Vector3D(getRand((this->getScene(1)->getSize().getX() / 2) - 10, (this->getScene(1)->getSize().getX() / 2) + 10),
				getRand(0, 2), 0)));
			this->getScene(1)->add(enemigos[enemigos.size() - 1]);

			//left
			this->enemigos.push_back(enemigos[(int)getRand(0, 2)]->clone(Vector3D(getRand(0, 2),
				getRand((this->getScene(1)->getSize().getY() / 2) - 10, (this->getScene(1)->getSize().getY() / 2) + 10), 0)));
			this->getScene(1)->add(enemigos[enemigos.size() - 1]);

			//right
			this->enemigos.push_back(enemigos[(int)getRand(0, 2)]->clone(Vector3D(getRand(this->getScene(1)->getSize().getX() - 2, this->getScene(1)->getSize().getX()),
				getRand((this->getScene(1)->getSize().getY() / 2) - 10, (this->getScene(1)->getSize().getY() / 2) + 10), 0)));
			this->getScene(1)->add(enemigos[enemigos.size() - 1]);

			//Tras 10 kills, el juego se vuelve más dificil y aparecen más enemigos
			if (pj->getKills()>=10)
			{
				//left
				this->enemigos.push_back(enemigos[(int)getRand(0, 2)]->clone(Vector3D(getRand(0, 2),
					getRand((this->getScene(1)->getSize().getY() / 2) - 10, (this->getScene(1)->getSize().getY() / 2) + 10), 0)));
				this->getScene(1)->add(enemigos[enemigos.size() - 1]);

				//right
				this->enemigos.push_back(enemigos[(int)getRand(0, 2)]->clone(Vector3D(getRand(this->getScene(1)->getSize().getX() - 2, this->getScene(1)->getSize().getX()),
					getRand((this->getScene(1)->getSize().getY() / 2) - 10, (this->getScene(1)->getSize().getY() / 2) + 10), 0)));
				this->getScene(1)->add(enemigos[enemigos.size() - 1]);
					if (pj->getKills() >= 20)
					{
						//top
						this->enemigos.push_back(enemigos[(int)getRand(0, 2)]->clone(Vector3D(getRand((this->getScene(1)->getSize().getX() / 2) - 10, (this->getScene(1)->getSize().getX() / 2) + 10),
							getRand(this->getScene(1)->getSize().getY() - 2, this->getScene(1)->getSize().getY()), 0)));
						this->getScene(1)->add(enemigos[enemigos.size() - 1]);

						//bottom
						this->enemigos.push_back(enemigos[(int)getRand(0, 2)]->clone(Vector3D(getRand((this->getScene(1)->getSize().getX() / 2) - 10, (this->getScene(1)->getSize().getX() / 2) + 10),
							getRand(0, 2), 0)));
						this->getScene(1)->add(enemigos[enemigos.size() - 1]);
					}
			}

			this->lastUpdateTimeSec = enemyAppearTime.count() - this->initialSeconds.count();
		}

	}
}
void MonsterAmbush::processKeyPressed(unsigned char key, int x, int y) {

	switch (key)
	{
	case '1': //Cambiar entre escenas
		if (this->getScene(0) != nullptr)
		{
			this->setActiveScene(this->getScene(0));
		}
		break;
	case '2':
		if (this->getScene(1) != nullptr)
		{
			this->setActiveScene(this->getScene(1));
		}
		break;
	case '3':
		if (this->getScene(2) != nullptr)
		{
			this->setActiveScene(this->getScene(2));
		}
	case '4':
		if (this->getScene(3) != nullptr)
		{
			this->setActiveScene(this->getScene(3));
		}
		break;
		//Cambiar la cámara
	case '8':

		alternativeCamera = false;

		break;
	case '9':

		alternativeCamera = true;

		break;
		//Controles del personaje
	case'w':
		pj->up();
		break;
	case'a':
		pj->left();

		break;
	case'd':
		pj->right();
		break;
	case's':
		pj->down();
		break;
	case'i':
		balas.push_back(balas[0]->setDirUp());
		this->getScene(1)->add(balas[balas.size() - 1]);
		break;
	case'j':
		balas.push_back(balas[0]->setDirLeft());
		this->getScene(1)->add(balas[balas.size() - 1]);

		break;
	case'l':
		balas.push_back(balas[0]->setDirRight());
		this->getScene(1)->add(balas[balas.size() - 1]);

		break;
	case'k':
		balas.push_back(balas[0]->setDirDown());
		this->getScene(1)->add(balas[balas.size() - 1]);

		break;
	}
	this->getActiveScene()->processKeyPressed(key, x, y);
}

void MonsterAmbush::processMouseMovement(int x, int y) {
	this->getActiveScene()->processMouseMovement(x, y);
}

void MonsterAmbush::processMouseClick(int button, int state, int x, int y) {
	this->getActiveScene()->processMouseClick(button, state, x, y);

//se ajustan los valores del click que viene en unidades de pixel para que coincidan con las medidas de la escena
	double escalatedX = 640 / this->getActiveScene()->getSize().getX();
	double escalatedY = 480 / this->getActiveScene()->getSize().getY();
	if (this->getActiveScene()==getScene(0))
	{
		this->jugar->collideButton(x / escalatedX, this->getActiveScene()->getSize().getY() - (y / escalatedY));
		this->salir->collideButton(x / escalatedX, this->getActiveScene()->getSize().getY() - (y / escalatedY));
	}

}