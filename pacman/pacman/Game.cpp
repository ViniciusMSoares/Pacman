#include<iostream>
#include <Windows.h>

#include"Constants.h"
#include "Game.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Interface.h"

using namespace std;

Game::Game() {
	SetWindowTitle("PAC++MAN");
	SetWindowSize(MAP_HEIGHT + 4, MAP_WIDTH);
	player = new Pacman(this);
	for (int i=0;i<4;++i) {
		ghosts[i] = new Ghost(this);
	}
}

Game::~Game() {
	delete player;
	for (int i = 0; i < 4; ++i) {
		delete ghosts[i];
	}
}

void Game::Start() {
	while (true) {
		MainLoop();
	}
}

void Game::MainLoop() {
	player->setScore(0);
	player->setLifes(3);
	bool gamerOver = false;
	for (int mapNum = 1; mapNum <= 255; ++mapNum) {
		loadMap();
		//se for 0 e pq o player ainda ao mexeu no jogo
		while (player->getLeft() != 0) {
			player->move();
			checkDeath();
			if (player->getLifes() == 0) {
				gamerOver = true;
				break;
			}
			moveGhosts();
			checkDeath();
			if (player->getLifes() == 0) {
				gamerOver = true;
				break;
			}
		}
		if (gamerOver == true) {
			break;
		}
	}
}

void Game::loadMap() {
	char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
		"1555555555555555555555555552",
		"6............^^............6",
		"6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
		"6.^  ^.^   ^.^^.^   ^.^  ^.6",
		"6.#%%$.#%%%$.#$.#%%%$.#%%$.6",
		"6..........................6",
		"6.!%%@.!@.!%%%%%%@.!@.!%%@.6",
		"6.#%%$.^^.#%%@!%%$.^^.#%%$.6",
		"6......^^....^^....^^......6",
		"355552.^#%%@ ^^ !%%$^.155554",
		"     6.^!%%$ #$ #%%@^.6     ",
		"     6.^^    B     ^^.6     ",
		"     6.^^ 155&&552 ^^.6     ",
		"555554.#$ 6      6 #$.355555",
		"      .   6I   C 6   .      ",
		"555552.!@ 6  P   6 !@.155555",
		"     6.^^ 35555554 ^^.6     ",
		"     6.^^          ^^.6     ",
		"     6.^^ !%%%%%%@ ^^.6     ",
		"155554.#$ #%%@!%%$ #$.355552",
		"6............^^............6",
		"6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
		"6.#%@^.#%%%$.#$.#%%%$.^!%$.6",
		"6...^^.......X .......^^...6",
		"6%@.^^.!@.!%%%%%%@.!@.^^.!%6",
		"6%$.#$.^^.#%%@!%%$.^^.#$.#%6",
		"6......^^....^^....^^......6",
		"6.!%%%%$#%%@.^^.!%%$#%%%%@.6",
		"6.#%%%%%%%%$.#$.#%%%%%%%%$.6",
		"6..........................6",
		"3555555555555555555555555554" };
	char impressor;
	SetCursorPosition(-3, 9);
	cout << "HIGH SCORE";
	player->printScore(0);
	SetCursorPosition(0, 0);
	player->setLeft(0);
	for (int y = 0; y < MAP_HEIGHT; ++y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			impressor = map[y][x];
			switch (impressor){
			case 'X':
				player->setXinit(x);
				player->setYinit(y);
				map[y][x] = ' ';
				break;
			case 'B':
				ghosts[0]->setXinit(x);
				ghosts[0]->setYinit(y);
				ghosts[0]->SetDirOpp('s');
				map[y][x] = ' ';
				break;
			case 'P':
				ghosts[1]->setXinit(x);
				ghosts[1]->setYinit(y);
				map[y][x] = ' ';
				break;
			case 'I':
				ghosts[2]->setXinit(x);
				ghosts[2]->setYinit(y);
				map[y][x] = ' ';
				break;
			case 'C':
				ghosts[2]->setXinit(x);
				ghosts[2]->setYinit(y);
				map[y][x] = ' ';
				break;
			case '.':
				map[y][x] = char(250);
				player->setLeft(player->getLeft() + 1);
				break;
			case ' ':
				map[y][x] = impressor;
				break;
			case '&':
				impressor = '%';
				break;
			default:
				break;
			}
			if (impressor == '1') {
				map[y][x] = char(201);
			}
			else if (impressor == '2') {
				map[y][x] = char(187);
			}
			else if (impressor == '3') {
				map[y][x] = char(200);
			}
			else if (impressor == '4') {
				map[y][x] = char(188);
			}
			else if (impressor == '5') {
				map[y][x] = char(205);
			}
			else if (impressor == '6') {
				map[y][x] = char(186);
			}
			else if (impressor == '!') {
				map[y][x] = char(218);
			}
			else if (impressor == '@') {
				map[y][x] = char(191);
			}
			else if (impressor == '#') {
				map[y][x] = char(192);
			}
			else if (impressor == '$') {
				map[y][x] = char(217);
			}
			else if (impressor == '%') {
				map[y][x] = char(196);
			}
			else if (impressor == '^') {
				map[y][x] = char(179);
			}
			cout << map[y][x];
		}
	}
	player->printLives();
}


void Game::checkDeath() {
	for (int i = 0; i < 4; ++i) {
		if (player->getPosX() == ghosts[i]->getPosX() && player->getPosY() == ghosts[i]->getPosY()) {
			player->dead();
		}
	}
}

void Game::gameOverMensage() {
	SetCursorPosition(17, 9);
	cout << "GAME  OVER";
	Sleep(1000);
}

void Game::moveGhosts() {
	if (player->getLeft() == 235) {
		ghosts[1]->setMode(false);
	}
	if (player->getLeft() == 200) {
		ghosts[2]->setMode(false);
	}
	if (player->getLeft() == 165) {
		ghosts[3]->setMode(false);
	}
	for (int i = 0; i < 4; ++i) {
		ghosts[i]->move(player->getPosY(), player->getPosX());
	}
}
