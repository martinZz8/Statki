#include "Board.h"

Board::Board(Utils& utils, float offset_x, float offset_y) :u(utils), offset_x(offset_x), offset_y(offset_y)
{
	width = u.getBoardSize();
	height = u.getBoardSize();
	setted_fields = false;
	made_ships = false;
	number_of_one_masted_ships = u.getNumberOfOneMastedShips();
	number_of_two_masted_ships = u.getNumberOfTwoMastedShips();
	number_of_three_masted_ships = u.getNumberOfThreeMastedShips();
	number_of_four_masted_ships = u.getNumberOfFourMastedShips();
}

//Board::Board()
//{
//	offset_x = 0;
//	offset_y = 0;
//	width = u.getBoardSize();
//	height = u.getBoardSize();
//	setted_fields = false;
//	made_ships = false;
//	number_of_one_masted_ships = u.getNumberOfOneMastedShips();
//	number_of_two_masted_ships = u.getNumberOfTwoMastedShips();
//	number_of_three_masted_ships = u.getNumberOfThreeMastedShips();
//	number_of_four_masted_ships = u.getNumberOfFourMastedShips();
//}

Board::~Board()
{

}

float Board::getXOffset()
{
	return offset_x;
}

float Board::getYOffset()
{
	return offset_y;
}

void Board::setFields()
{
	if (!setted_fields)
	{
		int iter = 0;
		int number_of_fields = u.getNumberOfFields();
		float field_size = u.getFieldSize();
		for (float i = 0; i < number_of_fields; i++) //y
			for (float j = 0; j < number_of_fields; j++) //x
			{
				float x1 = offset_x + (j * field_size);
				float y1 = offset_y + (i * field_size);
				Field field(u);
				field.setCoords(x1, y1);
				fields.push_back(field);
				iter++;
				cout << "Iter: " << iter << endl;
			}
		setted_fields = true;
	}

}

void Board::setOffset(float x, float y)
{
	offset_x = x;
	offset_y = y;
}

void Board::paintBoard()
{
	for (Field f : fields)
		f.render();
}

int Board::whichField(float mouse_x, float mouse_y)
{
	float field_size = u.getFieldSize();
	for (size_t i = 0; i < fields.size(); i++)
	{
		float l_x = fields[i].getCoordX(); //lewe x
		float r_x = fields[i].getCoordX() + field_size; //prawe x
		float u_y = fields[i].getCoordY(); //gorne y
		float d_y = fields[i].getCoordY() + field_size; //dolne y
		if (mouse_x >= l_x && mouse_x < r_x && mouse_y >= u_y && mouse_y < d_y)
		{
			cout << i << endl;
			return i;
		}
	}
	return -1;
}

void Board::setFieldOccupy(float mouse_x, float mouse_y, bool occupied)
{
	int indeks = whichField(mouse_x, mouse_y);
	fields[indeks].setOccupied(occupied);
}

int Board::whichShip(float mouse_x, float mouse_y)
{
	//sprawdzam czy isnieje statek o zadanych parametrach x i y - w tym celu przeszukuje caly vector shipow
	for (size_t i = 0; i < ships.size(); i++)
	{
		//przeszukuje kazde pole z vectora pol w danym statku
		int indeks = 0;
		int number_of_fields = ships[i].getNumberOfFields();
		for (size_t j = 0; j < number_of_fields; j++)
		{
			float l_x = ships[j].getCoordX(indeks); //lewe x
			float r_x = ships[j].getCoordX(indeks) + u.getFieldSize(); //prawe x
			float u_y = ships[j].getCoordY(indeks); //gorne y
			float d_y = ships[j].getCoordY(indeks) + u.getFieldSize(); //dolne y
			if (mouse_x >= l_x && mouse_x < r_x && mouse_y >= u_y && mouse_y < d_y)
			{
				return i;
			}
			indeks++;
		}
	}
}

void Board::paintStandardShip(float mouse_x, float mouse_y)
{
	//RYSOWANIE GDY MAMY USTAWIONE STATKI DOMYSLNE
	if (u.getShipSize() == 1)
	{
		float x1 = mouse_x - 0.5 * u.getFieldSize();
		float y1 = mouse_y - 0.5 * u.getFieldSize();
		float x2 = mouse_x + 0.5 * u.getFieldSize();
		float y2 = mouse_y + 0.5 * u.getFieldSize();
		al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
	}
	else if (u.getShipOrientation() == 1)
	{
		if (u.getShipSize() == 2)
		{
			float x1 = mouse_x - 0.5 * u.getFieldSize();
			float y1 = mouse_y - u.getFieldSize();
			float x2 = mouse_x + 0.5 * u.getFieldSize();
			float y2 = mouse_y + u.getFieldSize();
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
		else if (u.getShipSize() == 3)
		{
			float x1 = mouse_x - 0.5 * u.getFieldSize();
			float y1 = mouse_y - 1.5 * u.getFieldSize();
			float x2 = mouse_x + 0.5 * u.getFieldSize();
			float y2 = mouse_y + 1.5 * u.getFieldSize();
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
		else if (u.getShipSize() == 4)
		{
			float x1 = mouse_x - 0.5 * u.getFieldSize();
			float y1 = mouse_y - 2 * u.getFieldSize();
			float x2 = mouse_x + 0.5 * u.getFieldSize();
			float y2 = mouse_y + 2 * u.getFieldSize();
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
	}
	else if (u.getShipOrientation() == 2)
	{
		if (u.getShipSize() == 2)
		{
			float x1 = mouse_x - u.getFieldSize();
			float y1 = mouse_y - 0.5 * u.getFieldSize();
			float x2 = mouse_x + u.getFieldSize();
			float y2 = mouse_y + 0.5 * u.getFieldSize();
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
		else if (u.getShipSize() == 3)
		{
			float x1 = mouse_x - 1.5 * u.getFieldSize();
			float y1 = mouse_y - 0.5 * u.getFieldSize();
			float x2 = mouse_x + 1.5 * u.getFieldSize();
			float y2 = mouse_y + 0.5 * u.getFieldSize();
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
		else if (u.getShipSize() == 4)
		{
			float x1 = mouse_x - 2 * u.getFieldSize();
			float y1 = mouse_y - 0.5 * u.getFieldSize();
			float x2 = mouse_x + 2 * u.getFieldSize();
			float y2 = mouse_y + 0.5 * u.getFieldSize();
			al_draw_filled_rectangle(x1, y1, x2, y2, u.getColorOfShip());
		}
	}
}

void Board::deployStandardShip(float mouse_x, float mouse_y, int size, int orientation)
{
	//int indeks = whichField(mouse_x, mouse_y);
	//if (size == 1)
	//{		
	//	fields[indeks].setOccupied(1);
	//}
	//else if (size == 2)
	//{
	//	fields[indeks].setOccupied(1);
	//}

}
