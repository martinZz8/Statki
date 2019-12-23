#include "Buttons.h"

Buttons::Buttons(Utils& utils):u(utils)
{
	
	setButtons();
}

void Buttons::setButtons()
{
	/*MENU*/
	buttons.push_back(Button(u, "PLAY", 200, 80, 390, 190, 59, 15, false, BUTTON_MENU_PLAY)); //0
	buttons.push_back(Button(u, "OPTIONS", 200, 80, 390, 300, 30, 15, false, BUTTON_MENU_OPTIONS)); //1
	buttons.push_back(Button(u, "EXIT", 200, 80, 390, 410, 63, 15, false, BUTTON_MENU_EXIT)); //2
	/*OPTIONS*/
	buttons.push_back(Button(u, "BACK TO MENU", 120, 40, 870, 545, 6, 12, false, BUTTON_OPTIONS_BACK)); //3
	//ZMIENIC ARGUMENTY PONIZSZYCH METOD
	buttons.push_back(Button(u, "CLASSIC", 87, 50, 410, 120, 18, 14, u.getClassicGameMode(), BUTTON_OPTIONS_CLASSIC_GAME_MODE)); //4
	buttons.push_back(Button(u, "ADVANCED", 87, 50, 510, 120, 4, 14, u.getAdvancedGameMode(), BUTTON_OPTIONS_ADVANCED_GAME_MODE)); //5
	buttons.push_back(Button(u, "PvP", 87, 50, 510, 260, 18, 4, u.getPvPGameMode(), BUTTON_OPTIONS_PVP_GAME_MODE)); //6
	buttons.push_back(Button(u, "PvC", 87, 50, 410, 260, 16, 4, u.getPvCGameMode(), BUTTON_OPTIONS_PVC_GAME_MODE)); //7
	buttons.push_back(Button(u, "ON", 87, 50, 410, 400, 18, 4, u.getVolumeOn(), BUTTON_OPTIONS_VOLUME_ON)); //8
	buttons.push_back(Button(u, "OFF", 87, 50, 510, 400, 16, 4, u.getVolumeOff(), BUTTON_OPTIONS_VOLUME_OFF)); //9
	buttons.push_back(Button(u, "ADD", 40, 30, 200, 100, 4, 4, false, BUTTON_OPTIONS_PLUS_FOUR)); //10
	buttons.push_back(Button(u, "RMV", 40, 30, 200, 140, 4, 4, false, BUTTON_OPTIONS_MINUS_FOUR)); //11
	buttons.push_back(Button(u, "ADD", 40, 30, 200, 200, 4, 4, false, BUTTON_OPTIONS_PLUS_THREE)); //12
	buttons.push_back(Button(u, "RMV", 40, 30, 200, 240, 4, 4, false, BUTTON_OPTIONS_MINUS_THREE)); //13
	buttons.push_back(Button(u, "ADD", 40, 30, 200, 300, 4, 4, false, BUTTON_OPTIONS_PLUS_TWO)); //14
	buttons.push_back(Button(u, "RMV", 40, 30, 200, 340, 4, 4, false, BUTTON_OPTIONS_MINUS_TWO)); //15
	buttons.push_back(Button(u, "ADD", 40, 30, 200, 400, 4, 4, false, BUTTON_OPTIONS_PLUS_ONE)); //16
	buttons.push_back(Button(u, "RMV", 40, 30, 200, 440, 4, 4, false, BUTTON_OPTIONS_MINUS_ONE)); //17
	/*DEPLOYING*/
	buttons.push_back(Button(u, "PLAY", 120, 40, 740, 545, 45, 12, false, BUTTON_DEPLOYING_PLAY)); //18
	buttons.push_back(Button(u, "BACK TO MENU", 120, 40, 870, 545, 6, 12, false, BUTTON_DEPLOYING_BACK)); //19

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

void Buttons::paintButtonWithText(int indeks, int size)
{
	buttons[indeks].paintButtonWithText(size);
}

void Buttons::paintButtonHighlight(int indeks, int size)
{
	buttons[indeks].paintButtonHighlight(size);
}