#ifndef GHOST_H
#define GHOST_H

class Game;

class Ghost {
private:
    int posX,posY;
    int posXinit, posYinit;
    int wait;
    int color;
    char direction;
    char directionOld;
    char directionOps;
    char mode;
    char modeOld;
    char icon;

    Game *game;

public:
    Ghost(Game *const g);
    void Move(int, int);
    void HunterMode(bool[4]);
    void RandomDirection();
    bool TestCollision();
    void coordsChanges();
    void GetOpposite();
    void Show();
    void Hide();

    int GetPosY()         { return y;         }
    int GetPosX()         { return x;         }
    int GetPosYInit()     { return yInit;     }
    int GetPosXInit()     { return xInit;     }
    char GetMode()     { return mode;      }

    void SetPosY(int y)         { this->y = y;   }
    void SetPosX(int x)         { this->x = x;   }
    void SetPosYInit(int y)     { yInit = y;     }
    void SetPosXInit(int x)     { xInit = x;     }
    void SetWait(int w)      { wait = w;      }
    void SetDirectionOpp(char d)   { dirOpp = d;    }
    void SetMode(char m)     { mode = m;      }
    void SetModeOld(char m)  { modeOld = m;   }
    void SetIcon(char i)     { icon = i;      }
	void SetColor(int cor) { color = cor; }
};

#endif
