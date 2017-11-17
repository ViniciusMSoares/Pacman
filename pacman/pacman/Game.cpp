#include <iostream>
#include <Windows.h>

#include "Constants.h"

#include "Game.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Interface.h"

using namespace std;

Game::Game() {
    SetWindowTitle("PLP - PACMAN");
    SetWindowSize(MAP_HEIGHT + 4, MAP_WIDTH);
    SetCursorVisibility(false);
    player = new Pacman(this);
    for (int i = 0; i < 4; ++i) {
        ghosts[i] = new Ghost(this);
		ghosts[i]->SetColor(WHITE);
    }
}

Game::~Game() {
    delete player;
    for (int i = 0; i < 4; ++i) {
        delete ghosts[i];
    }
}

void Game::Go() {
    while (true) {
        MainLoop();
    }
}

void Game::MainLoop() {
    player->SetScore(0);
    player->SetLives(3);
    bool gameOver = false;
    for (int levelNum = 1; levelNum <= 255; ++levelNum) {
        LoadMap();
        //iniciacao do player no mapa
        while (player->GetLeft() != 0) {
            player->Move();
            CheckForDeath();
            if (!player->GetLives()) {
                gameOver = true;
                break;
            }
            MoveGhosts();
            CheckForDeath();
            if (!player->GetLives()) {
                gameOver = true;
                break;
            }
			UpdateTimers();
        }
        if (gameOver) {
            break;
        }
        NextLevel();
    }
}

void Game::UpdateTimers() {
	for (int i = 0; i < 4; ++i) {
		ghost[i]->SetColor(WHITE);
		if (ghosts[i]->GetMode() == 'r') {
			ghosts[i]->SetModeOld(ghosts[i]->GetMode());
			ghosts[i]->SetMode('c');
		}
	}
	ShowAll();
	
	if (oneUpTimer) {
		--oneUpTimer;
	}
	else {
		oneUpTimer = ONE_UP_MAX;
	}
	
	if (ghostModeTimer) {
		--ghostModeTimer;
		if (ghostModeTimer == MODE_MAX / 4) {
			for (int i = 0; i < 4; ++i) {
				if (ghosts[i]->GetMode() == 'c') {
					ghosts[i]->SetMode('s');
				}
			}
		}
	}
	else {
		for (int i = 0; i < 4; ++i) {
			if (ghosts[i]->GetMode() == 's') {
				ghosts[i]->SetMode('c');
			}
		}
		ghostModeTimer = MODE_MAX;
	}
	Sleep(15);
}

void Game::LoadMap() {
    char charMap[MAP_HEIGHT][MAP_WIDTH + 1] = {
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
        "3555555555555555555555555554"};
    char printer;
    SetTextColor(WHITE);
    SetCursorPosition(-3, 9);
    cout << "HIGH SCORE";
    player->PrintScore(0);
    SetCursorPosition(0, 0);
    player->SetLeft(0);
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            printer = charMap[y][x];
            SetTextColor(0);
            switch (printer) {
            case 'X':
                player->SetYInit(y);
                player->SetXInit(x);
                map[y][x] = ' ';
                break;
            case 'B':
                ghosts[VINICIUS]->SetPosYInit(y);
                ghosts[VINICIUS]->SetPosXInit(x);
                ghosts[VINICIUS]->SetDirectionOpp('s');
                map[y][x] = ' ';
                break;
            case 'P':
                ghosts[WESLEY]->SetPosYInit(y);
                ghosts[WESLEY]->SetPosXInit(x);
                map[y][x] = ' ';
                break;
            case 'I':
                ghosts[ITALO]->SetPosYInit(y);
                ghosts[ITALO]->SetPosXInit(x);
                map[y][x] = ' ';
                break;
            case 'C':
                ghosts[JOAO]->SetPosYInit(y);
                ghosts[JOAO]->SetPosXInit(x);
                level[y][x] = ' ';
                break;
            case '.':
                SetTextColor(WHITE);
                map[y][x] = char(250);
                player->SetLeft(player->GetLeft() + 1);
                break;
            case ' ':
                map[y][x] = printer;
                break;
            case '&':
                SetTextColor(WHITE);
                printer = '%';
            }
            if (printer == '1') {
                map[y][x] = char(201);
            }
            else if (printer == '2') {
                map[y][x] = char(187);
            }
            else if (printer == '3') {
                map[y][x] = char(200);
            }
            else if (printer == '4') {
                map[y][x] = char(188);
            }
            else if (printer == '5') {
                map[y][x] = char(205);
            }
            else if (printer == '6') {
                map[y][x] = char(186);
            }
            else if (printer == '!') {
                map[y][x] = char(218);
            }
            else if (printer == '@') {
                map[y][x] = char(191);
            }
            else if (printer == '#') {
                map[y][x] = char(192);
            }
            else if (printer == '$') {
                map[y][x] = char(217);
            }
            else if (printer == '%') {
                map[y][x] = char(196);
            }
            else if (printer == '^') {
                map[y][x] = char(179);
            }
            cout << map[y][x];
        }
        SetCursorPosition(y + 1, 0);
    }
    InitAll();
    ShowAll();
    player->PrintLives();
    PrintReady();
}

void Game::NextLevel() {
    Sleep(1000);
    HideAll();
    SetCursorPosition(12, 13);
    cout << "  ";
    for (int i = 0; i < 4; ++i) {
        SetScreenColor(WHITE);
        player->Show();
        Sleep(200);
        SetScreenColor(0);
        player->Show();
        Sleep(200);
    }
    SetCursorPosition(0, 0);
    InitAll();
}

void Game::PrintReady() {
    SetTextColor(WHITE);
    SetCursorPosition(17, 11);
    cout << "READY!";
    Sleep(2000);
    SetCursorPosition(17, 11);
    cout << "      ";
}

void Game::PrintGameOver() {
    SetCursorPosition(17, 9);
    SetTextColor(WHITE);
    cout << "GAME  OVER";
    Sleep(1000);
}

void Game::MoveGhosts() {
    // check for ghost mode changes
    if (player->GetLeft() == 235 && ghosts[WESLEY]->GetMode() == 'w') {
        ghosts[WESLEY]->SetMode('e');
    }
    if (player->GetLeft() == 200 && ghosts[ITALO]->GetMode() == 'w') {
        ghosts[ITALO]->SetMode('e');
    }
    if (player->GetLeft() == 165 && ghosts[JOAO]->GetMode() == 'w') {
        ghosts[JOAO]->SetMode('e');
    }
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->Move(player->GetY(), player->GetPosX());
    }
    ShowAll();
}


void Game::CheckDeath() {
    for (int i = 0; i < 4; ++i) {
        if (player->GetPosX() == ghosts[i]->GetPosX() && player->GetPosY() == ghosts[i]->GetPosY()){
                player->Dead();
        }
    }
}

void Game::ShowAll() {
    player->Show();
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->Show();
    }
}

void Game::HideAll() {
    player->Hide();
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->Hide();
    }
}

void Game::InitAll() {
    player->SetPosY(player->GetPosYInit());
    player->SetPosX(player->GetPosXInit());
    player->SetColor(WHITE);
    player->SetIcon(ICONS[1]);
    player->SetDirectionOld('a');
    player->SetWait(0);
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->SetPosY(ghosts[i]->GetPosYInit());
        ghosts[i]->SetPosX(ghosts[i]->GetPosXInit());
        ghosts[i]->SetMode('w');
        ghosts[i]->SetWait(0);
        ghosts[i]->SetIcon(GHOST_ICON);
    }
    ghosts[VINICIUS]->SetMode('c');
    ghosts[VINICIUS]->SetModeOld('c');
    if (player->GetLeft() <= 235) {
        ghosts[WESLEY]->SetMode('e');
    }
    if (player->GetLeft() <= 200) {
        ghosts[ITALO]->SetMode('e');
    }
    if (player->GetLeft() <= 165) {
        ghosts[JOAO]->SetMode('e');
    }
}
