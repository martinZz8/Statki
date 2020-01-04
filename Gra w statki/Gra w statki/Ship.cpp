#include "Ship.h"

Ship::Ship(Utils& utils, vector<Field> ship_f, vector<Field> surr_f) :u(utils), ship_fields(ship_f), surrounded_fields(surr_f)
{
	ship_destroyed_flag = false;
}

void Ship::setShipDestroyedFlag(vector <int>& numbers_of_not_destroyed_ships)
{
	int number_of_hits = 0;
	int size_of_vector = ship_fields.size();
	for (int indeks = 0; indeks < size_of_vector; indeks++)
	{
		if (ship_fields[indeks].getHit() == true)
			number_of_hits++;
	}

	if (number_of_hits == size_of_vector)
	{
		numbers_of_not_destroyed_ships[size_of_vector - 1]--;
		ship_destroyed_flag = true;
	}
	else
		ship_destroyed_flag = false;	
}

int Ship::setShipHitted(Field& field, vector <int>& numbers_of_not_destroyed_ships)
{
	int size_of_vector_1 = ship_fields.size();
	for (int indeks = 0; indeks < size_of_vector_1; indeks++)
	{
		if (ship_fields[indeks] == field)
		{
			if (ship_fields[indeks].getHit() == false)
			{
				ship_fields[indeks].setHit(true);
				setShipDestroyedFlag(numbers_of_not_destroyed_ships);
				return 0; //trafiono ten field statku
			}
			return 1; //juz wczesniej trafiony field statku
		}
	}

	if (ship_destroyed_flag == true && u.getHintsOn() == true)
	{
		int size_of_vector_2 = surrounded_fields.size();
		for (int indeks = 0; indeks < size_of_vector_2; indeks++)
		{
			if (surrounded_fields[indeks] == field)
				return 1; //trafiono surrounded field
		}
	}
	return -1; //nie trafionio tego statku
}

void Ship::copyShip(vector<Field>& new_ship_fields, vector<Field>& new_surrounded_fields)
{
	if (new_ship_fields.empty() == false)
		new_ship_fields.clear();
	if (new_surrounded_fields.empty() == false)
		new_surrounded_fields.clear();
	for (Field s_f : ship_fields)
		new_ship_fields.push_back(s_f);
	for (Field surr_f : surrounded_fields)
		new_surrounded_fields.push_back(surr_f);
}

void Ship::copyShipFields(vector<Field>& fields)
{
	if (fields.empty() == false)
		fields.clear();
	for (Field f : ship_fields)
		fields.push_back(f);	
}

void Ship::setShipFields(vector<Field>& new_ship_f)
{
	ship_fields.clear();
	for (Field f : new_ship_f)
		ship_fields.push_back(f);
}

void Ship::setSurroundedFields(vector<Field>& new_surr_f)
{
	surrounded_fields.clear();
	for (Field f : new_surr_f)
		surrounded_fields.push_back(f);
}

void Ship::setShip(Ship& ship)
{
	setShipFields(ship.ship_fields);
	setSurroundedFields(ship.surrounded_fields);
}

void Ship::moveShipFields(float offset_x, float offset_y)
{
	for (Field f : ship_fields)
	{
		float last_x = f.getCoordX();
		float last_y = f.getCoordY();
		f.setCoordX(last_x + offset_x);
		f.setCoordY(last_y + offset_y);
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

int Ship::getNumberOfHittedFields()
{
	int number_of_hitted_fields = 0;
	int size_of_vector = ship_fields.size();
	for (int indeks = 0; indeks < size_of_vector; indeks++)
	{
		if (ship_fields[indeks].getHit() == true)
			number_of_hitted_fields++;
	}
	return number_of_hitted_fields;
}

bool Ship::getShipDestroyedFlag()
{
	return ship_destroyed_flag;
}

void Ship::getShipFields(vector<float>& coord_x, vector<float>& coord_y)
{
	int size_of_vector = ship_fields.size();
	for (int indeks = 0; indeks < size_of_vector; indeks++)
	{
		if (ship_fields[indeks].getHit() == true)
		{
			coord_x.push_back(ship_fields[indeks].getCoordX());
			coord_y.push_back(ship_fields[indeks].getCoordY());
		}
	}
}

vector<Field>& Ship::getShipFields()
{
	return ship_fields;
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

bool Ship::isOnOtherShip(Field& checked_field, vector <Field>& this_ship_fields)
{
	if (this_ship_fields.size() == ship_fields.size())
	{
		int iter = 0;
		for (Field this_field : this_ship_fields)
		{
			for (Field actual_ship_field : ship_fields)
			{
				if (this_field == actual_ship_field)
				{
					iter++;
					break;
				}
			}
		}
		if (iter == this_ship_fields.size()) //ten sam statek
			return false;
	}
	
	for (Field f : ship_fields)
	{
		if (f == checked_field)
			return true;
	}
	return false;
}

void Ship::clearShipFields()
{
	if (ship_fields.empty() == false)
		ship_fields.clear();
}

void Ship::clearSurroundingFields()
{
	if (surrounded_fields.empty() == false)
		surrounded_fields.clear();
}