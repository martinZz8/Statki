#include "Field.h"

//Field& Field::operator=(const Field& f)
//{
//	u = f.u;
//	c_x = f.c_x;
//	c_y = f.c_y;
//	width = f.width;
//	hitted_flag = f.hitted_flag;
//	missed_flag = f.missed_flag;
//	return *this;
//}

bool Field::operator==(const Field& f)
{
	if (c_x == f.c_x && c_y == f.c_y)
		return true;
	return false;
}

bool Field::operator!=(const Field& f)
{
	if (c_x != f.c_x || c_y != f.c_y)
		return true;
	return false;
}

Field::Field(Utils& utils, float c_x, float c_y) :u(utils), c_x(c_x), c_y(c_y)
{
	width = u.getFieldSize();
	hitted_flag = false;
	missed_flag = false;
}

void Field::setCoordX(float c_x)
{
	this->c_x = c_x;
}

void Field::setCoordY(float c_y)
{
	this->c_y = c_y;
}

void Field::setHit(bool h)
{
	hitted_flag = h;
}

void Field::setMiss(bool m)
{
	missed_flag = m;
}

float Field::getCoordX()
{
	return c_x;
}

float Field::getCoordY()
{
	return c_y;
}

float Field::getWidth()
{
	return width;
}

bool Field::getHit()
{
	return hitted_flag;
}

bool Field::getMiss()
{
	return missed_flag;
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