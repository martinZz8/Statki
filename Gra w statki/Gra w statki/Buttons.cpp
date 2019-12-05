#include "Buttons.h"

Buttons::Buttons()
{
	
	setButtons();
}

void Buttons::setButtons()
{
	Button b(100, 100, 425, 150, BUTTON_MENU_PLAY);
	buttons.push_back(b); //0
	b = Button(100, 100, 425, 280, BUTTON_MENU_OPTION);
	buttons.push_back(b); //1
	b = Button(100, 100, 425, 410, BUTTON_MENU_EXIT);
	buttons.push_back(b); //2
	b = Button(100, 100, 700, 400, BUTTON_OPTIONS_BACK);
	buttons.push_back(b); //3
	b = Button(100, 100, 700, 400, BUTTON_DEPLOYING_PLAY);
	buttons.push_back(b); //4
	b = Button(100, 100, 700, 510, BUTTON_DEPLOYING_BACK);
	buttons.push_back(b); //5

}