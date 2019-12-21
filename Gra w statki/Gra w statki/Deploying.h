#pragma once
#include "State.h"
#include "Board.h"
#include "Buttons.h"

class Menu;

class Deploying:public State
{
	Utils& u;
	Buttons& buttons;
	Board& b1;
	Board& b2;
	Menu* m; //wskaznik tylko do porowania adresu
	State **s;
	const int windowID;
	bool audio_play_guard; //true - mozna grac, false - nie mozna grac
	bool resize_ship_guard; //true - mozna zmienic rozmiar, false - nie mozna zmienci rozmiaru
	bool rotate_ship_guard; //true - mozna zmienic polozenie, false - nie mozna zmienic polozenia

public:
	Deploying(State **state, Utils &utils, Buttons& buttons, Board &board1, Board &board2);
	~Deploying();
	void setStates(Menu* menu);
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	void classicKeyboardSwitches();
	void mouseSwitches();
	void paintButtons();
		
};

