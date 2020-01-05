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
	bool audio_error_play_guard; //zmienna zawierajaca informacje, czy mozna grac audio errora; true - tak, false - nie
	bool warning_sample_play_flag; //zmienna zawierajaca informacje, czy grac audio warninga; true - tak, false - nie
	bool mouse_click_guard; //true - mozna kliknac, false - nie mozna kliknac
	bool back_to_menu_guard; //zmienna zawierajaca informacje, czy mozna wrocic do menu; true - tak, false - nies
	bool warning_ship_remove_flag; //flaga, zawierajaca informacje, czy napisac warninga dotyczacego usuniecia statku, gdy ilosc tych statkow wynosi 0; true - tak, false - nie
	int warning_ship_remove_timer; //licznik, ktory wskazuje ile razy ma jeszcze zostac napisany dany warning
	bool warning_ship_add_flag; //flaga, zawierajaca informacje, czy napisac warninga dotyczacego dodania statku, gdy nie ma wystarczajacej ilosci dostepnych pol; true - tak, false - nie
	int warning_ship_add_timer; //licznik, ktory wskazuje ile razy ma jeszcze zostac napisany dany warning
	int number_of_left_fields; //ilosc pol, ktore mozna jeszcze wykorzystac do rozgrywki
	const int widnowID;
public:
	Options(State** state, Utils& utils, Buttons& buttons);
	void setStates(Menu* menu);
	void tick(); //metoda wykonujaca obliczenia
	void render(); //metoda wykonujaca rysowanie
	int getWindowID(); //metoda zwracajaca indeks okna
	void setBackToMenuGuard(); //ustawienie back_to_menu_guard
	void mouseSwitches();
	void paintButtons();
	void paintText();
	void paintWarnings(); //wypisanie warningow
	void paintBorders();
	void calculateNumberOfLeftFields();
	void playAudio();

};

