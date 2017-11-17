#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Windows.h>

// Propriedades do mapa
const int MAP_HEIGHT = 31;
const int MAP_WIDTH  = 28;
const char NO_COLLISION_CHAR[3] = {' ','\xfa'};
//portao central dos fantasmas
const int GATE_X = 13;
const int GATE_Y = 12;

// icones (direcionais e personagens)
const char DIRECTION[4]     = {'w','a','s','d'};
const char ICONS[4]        = {'v','>','^','<'};
const char GHOST_ICON      = 'O';

// Cor
const int WHITE     = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

// timers (solucao de todos os problemas)
const int ONE_UP_MAX  = 13;
const int PACMAN_MAX  = 8;
const int GHOST_MAX   = 10;
const int RUN_MAX     = 16;
const int DEAD_MAX    = 3;
const int MODE_MAX    = 1000;

// Ghost Names
const int VINICIUS = 0;
const int WESLEY  = 1;
const int ITALO   = 2;
const int JOAO  = 3;

#endif