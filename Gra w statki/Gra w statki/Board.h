#pragma once
#include "Field.h"
#include "Ship.h"

using namespace std;

class Board
{
	Utils& u;
	float offset_x; //offset w osi x
	float offset_y; //offset w osi y
	float width; //szerokosc
	float height; //wysokosc
	float field_size; //rozmiar pola
	bool deploy_ships_flag; //flaga wskzujaca, czy mozna rozstawiac statki; true - tak, false - nie
	vector <Field> fields; //vector pol planszy
	vector <Ship> ships; //vector statkow

public:
	Board(Utils& utils, float offset_x, float offset_y);
	vector <int> numbers_of_not_deployed_ships; //vector ilosci statkow, ktore zostaly jeszcze do rozstawienia; indeks+1 wskazuje jakiej dlugosci jest statek
	vector <int> numbers_of_not_destroyed_ships; //vector ilosci statkow, ktore nie zostaly jeszcze zniszczone; indeks+1 wzkazuje jakiej dlugosci jest statek
	float getXOffset();
	float getYOffset();
	float getWidth();
	float getHeight();
	float getFieldSize();
	bool getDeployShipsFlag();
	float getShipX(int indeks);
	float getShipY(int indeks);
	bool getShipsDestroyedFlag(int indeks);
	int getNumbersOfShipHittedFields(int indeks);
	void getCoordsOfShipHittedFields(int indeks, vector <float>& coord_x, vector <float>& coord_y);
	void paintBoard(bool visible_ships, bool const_visible_surrounding); //metoda rysujaca plansze; visible_ships == true - rysuje statki, const_visible_surrounding == true - rysuje surrounded fieldsy caly czas (nawet, gdy statek nie jest zniszczony)
	void setFields(); //metoda ustawiajaca koordynaty kazdego pola znajdujacego sie w vectorze pol
	void setOffset(float x, float y);
	void setDeployShipsFlag(); //metoda sprawdzajaca, czy mozna dalej rozstawiac statki na tym boardzie
	void setFieldsSurrounded(vector <int> indeks_of_ship_fields, vector <Field>& surrounded_fields); //metoda tworzaca vector surrounded danego statku; przyjmuje vector indeksow statku - wywolywane przy stawianiu statku
	void setNumbersOfNotDeployedShips();
	void setNumbersOfNotDestroyedShips();
	int setShipHitted(float mouse_x, float mouse_y); //metoda zwraca 0, gdy udalo sie ustawic fielda shipa na hitted, -1 gdy nie udalo sie ustawic fielda shipa na hitted; 1, gdy dany field shippa jest juz trafiony albo dany field boardu jest juz trafiony jako missed (przy opcji hints_on == true)
	int setShipHitted(float mouse_x, float mouse_y, int& indeks_of_last_hitted_ship); //metoda zwraca 0, gdy udalo sie ustawic fielda shipa na hitted, -1 gdy nie udalo sie ustawic fielda shipa na hitted; 1, gdy dany field shippa jest juz trafiony albo dany field boardu jest juz trafiony jako missed (przy opcji hints_on == true)
	void setShips(vector <Ship> s);
	int whichField(float mouse_x, float mouse_y); //metoda sprawdzajaca ktore pole jest o zadanych parametrach x i y - zwraca indeks vektora fields
	int whichShip(float mouse_x, float mouse_y); //metoda sprawdajaca ktory statek posiada zadane parametry x i y - zwraca indeks vectora ships albo -1, gdy nie ma takiego statku
	void paintClassicShip(float mouse_x, float mouse_y); //metoda ryzsujaca statek dla standardowych opcji statków
	int deployClassicShip(float mouse_x, float mouse_y, int ship_orientation, int ship_size); //metoda rozstawiajaca calssic ship; zwraca 0, gdy rozstawianie sie powiedzie, zwraca -1 gdy rozstawianie sie nie powiedzie
	int deployAdvancedShip(float mouse_x, float mouse_y, vector <Field>& created_advanced_ship, bool player_deploy); //metoda rozstawiajaca advanced ship, player_deploy - zmienna wskazujaca, czy rozstawia gracz czy komputer; zwraca 0, gdy sie powiedzie, zwraca -1 gdy sie nie powiedzie, zwraca 1 gdy (przy player_deploy == true) myszka znajduje sie nadal na tym samym fieldzie co ostatnio dodany do vectora created_advanced_ship albo (przy player_deploy == false) wylosowano field, ktory juz nalezy do vectora created_advanced_ship badz lezy za daleko od danego fielda badz lezy w zabronionym miejscu (aby nie marnowac juz dobrze wylosowanych fieldow)
	void addAdvancedShip(vector <Field>& created_advanced_ship); //metoda dodaje statek do vectora Shipow
	int whichQuarterOfField(float c_x, float c_y, float center_of_field_x, float center_of_field_y); //metoda zwraca, ktora cwiartka pola zostala kliknieta; 1 - prawa gorna, 2 - lewa gorna, 3 - lewa dolna, 4 - prawa dolna
	void clearVectors(); //metoda czyszczace vektory fieldow oraz shipow
	void clearVectorsOfShip(int indeks); //metoda czyszczace evektory ship_fields i surrounding_fields danego shipa
	void clearSurroundedFieldsVector(int indeks); //metoda czyszczaca vector surrounded filedow statku o danym indeksie w vectorze shipow
	bool isOnShip(Field& to_check_field); //metoda sprawdzajaca, czy to_check_field jest jakims statkiem; true - tak, false - nie
	bool isOnSurrounding(Field& to_check_field); //metoda sprawdzajaca, czy to_check_field otacza jakis statek; true - tak, false - nie
	bool isOnOtherShip(Field& to_check_field, vector <Field>& ship_fields);
	void copyShip(Ship& new_ship, int indeks); //metoda kopiuje statek o zadanym indeksie do shipa new_ship
	void copyFieldsOfShip(Ship& ship, vector <Field>& fields);
	void moveShipFields(int indeks, float offset_x, float offset_y); //metoda przesuwajaca fieldy shipa z vectora shipsow o zadanym indeksie o zadane wartosci offset
	int placeShip(Ship& coppied_ship, int indeks_of_coppied_ship, vector <Field>& fields_of_new_ship); //metoda stawiajaca statek w danym miejscu, gdy jest to mozliwe; zwraca 0, gdy sie powiedzie, -1 gdy sie nie powiedzie
};