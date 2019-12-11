#pragma once
#include "Button.h"

class Buttons
{
	Utils &u;
	vector <Button> buttons;
	
public:
	Buttons(Utils& u);
	void setButtons();
	void setHighlighted(int indeks, bool h);
	void setActivated(int indeks, bool p);
	bool getHighlighted(int indeks);
	bool getActivated(int indeks);
	bool isMouseOnButton(int indeks); //metoda sprawdzajaca, czy myszka znajduje sie w obrebie pola przycisku
	void paintButtonWithText(int indeks, const char* tekst, int size, float x_offset, float y_offset); //wywolanie metody rysujacej przycisk z napisem
	void paintButtonHighlight(int indeks, int size); //wywolanie metody rysowania obwodki przycisku
};

