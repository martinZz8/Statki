#pragma once
#include "Field.h"
#include "Ship.h"

using namespace std;

class Board
{
	Utils u;
	float offset_x; //offset w osi x
	float offset_y; //offset w osi y
	float width; //szerokosc
	float height; //wysokosc
	bool setted_fields; //flaga do jednorazowego ustawienia koordynatow pol
	bool made_ships; //?
	int number_of_one_masted_ships;
	int number_of_two_masted_ships;
	int number_of_three_masted_ships;
	int number_of_four_masted_ships;
	vector <Field> fields; //vector pol
	vector <Ship> ships; //vector statkow	

public:
	Board(Utils& utils, float offset_x, float offset_y);
	Board();
	~Board();
	float getXOffset();
	float getYOffset();
	void paintBoard(); //metoda rysujaca plansze (wraz z kratkami)
	void setFields(); //metoda ustawiajaca koordynaty kazdego pola znajdujacego sie w vectorze pol
	void setOffset(float x, float y);
	int whichField(float mouse_x, float mouse_y); //metoda sprawdzajaca ktore pole jest o zadanych parametrach x i y - zwraca indeks vektora fields
	void setFieldOccupy(float mouse_x, float mouse_y, bool occupied); //metoda ustawiajaca flage okupowania pola przez dany statek
	//DO POPRAWY (ROZSTAWIANIE BEDZIE POJEDYNCZE)
	void makeShip(); //metoda tworzaca statek
	int whichShip(float mouse_x, float mouse_y); //metoda sprawdajaca ktory statek posiada zadane parametry x i y - zwraca indeks vectora ships
	void paintShip(float mouse_x, float mouse_y); //metoda ryzsujaca statek, 
	//DO DOKONCZENIA METODA NIZEJ
	void deployShip(float mouse_x, float mouse_y, int size, int orientation); //metoda rozstawiajaca statek, size - rozmiar statku, orientation - orientacja statku
};



