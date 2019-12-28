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
	void setFields(Field f);
	void setShipDestroyedFlag();
	float getCoordX(int indeks_vfields); //zwraca koordynat x pola o danym indeksie z vectora pol
	float getCoordY(int indeks_vfields);//zwraca koordynat y pola o danym indeksie z vectora pol
	int getNumberOfFields(); //zwraca ilosc fieldow przyporzadkowanych do tego statku
	bool getShipDestroyedFlag();
	void paintShip(bool visible_ships); //metoda malujaca statek


};

