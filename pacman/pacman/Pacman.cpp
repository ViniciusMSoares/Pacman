#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>

#include "Constants.h"
#include "Game.h"
#include "pacman.h"
#include "Interface.h"

using namespace std;

Pacman::Pacman(Game *const g): game(g) {
	hiScore = 0;
}

void Pacman::move() {
	getDirection();
	if (collisionTest() == false) {
		SetCursorPosition(posYold, posXold);
		cout << game->getMapPositionChar(posYold, posXold);
		
		if (game->getMapPositionChar(posY, posX) != ' ') {
			printScore(10);
		}
		directionOld = direction;
		//game->SetLevel(y, x, ' ');
	}
}

void Pacman::getDirection() {
	direction = 'x';
	//checagem wasd
	if (_kbhit()) {
		direction = tolower(_getch());
	}
	if (!strchr(DIRECTIONS, direction)) {
		direction = directionOld;
	}
}

bool Pacman::collisionTest() {
	//salva coordenadas
	posXold = posX;
	posYold = posY;
	switch (direction) {
	case 'a':
		if (posX == 0) {
			posX = MAP_WIDTH - 1;
			icon = ICONS[1];
		}
		else if (strchr(NO_COLLISION_CHARS, game->getMapPositionChar(posY, posX - 1))) {
			--posX;
			icon = ICONS[1];
		}
		break;
	case 'd':
		if (posX == MAP_WIDTH - 1) {
			posX = 0;
			icon = ICONS[3];
		}
		else if (strchr(NO_COLLISION_CHARS, game->getMapPositionChar(posY, posX + 1))) {
			++posX;
			icon = ICONS[3];
		}
		break;
	case 'w':
		if (strchr(NO_COLLISION_CHARS, game->getMapPositionChar(posY - 1, posX))) {
			--posY;
			icon = ICONS[0];
		}
		break;
	case 's':
		if (strchr(NO_COLLISION_CHARS, game->getMapPositionChar(posY + 1, posX))) {
			++posY;
			icon = ICONS[2];
		}
	}
	//se as coordenadas nao mudaram e pq teve colisao
	if (posX == posXold && posY == posYold) {
		return true;
	}
	return false;
}

void Pacman::printScore(int scoreInc) {
	score += scoreInc;
	SetCursorPosition(-2, 0);
	if (score == 0) {
		cout << setw(7) << "00";
	}
	else {
		cout << setw(7) << score;
	}
	if (score > hiScore) {
		hiScore = score;
		cout << setw(11) << hiScore;
	}
}

void Pacman::printLives() {
	SetCursorPosition(MAP_HEIGHT, 2);
	for (int i = 1; i < lifes; ++i) {
		cout << 0 << " ";
	}
	cout << " ";
}

void Pacman::dead() {
	--lifes;
	if (lifes == 0) {
		game->gameOverMensage();
	}
	else {
		//reinicia jogo
	}
}