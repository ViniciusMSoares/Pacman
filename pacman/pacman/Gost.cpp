#include <iostream>

#include "Constants.h"
#include "Game.h"
#include "Ghost.h"
#include "Interface.h"

using namespace std;

Ghost::Ghost(Game *const g)
	: game(g) {}

void Ghost::move(int playerPosY, int playerPosX) {

	bool down = posY < playerPosY;
	bool up = posY > playerPosY;
	bool right = posX < playerPosX;
	bool left = posX > playerPosX;

	if (agressiveMode == true) {
		bool directionProb[4] = { up,left,down,right };
		persecution(directionProb);
	}
	else {
		randonMoviment();
	}
}

void Ghost::persecution(bool directionFav[4]) {
	int aux = 0;
	char bestDirection[4] = { ' ',' ',' ',' ' };
	for (int i = 0; i < 4; ++i) {
		direction = DIRECTIONS[i];
		if (directionFav[i] && collisionTest() == false && direction != directionOpp) {
			bestDirection[aux] = direction;
			++aux;
		}
	}
	if (aux == 0) {
		randonMoviment();
	}
	else {
		direction = bestDirection[rand() % aux];
		coordsChange();
	}
}

void Ghost::randonMoviment() {
	getOpp();
	do {
		do {
			direction = DIRECTIONS[rand() % 4];
		} while (direction == directionOpp);
	} while (collisionTest() == true);
	coordsChange();
}

//pega a direcão oposta
void Ghost::getOpp() {
	if (directionOld == 'a') {
		directionOpp = 'd';
	}
	if (directionOld == 'd') {
		directionOpp = 'a';
	}
	if (directionOld == 'w') {
		directionOpp = 's';
	}
	if (directionOld == 's') {
		directionOpp = 'w';
	}
}
void Ghost::coordsChange() {
	if (direction == 'a') {
		if (posX == 0) {
			posX = MAP_WIDTH - 1;
		}
		else {
			--posX;
		}
	}
	if (direction == 'd') {
		if (posX == MAP_WIDTH - 1) {
			posX = 0;
		}
		else {
			++posX;
		}
	}
	if (direction == 'w') {
		--posY;
	}
	if (direction == 's') {
		++posY;
	}
}

bool Ghost::collisionTest() {
	switch (direction) {
	case 'a':
		if (posX == 0 || strchr(NO_COLLISION_CHARS, game->getMapPositionChar(posY, posX - 1))) {
			return false;
		}
		break;
	case 'd':
		if (posX == MAP_WIDTH - 1 || strchr(NO_COLLISION_CHARS, game->getMapPositionChar(posY, posX + 1))) {
			return false;
		}
		break;
	case 'w':
		if (strchr(NO_COLLISION_CHARS, game->getMapPositionChar(posY - 1, posX))) {
			return false;
		}
		break;
	case 's':
		if (strchr(NO_COLLISION_CHARS, game->getMapPositionChar(posY + 1, posX))) {
			return false;
		}
		break;
	}
	return true;
}