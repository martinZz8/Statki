#pragma once
#include "State.h"
#include "Board.h"


class Menu:public State
{
	Utils& u;
	Board& b1;
	Board& b2;
	//Deploying* d; //wskaznik tylko do porowania adresu
	State** s;
	
	const int windowID;
public:
	Menu(State** state, Utils& utils, Board& board1, Board& board2);
	//void setStates(Deploying* deploying);
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	void paintMenu();

};

