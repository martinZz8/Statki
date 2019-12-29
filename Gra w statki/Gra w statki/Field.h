#pragma once
#include "Utils.h"

class Field
{
	Utils& u;
	float c_x; //koordynaty x
	float c_y; //koordynaty y
	float width; //szerokosc pola
	bool occupied_flag; //czy pole jest zajete przez statek (false - nie, true - tak)
	bool hitted_flag; //pole trafione przez przeciwnika (false - nie trafione, true - trafione)
	bool missed_flag; //pole nie trafione przez przeciwnika (false - nie trafione, true - trafione)
	bool surrounded_flag; //pole, na którym nie mo¿e zostaæ postawiony ¿aden statek (poniewa¿ ju¿ obok znajduje siê jakiœ statek) (false - nie ma obok statku, true - jest obok statek)

public:
	//Field& operator=(Field& f);
	Field(Utils& utils, float c_x, float c_y);
	void setCoordX(float c_x);
	void setCoordY(float c_y);
	void setOccupied(bool o);
	void setHit(bool h);
	void setMiss(bool m);
	void setSurrounded(bool s);
	float getCoordX();
	float getCoordY();
	bool getOccupied();
	bool getHit();
	bool getMiss();
	bool getSurrounded();
	void paintField(int scheme); //metoda renderujaca pole o zadanym schemacie
};