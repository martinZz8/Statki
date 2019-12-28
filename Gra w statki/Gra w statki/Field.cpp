#include "Field.h"

Field::Field(Utils& utils, float c_x, float c_y):u(utils),c_x(c_x),c_y(c_y)
{
	x_board_pos = 0;
	y_board_pos = 0;
	width = u.getFieldSize();
	occupied_flag = false;
	hitted_flag = false;
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

bool Field::getSurrounded()
{
	return surrounded_flag;
}

void Field::calculate_board_position(int x_board_offset, int y_board_offset, int c_x, int c_y, float mouse_x, float mouse_y)
{
	x_board_pos = (c_x - x_board_offset) / width;
	y_board_pos = (c_y - y_board_offset) / width;
}

void Field::paintField(int scheme)
{
	if (scheme == SCHEME_OF_FIELD)
		al_draw_filled_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfField());
	else if (scheme == SCHEME_OF_SHIP)
		al_draw_filled_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfShip());
	else if (scheme == SCHEME_OF_HIT)
	{
		al_draw_line(c_x, c_y, c_x + width, c_y + width, u.getColorOfHit(), 2);
		al_draw_line(c_x + width, c_y, c_x, c_y + width, u.getColorOfHit(), 2);
	}
	else if (scheme == SCHEME_OF_SURROUNDED)
		al_draw_filled_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfSurrounded());
	al_draw_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfLine(), 3);
	
}
