#pragma once
#include "Utils.h"
#include "Field.h"

class Ship
{
	Utils& u;
	vector <Field> ship_fields; //vector fieldow statku
	vector <Field> surrounded_fields; //vector fieldow otaczajacych statek
	bool ship_destroyed_flag; //flaga wskazujaca na to, czy statek zostal znisczony czy nie; true - tak, false - nie

public:
	Ship(Utils& utils, vector<Field> ship_f = {}, vector<Field> surr_f = {});
	void setShipDestroyedFlag(vector <int>& numbers_of_not_destroyed_ships);
	int setShipHitted(Field& field, vector <int>& numbers_of_not_destroyed_ships); //metoda sprawdzajaca czy wybrany field istnieje w podanym statku i czy nie jest juz hitted. Jezeli istnieje i nie jet hitted, to ustawia fielda shipa na hitted ;zwraca 0 gdy trafienie sie powiedzie, -1 gdy sie nie powiedzie, 1 gdy dany field jest juz trafiony albo trafiono w surrounded fielda zniszczonego statku przy hints_on == true
	void copyShip(vector <Field>& new_ship_fields, vector <Field>& new_surrounded_fields);
	void copyShipFields(vector <Field>& fields);
	void setShipFields(vector <Field>& new_ship_f);
	void setSurroundedFields(vector <Field>& new_surr_f);
	void setShip(Ship& ship);
	float getCoordX(int indeks_vfields); //zwraca koordynat x pola o danym indeksie z vectora pol
	float getCoordY(int indeks_vfields);//zwraca koordynat y pola o danym indeksie z vectora pol
	int getNumberOfFields(); //zwraca ilosc fieldow przyporzadkowanych do tego statku
	int getNumberOfHittedFields(); //zwraca ilosc fieldow statku, ktore sa trafione
	bool getShipDestroyedFlag();
	void getShipFields(vector <float>& coord_x, vector <float>& coord_y);
	void paintShip(bool visible_ships, bool const_visible_surrounding); //metoda malujaca statek
	bool isOnShip(Field& checked_field); //metoda sprawdza, czy to_check_field jest shipem (jest taki sam jak ktorys z fieldow z vectora ship_fields); true - tak, false - nie
	bool isOnSurrounding(Field& checked_surrounding_field);//metoda sprawdza, czy to_check_surrounding_field jest surrounding (jest taki sam jak ktorys z fieldow z vectora surrounding_fields); true - tak, false - nie
	bool isOnOtherShip(Field& checked_field, vector <Field>& this_ship_fields); //metoda sprawdza, czy checked_field jest shipem, ale nie nalezacym do vectora fieldow this_ship_fields; true - tak, false - nie
	void clearShipFields(); //metoda czyszczaca vektor ship_fields oraz surrounding_fields
	void clearSurroundingFields(); //metoda czyszczaca vektor surrounding_fields

};