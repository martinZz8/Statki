#pragma once
#include "State.h"
#include "Board.h"
#include "Buttons.h"

class Menu;
//TODO ZROBIC KLASE PLAYER I PRZEKAZAC JEMU WSZYSTKIE RZECZY ZWIAZANE Z PLAYEREM (BEDA OBIEKTY PLAYER1, PLAYER2, COMPUTER)
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
	bool warning_sample_play_flag; //zmienna zawierajaca informacje, czy grac audio warninga; true - tak, false - nie
	bool place_ship_sample_flag; //zmienna zawierajaca informacje, czy grac audio rozstawiania statku; true - tak, false - nie
	bool resize_ship_guard; //true - mozna zmienic rozmiar, false - nie mozna zmienci rozmiaru
	bool rotate_ship_guard; //true - mozna zmienic polozenie, false - nie mozna zmienic polozenia
	bool mouse_click_guard; //true - mozna kliknac, false - nie mozna kliknac
	void fixShipSize(); //metoda naprawiajaca zmienna ship_size, gdy nie ma statku o takim rozmiarze
	void restoreDefaults();

public:
	Deploying(State **state, Utils &utils, Buttons& buttons, Board &board1, Board &board2);
	void setStates(Menu* menu);
	void setNUmbersOfNotDeployedShips();
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	void classicKeyboardSwitches();
	void mouseSwitches();
	void classicPlayerDeploy();
	void classicComputerDeploy();
	void classicBoardCopy();
	void paintButtons();
	void playAudio();
	
		
};

