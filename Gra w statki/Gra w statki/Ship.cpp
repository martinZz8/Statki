#include "Ship.h"

Ship::Ship(Utils& utils) :u(utils)
{
	remaining_parts = 0;
	number_of_fields = 0;
}

//Ship::Ship()
//{
//	remaining_parts = 0;
//	number_of_fields = 0;
//}

Ship::~Ship()
{

}

void Ship::setFields(Field f)
{
	fields.push_back(f);
}

void Ship::setNumberOfFields(int n)
{
	number_of_fields = n;
}

//void Ship::setHitField(float x_mouse, float y_mouse)
//{
//
//}

float Ship::getCoordX(int indeks_vfields)
{
	if (indeks_vfields < number_of_fields)
		return fields[indeks_vfields].getCoordX();
	else return -1;
}

float Ship::getCoordY(int indeks_vfields)
{
	if (indeks_vfields < number_of_fields)
		return fields[indeks_vfields].getCoordY();
	else return -1;
}

int Ship::getNumberOfFields()
{
	return number_of_fields;
}
