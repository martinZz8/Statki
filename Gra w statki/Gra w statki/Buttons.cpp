#include "Buttons.h"

Buttons::Buttons(Utils& utils):u(utils)
{
	
	setButtons();
}

void Buttons::setButtons()
{
	/*MENU*/
	buttons.push_back(Button(u, 200, 80, 390, 190, false, BUTTON_MENU_PLAY)); //0
	buttons.push_back(Button(u, 200, 80, 390, 300, false, BUTTON_MENU_OPTIONS)); //1
	buttons.push_back(Button(u, 200, 80, 390, 410, false, BUTTON_MENU_EXIT)); //2
	/*OPTIONS*/
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_BACK)); //3
	//ZMIENIC ARGUMENTY PONIZSZYCH METOD
	buttons.push_back(Button(u, 100, 60, 700, 400, true, BUTTON_OPTIONS_CLASSIC_GAME_MODE)); //4
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_ADVANCED_GAME_MODE)); //5
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_PVP_GAME_MODE)); //6
	buttons.push_back(Button(u, 200, 80, 700, 400, true, BUTTON_OPTIONS_PVC_GAME_MODE)); //7
	buttons.push_back(Button(u, 200, 80, 700, 400, true, BUTTON_OPTIONS_VOLUME_ON)); //8
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_VOLUME_OFF)); //9
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_ARROW_UP_FOUR)); //10
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_ARROW_DOWN_FOUR)); //11
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_ARROW_UP_THREE)); //12
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_ARROW_DOWN_THREE)); //13
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_ARROW_UP_TWO)); //14
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_ARROW_DOWN_TWO)); //15
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_ARROW_UP_ONE)); //16
	buttons.push_back(Button(u, 200, 80, 700, 400, false, BUTTON_OPTIONS_ARROW_DOWN_ONE)); //17
	/*DEPLOYING*/
	buttons.push_back(Button(u, 120, 40, 740, 545, false, BUTTON_DEPLOYING_PLAY)); //18
	buttons.push_back(Button(u, 120, 40, 870, 545, false, BUTTON_DEPLOYING_BACK)); //19

}

void Buttons::setHighlighted(int indeks, bool h)
{
	buttons[indeks].setHighlighted(h);
}

void Buttons::setActivated(int indeks, bool p)
{
	buttons[indeks].setActivated(p);
}

bool Buttons::getHighlighted(int indeks)
{
	return buttons[indeks].getHighlighted();
}

bool Buttons::getActivated(int indeks)
{
	return buttons[indeks].getActivated();
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