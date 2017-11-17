#ifndef PACMAN_H
#define PACMAN_H

class Game;

class Pacman {
	private:
		int posX, posY;
		int posXold, posYold;
		int posXinit, posYinit;
		int lifes;
		int left;
		int score;
		int hiScore;
		char direction;
		char directionOld;
		char icon;//simbolizacao

		Game *game;

	public:
		Pacman(Game *const g);
		void move();
		bool collisionTest();
		void dead();
		void getDirection();
		void printScore(int);
		void printLives();

		int getPosX() { return posX; }
		int getPosY() { return posY; }
		int getLeft() { return left; }
		int getPosXinit() { return posXinit; }
		int getPosYinit() { return posYinit; }
		int getLifes() { return lifes; }

		void setPosX(int posX) { this->posX = posX; }
		void setPosY(int posY) { this->posY = posY; }
		void setXinit(int posXinit) { this->posXinit = posXinit; }
		void setYinit(int posYinit) { this->posYinit = posYinit; }
		void setLifes(int newLife) { lifes = newLife; }
		void setScore(int score) { this->score = score; }
		void setDirectionOld(char dir) { directionOld = dir; }
		void setIcon(char i) { icon = i; }
		void setLeft(int l) { left = l; }
};
#endif