#pragma once
#include "State.h"
#include "Board.h"
#include "Buttons.h"

class Menu;
class Game;

class Deploying :public State
{
	Utils& u;
	Buttons& buttons;
	Board& b1;
	Board& b2;
	Menu* m; //wskaznik tylko do ustawienia adresu
	Game* g; //wskaznik tylko do ustawienia adresu
	State** s;
	vector <Field> created_advanced_ship; //vector fieldow jednego shipa, ktory jest tworzony tylko przy wyborze opcji advanced (tymczasowy statek)
	Ship coppied_ship; //przechowywana kopia zapasowa danego shipa
	int indeks_of_coppied_ship; //indeks przechowywanej kopii shipa w oryginalnym vectorze shipow
	vector <Field> fields_of_temporary_ship; //vector fieldow tymczasowego statku, ktory jest przesuwany
	vector <float> difference_x; //roznica miedzy mouse_x a pierwotnym stanem x temporary_shipa
	vector <float> difference_y; //roznica miedzy mouse_y a pierwotnym stanem y temporaty_shipa
	const int windowID;
	bool choosed_for_move_ship_guard; //true - wybrany, false - nie wybrany
	bool audio_play_guard; //true - mozna grac, false - nie mozna grac
	bool warning_sample_play_guard; //true - mozna grac, false - nie mozna grac
	bool warning_sample_play_flag; //zmienna zawierajaca informacje, czy grac audio warninga; true - tak, false - nie
	bool place_ship_sample_flag; //zmienna zawierajaca informacje, czy grac audio rozstawiania statku; true - tak, false - nie
	bool add_advanced_ship_field_sample_flag; //zmienna zawierajaca informacje, czy grac audio dodawania fielda do advanced statku; true - tak, false - nie
	bool add_advanced_ship_field_sample_guard; //true - mozna grac, false - nie mozna grac
	bool resize_ship_guard; //true - mozna zmienic rozmiar, false - nie mozna zmienci rozmiaru
	bool rotate_ship_guard; //true - mozna zmienic polozenie, false - nie mozna zmienic polozenia
	bool mouse_click_guard; //true - mozna kliknac, false - nie mozna kliknac
	bool done_deploying_b1; //true- rozstawiono finalnie board1, false - nie rozstawiono finalnie board1
	bool done_deploying_b2; //true- rozstawiono finalnie board2, false - nie rozstawiono finalnie board2; jezeli rozstawiono board2, to mozna kliknac przycisk play
	bool moving_ship_mode_on; //tryb przesuwania statku; true - wlaczony, false - wylaczony (wtedy jest wlaczony zwykly tryb rozstawiania statku)
	void fixShipSize(); //metoda naprawiajaca zmienna ship_size, gdy nie ma statku o takim rozmiarze
	void clearBoard1();
	void clearBoard2();

public:
	Deploying(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2);
	void setStates(Menu* menu, Game* game);
	void restoreDefaults();
	void setNUmbersOfNotDeployedShips();
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna;
	void classicShipSwitch(vector <int>& numbers_of_not_deployed_ships); //NOWA METODA
	void classicKeyboardSwitches();
	void mouseSwitches();
	void classicPlayer1Deploy();
	void classicPlayer2Deploy();
	void classicComputerDeploy(Board& b, bool deploy_for_player);
	void advancedPlayer1Deploy();
	void advancedPlayer2Deploy();
	void advancedComputerDeploy(Board& b, bool deploy_for_player);
	void movePlayerShip(Board& b);
	int placeMovedPlayerShip(Board& b); //metoda stawia przesuniety statek; zwraca 0 gdy sie powiodlo, -1 gdy sie nie udalo
	void paintButtons();
	void paintText();
	void paintBorders();
	void paintCreatedAdvancedShip();
	void paintTemporaryShip();
	void playAudio();
	void copyShips(Board& from, Board& to); //metoda kopiuje vector shipow z "from" do "to"

};