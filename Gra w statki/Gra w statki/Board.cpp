#include "Board.h"

Board::Board(Utils& utils, float offset_x, float offset_y) :u(utils), offset_x(offset_x), offset_y(offset_y)
{
	width = u.getBoardSize();
	height = u.getBoardSize();
	field_size = u.getFieldSize();
	deploy_ships_flag = true;
	setFields();

}


float Board::getXOffset()
{
	return offset_x;
}

float Board::getYOffset()
{
	return offset_y;
}

float Board::getWidth()
{
	return width;
}

float Board::getHeight()
{
	return height;
}

float Board::getFieldSize()
{
	return field_size;
}

bool Board::getDeployShipsFlag()
{
	return deploy_ships_flag;
}

vector<Ship> Board::getShips()
{
	return ships;
}

void Board::setFields()
{
	int iter = 0;
	int number_of_fields = u.getNumberOfFields();
	float field_size = u.getFieldSize();
	float x1, y1;
	for (float i = 0; i < number_of_fields; i++) //y
		for (float j = 0; j < number_of_fields; j++) //x
		{
			x1 = offset_x + (j * field_size);
			y1 = offset_y + (i * field_size);
			Field field(u, x1, y1);
			fields.push_back(field);
			iter++;
			cout << "Iter: " << iter << endl;
		}
}

void Board::setOffset(float x, float y)
{
	offset_x = x;
	offset_y = y;
}

void Board::setDeployShipsFlag()
{
	for (int n : numbers_of_not_deployed_ships)
	{
		if (n > 0)
		{
			deploy_ships_flag = true;
			return;
		}
	}
	deploy_ships_flag = false;
}

void Board::paintBoard(bool visible_ships, bool const_visible_surrounding)
{
	/*Rysowanie fieldow*/
	for (Field f : fields)
	{
		f.paintField(SCHEME_OF_FIELD);
		if (f.getMiss() == true)
			f.paintField(SCHEME_OF_SURROUNDED);
    }

	/*Rysowanie statkow i fieldow surrounded zniszczonych statkow, gdy sa wlaczone podpowiedzi*/
	for (Ship s : ships)
	{
		s.paintShip(visible_ships, const_visible_surrounding);
	}
}

void Board::setFieldsSurrounded(vector <int> indeks_of_ship_fields, vector <Field>& surrounded_fields)
{
	for (int indeks : indeks_of_ship_fields)
	{
		int offset = -11;
		vector <int> prohibited_offsets; //zabronione offsety
		if ((indeks % 10) == 0) //jezeli field jest przy lewej krawedzi boardu
		{
			prohibited_offsets.push_back(-11);
			prohibited_offsets.push_back(-1);
			prohibited_offsets.push_back(9);
		}
		else if (((indeks + 1) % 10) == 0) //jezeli field jest przy prawej krawedzi boardu
		{
			prohibited_offsets.push_back(-9);
			prohibited_offsets.push_back(1);
			prohibited_offsets.push_back(11);
		}

		for (int i = 1; i <= 8; i++, offset++)
		{
			int new_indeks = indeks + offset;
			bool go_next_flag = true; //flaga wskazujaca, czy mozna isc dalej
			for (int j : prohibited_offsets)
			{
				if (offset == j)
				{
					go_next_flag = false;
					break;
				}
			}
			for (int j : indeks_of_ship_fields)
			{
				if (new_indeks == j)
				{
					go_next_flag = false;
					break;
				}
			}
			
			if (new_indeks >= 0 && new_indeks <= 99 && go_next_flag == true) //if (isOnShip(fields[new_indeks]) == false) NIEPOTRZEBNY WARUNEK BYL TUTAJ
			{
				bool can_be_added = true;
				for (Field f : surrounded_fields)
				{
					if (fields[new_indeks] == f)
						can_be_added = false;
				}
				if (can_be_added == true)
				{
					surrounded_fields.push_back(fields[new_indeks]);
					cout << "Dodalem surrounded fielda" << endl;
				}
			}
			if (offset == -9)
				offset = -2;
			else if (offset == -1)
				offset = 0;
			else if (offset == 1)
				offset = 8;
		}
	}
}

void Board::setNumbersOfNotDeployedShips()
{
	if (numbers_of_not_deployed_ships.empty() == false)
	{
		numbers_of_not_deployed_ships.clear();
	}
	numbers_of_not_deployed_ships.push_back(u.getNumberOfOneMastedShips()); //indeks 0
	numbers_of_not_deployed_ships.push_back(u.getNumberOfTwoMastedShips()); //indeks 1
	numbers_of_not_deployed_ships.push_back(u.getNumberOfThreeMastedShips()); //indeks 2
	numbers_of_not_deployed_ships.push_back(u.getNumberOfFourMastedShips()); //indeks 3
}

int Board::setShipHitted(Field& field)
{
	for (Ship s : ships)
	{
		int i = s.setShipHitted(field);
		if (i == 0)
			return 0;
		else if (i == 1)
			return -1;
	}
	return -1;
}

void Board::setShips(vector<Ship> s)
{
	ships.clear();
	for (Ship new_ship : s)
	{
		ships.push_back(new_ship);
	}
}

int Board::whichField(float mouse_x, float mouse_y)
{
	int fields_size = fields.size();
	for (int i = 0; i < fields_size; i++)
	{
		float l_x = fields[i].getCoordX(); //lewe x
		float r_x = fields[i].getCoordX() + field_size; //prawe x
		float u_y = fields[i].getCoordY(); //gorne y
		float d_y = fields[i].getCoordY() + field_size; //dolne y
		if (mouse_x >= l_x && mouse_x < r_x && mouse_y >= u_y && mouse_y < d_y)
		{
			return i;
		}
	}
	//zwrocenie -1 oznacza, ze pod danymi koordynatami mouse_x i mouse_y nie ma fielda
	return -1;
}

int Board::whichShip(float mouse_x, float mouse_y)
{
	//sprawdzam czy isnieje statek o zadanych parametrach x i y - w tym celu przeszukuje caly vector shipow
	int ships_size = ships.size();
	for (int i = 0; i < ships_size; i++)
	{
		//przeszukuje kazde pole z vectora pol w danym statku
		int indeks = 0;
		int number_of_fields = ships[i].getNumberOfFields();
		for (int j = 0; j < number_of_fields; j++)
		{
			float l_x = ships[j].getCoordX(indeks); //lewe x
			float r_x = l_x + field_size; //prawe x
			float u_y = ships[j].getCoordY(indeks); //gorne y
			float d_y = u_y + field_size; //dolne y
			if (mouse_x >= l_x && mouse_x < r_x && mouse_y >= u_y && mouse_y < d_y)
			{
				return i;
			}
			indeks++;
		}
	}
	//zwrocenie -1 oznacza, ze pod danymi koordynatami mouse_x i mouse_y nie ma statku
	return -1;
}

void Board::paintClassicShip(float mouse_x, float mouse_y)
{
	//RYSOWANIE GDY MAMY USTAWIONE STATKI KLASYCZNE
	float field_size = u.getFieldSize();
	int ship_size = u.getShipSize();
	int ship_orientation = u.getShipOrientation();
	if (ship_size == 1)
	{
		float x1 = mouse_x - 0.5 * field_size;
		float y1 = mouse_y - 0.5 * field_size;
		float x2 = mouse_x + 0.5 * field_size;
		float y2 = mouse_y + 0.5 * field_size;
		al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
	}
	else if (ship_orientation == 1)
	{
		if (ship_size == 2)
		{
			float x1 = mouse_x - 0.5 * field_size;
			float y1 = mouse_y - field_size;
			float x2 = mouse_x + 0.5 * field_size;
			float y2 = mouse_y + field_size;
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
		else if (ship_size == 3)
		{
			float x1 = mouse_x - 0.5 * field_size;
			float y1 = mouse_y - 1.5 * field_size;
			float x2 = mouse_x + 0.5 * field_size;
			float y2 = mouse_y + 1.5 * field_size;
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
		else if (ship_size == 4)
		{
			float x1 = mouse_x - 0.5 * field_size;
			float y1 = mouse_y - 2 * field_size;
			float x2 = mouse_x + 0.5 * field_size;
			float y2 = mouse_y + 2 * field_size;
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
	}
	else if (ship_orientation == 2)
	{
		if (ship_size == 2)
		{
			float x1 = mouse_x - field_size;
			float y1 = mouse_y - 0.5 * field_size;
			float x2 = mouse_x + field_size;
			float y2 = mouse_y + 0.5 * field_size;
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
		else if (ship_size == 3)
		{
			float x1 = mouse_x - 1.5 * field_size;
			float y1 = mouse_y - 0.5 * field_size;
			float x2 = mouse_x + 1.5 * field_size;
			float y2 = mouse_y + 0.5 * field_size;
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
		else if (ship_size == 4)
		{
			float x1 = mouse_x - 2 * field_size;
			float y1 = mouse_y - 0.5 * field_size;
			float x2 = mouse_x + 2 * field_size;
			float y2 = mouse_y + 0.5 * field_size;
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
	}
}

//TODO
//1) ZMIENIC UZYWAJAC UNIWERSALNYCH FUNKCJI
//2) USUNAC TO_INSERT I PRZEKAZYWAC SURR_F PRZEZ REFERENCJE DO METODY SETFIELDSSURROUNDED, GDZIE BEDZIE USTAWIANY SURR_F BEZ POWTORZEN
int Board::deployClassicShip(float mouse_x, float mouse_y, int ship_orientation, int ship_size)
{
	vector <Field> surr_f; //vector zawierajacy surrounding fieldy; wsadzany potem do vectora shipow
	
	if (ship_size == 1)
	{
		float l_x = mouse_x - (0.5 * field_size); /*koordynaty lewego gornego rogu statku*/
		float u_y = mouse_y - (0.5 * field_size); /*                                     */
		float r_x = mouse_x + (0.5 * field_size); /*koordynaty prawego dolnego rogu statku*/
		float d_y = mouse_y + (0.5 * field_size); /*                                      */
		int indeks = whichField(l_x, u_y); //indeks_l_u
		int indeks_r_u = whichField(r_x, u_y);
		int indeks_r_d = whichField(r_x, d_y);
		int indeks_l_d = whichField(l_x, d_y);
		//sprawdzenie, czy lewy gorny rog statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
		if (indeks == -1)
			return -1;
		float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
		float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
		int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
		if (quarter_of_field == 1) //postawienie na prawo
		{
			//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
			if (indeks_r_u == -1)
				return -1;
			if (isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true)
				return -1;
			numbers_of_not_deployed_ships[ship_size - 1]--;
			vector <int> indeks_of_ship_fields = { indeks + 1 };
			setFieldsSurrounded(indeks_of_ship_fields, surr_f);
			vector <Field> f{ fields[indeks + 1] }; //vector zawierajacy fieldy nalezace do statku
			ships.push_back(Ship(u, f, surr_f));
		}
		else if (quarter_of_field == 2) //postawienie w fieldzie o indeksie "indeks"
		{
			if (isOnShip(fields[indeks]) == true || isOnSurrounding(fields[indeks]) == true)
				return -1;
			numbers_of_not_deployed_ships[ship_size - 1]--;
			vector <int> indeks_of_ship_fields = { indeks };
			setFieldsSurrounded(indeks_of_ship_fields, surr_f);
			vector <Field> f{ fields[indeks] };
			ships.push_back(Ship(u, f, surr_f));
		}
		else if (quarter_of_field == 3)
		{
			//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
			if (indeks_l_d == -1)
				return -1;
			if (isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true)
				return -1;
			numbers_of_not_deployed_ships[ship_size - 1]--;
			vector <int> indeks_of_ship_fields = { indeks + 10 };
			setFieldsSurrounded(indeks_of_ship_fields, surr_f);
			vector <Field> f{ fields[indeks + 10] };
			ships.push_back(Ship(u, f, surr_f));
		}
		else //quarter_of_field == 4
		{
			//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
			if (indeks_r_d == -1)
				return -1;
			if (isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true)
				return -1;
			numbers_of_not_deployed_ships[ship_size - 1]--;
			vector <int> indeks_of_ship_fields = { indeks + 11 };
			setFieldsSurrounded(indeks_of_ship_fields, surr_f);
			vector <Field> f{ fields[indeks + 11] };
			ships.push_back(Ship(u, f, surr_f));
		}
	}
	else if (ship_orientation == 1) //pionowo
	{
		float l_x = mouse_x - (0.5 * field_size);
		float r_x = mouse_x + (0.5 * field_size);

		if (ship_size == 2)
		{
			float u_y = mouse_y - field_size;
			float d_y = mouse_y + field_size;
			int indeks = whichField(l_x, u_y); //indeks_l_u
			int indeks_r_u = whichField(r_x, u_y);
			int indeks_r_d = whichField(r_x, d_y);
			int indeks_l_d = whichField(l_x, d_y);
			int check_indeks = whichField(l_x, u_y + field_size); //indeks sprawdzajacy, czy lewy dolny rog pierwszej kratki znajduje sie w planszy
			//sprawdzenie, czy lewy gorny rog statku albo lewy dolny rog pierwszej kratki statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1 || check_indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true || isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 1, indeks + 11 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 1], fields[indeks + 11] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (isOnShip(fields[indeks]) == true || isOnSurrounding(fields[indeks]) == true || isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks, indeks + 10 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks], fields[indeks + 10] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true || isOnShip(fields[indeks + 20]) == true || isOnSurrounding(fields[indeks + 20]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 10, indeks + 20 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 10], fields[indeks + 20] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 21]) == true || isOnSurrounding(fields[indeks + 21]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 11, indeks + 21 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 11], fields[indeks + 21] };
				ships.push_back(Ship(u, f, surr_f));
			}
		}
		else if (ship_size == 3)
		{
			float u_y = mouse_y - (1.5 * field_size);
			float d_y = mouse_y + (1.5 * field_size);
			int indeks = whichField(l_x, u_y); //indeks_l_u
			int indeks_r_u = whichField(r_x, u_y);
			int indeks_r_d = whichField(r_x, d_y);
			int indeks_l_d = whichField(l_x, d_y);
			int check_indeks = whichField(l_x, u_y + 2 * field_size); //indeks sprawdzajacy, czy lewy dolny rog drugiej kratki znajduje sie w planszy
			//sprawdzenie, czy lewy gorny rog statku albo lewy dolny rog drugiej kratki statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1 || check_indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true || isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 21]) == true || isOnSurrounding(fields[indeks + 21]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 1, indeks + 11, indeks + 21 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 1], fields[indeks + 11], fields[indeks + 21] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (isOnShip(fields[indeks]) == true || isOnSurrounding(fields[indeks]) == true || isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true || isOnShip(fields[indeks + 20]) == true || isOnSurrounding(fields[indeks + 20]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks, indeks + 10, indeks + 20 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks], fields[indeks + 10], fields[indeks + 20] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true || isOnShip(fields[indeks + 20]) == true || isOnSurrounding(fields[indeks + 20]) == true || isOnShip(fields[indeks + 30]) == true || isOnSurrounding(fields[indeks + 30]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = {indeks + 10, indeks + 20, indeks + 30 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 10], fields[indeks + 20], fields[indeks + 30] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 21]) == true || isOnSurrounding(fields[indeks + 21]) == true || isOnShip(fields[indeks + 31]) == true || isOnSurrounding(fields[indeks + 31]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 11, indeks + 21, indeks + 31 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 11], fields[indeks + 21], fields[indeks + 31] };
				ships.push_back(Ship(u, f, surr_f));
			}
		}
		else //ship_size == 4
		{
			float u_y = mouse_y - (2 * field_size);
			float d_y = mouse_y + (2 * field_size);
			int indeks = whichField(l_x, u_y); //indeks_l_u
			int indeks_r_u = whichField(r_x, u_y);
			int indeks_r_d = whichField(r_x, d_y);
			int indeks_l_d = whichField(l_x, d_y);
			int check_indeks = whichField(l_x, u_y + 3 * field_size); //indeks sprawdzajacy, czy lewy dolny rog trzeciej kratki znajduje sie w planszy
			//sprawdzenie, czy lewy gorny rog statku albo lewy dolny rog trzeciej kratki statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1 || check_indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true || isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 21]) == true ||isOnSurrounding(fields[indeks + 21]) == true || isOnShip(fields[indeks + 31]) == true || isOnSurrounding(fields[indeks + 31]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 1, indeks + 11, indeks + 21, indeks + 31 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 1], fields[indeks + 11], fields[indeks + 21], fields[indeks + 31] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (isOnShip(fields[indeks]) == true || isOnSurrounding(fields[indeks]) == true || isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true || isOnShip(fields[indeks + 20]) == true || isOnSurrounding(fields[indeks + 20]) == true || isOnShip(fields[indeks + 30]) == true || isOnSurrounding(fields[indeks + 30]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks, indeks + 10, indeks + 20, indeks + 30 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks], fields[indeks + 10], fields[indeks + 20], fields[indeks + 30] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true || isOnShip(fields[indeks + 20]) == true || isOnSurrounding(fields[indeks + 20]) == true || isOnShip(fields[indeks + 30]) == true || isOnSurrounding(fields[indeks + 30]) == true || isOnShip(fields[indeks + 40]) == true || isOnSurrounding(fields[indeks + 40]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 10, indeks + 20, indeks + 30, indeks + 40 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 10], fields[indeks + 20], fields[indeks + 30], fields[indeks + 40] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 21]) == true || isOnSurrounding(fields[indeks + 21]) == true || isOnShip(fields[indeks + 31]) == true || isOnSurrounding(fields[indeks + 31]) == true || isOnShip(fields[indeks + 41]) == true || isOnSurrounding(fields[indeks + 41]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 11, indeks + 21, indeks + 31, indeks + 41 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 11], fields[indeks + 21], fields[indeks + 31], fields[indeks + 41] };
				ships.push_back(Ship(u, f, surr_f));
			}
		}
	}
	else //ship_orientation == 2  - poziomo
	{
		float u_y = mouse_y - (0.5 * field_size);
		float d_y = mouse_y + (0.5 * field_size);

		if (ship_size == 2)
		{
			float l_x = mouse_x - field_size;
			float r_x = mouse_x + field_size;
			int indeks = whichField(l_x, u_y); //indeks_l_u
			int indeks_r_u = whichField(r_x, u_y);
			int indeks_r_d = whichField(r_x, d_y);
			int indeks_l_d = whichField(l_x, d_y);
			int check_indeks = whichField(l_x + field_size, u_y); //indeks sprawdzajacy, czy prawy gorny rog pierwszej kratki znajduje sie w planszy
			//sprawdzenie, czy lewy gorny rog statku albo prawy gorny rog pierwszej kratki statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1 || check_indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true || isOnShip(fields[indeks + 2]) == true || isOnSurrounding(fields[indeks + 2]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 1, indeks + 2 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 1], fields[indeks + 2] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (isOnShip(fields[indeks]) == true || isOnSurrounding(fields[indeks]) == true || isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks, indeks + 1 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks], fields[indeks + 1] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true || isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 10, indeks + 11 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 10], fields[indeks + 11] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 12]) == true || isOnSurrounding(fields[indeks + 12]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 11, indeks + 12 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
			    vector <Field> f{ fields[indeks + 11], fields[indeks + 12] };
				ships.push_back(Ship(u, f, surr_f));
			}
		}
		else if (ship_size == 3)
		{
			float l_x = mouse_x - (1.5 * field_size);
			float r_x = mouse_x + (1.5 * field_size);
			int indeks = whichField(l_x, u_y); //indeks_l_u
			int indeks_r_u = whichField(r_x, u_y);
			int indeks_r_d = whichField(r_x, d_y);
			int indeks_l_d = whichField(l_x, d_y);
			int check_indeks = whichField(l_x + 2 * field_size, u_y); //indeks sprawdzajacy, czy prawy gorny rog drugiej kratki znajduje sie w planszy
			//sprawdzenie, czy lewy gorny rog statku albo prawy gorny rog drugiej kratki statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1 || check_indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true || isOnShip(fields[indeks + 2]) == true || isOnSurrounding(fields[indeks + 2]) == true || isOnShip(fields[indeks + 3]) == true || isOnSurrounding(fields[indeks + 3]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 1, indeks + 2, indeks + 3 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 1], fields[indeks + 2], fields[indeks + 3] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (isOnShip(fields[indeks]) == true || isOnSurrounding(fields[indeks]) == true || isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true || isOnShip(fields[indeks + 2]) == true || isOnSurrounding(fields[indeks + 2]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks, indeks + 1, indeks + 2 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks], fields[indeks + 1], fields[indeks + 2] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true || isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 12]) == true || isOnSurrounding(fields[indeks + 12]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 10, indeks + 11, indeks + 12 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 10], fields[indeks + 11], fields[indeks + 12] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 12]) == true || isOnSurrounding(fields[indeks + 12]) == true || isOnShip(fields[indeks + 13]) == true || isOnSurrounding(fields[indeks + 13]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 11, indeks + 12, indeks + 13 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 11], fields[indeks + 12], fields[indeks + 13] };
				ships.push_back(Ship(u, f, surr_f));
			}
		}
		else //ship_size == 4
		{
			float l_x = mouse_x - (2 * field_size);
			float r_x = mouse_x + (2 * field_size);
			int indeks = whichField(l_x, u_y); //indeks_l_u
			int indeks_r_u = whichField(r_x, u_y);
			int indeks_r_d = whichField(r_x, d_y);
			int indeks_l_d = whichField(l_x, d_y);
			int check_indeks = whichField(l_x + 3 * field_size, u_y); //indeks sprawdzajacy, czy prawy gorny rog trzeciej kratki znajduje sie w planszy
			//sprawdzenie, czy lewy gorny rog statku albo prawy gorny rog drugiej trzeciej statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1 || check_indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true || isOnShip(fields[indeks + 2]) == true || isOnSurrounding(fields[indeks + 2]) == true || isOnShip(fields[indeks + 3]) == true || isOnSurrounding(fields[indeks + 3]) == true || isOnShip(fields[indeks + 4]) == true || isOnSurrounding(fields[indeks + 4]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 1, indeks + 2, indeks + 3, indeks + 4 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 1], fields[indeks + 2], fields[indeks + 3], fields[indeks + 4] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (isOnShip(fields[indeks]) == true || isOnSurrounding(fields[indeks]) == true || isOnShip(fields[indeks + 1]) == true || isOnSurrounding(fields[indeks + 1]) == true || isOnShip(fields[indeks + 2]) == true || isOnSurrounding(fields[indeks + 2]) == true || isOnShip(fields[indeks + 3]) == true || isOnSurrounding(fields[indeks + 3]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks, indeks + 1, indeks + 2, indeks + 3 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks], fields[indeks + 1], fields[indeks + 2], fields[indeks + 3] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 10]) == true || isOnSurrounding(fields[indeks + 10]) == true || isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 12]) == true || isOnSurrounding(fields[indeks + 12]) == true || isOnShip(fields[indeks + 13]) == true || isOnSurrounding(fields[indeks + 13]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 10, indeks + 11, indeks + 12, indeks + 13 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
			    vector <Field> f{ fields[indeks + 10], fields[indeks + 11], fields[indeks + 12], fields[indeks + 13] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (isOnShip(fields[indeks + 11]) == true || isOnSurrounding(fields[indeks + 11]) == true || isOnShip(fields[indeks + 12]) == true || isOnSurrounding(fields[indeks + 12]) == true || isOnShip(fields[indeks + 13]) == true || isOnSurrounding(fields[indeks + 13]) == true || isOnShip(fields[indeks + 14]) == true || isOnSurrounding(fields[indeks + 14]) == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				vector <int> indeks_of_ship_fields = { indeks + 11, indeks + 12, indeks + 13, indeks + 14 };
				setFieldsSurrounded(indeks_of_ship_fields, surr_f);
				vector <Field> f{ fields[indeks + 11], fields[indeks + 12], fields[indeks + 13], fields[indeks + 14] };
				ships.push_back(Ship(u, f, surr_f));
			}
		}
	}
	return 0;
}

int Board::deployAdvancedShip(float mouse_x, float mouse_y, vector<Field>& created_advanced_ship, bool player_deploy)
{
	int indeks = whichField(mouse_x, mouse_y);
	if (indeks != -1)
	{
		if (created_advanced_ship.empty() == true)
		{
			if (isOnShip(fields[indeks]) == false && isOnSurrounding(fields[indeks]) == false)
			{
				created_advanced_ship.push_back(fields[indeks]);
				return 0;
			}
			return -1;
		}
		else if (created_advanced_ship[created_advanced_ship.size()-1] != fields[indeks])
		{
			int last_ship_indeks = created_advanced_ship.size() - 1;
			if (player_deploy == true)
			{
				if (last_ship_indeks >= 1)
				{
					if (fields[indeks] == created_advanced_ship[last_ship_indeks - 1]) //kiedy najechano kliknieta myszka na przedostatni field w vectorze created_advanced_ship
					{
						created_advanced_ship.pop_back();
						return 0;
					}
				}
			}
			
			float last_field_x = created_advanced_ship[last_ship_indeks].getCoordX();
			float last_field_y = created_advanced_ship[last_ship_indeks].getCoordY();
			float l_x = last_field_x - field_size;
			float r_x = last_field_x + (2 * field_size);
			float u_y = last_field_y - field_size;
			float d_y = last_field_y + (2 * field_size);
			if (mouse_x >= l_x && mouse_x <= r_x && mouse_y >= u_y && mouse_y <= d_y)
			{
				int indeks_left_field = whichField(l_x, last_field_y);
				int indeks_right_field = whichField(last_field_x + field_size, last_field_y);
				int indeks_upper_field = whichField(last_field_x, u_y);
				int indeks_down_field = whichField(last_field_x, last_field_y + field_size);
				if (indeks == indeks_left_field || indeks == indeks_right_field || indeks == indeks_upper_field || indeks == indeks_down_field)
				{
					if (player_deploy == true)
					{
						for (Field f : created_advanced_ship)
						{
							if (fields[indeks] == f)
								return -1;
						}
					}
					else //player_deploy == false
					{
						for (Field f : created_advanced_ship)
						{
							if (fields[indeks] == f)
								return 1;
						}
					}

					if (isOnShip(fields[indeks]) == false && isOnSurrounding(fields[indeks]) == false)
					{
						created_advanced_ship.push_back(fields[indeks]);
						return 0;
					}
					
					if (player_deploy == true)
						return -1;
					return 1;
				}
				if (player_deploy == true)
					return -1;
				return 1;
			}
			if (player_deploy == true)
				return -1;
			return 1;
		}
		return 1;
	}
	return -1;
}

void Board::addAdvancedShip(vector<Field>& created_advanced_ship)
{
	numbers_of_not_deployed_ships[created_advanced_ship.size() - 1]--;
	vector <int> indeks_of_ship_fields;
	vector <Field> surr_f; //vector zawierajacy surrounding fieldy; wsadzany potem do vectora shipow
	for (Field f : created_advanced_ship)
	{
		int indeks = whichField(f.getCoordX(), f.getCoordY());
		indeks_of_ship_fields.push_back(indeks);
	}
	setFieldsSurrounded(indeks_of_ship_fields, surr_f);
	ships.push_back(Ship(u, created_advanced_ship, surr_f));
}

int Board::whichQuarterOfField(float c_x, float c_y, float center_of_field_x, float center_of_field_y)
{
	if (c_x <= center_of_field_x)
	{
		if (c_y <= center_of_field_y)
			return 2;
		else
			return 3;
	}
	else
	{
		if (c_y <= center_of_field_y)
			return 1;
		else
			return 4;
	}
}

void Board::clearVectors()
{
	ships.clear();
	fields.clear();
	numbers_of_not_deployed_ships.clear();
}

bool Board::isOnShip(Field& to_check_field)
{
	for (Ship s : ships)
	{
		if (s.isOnShip(to_check_field) == true)
			return true;
	}
	return false;
}

bool Board::isOnSurrounding(Field& to_check_field)
{
	for (Ship s : ships)
	{
		if (s.isOnSurrounding(to_check_field) == true)
			return true;
	}
	return false;
}