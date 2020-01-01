#include "Ship.h"

Ship::Ship(Utils& utils, vector<Field> ship_f, vector<Field> surr_f) :u(utils), ship_fields(ship_f), surrounded_fields(surr_f)
{
	remaining_parts = 0;
	ship_destroyed_flag = false;
}

void Ship::setShipDestroyedFlag()
{
	int number_of_hits = 0;
	for (Field f : ship_fields)
	{
		if (f.getHit() == true)
			number_of_hits++;
	}
	if (number_of_hits == ship_fields.size())
		ship_destroyed_flag = true;
	else
		ship_destroyed_flag = false;
}

int Ship::setShipHitted(Field& field)
{
	for (Field ship_field : ship_fields)
	{
		if (ship_field == field)
		{
			if (field.getHit() == false)
			{
				ship_field.setHit(true);
				return 0;
			}
			else
				return 1;
		}	
	}
	return -1;
}

void Ship::setShipFields(vector<Field>& new_ship_f)
{
	ship_fields.clear();
	for (Field f : new_ship_f)
	{
		ship_fields.push_back(f);
	}
}

void Ship::setSurroundedFields(vector<Field>& new_surr_f)
{
	surrounded_fields.clear();
	for (Field f : new_surr_f)
	{
		surrounded_fields.push_back(f);
	}
}

void Ship::moveShipFields(float offset_x, float offset_y)
{
	for (Field f : ship_fields)
	{
		f.setCoordX(f.getCoordX() + offset_x);
		f.setCoordY(f.getCoordY() + offset_y);
	}
}

void Ship::moveSurroundedFields(float offset_x, float offset_y)
{
	for (Field f : surrounded_fields)
	{
		f.setCoordX(f.getCoordX() + offset_x);
		f.setCoordY(f.getCoordY() + offset_y);
	}
}

float Ship::getCoordX(int indeks_vfields)
{
	if (indeks_vfields < ship_fields.size())
		return ship_fields[indeks_vfields].getCoordX();
	else return -1;
}

float Ship::getCoordY(int indeks_vfields)
{
	if (indeks_vfields < ship_fields.size())
		return ship_fields[indeks_vfields].getCoordY();
	else return -1;
}

int Ship::getNumberOfFields()
{
	return ship_fields.size();
}

bool Ship::getShipDestroyedFlag()
{
	return ship_destroyed_flag;
}

void Ship::paintShip(bool visible_ships, bool const_visible_surrounding)
{
	for (Field f : ship_fields)
	{
		if (ship_destroyed_flag == true)
		{
			f.paintField(SCHEME_OF_SHIP);
		}
		else if (visible_ships == true)
			f.paintField(SCHEME_OF_SHIP);

		if (f.getHit() == true)
			f.paintField(SCHEME_OF_HIT);
	}
	for (Field f : surrounded_fields)
	{
		if(const_visible_surrounding == true)
			f.paintField(SCHEME_OF_SURROUNDED);
		else if (ship_destroyed_flag == true && u.getHintsOn() == true)
		{
			f.paintField(SCHEME_OF_SURROUNDED);
		}
	}
}

bool Ship::isOnShip(Field& checked_field)
{
	for (Field f : ship_fields)
	{
		if (f == checked_field)
			return true;
	}
	return false;
}

bool Ship::isOnSurrounding(Field& checked_surrounding_field)
{
	for (Field surr_f : surrounded_fields)
	{
		if (surr_f == checked_surrounding_field)
			return true;
	}
	return false;
}
