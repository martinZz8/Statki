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
#define AUDIO_MENU_CLICK 0
#define AUDIO_PLACED_SHIP 1
#define AUDIO_MISSED_SHOT 2
#define AUDIO_HITTED_SHIP 3
#define AUDIO_DESTROYED_SHIP 4


class Utils
{
	bool audio_setted; //flaga czy zostala dodana muzyka
	vector <ALLEGRO_SAMPLE*> samples; //vector wszystkich utworow
	bool running; //true - program dziala, false - program jest wylaczany
	static float mouse_x;
	static float mouse_y;
	bool mouse1_clicked; //true - klikniete, false - puszczone
	bool mouse2_clicked; //true - klikniete, false - puszczone
	bool space_pressed; //true - wcisniete, false - puszczone
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
	bool getRunning();
	float getMouseX();
	float getMouseY();
	bool getMouse1Clicked();
	bool getMouse2Clicked();
	bool getSpacePressed();
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
	void setRunning(bool b);
	void setMouseX(float x);
	void setMouseY(float y);
	void setMouse1Clicked(bool b);
	void setMouse2Clicked(bool b);
	void setSpacePressed(bool b);
	void setShipSize(int s);
	void setShipOrientation(int o);
	void setNumberOfOneMastedShips(int n);
	void setNumberOfTwoMastedShips(int n);
	void setNumberOfThreeMastedShips(int n);
	void setNumberOfFourMastedShips(int n);
	void loadAudio();
	void playSample(int ID);
	ALLEGRO_COLOR getColorOfBackground();
	ALLEGRO_COLOR getColorOfBoard();
	ALLEGRO_COLOR getColorOfLine();
	ALLEGRO_COLOR getColorOfShip();
	
};

