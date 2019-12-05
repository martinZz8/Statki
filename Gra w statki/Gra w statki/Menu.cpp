#include "Menu.h"

Menu::Menu(State** state, Utils& utils, Board& board1, Board& board2):windowID(WINDOW_MENU), s(state), u(utils), b1(board1), b2(board2)
{
	//d = NULL;
}

void Menu::tick()
{
	
}

void Menu::render()
{
	paintMenu();
}

int Menu::getWindowID()
{
	return windowID;
}

void Menu::paintMenu()
{
	u.drawText("Statki", FONT_SIZE_HUGE, 183, 234, 243, 425, 120);
}