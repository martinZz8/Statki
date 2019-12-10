#pragma once
#include "Button.h"

class Buttons
{
	Utils &u;
	vector <Button> buttons;
	
public:
	Buttons(Utils& u);
	void setButtons();
	bool isMouseOnButton(int indeks);
};

