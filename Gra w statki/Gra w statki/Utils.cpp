#include "Utils.h"

float Utils::mouse_x = 0;
float Utils::mouse_y = 0;

Utils::Utils()
{
	running = true;
	actual_window = -1;
	mouse1_clicked = false;
	mouse2_clicked = false;
	key_space_pressed = false;
	key_up_pressed = false;
	key_down_pressed = false;
	key_left_pressed = false;
	key_right_pressed = false;
	ship_size = 1;
	ship_orientation = 1;
	audio_samples = 2; //do zmiany jezeli bedzie wiecej audio sampli
	font_samples = 3; //do zmiany jezeli bedzie wiecej font sampli
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
	loadAudio();
	loadFonts();
	
}

Utils::~Utils()
{
	for (int i = 0; i < audio_samples; i++)
		al_destroy_sample(samples[i]);
	for (int i = 0; i < font_samples; i++)
		al_destroy_font(fonts[i]);
}

ALLEGRO_COLOR Utils::color(float r, float g, float b)
{
	return al_map_rgb(r, g, b);
}

bool Utils::getRunning()
{
	return running;
}

int Utils::getActualWindow()
{
	return actual_window;
}

float Utils::getMouseX()
{
	return mouse_x;
}

float Utils::getMouseY()
{
	return mouse_y;
}

bool Utils::getMouse1Clicked()
{
	return mouse1_clicked;
}

bool Utils::getMouse2Clicked()
{
	return mouse2_clicked;
}

bool Utils::getKeySpacePressed()
{
	return key_space_pressed;
}

bool Utils::getKeyUpPressed()
{
	return key_up_pressed;
}

bool Utils::getKeyDownPressed()
{
	return key_down_pressed;
}

bool Utils::getKeyLeftPressed()
{
	return key_left_pressed;
}

bool Utils::getKeyRightPressed()
{
	return key_right_pressed;
}

int Utils::getShipSize()
{
	return ship_size;
}

int Utils::getShipOrientation()
{
	return ship_orientation;
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

void Utils::setRunning(bool b)
{
	running = b;
}

void Utils::setActualWindow(int w)
{
	actual_window = w;
}

void Utils::setMouseX(float x)
{
	mouse_x = x;
}

void Utils::setMouseY(float y)
{
	mouse_y = y;
}

void Utils::setMouse1Clicked(bool b)
{
	mouse1_clicked = b;
}

void Utils::setMouse2Clicked(bool b)
{
	mouse2_clicked = b;
}

void Utils::setKeySpacePressed(bool b)
{
	key_space_pressed = b;
}

void Utils::setKeyUpPressed(bool b)
{
	key_up_pressed = b;
}

void Utils::setKeyDownPressed(bool b)
{
	key_down_pressed = b;
}

void Utils::setKeyLeftPressed(bool b)
{
	key_left_pressed = b;
}

void Utils::setKeyRightPressed(bool b)
{
	key_right_pressed = b;
}

void Utils::setShipSize(int s)
{
	ship_size = s;
}

void Utils::setShipOrientation(int o)
{
	ship_orientation = o;
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

void Utils::loadAudio()
{
	samples.push_back(al_load_sample("menu_click.wav")); //0
	samples.push_back(al_load_sample("placed_ship.wav")); //1
	
	
}

void Utils::loadFonts()
{
	
	fonts.push_back(al_load_font("PiratesBay.ttf", 15, 0)); //0
	fonts.push_back(al_load_font("PiratesBay.ttf", 35, 0)); //1
	fonts.push_back(al_load_font("PiratesBay.ttf", 130, 0)); //2
	
}

void Utils::playSample(int ID)
{
	al_play_sample(samples[ID], 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Utils::drawText(const char* text,int size, float r,float g, float b, float x, float y)
{
	if(size == FONT_SIZE_SMALL)
		al_draw_text(fonts[FONT_SIZE_SMALL], color(r, g, b), x, y, 0, text);
	else if(size == FONT_SIZE_BIG)
		al_draw_text(fonts[FONT_SIZE_BIG], color(r, g, b), x, y, 0, text);
	else 
		al_draw_text(fonts[FONT_SIZE_HUGE], color(r, g, b), x, y, 0, text);
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