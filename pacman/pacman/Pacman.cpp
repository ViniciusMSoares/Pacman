#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>

#include "Constants.h"

#include "Game.h"
#include "Pacman.h"
#include "Interface.h"

using namespace std;

Pacman::Pacman(Game *const g)
: game(g) {
    hiScore = 0;
}

void Pacman::Move() {
    //espera contador para iniciar movimento
    if (wait) {
        --wait;
    }
    else {
        GetDirection();
        if (TestCollision() == false) {
            //setagem do movimento
            SetCursorPosition(posYOld, posXOld);
            cout << game->GetMapChar(posYOld, posXOld);
            //coleta de pontinhos
            if (game->GetMapChar(posY, posX) != ' ') {
                int scoreInc = 10;
                PrintScore(scoreInc);
                game->SetMapChar(posY, posX, ' ');
                --left;
            }
            Show();
            directionOld = direction;
            //espera de tempo (evitar full speed)
            wait = PACMAN_MAX;
        }
    }
}

void Pacman::GetDirection() {
    direction = 'x';
    // chekagem do teclado
    if (_kbhit()) {
        direction = tolower(_getch());
    }
    // se nao for wasd continua o movimento antigo
    if (!strchr(DIRECTION, direction)) {
        direction = directionOld;
    }
}

bool Pacman::TestCollision() {
    posXold = posX;
    posYold = posY;

    switch (direction) {
    case 'a':
        if (posX == 0) {
            posX = MAP_WIDTH - 1;
            icon = ICONS[1];
        }
        else if (strchr(NO_COLLISION_CHAR, game->GetMapChar(posY, posX - 1))) {
            --posX;
            icon = ICONS[1];
        }
        break;
    case 'd':
        //travessia lateral de tela
        if (posX == MAP_WIDTH - 1) {
            posX = 0;
            icon = ICONS[3];
        }
        else if (strchr(NO_COLLISION_CHAR, game->GetMapChar(posY, posX + 1))) {
            ++posX;
            icon = ICONS[3];
        }
        break;
    case 'w':
        if (strchr(NO_COLLISION_CHAR, game->GetMapChar(posY - 1, posX))) {
            --posY;
            icon = ICONS[0];
        }
        break;
    case 's':
        if (strchr(NO_COLLISION_CHAR, game->GetMapChar(posY + 1, posX))) {
            ++posY;
            icon = ICONS[2];
        }
    }
    // if coordinates were not changed, there was a collision
    if (posX == posXold && posY == posYold) {
        return true;
    }
    return false;
}

void Pacman::PrintScore(int scoreInc) {
    score += scoreInc;
    SetTextColor(WHITE);
    SetCursorPosition(-2, 0);
    cout << setw(7) << score;
    if (score > hiScore) {
        hiScore = score;
        cout << setw(11) << hiScore;
    }
}

void Pacman::PrintLives() {
    SetTextColor(WHITE);
    SetCursorPosition(MAP_HEIGHT, 2);
    for (int i = 1; i < lives; ++i) {
        cout << ICONS[1] << " ";
    }
    cout << " ";
}

void Pacman::Dead() {
    Sleep(1000);
    game->HideAll();
    for (int i = 0; i < 8; ++i) {
        icon = ICONS[i % 4];
        Show();
        Sleep(100);
    }
    Hide();
    Sleep(500);
    --lives;
    if (lives != 0) {
        game->InitAll();
        game->ShowAll();
        PrintLives();
        game->PrintStart();
    }
    else {
        game->PrintGameOver();
    }
}

void Pacman::Show() {
    SetTextColor(WHITE);
    SetCursorPosition(posY, posX);
    cout << icon;
}

void Pacman::Hide() {
    SetCursorPosition(posY, posX);
    cout << game->GetMapChar(posY, posX);
}
