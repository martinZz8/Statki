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
	void setHighlighted(bool h);
};

