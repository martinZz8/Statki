#include "Field.h"

Field& Field::operator=(Field& f)
{
	this->c_x = f.c_x;
	this->c_y = f.c_y;
	this->occupied_flag = f.occupied_flag;
	this->hitted_flag = f.hitted_flag;
	this->missed_flag = f.missed_flag;
	this->surrounded_flag = f.surrounded_flag;
	return *this;
}

Field::Field(Utils& utils, float c_x, float c_y):u(utils),c_x(c_x),c_y(c_y)
{
	width = u.getFieldSize();
	occupied_flag = false;
	hitted_flag = false;
	missed_flag = false;
	surrounded_flag = false;
}

Field::~Field()
{

}

void Field::setCoordX(float c_x)
{
	this->c_x = c_x;
}

void Field::setCoordY(float c_y)
{
	this->c_y = c_y;
}

void Field::setOccupied(bool o)
{
	occupied_flag = o;
}

void Field::setHit(bool h)
{
	hitted_flag = h;
}

void Field::setMiss(bool m)
{
	missed_flag = m;
}

void Field::setSurrounded(bool s)
{
	surrounded_flag = s;
}

float Field::getCoordX()
{
	return c_x;
}

float Field::getCoordY()
{
	return c_y;
}

bool Field::getOccupied()
{
	return occupied_flag;
}

bool Field::getHit()
{
	return hitted_flag;
}

bool Field::getMiss()
{
	return missed_flag;
}

bool Field::getSurrounded()
{
	return surrounded_flag;
}

void Field::paintField(int scheme)
{
	if (scheme == SCHEME_OF_FIELD) //zwykle pole fielda
		al_draw_filled_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfField());
	else if (scheme == SCHEME_OF_SHIP) //brazowy field statku
		al_draw_filled_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfShip());
	else if (scheme == SCHEME_OF_HIT) //czerwony krzyzyk na fieldzie
	{
		al_draw_line(c_x, c_y, c_x + width, c_y + width, u.getColorOfHit(), 2);
		al_draw_line(c_x + width, c_y, c_x, c_y + width, u.getColorOfHit(), 2);
	}
	else if (scheme == SCHEME_OF_SURROUNDED) //ciemniejsze pole na fieldzie
		al_draw_filled_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfSurrounded());
	al_draw_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfLine(), 3); //rysowanie otoczki fielda
	
}
