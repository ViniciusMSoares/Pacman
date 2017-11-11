#include <iostream>

using namespace std;

char mapa[20][21] = {
"00000000000000000000",
"0...00...00...00...0",
"000....000000....000",
"0...00...00...00...0",
"000.00.000000.00.000",
"00......0000......00",
"0..0000..00..0000..0",
"0.000000.00.000000.0",
"0........00........0",
"00000000000000000000",
"00000000000000000000",
"0...00...00...00...0",
"000....000000....000",
"0...00...00...00...0",
"000.00........00.000",
"00......0000......00",
"0..0000..00..0000..0",
"0.000000.00.000000.0",
"0........00........0",
"00000000000000000000"};

int pacmanX = 14;
int pacmanY = 11;

void imprimeMapa(){
	for (int i = 0; i < 20; i++){
		    cout << mapa[i] << "\n";
	}
}

void modificaMapa(int oldX, int oldY){
	mapa[pacmanY][pacmanX] = 'p';
	mapa[oldY][oldX] = ' ';
}

void move(char dir){
	int x = pacmanX;
	int y = pacmanY;
	switch(dir){
		case 'w':
			pacmanY += 1;
		case 'a':
			pacmanX -= 1;
		case 's':
			pacmanY -= 1;
		case 'd':
			pacmanX += 1;
	}
	modificaMapa(x, y);
}

int main() {
	
	imprimeMapa();
	
	char comando;
	for (int i = 0; i < 100; i++) {
		cin >> comando;
		move(comando);
		imprimeMapa();
	}

	
}
