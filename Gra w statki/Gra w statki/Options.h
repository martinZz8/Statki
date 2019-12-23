#pragma once
#include "State.h"
#include "Utils.h"
#include "Buttons.h"

class Menu;

class Options:public State
{
	Utils& u;
	Buttons& buttons;
	Menu* m; //wskaznik tylko do porowania adresu
	State** s;
	bool audio_play_guard; //zmienna zawierajaca informacje, czy mozna grac audio; true - tak, false - nie
	const int widnowID;
public:
	Options(State** state, Utils& utils, Buttons& buttons);
	void setStates(Menu* menu);
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	void mouseSwitches();
	void paintButtons();
	void paintText();

};

