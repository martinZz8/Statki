#pragma once
#include "State.h"
#include "Board.h"

class Deploying:public State
{
	Utils& u;
	Board& b1;
	Board& b2;
	const int windowID;
	bool play_sample_guard; //true - mozna grac, false - nie mozna grac

public:
	Deploying(Utils &utils, Board &board1, Board &board2);
	//Deploying();
	~Deploying();
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	
};

