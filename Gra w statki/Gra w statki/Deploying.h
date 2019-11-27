#pragma once
#include "State.h"
#include "Board.h"

class Deploying:public State
{
	Utils& u;
	Board& b1;
	Board& b2;
	const int windowID;
	bool deploy_ship_guard; //true - mozna grac, false - nie mozna grac
	bool resize_ship_guard; //true - mozna zmienic rozmiar, false - nie mozna zmienci rozmiaru
	bool rotate_ship_guard; //true - mozna zmienic polozenie, false - nie mozna zmienic polozenia

public:
	Deploying(Utils &utils, Board &board1, Board &board2);
	//Deploying();
	~Deploying();
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	void StandardKeyboardSwitches();
	void MouseSwitches();
	
};

