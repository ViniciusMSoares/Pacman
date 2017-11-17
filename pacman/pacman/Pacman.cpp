#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>

#include "Constants.h"

#include "Game.h"
#include "Pacman.h"
#include "SetConsoleAttributes.h"

using namespace std;

Pacman::Pacman(Game *const g)
: game(g) {
    hiScore = 0;
}

// check for user input every time the wait timer reaches 0
void Pacman::Move() {
    if (wait) {
        --wait;
    }
    else {
        GetDirection();
        if (TestForCollision() == false) {
            // replace old coordinates with a space
            SetCursorPosition(yOld, xOld);
            cout << game->GetLevel(yOld, xOld);
            // if the player picked up a pellet
            if (game->GetLevel(y, x) != ' ') {
                int scoreInc = 10;
                PrintScore(scoreInc);
                game->SetLevel(y, x, ' ');
                --left;
            }
            Show();
            dirOld = dir;
            wait = PACMAN_MAX;
        }
    }
}

void Pacman::GetDirection() {
    dir = 'x';
    // check if the user has entered 'w', 'a', 's' or 'd'
    if (_kbhit()) {
        dir = tolower(_getch());
    }
    // if not, try moving in the same direction as before
    if (!strchr(ALL_DIRS, dir)) {
        dir = dirOld;
    }
}

bool Pacman::TestForCollision() {
    // save old coordinates
    xOld = x;
    yOld = y;
    // if the character in front of the player is a space, move in the appropriate direction
    switch (dir) {
    case 'a':
        // if travelling through the tunnel
        if (x == 0) {
            x = LEVEL_WIDTH - 1;
            icon = ICONS[1];
        }
        else if (strchr(NO_COLLISION_TILES, game->GetLevel(y, x - 1))) {
            --x;
            icon = ICONS[1];
        }
        break;
    case 'd':
        // if travelling through the tunnel
        if (x == LEVEL_WIDTH - 1) {
            x = 0;
            icon = ICONS[3];
        }
        else if (strchr(NO_COLLISION_TILES, game->GetLevel(y, x + 1))) {
            ++x;
            icon = ICONS[3];
        }
        break;
    case 'w':
        if (strchr(NO_COLLISION_TILES, game->GetLevel(y - 1, x))) {
            --y;
            icon = ICONS[0];
        }
        break;
    case 's':
        if (strchr(NO_COLLISION_TILES, game->GetLevel(y + 1, x))) {
            ++y;
            icon = ICONS[2];
        }
    }
    // if coordinates were not changed, there was a collision
    if (x == xOld && y == yOld) {
        return true;
    }
    return false;
}

void Pacman::PrintScore(int scoreInc) {
    score += scoreInc;
    SetTextColor(WHITE);
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

void Pacman::PrintLives() {
    SetTextColor(color);
    SetCursorPosition(LEVEL_HEIGHT, 2);
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
        game->PrintReady();
    }
    else {
        game->PrintGameOver();
    }
}

void Pacman::Show() {
    SetTextColor(color);
    SetCursorPosition(y, x);
    cout << icon;
}

void Pacman::Hide() {
    SetCursorPosition(y, x);
    cout << game->GetLevel(y, x);
}
