#ifndef GAME_H
#define GAME_H

#include "Constants.h"

class Pacman;
class Ghost;

class Game {
private:
    char map[MAP_HEIGHT][MAP_WIDTH];
    int oneUpTimer = ONE_UP_MAX;
    int oneUpColor = WHITE;
    int ghostModeTimer = MODE_MAX;

    Pacman* player;
    Ghost* ghosts[4];

    void MainLoop();

public:
    Game();
    ~Game();
    void Go();

    void LoadMap();
    void NextLevel();
    void PrintReady();
    void PrintGameOver();

    void MoveGhosts();
    void CheckDeath();
    void ShowAll();
    void HideAll();
    void InitAll();
	void UpdateTimers();

    char GetMapChar(int y, int x) { return map[y][x];    }
    int GetOneUpTimer()         { return oneUpTimer;     }
    int GetOneUpColor()         { return oneUpColor;     }
    int GetGhostModeTimer()     { return ghostModeTimer; }

    void SetMapChar(int y, int x, char c) { map[y][x] = c;    }
    void SetOneUpTimer(int t)           { oneUpTimer = t;     }
    void SetOneUpColor(int c)           { oneUpColor = c;     }
    void SetGhostModeTimer(int t)       { ghostModeTimer = t; }
};

#endif
