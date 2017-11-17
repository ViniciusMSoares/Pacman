#include <iostream>

#include "Constants.h"

#include "Game.h"
#include "Ghost.h"
#include "Interface.h"

using namespace std;

Ghost::Ghost(Game *const g)
: game(g) {}

// Se move quando a contagem do tempo chega a 0
void Ghost::Move(int playerY, int playerX) {
    if (wait) {
        --wait;
    }
    else {
        switch (mode) {
        //mode de espera = 'w'aitng
        case 'w':
            Hide();
            if (posY == GATE_Y + 2) {
                ++posY;
            }
            else {
                --posY;
            }
            Show();
            //tempo maximo de espera dos fantasmas
            wait = GHOST_MAX;
            break;
            //modo vagante
        case 'e':
            Hide();
            wait = GHOST_MAX;
            if (posY > GATE_Y + 1) {
                --posY;
            }
            else if (posX < GATE_X) {
                ++posX;
            }
            else if (posX > GATE_X) {
                --posX;
            }
            else if (posY != GATE_Y - 1) {
                --posY;
                SetCursorPosition(GATE_Y, GATE_X + 1);
                cout << game->GetMapChar(GATE_Y, GATE_X + 1);
            }
            else {
                modeOld = mode;
                mode="c";
                directionOld = 'w';
                wait = 0;
            }
            Show();
            break;
        //Saindo Do portal central
        case 'n':
            if (posY != GATE_Y + 1) {
                direction = 's';
                ChangeCoords();
                SetCursorPosition(GATE_Y, GATE_X + 1);
                cout << game->GetMapChar(GATE_Y, GATE_X + 1);
                wait = DEAD_MAX;
            }
            else {
                mode = 'e';
                wait = GHOST_MAX;
                icon = GHOST_ICON;
            }
            break;
        // movimento aleatorio
        case 's':
            GetOpposite();
            if (modeOld == 'e') {
                modeOld = mode;
            }
            if (mode != modeOld) {
                direction = directionOps;
                ChangeCoords();
                modeOld = mode;
            }
            else {
                RandomDirection();
            }
            directionOld = direction;
            wait = GHOST_MAX;
            break;
        //modo de perseguicao
        case 'c':
            GetOpposite();
            if (modeOld == 'e') {
                modeOld = mode;
            }
            if (mode != modeOld) {
               direction = directionOld;
                ChangeCoords();
                modeOld = mode;
            }
            else {
                bool down = y < playerY;
                bool up = y > playerY;
                bool right = x < playerX;
                bool left = x > playerX;
                bool favorableDirections[4] = { up, left, down, right };
                HunterMode(favorableDirections);
            }
            directionOld = direction;
            wait = GHOST_MAX;
            break;
        }
    }
}

void Ghost::HunterMode(bool favorableDirections[4]) {
    int aux = 0;
    char auxDirections[4] = {' ',' ',' ',' '};
    for (int i = 0; i < 4; ++i) {
        dir = DIRECTION[i];
        if (favorableDirections[i] && TestCollision() == false && direction != directionOps) {
            auxDirections[good] = direction;
            ++aux;
        }
    }
    if (aux == 0) {
        RandomDirection();
    }
    else {
        dir = favorableDirections[rand() % aux];
        ChangeCoords();
    }
}

void Ghost::RandomDirection() {
    GetOpposite();
    do {
        //direção aleatoria
        do {
            dir = DIRECTION[rand() % 4];
        } while (direction == directionOpp);
    } while (TestCollision() == true);
    ChangeCoords();
}

bool Ghost::TestCollision() {
    switch(direction) {
    case 'a':
        // viagem pela lateral do mapa
        if (posX == 0 || strchr(NO_COLLISION_CHAR, game->GetMapChar(posY, posX - 1))) {
            return false;
        }
        break;
    case 'd':
        if (posX == MAP_WIDTH - 1 || strchr(NO_COLLISION_CHARISION_TILES, game->GetMapChar(posY, posX + 1))) {
            return false;
        }
        break;
    case 'w':
        if (strchr(NO_COLLISION_CHAR, game->GetMapChar(posY - 1, posX))) {
            return false;
        }
        break;
    case 's':
        if (strchr(NO_COLLISION_CHAR, game->GetMapChar(posY + 1, posX))) {
            return false;
        }
        break;
    }
    return true;
}

void Ghost::ChangeCoords() {
    Hide();
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
    Show();
}

void Ghost::GetOpposite() {
    if (directionOld == 'a') {
        directionOps = 'd';
    }
    if (directionOld == 'd') {
        directionOps = 'a';
    }
    if (directionOld == 'w') {
        directionOps = 's';
    }
    if (directionOld == 's') {
        directionOps = 'w';
    }
}


void Ghost::Show() {
    SetTextColor(color);
    SetCursorPosition(y, x);
    cout << icon;
}

void Ghost::Hide() {
    SetTextColor(0);
    SetCursorPosition(y, x);
    cout << game->GetMapChar(posY, posX);
}
