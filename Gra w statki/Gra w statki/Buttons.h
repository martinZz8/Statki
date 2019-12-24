#pragma once
#include "Button.h"

class Buttons
{
	Utils &u;
	vector <Button> buttons;
	
public:
	/*
Button:
	Button(x,y,height, width, text, fontSize)
	onClick(Callback)
	paint(mouse)
Buttons:
	Buttons(vector<Button>)
	paint(mouse)
	*/
	Buttons(Utils& u);
	void setButtons();
	void setHighlighted(int indeks, bool h);
	void setActivated(int indeks, bool p);
	void setChoosed(int indeks, bool p);
	bool getHighlighted(int indeks);
	bool getActivated(int indeks);
	bool getChoosed(int indeks);
	bool isMouseOnButton(int indeks); //metoda sprawdzajaca, czy myszka znajduje sie w obrebie pola przycisku
	void paintButtonWithText(int indeks, int size); //wywolanie metody rysujacej przycisk z napisem
	void paintButtonHighlight(int indeks, int size); //wywolanie metody rysowania obwodki przycisku
};

