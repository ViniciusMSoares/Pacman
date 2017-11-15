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
"0000.0000000000.0000",
"000....000000....000",
"0...00...00...00...0",
"000....000000....000",
"0...00...00...00...0",
"000.00........00.000",
"00......0000......00",
"0..0000..00..0000..0",
"0.000000.00.000000.0",
"0........00........0",
"00000000000000000000"};

int pacmanX = 10;
int pacmanY = 14;
int numVidas = 3;
int pontuacao = 0;

void imprimeMapa(){
	for (int i = 0; i < 20; i++){
		    cout << mapa[i] << "\n";
	}
}

void resetaMapa(){
	for(int i = 0; i < 20 ; i++){
		for(int j = 0; j < 21; j++){
			if (mapa[i][j] == ' ' || mapa[i][j] == 'p'){
				mapa[i][j] = '.';
			}
		}
	}
}

void modificaMapa(int oldX, int oldY){
	mapa[pacmanY][pacmanX] = 'p';
	mapa[oldY][oldX] = ' ';
}

void iniciaMapa(){
	mapa[pacmanY][pacmanX] = 'p';
}

void imprimeVidas(){
	cout << "Vidas: " << numVidas << endl;
}

void imprimePontuacao(){
	cout << "Pontos: " << pontuacao << endl;	
}

void passaDeFase(){
	pontuacao += 100;
	resetaMapa();
	pacmanX = 10;
	pacmanY = 14;
	iniciaMapa();
	imprimeVidas();
	imprimePontuacao();
	imprimeMapa();
}

void marcaPonto(){
	pontuacao += 1;
}

bool mapaVazio(){
	int numPontos = 0;
	
	for(int i = 0; i < 20 ; i++){
		for(int j = 0; j < 21; j++){
			if (mapa[i][j] == '.'){
				numPontos = numPontos + 1;
			}
		}
	}
	
	if(numPontos == 0){
		return true;
	}else{
		return false;
	}
}

bool move(char dir){
	int oldX = pacmanX;
	int oldY = pacmanY;
	switch(dir){
		case 'w':
			pacmanY -= 1;
			break;
		case 'a':
			pacmanX -= 1;
			break;
		case 's':
			pacmanY += 1;
			break;
		case 'd':
			pacmanX += 1;
			break;
	}
	
	if (mapa[pacmanY][pacmanX] == '0') {
		pacmanX = oldX;
		pacmanY = oldY;
		return false;
	}
	
	modificaMapa(oldX, oldY);
	marcaPonto();
	return true;
}

int main() {
	iniciaMapa();
	imprimeVidas();
	imprimePontuacao();
	imprimeMapa();
	
	char comando;
	for (int i = 0; i < 600; i++) {
		cin >> comando;
		move(comando);
		imprimeVidas();
		imprimePontuacao();
		imprimeMapa();
		if(mapaVazio() == 1){
			passaDeFase();
		};
	}
	
}
