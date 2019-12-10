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
	bool pressed; //zmienna, ktora wskazuje na to, czy przycisk zostal wcisniety; true - tak, false - nie
	int button_ID; //id przycisku, ktore wskazuje na to, co dany przycisk robi
public:
	Button(Utils &utils, float width, float height, float x, float y, int button_ID);
	void setWidth(float width);
	void setHeight(float height);
	void setX(float x);
	void setY(float y);
	void setHighlighted(bool h);
	void setPressed(bool h);
	float getX();
	float getY();
	float getHeight();
	float getWidth();
	bool getHighlighted();
	bool getPressed();
	int getButtonID();
	void paintButtonWithText(const char* tekst, int size, float x_offset, float y_offset); //metoda rysujaca przycisk z napisem
	void paintButtonHighlight(int size); //metoda rysujaca obwodke, gdy najedziemy myszka na przycisk
	
};

