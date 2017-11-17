#ifndef CONSTANTS_H
#define CONSTANTS_H

//Propriedades do Mapa:
const int MAP_HEIGHT = 31;
const int MAP_WIDTH = 28;
const char NO_COLLISION_CHARS[3] = { ' ','o','\xfa' };
const int GATE_X = 13;
const int GATE_Y = 12;

// Direcionais
const char DIRECTIONS[4] = { 'w','a','s','d' };

//Simbolos/icones

const char ICONS[4] = { 'v','>','^','<' };
const char GHOST_ICON = 'O';
#endif