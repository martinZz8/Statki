#pragma once
#include "Utils.h"
#include "Field.h"

class Ship
{
	Utils& u;
	vector <Field> ship_fields; //vector fieldow statku
	vector <Field> surrounded_fields; //vector fieldow otaczajacych statek
	int remaining_parts; //pozostale nie trafione pola statku
	bool ship_destroyed_flag; //flaga wskazujaca na to, czy statek zostal znisczony czy nie; true - tak, false - nie

public:
	Ship(Utils& utils, vector<Field> ship_f, vector<Field> surr_f = {});
	void setShipDestroyedFlag();
	int setShipHit(Field& field, bool h); //metoda sprawdzajaca czy wybrany field istenieje w podanym statku, jezeli tak, to ustawia hit na wartosc h ;zwraca 0 gdy trafienie sie powiedzie, -1 gdy sie nie powiedzie
	//Dwie metody ponizej byly problematyczne
	void setShipFields(vector <Field>& new_ship_f);
	void setSurroundedFields(vector <Field>& new_surr_f);
	void moveShipFields(float offset_x, float offset_y);
	void moveSurroundedFields(float offset_x, float offset_y);
	float getCoordX(int indeks_vfields); //zwraca koordynat x pola o danym indeksie z vectora pol
	float getCoordY(int indeks_vfields);//zwraca koordynat y pola o danym indeksie z vectora pol
	int getNumberOfFields(); //zwraca ilosc fieldow przyporzadkowanych do tego statku
	bool getShipDestroyedFlag();
	void paintShip(bool visible_ships, bool deploying_phase); //metoda malujaca statek
	bool isOnShip(Field& to_check_field); //metoda sprawdza, czy to_check_field jest shipem (jest taki sam jak ktorys z fieldow z vectora ship_fields); true - tak, false - nie
	bool isOnSurrounding(Field& to_check_surrounding_field);//metoda sprawdza, czy to_check_surrounding_field jest surrounding (jest taki sam jak ktorys z fieldow z vectora surrounding_fields); true - tak, false - nie

};