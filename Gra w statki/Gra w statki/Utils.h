#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/***WINDOW***/
#define WINDOW_MENU 0
#define WINDOW_OPTIONS 1
#define WINDOW_GAME 2
#define WINDOW_DEPLOYING 3
/***AUDIO***/
#define AUDIO_BUTTON_HIGHLIGHT 0
#define AUDIO_MOUSE_CLICK 1
#define AUDIO_PLACED_SHIP 2
#define AUDIO_MISSED_SHOT 3
#define AUDIO_HITTED_SHIP 4

/***FONT***/
#define FONT_SIZE_SMALL 0
#define FONT_SIZE_BIG 1
#define FONT_SIZE_HUGE 2
/***BUTTONS***/
     /*MENU*/
#define BUTTON_MENU_PLAY 0
#define BUTTON_MENU_OPTIONS 1
#define BUTTON_MENU_EXIT 2
     /*OPTIONS*/
#define BUTTON_OPTIONS_BACK 3
#define BUTTON_OPTIONS_CLASSIC_GAME_MODE 4
#define BUTTON_OPTIONS_ADVANCED_GAME_MODE 5
#define BUTTON_OPTIONS_PVP_GAME_MODE 6
#define BUTTON_OPTIONS_PVC_GAME_MODE 7
#define BUTTON_OPTIONS_VOLUME_ON 8
#define BUTTON_OPTIONS_VOLUME_OFF 9
#define BUTTON_OPTIONS_ARROW_UP_FOUR 10
#define BUTTON_OPTIONS_ARROW_DOWN_FOUR 11
#define BUTTON_OPTIONS_ARROW_UP_THREE 12
#define BUTTON_OPTIONS_ARROW_DOWN_THREE 13
#define BUTTON_OPTIONS_ARROW_UP_TWO 14
#define BUTTON_OPTIONS_ARROW_DOWN_TWO 15
#define BUTTON_OPTIONS_ARROW_UP_ONE 16
#define BUTTON_OPTIONS_ARROW_DOWN_ONE 17
     /*DEPLOYING*/
#define BUTTON_DEPLOYING_PLAY 18
#define BUTTON_DEPLOYING_BACK 19
     /*GAME*/

class Utils
{
	vector <ALLEGRO_SAMPLE*> samples; //vector wszystkich utworow
	vector <ALLEGRO_FONT*> fonts; //vector wszystkich czcionek (nawet tych samych ze zmienionym rozmiarem)
	bool running; //true - program dziala, false - program jest wylaczany
	bool mouse_clicked_before_state_switch; //zmienna wskazujaca na to, czy zostal klikniety przycisk przed zmiena okna, czy nie; true - tak, false - nie
	static float mouse_x;
	static float mouse_y;
	bool mouse_1_click_guard; //true - mozna kliknac, false - nie mozna kliknac
	bool mouse_2_click_guard; //true - mozna kliknac, false - nie mozna kliknac
	bool mouse1_clicked;                    /*                                      */
	bool mouse2_clicked;                    /*                                      */
	bool key_space_pressed;                 /*                                      */
	bool key_up_pressed;                    /*   true-klikniete, false-puszczone    */
	bool key_down_pressed;                  /*                                      */
	bool key_left_pressed;                  /*                                      */
	bool key_right_pressed;                 /*                                      */
	                                        /****************************************/
	bool classic_game_mode;                 /*                                      */
	bool advanced_game_mode;                /*                                      */
	bool pvc_game_mode;                     /* true-aktywowane, false-dezaktywowane */
	bool pvp_game_mode;                     /*                                      */
	bool volume_on;                         /*                                      */
	int ship_size; //rozmiar statku w danym momencie (ilosc fieldow)
	int ship_orientation; //orientacja statku w danym momencie (1 - do dolu, 2 - na bok)
	int audio_samples;
	int font_samples;
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
	bool getMouseClickedBeforeStateSwitch();
	float getMouseX();
	float getMouseY();
	bool getMouse1ClickGuard();
	bool getMouse2ClickGuard();
	bool getMouse1Clicked();
	bool getMouse2Clicked();
	bool getKeySpacePressed();
	bool getKeyUpPressed();
	bool getKeyDownPressed();
	bool getKeyLeftPressed();
	bool getKeyRightPressed();
	bool getClassicGameMode();
	bool getAdvancedGameMode();
	bool getPvCGameMode();
	bool getPvPGameMode();
	bool getVolumeOn();
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
	void setMouseClickedBeforeStateSwitch(bool c);
	void setMouseX(float x);
	void setMouseY(float y);
	void setMouse1ClickGuard(bool g);
	void setMouse2ClickGuard(bool g);
	void setMouse1Clicked(bool b);
	void setMouse2Clicked(bool b);
	void setKeySpacePressed(bool b);
	void setKeyUpPressed(bool b);
	void setKeyDownPressed(bool b);
	void setKeyLeftPressed(bool b);
	void setKeyRightPressed(bool b);
	void setClassicGameMode(bool b);
	void setAdvancedGameMode(bool b);
	void setPvCGameMode(bool b);
	void setPvPGameMode(bool b);
	void setVolumeOn(bool b);
	void setShipSize(int s);
	void setShipOrientation(int o);
	void setNumberOfOneMastedShips(int n);
	void setNumberOfTwoMastedShips(int n);
	void setNumberOfThreeMastedShips(int n);
	void setNumberOfFourMastedShips(int n);
	void loadAudio();
	void loadFonts();
	void playSample(int ID);
	void drawText(const char* text,int size,float r,float g, float b,float x,float y);
	ALLEGRO_COLOR getColorOfBackground();
	ALLEGRO_COLOR getColorOfBoard();
	ALLEGRO_COLOR getColorOfLine();
	ALLEGRO_COLOR getColorOfShip();
	
};

