#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_color.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define WINDOW_MENU 1
#define WINDOW_GAME 2
#define WINDOW_DEPLOYING 3
#define AUDIO_PLACED_SHIP 0


class Utils
{
	static float mouse_x;
	static float mouse_y;
	int ship_size; //rozmiar statku w danym momencie (ilosc fieldow)
	int ship_orientation; //orientacja statku w danym momencie (1 - do dolu, 2 - na bok)
	int audio_samples;
	float display_x;
	float display_y;
	double timer;
	float board_size;
	float mini_board_size;
	float field_size;
	int number_of_fields;
	int number_of_one_masted_ships; //ilosc jednomasztowcow
	int number_of_two_masted_ships; //ilosc dwumasztowcow
	int number_of_three_masted_ships; //ilosc trojmasztowcow
	int number_of_four_masted_ships; //ilosc czteromasztowcow
public:
	Utils();
	~Utils();
	ALLEGRO_COLOR color(float r, float g, float b);
	float getMouseX();
	float getMouseY();
	int getShipSize();
	int getShipOrientation();
	int getAudioSamples();
	float getDisplayX();
	float getDisplayY();
	double getTimer();
	float getBoardSize();
	float getFieldSize();
	int getNumberOfFields();
	int getNumberOfOneMastedShips();
	int getNumberOfTwoMastedShips();
	int getNumberOfThreeMastedShips();
	int getNumberOfFourMastedShips();
	void setMouseX(float x);
	void setMouseY(float y);
	void setShipSize(int s);
	void setShipOrientation(int o);
	void setNumberOfOneMastedShips(int n);
	void setNumberOfTwoMastedShips(int n);
	void setNumberOfThreeMastedShips(int n);
	void setNumberOfFourMastedShips(int n);
	ALLEGRO_COLOR getColorOfBackground();
	ALLEGRO_COLOR getColorOfBoard();
	ALLEGRO_COLOR getColorOfLine();
	ALLEGRO_COLOR getColorOfShip();

};

