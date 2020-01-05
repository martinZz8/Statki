#pragma once
#include "State.h"
#include "Board.h"
#include "Buttons.h"

class Menu;
class Deploying;

class Game :public State
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
	bool end_of_game_flag; //true - gra zakonczona, false - gra nie zakonczona
	int who_won_game; //numer boardu, ktory wygral gre
	int indeks_of_last_hitted_ship; //zmienna zawierajaca informacje o indeksie ostatnio trafionego statku przez komputer
	int check_end_of_game(); //metoda sprawdza, czy jest juz koniec gry; zwraca 1, gdy wygral gracz pod plansza nr 1; zwraca 2, gdy wygral gracz pod plansza nr 2; zwraca 0, gdy nikt nie wygral

public:
	Game(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2);
	void choose_who_starts(); //metoda ustawiajaca, kto zaczyna rozgrywke
	void setStates(Menu* menu, Deploying* deploying);
	void tick();
	void render();
	int getWindowID(); //metoda zwracajaca indeks okna
	int playerShoot(Board& b); //metoda oddajaca strzal gracza do boardu b; zwraca 0 gdy strzal sie powiodl; zwraca -1 gdy strzal zostal nie trafiony; zwraca 1 gdy strzal zostal oddany w zabronione miejsce (wtedy mozna oddac strzal jeszcze raz)
	int classicComputerPvCShoot(Board& b); //metoda oddajaca strzal komputera w trybie klasycznym do boardu b; zwraca -1 gdy strzal zostal nie trafiony; zwraca 1 gdy strzal zostal oddany w zabronione miejsce (wtedy mozna oddac strzal jeszcze raz)
	int advancedComputerPvCShoot(Board& b); //metoda oddajaca strzal komputera w trybie zaawansowanym do boardu b; zwraca -1 gdy strzal zostal nie trafiony; zwraca 1 gdy strzal zostal oddany w zabronione miejsce (wtedy mozna oddac strzal jeszcze raz)
	void mouseSwitches();
	void playAudio();
	void paintText();
	void paintBorders();
	void paintButtons();

};

