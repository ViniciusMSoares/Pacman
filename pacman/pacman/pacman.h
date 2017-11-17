#ifndef PACMAN_H
#define PACMAN_H

class Game;

class Pacman {
private:
    int y, x;
    int yOld, xOld;
    int yInit, xInit;
    int wait;
    int left;
    int score;
    int hiScore;
    int lives;
    int color;
    char dir;
    char dirOld;
    char icon;

    Game *game;

public:
    Pacman(Game *const g);
    void Move();
    void GetDirection();
    bool TestForCollision();
    void PrintScore(int);
    void PrintLives();
    void Dead();
    void Show();
    void Hide();

    int GetY()     { return y;     }
    int GetX()     { return x;     }
    int GetYInit() { return yInit; }
    int GetXInit() { return xInit; }
    int GetLeft()  { return left;  }
    int GetLives() { return lives; }

    void SetY(int y)         { this->y = y;   }
    void SetX(int x)         { this->x = x;   }
    void SetYInit(int y)     { yInit = y;     }
    void SetXInit(int x)     { xInit = x;     }
    void SetWait(int w)      { wait = w;      }
    void SetLeft(int l)      { left = l;      }
    void SetScore(int s)     { score = s;     }
    void SetLives(int l)     { lives = l;     }
    void SetColor(int c)     { color = c;     }
    void SetDirOld(char d)   { dirOld = d;    }
    void SetIcon(char i)     { icon = i;      }
};

#endif
