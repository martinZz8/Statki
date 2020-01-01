#pragma once
#include "State.h"
#include "Board.h"
#include "Buttons.h"

class Menu;

class Deploying :public State
{
	Utils& u;
	Buttons& buttons;
	Board& b1;
	Board& b2;
	Menu* m; //wskaznik tylko do porowania adresu
	State** s;
	vector <Field> created_advanced_ship; //vector fieldow jednego shipa, ktory jest tworzony tylko przy wyborze opcji advanced (tymczasowy statek)
	const int windowID;
	bool audio_play_guard; //true - mozna grac, false - nie mozna grac
	bool warning_sample_play_flag; //zmienna zawierajaca informacje, czy grac audio warninga; true - tak, false - nie
	bool place_ship_sample_flag; //zmienna zawierajaca informacje, czy grac audio rozstawiania statku; true - tak, false - nie
	bool resize_ship_guard; //true - mozna zmienic rozmiar, false - nie mozna zmienci rozmiaru
	bool rotate_ship_guard; //true - mozna zmienic polozenie, false - nie mozna zmienic polozenia
	bool mouse_click_guard; //true - mozna kliknac, false - nie mozna kliknac
	bool done_deploying_b1; //true- rozstawiono finalnie board1, false - nie rozstawiono finalnie board1
	bool done_deploying_b2; //true- rozstawiono finalnie board2, false - nie rozstawiono finalnie board2; jezeli rozstawiono board2, to mozna kliknac przycisk play
	bool done_copy_b1_to_b2; //true - skopiowano, false - nie skopiowano
	void fixShipSize(); //metoda naprawiajaca zmienna ship_size, gdy nie ma statku o takim rozmiarze
	void restoreDefaults();

public:
	Deploying(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2);
	void setStates(Menu* menu);
	void setNUmbersOfNotDeployedShips();
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	void classicShipSwitch(vector <int>& numbers_of_not_deployed_ships); //NOWA METODA
	void classicKeyboardSwitches();
	void mouseSwitches();
	void classicPlayer1Deploy();
	void classicPlayer2Deploy();
	void classicComputerDeploy();
	void advancedPlayer1Deploy(); //nowa metoda
	void advancedPlayer2Deploy(); //nowa metoda
	void advancedComputerDeploy(); //nowa metoda
	void paintButtons();
	void paintText();
	void paintBorders();
	void playAudio();
	void copyShips(Board& from, Board& to); //metoda kopiuje vector shipow z "from" do "to"


};