#pragma once
#include "State.h"
#include "Board.h"
#include "Buttons.h"

class Deploying;
class Options;

class Menu:public State
{
	Utils& u;
	Buttons& buttons;
	Board& b1;
	Board& b2;
	Options* o; //wskaznik tylko do porowania adresu
	Deploying* d; //wskaznik tylko do porowania adresu
	State** s;
	bool audio_play_guard; //zmienna zawierajaca informacje, czy mozna grac audio; true - tak, false - nie
	const int windowID;
public:
	Menu(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2);
	void setStates(Options* options, Deploying* deploying);
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	void mouseSwitches();
	void paintButtons();
};

