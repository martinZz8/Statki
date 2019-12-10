#include "Menu.h"
#include "Deploying.h"

Menu::Menu(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2):windowID(WINDOW_MENU), s(state), u(utils), buttons(buttons), b1(board1), b2(board2)
{
	d = NULL;
}

void Menu::setStates(Deploying* deploying)
{
	d = deploying;
}

void Menu::tick()
{
	if (buttons.getPressed(BUTTON_MENU_PLAY) == true)
		*s = d;
    //else if(buttons.getPressed(BUTTON_MENU_OPTIONS)==true)
		//*s=o;
	else if (buttons.getPressed(BUTTON_MENU_EXIT) == true)
		u.setRunning(false);

		
}

void Menu::render()
{
	paintMenu();
	if (buttons.getHighlighted(BUTTON_MENU_PLAY) == true)
		buttons.paintButtonHighlight(BUTTON_MENU_PLAY, FONT_SIZE_BIG);
	else if (buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true)
		buttons.paintButtonHighlight(BUTTON_MENU_OPTIONS, FONT_SIZE_BIG);
	else if (buttons.getHighlighted(BUTTON_MENU_EXIT) == true)
		buttons.paintButtonHighlight(BUTTON_MENU_EXIT, FONT_SIZE_BIG);


}

int Menu::getWindowID()
{
	return windowID;
}

void Menu::paintMenu()
{
	u.drawText("Statki", FONT_SIZE_HUGE, 183, 234, 243, 350, 40);
	buttons.paintButtonWithText(BUTTON_MENU_PLAY, "PLAY", FONT_SIZE_BIG, 59, 15);
	buttons.paintButtonWithText(BUTTON_MENU_OPTIONS, "OPTIONS", FONT_SIZE_BIG, 30, 15);
	buttons.paintButtonWithText(BUTTON_MENU_EXIT, "EXIT", FONT_SIZE_BIG, 63, 15);
}