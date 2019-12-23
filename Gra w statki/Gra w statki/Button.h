#pragma once
#include "Utils.h"
#include <string.h>

class Button
{
	Utils& u;
	string text;
	float width;
	float height;
	float x;
	float y;
	float text_x_offset;
	float text_y_offset;
	bool highlighted; //zmienna, ktora wskazuje na to, czy mysz znajduje sie na danym buttonie; true - tak, false - nie
	bool activated; //zmienna, ktora wskazuje na to, czy przycisk zostal aktywowany; true - tak, false - nie
	bool choosed; //zmienna, ktora wskazuje na to, czy dana opcja jest wybrana
	int button_ID; //id przycisku, ktore wskazuje na to, co dany przycisk robi
public:
	Button(Utils &utils, string text, float width, float height, float x, float y, float text_x_offset, float text_y_offset, bool choosed, int button_ID);
	void setWidth(float width);
	void setHeight(float height);
	void setX(float x);
	void setY(float y);
	void setHighlighted(bool h);
	void setActivated(bool h);
	void setChoosed(bool h);
	float getX();
	float getY();
	float getHeight();
	float getWidth();
	bool getHighlighted();
	bool getActivated();
	bool getChoosed();
	int getButtonID();
	void paintButtonWithText(int size); //metoda rysujaca przycisk z napisem
	void paintButtonHighlight(int size); //metoda rysujaca obwodke, gdy najedziemy myszka na przycisk
	
};

