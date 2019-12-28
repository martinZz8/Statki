#include "Board.h"

//Board& Board::operator=(const Board& b)
//{
//	this->ships = b.ships;
//	return *this;
//}

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

bool Board::getDeployShipsFlag()
{
	return deploy_ships_flag;
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

void Board::paintBoard(bool visible_ships, bool deploying_surrounded)
{
	/*Rysowanie fieldow*/
	for (Field f : fields)
	{
		f.paintField(SCHEME_OF_FIELD);
		if (f.getSurrounded() == true && deploying_surrounded == true) //rysowanie surrounded dla deploying
		{
			f.paintField(SCHEME_OF_SURROUNDED);
		}
		else if (f.getMiss() == true)
		{
			f.paintField(SCHEME_OF_SURROUNDED);
		}
	}

	/*Rysowanie statkow i fieldow surrounded zniszczonych statkow*/
	for (Ship s : ships)
	{
		s.paintShip(visible_ships);
	}

}

vector<Field> Board::setFieldsSurrounded(int indeks, bool surrounded)
{
	int offset = -11;
	vector <int> prohibited_offsets;
	vector <Field> surrounded_fields;
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

	int vector_size = prohibited_offsets.size();
	for (int i = 1; i <= 8; i++, offset++)
	{
		int new_indeks = indeks + offset;
		bool flag = true; //flaga wskazujaca, czy potencjalnie mozna zaznaczyc danego fielda za sasiadujacego ze statkiem
		for (int j = 0; j < vector_size; j++)
		{
			if (offset == prohibited_offsets[j])
			{
				flag = false;
				break;
			}
		}
		if (new_indeks >= 0 && new_indeks <= 99 && flag == true)
			if (fields[new_indeks].getOccupied() == false)
			{
				fields[new_indeks].setSurrounded(surrounded);
				cout << "Dodalem surrounded na " << surrounded << endl;
				surrounded_fields.push_back(fields[new_indeks]);
			}
		if (offset == -9)
			offset = -2;
		else if (offset == -1)
			offset = 0;
		else if (offset == 1)
			offset = 8;
	}
	return surrounded_fields;
}

void Board::setNumbersOfNotDeployedShips()
{
	if (numbers_of_not_deployed_ships.empty() == false)
	{
		numbers_of_not_deployed_ships.clear();
		numbers_of_not_deployed_ships.clear();
	}
	numbers_of_not_deployed_ships.push_back(u.getNumberOfOneMastedShips()); //indeks 0
	numbers_of_not_deployed_ships.push_back(u.getNumberOfTwoMastedShips()); //indeks 1
	numbers_of_not_deployed_ships.push_back(u.getNumberOfThreeMastedShips()); //indeks 2
	numbers_of_not_deployed_ships.push_back(u.getNumberOfFourMastedShips()); //indeks 3
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
	//zwrocenie -1 oznacza, ¿e pod danymi koordynatami mouse_x i mouse_y nie ma fielda
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

//TODO ZMIENIC UZYWAJAC UNIWERSALNYCH FUNKCJI
int Board::deployClassicShip(float mouse_x, float mouse_y)
{
	int ship_orientation = u.getShipOrientation();
	int ship_size = u.getShipSize();
	vector <Field> surr_f; //vector zawierajacy surrounding fieldy
	vector <Field> to_insert; //vector do dodania surrounding fieldow
	
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
			if (fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true)
				return -1;
			numbers_of_not_deployed_ships[ship_size - 1]--;
			fields[indeks + 1].setOccupied(true);
			surr_f = setFieldsSurrounded(indeks + 1, true);
			vector <Field> f{ fields[indeks + 1] };
			ships.push_back(Ship(u, f, surr_f));
			cout << "Wypisanie surr_f dla ship_size 1" << endl;
			int iter = 0;
			for (Field fi : surr_f)
			{
				cout << iter << ": " << fi.getSurrounded() << endl;
				iter++;
			}
		}
		else if (quarter_of_field == 2) //postawienie w fieldzie o indeksie "indeks"
		{
			if (fields[indeks].getOccupied() == true || fields[indeks].getSurrounded() == true)
				return -1;
			numbers_of_not_deployed_ships[ship_size - 1]--;
			fields[indeks].setOccupied(true);
			surr_f = setFieldsSurrounded(indeks, true);
			vector <Field> f{ fields[indeks] };
			ships.push_back(Ship(u, f, surr_f));
		}
		else if (quarter_of_field == 3)
		{
			//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
			if (indeks_l_d == -1)
				return -1;
			if (fields[indeks + 10].getOccupied() == true || fields[indeks + 10].getSurrounded() == true)
				return -1;
			numbers_of_not_deployed_ships[ship_size - 1]--;
			fields[indeks + 10].setOccupied(true);
			surr_f = setFieldsSurrounded(indeks + 10, true);
			vector <Field> f{ fields[indeks + 10] };
			ships.push_back(Ship(u, f, surr_f));
		}
		else //quarter_of_field == 4
		{
			//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
			if (indeks_r_d == -1)
				return -1;
			if (fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true)
				return -1;
			numbers_of_not_deployed_ships[ship_size - 1]--;
			fields[indeks + 11].setOccupied(true);
			surr_f = setFieldsSurrounded(indeks + 11, true);
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
			//sprawdzenie, czy lewy gorny rog statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true || fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 1].setOccupied(true);
				fields[indeks + 11].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 1, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 1], fields[indeks + 11] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (fields[indeks].getOccupied() == true || fields[indeks].getSurrounded() == true || fields[indeks+10].getOccupied() == true || fields[indeks+10].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks].setOccupied(true);
				fields[indeks+10].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 10, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks], fields[indeks + 10] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (fields[indeks + 10].getOccupied() == true || fields[indeks + 10].getSurrounded() == true || fields[indeks + 20].getOccupied() == true || fields[indeks + 20].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 10].setOccupied(true);
				fields[indeks + 20].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 10, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 20, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 10], fields[indeks + 20] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 21].getOccupied() == true || fields[indeks + 21].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 21].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 21, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
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
			//sprawdzenie, czy lewy gorny rog statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true || fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 21].getOccupied() == true || fields[indeks + 21].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 1].setOccupied(true);
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 21].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 1, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 21, true);
				vector <Field> f{ fields[indeks + 1], fields[indeks + 11], fields[indeks + 21] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (fields[indeks].getOccupied() == true || fields[indeks].getSurrounded() == true || fields[indeks + 10].getOccupied() == true || fields[indeks + 10].getSurrounded() == true || fields[indeks + 20].getOccupied() == true || fields[indeks + 20].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks].setOccupied(true);
				fields[indeks + 10].setOccupied(true);
				fields[indeks + 20].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 10, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 20, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks], fields[indeks + 10], fields[indeks + 20] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (fields[indeks + 10].getOccupied() == true || fields[indeks + 10].getSurrounded() == true || fields[indeks + 20].getOccupied() == true || fields[indeks + 20].getSurrounded() == true || fields[indeks + 30].getOccupied() == true || fields[indeks + 30].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 10].setOccupied(true);
				fields[indeks + 20].setOccupied(true);
				fields[indeks + 30].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 10, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 20, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 30, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 10], fields[indeks + 20], fields[indeks + 30] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 21].getOccupied() == true || fields[indeks + 21].getSurrounded() == true || fields[indeks + 31].getOccupied() == true || fields[indeks + 31].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 21].setOccupied(true);
				fields[indeks + 31].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 21, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 31, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
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
			//sprawdzenie, czy lewy gorny rog statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true || fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 21].getOccupied() == true || fields[indeks + 21].getSurrounded() == true || fields[indeks + 31].getOccupied() == true || fields[indeks + 31].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 1].setOccupied(true);
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 21].setOccupied(true);
				fields[indeks + 31].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 1, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 21, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 31, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 1], fields[indeks + 11], fields[indeks + 21], fields[indeks + 31] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (fields[indeks].getOccupied() == true || fields[indeks].getSurrounded() == true || fields[indeks + 10].getOccupied() == true || fields[indeks + 10].getSurrounded() == true || fields[indeks + 20].getOccupied() == true || fields[indeks + 20].getSurrounded() == true || fields[indeks + 30].getOccupied() == true || fields[indeks + 30].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks].setOccupied(true);
				fields[indeks + 10].setOccupied(true);
				fields[indeks + 20].setOccupied(true);
				fields[indeks + 30].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 10, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 20, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 30, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks], fields[indeks + 10], fields[indeks + 20], fields[indeks + 30] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (fields[indeks + 10].getOccupied() == true || fields[indeks + 10].getSurrounded() == true || fields[indeks + 20].getOccupied() == true || fields[indeks + 20].getSurrounded() == true || fields[indeks + 30].getOccupied() == true || fields[indeks + 30].getSurrounded() == true || fields[indeks + 40].getOccupied() == true || fields[indeks + 40].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 10].setOccupied(true);
				fields[indeks + 20].setOccupied(true);
				fields[indeks + 30].setOccupied(true);
				fields[indeks + 40].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 10, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 20, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 30, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 40, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 10], fields[indeks + 20], fields[indeks + 30], fields[indeks + 40] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 21].getOccupied() == true || fields[indeks + 21].getSurrounded() == true || fields[indeks + 31].getOccupied() == true || fields[indeks + 31].getSurrounded() == true || fields[indeks + 41].getOccupied() == true || fields[indeks + 41].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 21].setOccupied(true);
				fields[indeks + 31].setOccupied(true);
				fields[indeks + 41].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 21, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 31, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 41, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
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
			//sprawdzenie, czy lewy gorny rog statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true || fields[indeks + 2].getOccupied() == true || fields[indeks + 2].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 1].setOccupied(true);
				fields[indeks + 2].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 1, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 2, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 1], fields[indeks + 2] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (fields[indeks].getOccupied() == true || fields[indeks].getSurrounded() == true || fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks].setOccupied(true);
				fields[indeks + 1].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 1, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks], fields[indeks + 1] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (fields[indeks + 10].getOccupied() == true || fields[indeks + 10].getSurrounded() == true || fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 10].setOccupied(true);
				fields[indeks + 11].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 10, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 10], fields[indeks + 11] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 12].getOccupied() == true || fields[indeks + 12].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 12].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 12, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
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
			//sprawdzenie, czy lewy gorny rog statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true || fields[indeks + 2].getOccupied() == true || fields[indeks + 2].getSurrounded() == true || fields[indeks + 3].getOccupied() == true || fields[indeks + 3].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 1].setOccupied(true);
				fields[indeks + 2].setOccupied(true);
				fields[indeks + 3].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 1, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 2, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 3, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 1], fields[indeks + 2], fields[indeks + 3] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (fields[indeks].getOccupied() == true || fields[indeks].getSurrounded() == true || fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true || fields[indeks + 2].getOccupied() == true || fields[indeks + 2].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks].setOccupied(true);
				fields[indeks + 1].setOccupied(true);
				fields[indeks + 2].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 1, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 2, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks], fields[indeks + 1], fields[indeks + 2] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (fields[indeks + 10].getOccupied() == true || fields[indeks + 10].getSurrounded() == true || fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 12].getOccupied() == true || fields[indeks + 12].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 10].setOccupied(true);
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 12].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 10, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 12, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 10], fields[indeks + 11], fields[indeks + 12] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 12].getOccupied() == true || fields[indeks + 12].getSurrounded() == true || fields[indeks + 13].getOccupied() == true || fields[indeks + 13].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 12].setOccupied(true);
				fields[indeks + 13].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 12, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 13, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
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
			//sprawdzenie, czy lewy gorny rog statku znajduje sie w planszy, jezeli nie to nie dodajemy tego statku
			if (indeks == -1)
				return -1;
			float center_of_field_l_x = fields[indeks].getCoordX() + (0.5 * field_size);
			float center_of_field_u_y = fields[indeks].getCoordY() + (0.5 * field_size);
			int quarter_of_field = whichQuarterOfField(l_x, u_y, center_of_field_l_x, center_of_field_u_y);
			if (quarter_of_field == 1)
			{
				//jezeli prawy gorny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_r_u == -1)
					return -1;
				if (fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true || fields[indeks + 2].getOccupied() == true || fields[indeks + 2].getSurrounded() == true || fields[indeks + 3].getOccupied() == true || fields[indeks + 3].getSurrounded() == true || fields[indeks + 4].getOccupied() == true || fields[indeks + 4].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 1].setOccupied(true);
				fields[indeks + 2].setOccupied(true);
				fields[indeks + 3].setOccupied(true);
				fields[indeks + 4].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 1, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 2, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 3, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 4, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 1], fields[indeks + 2], fields[indeks + 3], fields[indeks + 4] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 2)
			{
				if (fields[indeks].getOccupied() == true || fields[indeks].getSurrounded() == true || fields[indeks + 1].getOccupied() == true || fields[indeks + 1].getSurrounded() == true || fields[indeks + 2].getOccupied() == true || fields[indeks + 2].getSurrounded() == true || fields[indeks + 3].getOccupied() == true || fields[indeks + 3].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks].setOccupied(true);
				fields[indeks + 1].setOccupied(true);
				fields[indeks + 2].setOccupied(true);
				fields[indeks + 3].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 1, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 2, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 3, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks], fields[indeks + 1], fields[indeks + 2], fields[indeks + 3] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else if (quarter_of_field == 3)
			{
				//jezeli lewy dolny rog statku jest poza mapa, to nie dodajemy go
				if (indeks_l_d == -1)
					return -1;
				if (fields[indeks + 10].getOccupied() == true || fields[indeks + 10].getSurrounded() == true || fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 12].getOccupied() == true || fields[indeks + 12].getSurrounded() == true || fields[indeks + 13].getOccupied() == true || fields[indeks + 13].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 10].setOccupied(true);
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 12].setOccupied(true);
				fields[indeks + 13].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 10, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 12, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 13, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 10], fields[indeks + 11], fields[indeks + 12], fields[indeks + 13] };
				ships.push_back(Ship(u, f, surr_f));
			}
			else //quarter_of_field == 4
			{
				//jezeli statek jest przy dolnej krawedzi i prawej krawedzi, to wtedy nie dodajemy go na mape
				if (indeks_r_d == -1)
					return -1;
				if (fields[indeks + 11].getOccupied() == true || fields[indeks + 11].getSurrounded() == true || fields[indeks + 12].getOccupied() == true || fields[indeks + 12].getSurrounded() == true || fields[indeks + 13].getOccupied() == true || fields[indeks + 13].getSurrounded() == true || fields[indeks + 14].getOccupied() == true || fields[indeks + 14].getSurrounded() == true)
					return -1;
				numbers_of_not_deployed_ships[ship_size - 1]--;
				fields[indeks + 11].setOccupied(true);
				fields[indeks + 12].setOccupied(true);
				fields[indeks + 13].setOccupied(true);
				fields[indeks + 14].setOccupied(true);
				to_insert = setFieldsSurrounded(indeks + 11, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 12, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 13, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				to_insert = setFieldsSurrounded(indeks + 14, true);
				surr_f.insert(surr_f.end(), to_insert.begin(), to_insert.end());
				vector <Field> f{ fields[indeks + 11], fields[indeks + 12], fields[indeks + 13], fields[indeks + 14] };
				ships.push_back(Ship(u, f, surr_f));
			}
		}
	}
	return 0;
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
