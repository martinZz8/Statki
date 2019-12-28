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
	vector <Field> fields; //vector pol
	vector <Ship> ships; //vector statkow

public:
	//Board& operator=(const Board& b);
	Board(Utils& utils, float offset_x, float offset_y);
	vector <int> numbers_of_not_deployed_ships; //vector ilosci statkow, ktore zostaly jeszcze do rozstawienia; indeks+1 wskazuje jakiej dlugosci jest statek
	float getXOffset();
	float getYOffset();
	bool getDeployShipsFlag();
	void paintBoard(bool visible_ships, bool deploying_surrounded); //metoda rysujaca plansze; visible_ships == true - rysuje statki, deploying_surrounded == true - rysuje wszystkie pola, ktore w surrounded maja true
	void setFields(); //metoda ustawiajaca koordynaty kazdego pola znajdujacego sie w vectorze pol
	void setOffset(float x, float y);
	void setDeployShipsFlag(); //metoda sprawdzajaca, czy mozna dalej rozstawiac statki na tym boardzie
	vector<Field> setFieldsSurrounded(int indeks, bool surrounded); //metoda ustawiajaca polu sasiadujacemu z polem o zadanych wartosciach wartosc surrounded_flag na true, gdy nie ma statku na danym polu - wywolywane przy stawianiu statku
	void setNumbersOfNotDeployedShips();
	int whichField(float mouse_x, float mouse_y); //metoda sprawdzajaca ktore pole jest o zadanych parametrach x i y - zwraca indeks vektora fields
	int whichShip(float mouse_x, float mouse_y); //metoda sprawdajaca ktory statek posiada zadane parametry x i y - zwraca indeks vectora ships
	void paintClassicShip(float mouse_x, float mouse_y); //metoda ryzsujaca statek dla standardowych opcji statków
	//TODO - DO DOKONCZENIA METODA NIZEJ (ZROBIC UNIWERSALNE METODY)
	int deployClassicShip(float mouse_x, float mouse_y); //metoda rozstawiajaca statek, zwraca 0, gdy rozstawianie sie powiedzie, zwraca -1 gdy rozstawianie sie nie powiedzie
	int whichQuarterOfField(float c_x, float c_y, float center_of_field_x, float center_of_field_y); //metoda zwraca, ktora cwiartka pola zostala kliknieta; 1 - prawa gorna, 2 - lewa gorna, 3 - lewa dolna, 4 - prawa dolna
	void clearVectors(); //metoda czyszczace vektory fieldow oraz shipow
	
};



