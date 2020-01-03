#pragma once
#include "State.h"
#include "Board.h"
#include "Buttons.h"

class Menu;
class Deploying;

class Game:public State
{
	Utils& u;
	Buttons& buttons;
	Board& b1;
	Board& b2;
	State** s;
	Menu* m; //wskaznik stworzony do przechowywania adresu obiektu klasy deploying
	Deploying* d; //wskaznik stworzony do przechowywania adresu obiektu klasy deploying
	const int windowID;
	bool player1_turn_flag; //flaga wskazujaca, kto pierwszy zaczyna rozgrywke
	bool audio_play_guard; //true - mozna grac, false - nie mozna grac
	bool warning_sample_play_guard; //true - mozna grac, false - nie mozna grac
	bool warning_sample_play_flag; //zmienna zawierajaca informacje, czy grac audio warninga; true - tak, false - nie
	bool mouse_click_guard; //true - mozna kliknac, false - nie mozna kliknac
	bool ship_hitted_sample_play_flag; //true - trafiony, false - nie trafiony
	bool ship_missed_sample_play_flag; //true - zmissowany, false - nie zmissowany
	void choose_who_starts(); //metoda ustawiajaca, kto zaczyna rozgrywke

public:
	Game(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2);
	void setStates(Menu* menu, Deploying* deploying);
	void tick();
	void render();
	int getWindowID(); //metoda zwracajaca indeks okna;
	void mouseSwitches();
	void playAudio();
	void paintText();
	void paintBorders();
	void paintButtons();
	

};

