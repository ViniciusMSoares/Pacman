#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

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

int numVidas = 3;
int pontuacao = 0;
int pacmanX = 14;
int pacmanY = 10;
int monstro1X = 2;
int monstro1Y = 5;
bool espacoComPontoMonstro1 = true;
int listaRecords[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
string listaPlayers[10] = {"------", "------","------", "------", "------",
 "------", "------", "------", "------", "------"};

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

bool ehParede(int x, int y){
	if (mapa[x][y] == '0'){
		return true;
	}else{
		return false;
	}
}

bool ehPonto(int x, int y){
	if (mapa[x][y] == '.'){
		return true;
	}else{
		return false;
	}
}

void modificaMapa(int oldX, int oldY){
	mapa[pacmanX][pacmanY] = 'p';
	mapa[oldX][oldY] = ' ';
}

void iniciaMapa(){
	mapa[pacmanX][pacmanY] = 'p';
	mapa[monstro1X][monstro1Y] = 'm';
}

void resetaPosicoes(){
	// bug aqui: quando o monstro come o pacman se ele tiver com um ponto em cima
	// ele desaparece.
	if(espacoComPontoMonstro1 == 1){
		mapa[monstro1X][monstro1Y] = '.';
	}else{
		mapa[monstro1X][monstro1Y] = ' ';
	}
	mapa[pacmanX][pacmanY];
	
	monstro1X = 2;
	monstro1Y = 5;
	pacmanX = 14;
	pacmanY = 10;
}

void imprimeVidas(){
	cout << "Vidas: " << numVidas << endl;
}

void imprimePontuacao(){
	cout << "Pontos: " << pontuacao << endl;	
}

void estaMorto(){
	if (monstro1X == pacmanX && monstro1Y == pacmanY){
		numVidas -= 1;
		resetaPosicoes();
		iniciaMapa();
		cout << "Voce morreu :(" << endl;
		imprimeVidas();
		imprimePontuacao();
		imprimeMapa();
	}
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

void moveMonsters(){
	int oldMonster1X = monstro1X;
	int oldMonster1Y = monstro1Y;
	
	int chancePerseguirVertical = rand() % 100;
	

	if(chancePerseguirVertical > 50){
		if(oldMonster1X < pacmanX){
			monstro1X += 1;
		}else{
			monstro1X -= 1;
		}
	}else{
		if(oldMonster1Y < pacmanY){
			monstro1Y += 1;
		}else{
			monstro1Y -= 1;
		}
	}
	

	if(ehPonto(monstro1X,monstro1Y)){
		espacoComPontoMonstro1 = true;	
	}else{
		espacoComPontoMonstro1 = false;
	}
	
	if(espacoComPontoMonstro1 == 1){
		mapa[oldMonster1X][oldMonster1Y] = '.';
	}else{
		mapa[oldMonster1X][oldMonster1Y] = ' ';
	}
	
	if (ehParede(monstro1X,monstro1Y)) {
		monstro1X = oldMonster1X;
		monstro1Y = oldMonster1Y;
	}
	
	mapa[monstro1X][monstro1Y] = 'm';
	
	
}

bool move(char dir){
	int oldX = pacmanX;
	int oldY = pacmanY;
	switch(dir){
		case 'w':
			pacmanX -= 1;
			break;
		case 'a':
			pacmanY -= 1;
			break;
		case 's':
			pacmanX += 1;
			break;
		case 'd':
			pacmanY += 1;
			break;
	}
	
	if(ehPonto(pacmanX,pacmanY) == 1){
		marcaPonto();	
	}
	
	if (mapa[pacmanX][pacmanY] == '0') {
		pacmanX = oldX;
		pacmanY = oldY;
		return false;
	}
	
	modificaMapa(oldX, oldY);	
	return true;
}

void registraRecord(){
	
}

void isGameOver(){
	if (numVidas == 0){
		cout << "Suas vidas acabaram. GAME OVER" << endl;
	}
	if (pontuacao > listaRecords[10]){
		cout << "Voce bateu ";
	}
}

void imprimeIntro(){
	cout << "======Olá Jogador======" << endl;
	cout << "Escolha uma das opções" << endl;
	cout << "1 - Jogar Pacman" << endl;
	cout << "2 - Ver Recordes" << endl;
	cout << "3 - Sair" << endl;
}


void listarRecordes(){
	//organizar lista
	 
	cout << "~~~~Hall da Fama~~~~" << endl;
	for (int i = 0; i < 10 ;i++){
		cout << "* Nome " << listaPlayers[i] << "\t Pontuacao " << listaRecords[i] << '\n';
	}
}

void inicializaJogo(){
	iniciaMapa();
	imprimeVidas();
	imprimePontuacao();
	imprimeMapa();
}

void passaTurno(char comando){
	move(comando);
	imprimeVidas();
	imprimePontuacao();
	estaMorto();
	moveMonsters();
	imprimeMapa();
	estaMorto();

	if(mapaVazio() == 1){
		passaDeFase();
	};
}

int main() {
	
	char opcao;
	cin >> opcao;
	switch(opcao){
		case '1':
			inicializaJogo();
			char comando;
			for (int i = 0; i < 600; i++) {
				cin >> comando;
				passaTurno(comando);
			}
			break;
		case '2':
			listarRecordes();
			break;
		case '3':
			break;
	}
	
	return 1;	
}

