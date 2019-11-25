#pragma once
#include "Utils.h"
#include "Field.h"

class Ship
{
	Utils u;
	vector <Field> fields;
	//STWORZYC VECTOR INTOW SHIPOW
	int remaining_parts; //pozostale nie trafione pola statku
	int number_of_fields; //liczba pol statku
public:
	Ship(Utils& utils);
	Ship();
	~Ship();
	void setFields(Field f);
	void setNumberOfFields(int n);
	//void setHitField(float x_mouse, float y_mouse);
	float getCoordX(int indeks_vfields); //zwraca koordynat x pola o danym indeksie z vectora pol
	float getCoordY(int indeks_vfields);//zwraca koordynat y pola o danym indeksie z vectora pol
	int getNumberOfFields(); //zwraca ilosc fieldow przyporzadkowanych do tego statku


};

