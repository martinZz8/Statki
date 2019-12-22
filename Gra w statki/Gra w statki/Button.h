#pragma once
#include "Utils.h"

class Button
{
	Utils& u;
	float width;
	float height;
	float x;
	float y;
	bool highlighted; //zmienna, ktora wskazuje na to, czy mysz znajduje sie na danym buttonie; true - tak, false - nie
	bool activated; //zmienna, ktora wskazuje na to, czy przycisk zostal aktywowany; true - tak, false - nie
	int button_ID; //id przycisku, ktore wskazuje na to, co dany przycisk robi
public:
	Button(Utils &utils, float width, float height, float x, float y, bool activated, int button_ID);
	void setWidth(float width);
	void setHeight(float height);
	void setX(float x);
	void setY(float y);
	void setHighlighted(bool h);
	void setActivated(bool h);
	float getX();
	float getY();
	float getHeight();
	float getWidth();
	bool getHighlighted();
	bool getActivated();
	int getButtonID();
	void paintButtonWithText(const char* tekst, int size, float x_offset, float y_offset); //metoda rysujaca przycisk z napisem
	void paintButtonHighlight(int size); //metoda rysujaca obwodke, gdy najedziemy myszka na przycisk
	
};

