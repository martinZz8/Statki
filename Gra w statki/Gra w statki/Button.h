#pragma once
#include "Utils.h"

class Button
{
	float width;
	float height;
	float x;
	float y;
	bool highlighted; //zmienna, ktora wskazuje na to, czy mysz znajduje sie na danym buttonie; true - tak, false - nie
	int button_ID; //id przycisku, ktore wskazuje na to, co dany przycisk robi
public:
	Button(float width, float height, float x, float y, int button_ID);
	void setWidth(float width);
	void setHeight(float height);
	void setX(float x);
	void setY(float y);
	void setHighlighted(bool h);
	float getX();
	float getY();
	float getHeight();
	float getWidth();
	bool getHighlighted();
	int getButtonID();
	
};

