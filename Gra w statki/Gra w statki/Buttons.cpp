#include "Buttons.h"

Buttons::Buttons(Utils& utils):u(utils)
{
	
	setButtons();
}

void Buttons::setButtons()
{
	buttons.push_back(Button(u, 200, 80, 390, 190, BUTTON_MENU_PLAY)); //0
	buttons.push_back(Button(u, 200, 80, 390, 300, BUTTON_MENU_OPTIONS)); //1
	buttons.push_back(Button(u, 200, 80, 390, 410, BUTTON_MENU_EXIT)); //2
	buttons.push_back(Button(u, 200, 80, 700, 400, BUTTON_OPTIONS_BACK)); //3
	buttons.push_back(Button(u, 200, 80, 700, 400, BUTTON_DEPLOYING_PLAY)); //4
	buttons.push_back(Button(u, 200, 80, 700, 510, BUTTON_DEPLOYING_BACK)); //5

}

void Buttons::setHighlighted(int indeks, bool h)
{
	buttons[indeks].setHighlighted(h);
}

void Buttons::setPressed(int indeks, bool p)
{
	buttons[indeks].setPressed(p);
}

bool Buttons::getHighlighted(int indeks)
{
	return buttons[indeks].getHighlighted();
}

bool Buttons::getPressed(int indeks)
{
	return buttons[indeks].getPressed();
}

bool Buttons::isMouseOnButton(int indeks)
{
	float mouse_x = u.getMouseX();
	float mouse_y = u.getMouseY();
	float button_x = buttons[indeks].getX();
	float button_y = buttons[indeks].getY();
	float button_height = buttons[indeks].getHeight();
	float button_width = buttons[indeks].getWidth();

	if (mouse_x >= button_x && mouse_x <= (button_x + button_width) && mouse_y >= button_y && mouse_y <= (button_y + button_height))
		return true;
	return false;
}

void Buttons::paintButtonWithText(int indeks, const char* tekst, int size, float x_offset, float y_offset)
{
	buttons[indeks].paintButtonWithText(tekst, size, x_offset, y_offset);
}

void Buttons::paintButtonHighlight(int indeks, int size)
{
	buttons[indeks].paintButtonHighlight(size);
}