#pragma once
#include "Utils.h"

class Field
{
	Utils& u;
	float c_x; //co-ordinates x
	float c_y; //co-orginates y
	int x_board_pos, y_board_pos;
	float width; //szerokosc pola
	bool occupied; //czy pole jest zajete przez statek (0 - nie, 1 - tak)
	bool hit; //pole trafione przez przeciwnika (0 - nie trafione, 1 - trafione)
	bool surrounded; //pole, na którym nie mo¿e zostaæ postawiony ¿aden statek (poniewa¿ ju¿ obok znajduje siê jakiœ statek) (0- nie ma obok statku, 1 - jest obok statek)

public:
	Field(Utils& utils);
	//Field();
	~Field();
	void setCoords(float x, float y);
	void setOccupied(bool o);
	void setHit(bool h);
	void setSurrounded(bool s);
	float getCoordX();
	float getCoordY();
	bool getOccupied();
	bool getHit();
	bool getSurrounded();
	void calculate_board_position(int x_board_offset, int y_board_offset, int c_x, int c_y, float mouse_x, float mouse_y); //metoda obliczajaca x_board_pos
	void paintField(); //metoda renderujaca pole
};

