#pragma once
#include "Utils.h"

class Field
{
	Utils& u;
	float c_x; //koordynaty x
	float c_y; //koordynaty y
	float width; //szerokosc pola
	bool hitted_flag; //pole trafione przez przeciwnika (false - nie trafione, true - trafione)
	bool missed_flag; //pole nie trafione przez przeciwnika (false - nie trafione, true - trafione)
	
public:
	bool operator==(const Field& f); //porownuje c_x z f.c_x oraz c_y z f.c_y
	bool operator!=(const Field& f); //porownuje c_x z f.c_x oraz c_y z f.c_y
	Field(Utils& utils, float c_x, float c_y);
	void setCoordX(float new_c_x);
	void setCoordY(float new_c_y);
	void setHit(bool h);
	void setMiss(bool m);
	float getCoordX();
	float getCoordY();
	float getWidth();
	bool getHit();
	bool getMiss();
	void paintField(int scheme); //metoda renderujaca pole o zadanym schemacie
};