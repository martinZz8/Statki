#include "Field.h"

Field::Field(Utils& utils):u(utils)
{
	c_x = 0;
	c_y = 0;
	x_board_pos = 0;
	y_board_pos = 0;
	width = u.getFieldSize();
	occupied = false;
	hit = false;
	surrounded = false;
}

Field::~Field()
{

}
void Field::setCoords(float x, float y)
{
	c_x = x;
	c_y = y;
}

void Field::setOccupied(bool o)
{
	occupied = o;
}

void Field::setHit(bool h)
{
	hit = h;
}

void Field::setSurrounded(bool s)
{
	surrounded = s;
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
	return occupied;
}

bool Field::getHit()
{
	return hit;
}

bool Field::getSurrounded()
{
	return surrounded;
}

void Field::calculate_board_position(int x_board_offset, int y_board_offset, int c_x, int c_y, float mouse_x, float mouse_y)
{
	x_board_pos = (c_x - x_board_offset) / width;
	y_board_pos = (c_y - y_board_offset) / width;
}

void Field::paintField()
{
	al_draw_filled_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfBoard());
	al_draw_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfLine(), 3);
}
