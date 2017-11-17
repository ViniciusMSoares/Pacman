#ifndef PACMAN_H
#define PACMAN_H

class Game;

class Pacman {
private:
    int posY, posX;
    int posYold, posXold;
    int posYInit, posXInit;
    int wait;
    int left;
    int score;
    int hiScore;
    int lives;
    int color;
    char direction;
    char directionOld;
    char icon;

    Game *game;

public:
    Pacman(Game *const g);
    void Move();
    void GetDirection();
    bool TestCollision();
    void PrintScore(int);
    void PrintLives();
    void Dead();
    void Show();
    void Hide();

    int GetPosY()     { return posY;     }
    int GetPosX()     { return posX;     }
    int GetPosYInit() { return posYInit; }
    int GetPosXInit() { return posXInit; }
    int GetLeft()  { return left;  }
    int GetLives() { return lives; }

    void SetPosY(int y)         { posY = y;   }
    void SetPosX(int x)         { posX = x;   }
    void SetPosYInit(int y)     { posYInit = y;     }
    void SetPosXInit(int x)     { posxInit = x;     }
    void SetWait(int w)         { wait = w;      }
    void SetLeft(int l)         { left = l;      }
    void SetScore(int s)        { score = s;     }
    void SetLives(int l)        { lives = l;     }
    void SetColor(int c)        { color = c;     }
    void SetDirectionOld(char d){ directionOld = d;    }
    void SetIcon(char i)        { icon = i;      }
};

#endif
