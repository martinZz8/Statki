#pragma once
#include "State.h"
#include "Board.h"

class Menu;

class Deploying:public State
{
	Utils& u;
	Board& b1;
	Board& b2;
	Menu* m; //wskaznik tylko do porowania adresu
	State **s;
	const int windowID;
	bool deploy_ship_guard; //true - mozna grac, false - nie mozna grac
	bool resize_ship_guard; //true - mozna zmienic rozmiar, false - nie mozna zmienci rozmiaru
	bool rotate_ship_guard; //true - mozna zmienic polozenie, false - nie mozna zmienic polozenia

public:
	Deploying(State **state, Utils &utils, Board &board1, Board &board2);
	void setStates(Menu* menu);
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	void DefaultKeyboardSwitches();
	void MouseSwitches();
	
};

