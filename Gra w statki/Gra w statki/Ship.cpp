#include "Ship.h"

Ship& Ship::operator=(const Ship& s)
{
	this->fields = s.fields;
	this->surrounded_fields = s.surrounded_fields;
	return *this;
}

Ship::Ship(Utils& utils, vector<Field> f, vector<Field> surr_f):u(utils),fields(f),surrounded_fields(surr_f)
{
	remaining_parts = 0;
	ship_destroyed_flag = false;
}

void Ship::setFields(Field f)
{
	fields.push_back(f);
}

void Ship::setShipDestroyedFlag()
{
	int number_of_hits = 0;
	for (Field f : fields)
	{
		if (f.getHit() == true)
			number_of_hits++;
	}
	if (number_of_hits == fields.size())
		ship_destroyed_flag = true;
	else
		ship_destroyed_flag = false;
}

float Ship::getCoordX(int indeks_vfields)
{
	if (indeks_vfields < fields.size())
		return fields[indeks_vfields].getCoordX();
	else return -1;
}

float Ship::getCoordY(int indeks_vfields)
{
	if (indeks_vfields < fields.size())
		return fields[indeks_vfields].getCoordY();
	else return -1;
}

int Ship::getNumberOfFields()
{
	return fields.size();
}

bool Ship::getShipDestroyedFlag()
{
	return ship_destroyed_flag;
}

void Ship::paintShip(bool visible_ships)
{
	for (Field f : fields)
	{
		if (ship_destroyed_flag == true)
		{
			f.paintField(SCHEME_OF_SHIP);
			f.paintField(SCHEME_OF_HIT);
		}
		else if (visible_ships == true)
			f.paintField(SCHEME_OF_SHIP);
		
		if (f.getHit() == true)
			f.paintField(SCHEME_OF_HIT);
		
	}
	for (Field f : surrounded_fields)
	{
		if (ship_destroyed_flag == true && u.getHintsOn() == true)
		{
			f.paintField(SCHEME_OF_SURROUNDED);
		}
	}
		
}

