#include "Utils.h"

float Utils::mouse_x = 0;
float Utils::mouse_y = 0;

Utils::Utils()
{
	mouse_clicked_before_state_switch = false;
	mouse_1_click_guard = true;
	mouse_2_click_guard = true;
	running = true;
	mouse1_clicked = false;
	mouse2_clicked = false;
	key_space_pressed = false;
	key_up_pressed = false;
	key_down_pressed = false;
	key_left_pressed = false;
	key_right_pressed = false;
	/*poczatek wybranych trybow gry*/
	classic_game_mode = true;
	advanced_game_mode = false;
	pvc_game_mode = true;
	pvp_game_mode = false;
	volume_on = true;
	/*koniec wybranych trybow gry*/
	ship_size = 1;
	ship_orientation = 1;
	audio_samples = 6; //do zmiany jezeli bedzie wiecej audio sampli
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
	al_uninstall_audio();
}

ALLEGRO_COLOR Utils::color(float r, float g, float b)
{
	return al_map_rgb(r, g, b);
}

bool Utils::getRunning()
{
	return running;
}

bool Utils::getMouseClickedBeforeStateSwitch()
{
	return mouse_clicked_before_state_switch;
}

float Utils::getMouseX()
{
	return mouse_x;
}

float Utils::getMouseY()
{
	return mouse_y;
}

bool Utils::getMouse1ClickGuard()
{
	return mouse_1_click_guard;
}

bool Utils::getMouse2ClickGuard()
{
	return mouse_2_click_guard;
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

bool Utils::getClassicGameMode()
{
	return classic_game_mode;
}

bool Utils::getAdvancedGameMode()
{
	return advanced_game_mode;
}

bool Utils::getPvCGameMode()
{
	return pvc_game_mode;
}

bool Utils::getPvPGameMode()
{
	return pvp_game_mode;
}

bool Utils::getVolumeOn()
{
	return volume_on;
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

void Utils::setMouseClickedBeforeStateSwitch(bool c)
{
	mouse_clicked_before_state_switch = c;
}

void Utils::setMouseX(float x)
{
	mouse_x = x;
}

void Utils::setMouseY(float y)
{
	mouse_y = y;
}

void Utils::setMouse1ClickGuard(bool g)
{
	mouse_1_click_guard = g;
}

void Utils::setMouse2ClickGuard(bool g)
{
	mouse_2_click_guard = g;
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

void Utils::setClassicGameMode(bool b)
{
	classic_game_mode = b;
}

void Utils::setAdvancedGameMode(bool b)
{
	advanced_game_mode = b;
}

void Utils::setPvCGameMode(bool b)
{
	pvc_game_mode = b;
}

void Utils::setPvPGameMode(bool b)
{
	pvp_game_mode = b;
}

void Utils::setVolumeOn(bool b)
{
	volume_on = b;
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
	samples.push_back(al_load_sample("button_highlight.wav")); //0
	samples.push_back(al_load_sample("mouse_click.wav")); //1
	samples.push_back(al_load_sample("placed_ship.wav")); //2
	samples.push_back(al_load_sample("missed_shot.wav")); //3
	samples.push_back(al_load_sample("hitted_ship.wav")); //4
	samples.push_back(al_load_sample("error.wav")); //5
	
}

void Utils::loadFonts()
{
	//Wczesniej bylo: al_load_font
	fonts.push_back(al_load_ttf_font("PiratesBay.ttf", 15, 0)); //0
	fonts.push_back(al_load_ttf_font("PiratesBay.ttf", 35, 0)); //1
	fonts.push_back(al_load_ttf_font("PiratesBay.ttf", 130, 0)); //2
	
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

void Utils::drawBorders(float x, float y, float width, float height, float thickness, float r, float g, float b)
{
	al_draw_rectangle(x, y, x + width, y + height, color(r, g, b), thickness);
}

void Utils::restoreDefaults()
{
	classic_game_mode = true;
	advanced_game_mode = false;
	pvc_game_mode = true;
	pvp_game_mode = false;
	volume_on = true;
	number_of_one_masted_ships = 4;
	number_of_two_masted_ships = 3;
	number_of_three_masted_ships = 2;
	number_of_four_masted_ships = 1;

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