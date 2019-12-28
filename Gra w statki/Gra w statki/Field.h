#pragma once
#include "Utils.h"

class Field
{
	Utils& u;
	float c_x; //koordynaty x
	float c_y; //koordynaty y
	int x_board_pos, y_board_pos;
	float width; //szerokosc pola
	bool occupied_flag; //czy pole jest zajete przez statek (false - nie, true - tak)
	bool hitted_flag; //pole trafione przez przeciwnika (false - nie trafione, true - trafione)
	bool surrounded_flag; //pole, na którym nie mo¿e zostaæ postawiony ¿aden statek (poniewa¿ ju¿ obok znajduje siê jakiœ statek) (false - nie ma obok statku, true - jest obok statek)

public:
	Field(Utils& utils, float c_x, float c_y);
	~Field();
	void setCoordX(float c_x);
	void setCoordY(float c_y);
	void setOccupied(bool o);
	void setHit(bool h);
	void setSurrounded(bool s);
	float getCoordX();
	float getCoordY();
	bool getOccupied();
	bool getHit();
	bool getSurrounded();
	void calculate_board_position(int x_board_offset, int y_board_offset, int c_x, int c_y, float mouse_x, float mouse_y); //metoda obliczajaca x_board_pos
	void paintField(int scheme); //metoda renderujaca pole o zadanym schemacie
};

