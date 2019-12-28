#pragma once
#include "Utils.h"
#include "Field.h"

class Ship
{
	Utils& u;
	vector <Field> fields;
	int remaining_parts; //pozostale nie trafione pola statku
	int number_of_fields; //liczba pol statku
	bool ship_destroyed_flag; //flaga wskazujaca na to, czy statek zostal znisczony czy nie; true - tak, false - nie
	
public:
	Ship(Utils& utils, vector<Field> f);
	void setFields(Field f);
	void setNumberOfFields(int n);
	//void setHitField(float x_mouse, float y_mouse);
	float getCoordX(int indeks_vfields); //zwraca koordynat x pola o danym indeksie z vectora pol
	float getCoordY(int indeks_vfields);//zwraca koordynat y pola o danym indeksie z vectora pol
	int getNumberOfFields(); //zwraca ilosc fieldow przyporzadkowanych do tego statku
	void paintShip(); //metoda malujaca statek


};

