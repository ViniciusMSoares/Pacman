#ifndef GHOST_H
#define GHOST_H

class Game;

class Ghost {
	private:
		int posX, posY;
		int posXinit, posYinit;
		char direction;
		char directionOld;
		char directionOpp;
		bool agressiveMode;
		char icon;
		
		Game *game;

	public:
		Ghost(Game *const g);
		void move(int, int);
		void persecution(bool[4]);
		void randonMoviment();
		bool collisionTest();
		void coordsChange();
		void getOpp();

		int getPosX() { return posX; }
		int getPosY() { return posY; }
		bool getMode() { return agressiveMode; }
		int getPosXinit() { return posXinit; }
		int getPosYinit() { return posYinit; }

		void setMode(bool mode) { agressiveMode = mode; }
		void setPosX(int posX) { this->posX = posX; }
		void setPosY(int posY) { this->posY = posY; }
		void SetDirOpp(char d) { directionOpp = d; }
		void setXinit(int posXi) { posXinit = posXi; }
		void setYinit(int posYi) { posYinit = posYi; }

};
#endif