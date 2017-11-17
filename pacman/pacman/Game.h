#ifndef GAME_H
#define GAME_H

#include "Constants.h"

class Pacman;
class Ghost;

class Game{
	private:
		char map[MAP_HEIGHT][MAP_WIDTH];

		Pacman* player;
		Ghost* ghosts[4];

		void MainLoop();

	public:
		Game();
		~Game();
		void Start();

		void loadMap();
		void gameOverMensage();
		void winsMensage();

		void moveGhosts();
		void checkDeath();

		char getMapPositionChar(int posX, int posY) { return map[posX][posY]; }

		void setMapPositionChar(int posY, int posX, char c) { map[posY][posX] = c; }

};
#endif