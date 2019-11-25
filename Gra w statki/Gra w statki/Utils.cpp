#include "Utils.h"

int Utils::ship_size = 1;
int Utils::ship_orientation = 1;

Utils::Utils()
{
	audio_samples = 1; //do zmiany jezeli bedzie wiecej audio sampli
	display_x = 1000;
	display_y = 600;
	timer = 1.0 / 60;
	board_size = 400;
	mini_board_size = 150;
	field_size = 40;
	number_of_fields = board_size / field_size;
	number_of_one_masted_ships = 4;
	number_of_two_masted_ships = 3;
	number_of_three_masted_ships = 2;
	number_of_four_masted_ships = 1;
	
}

Utils::~Utils()
{

}

ALLEGRO_COLOR Utils::color(float r, float g, float b)
{
	return al_map_rgb(r, g, b);
}

int Utils::getAudioSamples()
{
	return audio_samples;
}

float Utils::getDisplayX()
{
	return display_x;
}

float Utils::getDisplayY()
{
	return display_y;
}

double Utils::getTimer()
{
	return timer;
}

float Utils::getBoardSize()
{
	return board_size;
}

float Utils::getFieldSize()
{
	return field_size;
}

int Utils::getNumberOfFields()
{
	return number_of_fields;
}

int Utils::getNumberOfOneMastedShips()
{
	return number_of_one_masted_ships;
}

int Utils::getNumberOfTwoMastedShips()
{
	return number_of_two_masted_ships;
}

int Utils::getNumberOfThreeMastedShips()
{
	return number_of_three_masted_ships;
}

int Utils::getNumberOfFourMastedShips()
{
	return number_of_four_masted_ships;
}

void Utils::setNumberOfOneMastedShips(int n)
{
	number_of_one_masted_ships = n;
}

void Utils::setNumberOfTwoMastedShips(int n)
{
	number_of_two_masted_ships = n;
}

void Utils::setNumberOfThreeMastedShips(int n)
{
	number_of_three_masted_ships = n;
}

void Utils::setNumberOfFourMastedShips(int n)
{
	number_of_four_masted_ships = n;
}

ALLEGRO_COLOR Utils::getColorOfBackground()
{
	return color(0, 0, 0);
}

ALLEGRO_COLOR Utils::getColorOfBoard()
{
	return color(0, 211, 253);
}

ALLEGRO_COLOR Utils::getColorOfLine()
{
	return color(25, 25, 25);
}

ALLEGRO_COLOR Utils::getColorOfShip()
{
	return color(51, 29, 23);
}