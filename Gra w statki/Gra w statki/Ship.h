#pragma once
#include "Utils.h"
#include "Field.h"

class Ship
{
	Utils& u;
	vector <Field> fields; //vector fieldow statku
	//TODO WYPELNIC SURROUNDED_FIELDS W BOARDZIE W METODZIE DEPLOYCLASSICSHIP
	vector <Field> surrounded_fields; //vector fieldow otaczajacych statek
	int remaining_parts; //pozostale nie trafione pola statku
	bool ship_destroyed_flag; //flaga wskazujaca na to, czy statek zostal znisczony czy nie; true - tak, false - nie

public:
	//Ship& operator=(const Ship& s);
	Ship(Utils& utils, vector<Field> f, vector<Field> surr_f = {});
	void setShipDestroyedFlag();
	float getCoordX(int indeks_vfields); //zwraca koordynat x pola o danym indeksie z vectora pol
	float getCoordY(int indeks_vfields);//zwraca koordynat y pola o danym indeksie z vectora pol
	int getNumberOfFields(); //zwraca ilosc fieldow przyporzadkowanych do tego statku
	bool getShipDestroyedFlag();
	void paintShip(bool visible_ships, bool deploying_phase); //metoda malujaca statek
	bool isOnShip(Field& to_check_field); //metoda sprawdza, czy to_check_field jest shipem (jest taki sam jak ktorys z fieldow z vectora fields); true - tak, false - nie
	bool isOnSurrounding(Field& to_check_surrounding_field);//metoda sprawdza, czy to_check_surrounding_field jest surrounding (jest taki sam jak ktorys z fieldow z vectora surrounding_fields); true - tak, false - nie

};