#include "Menu.h"
#include "Deploying.h"

Menu::Menu(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2):windowID(WINDOW_MENU), s(state), u(utils), buttons(buttons), b1(board1), b2(board2)
{
	audio_play_guard = false;
	d = NULL;
}

void Menu::setStates(Deploying* deploying)
{
	d = deploying;
}

void Menu::tick()
{
	
	mouseSwitches();
		
}

void Menu::render()
{
	u.drawText("Statki", FONT_SIZE_HUGE, 183, 234, 243, 350, 40);
	paintButtons();

}

int Menu::getWindowID()
{
	return windowID;
}

void Menu::mouseSwitches()
{
	if (u.getMouseClickedBeforeStateSwitch() == true)
	{
		u.setMouse1Clicked(false); //sztuczne ustawienie kliknietego lewego przycisku myszy na false po zmianie okna
		u.setMouseClickedBeforeStateSwitch(false);
	}
	else
	{
		if (buttons.getActivated(BUTTON_MENU_PLAY) == true)
		{
			*s = d;
			u.setMouseClickedBeforeStateSwitch(true);
			cout << "Przelaczenie z  MENU do DEPLOYING" << endl;
		}
		/*else if (buttons.getActivated(BUTTON_MENU_OPTIONS) == true)
		{
			*s = o;
			u.setButtonCanBeActivated(false);
			cout << "Przelaczenie z  MENU do  OPTIONS" << endl;
		}	*/
		else if (buttons.getActivated(BUTTON_MENU_EXIT) == true)
		{
			u.setRunning(false);
		}

		if ((buttons.getHighlighted(BUTTON_MENU_PLAY) == true || buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true || buttons.getHighlighted(BUTTON_MENU_EXIT) == true) && audio_play_guard == true)
		{
			u.playSample(AUDIO_MENU_CLICK);
			audio_play_guard = false;
		}
		else if ((buttons.getHighlighted(BUTTON_MENU_PLAY) == true || buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true || buttons.getHighlighted(BUTTON_MENU_EXIT) == true) == false)
			audio_play_guard = true;

	}

}

void Menu::paintButtons()
{
	buttons.paintButtonWithText(BUTTON_MENU_PLAY, "PLAY", FONT_SIZE_BIG, 59, 15);
	buttons.paintButtonWithText(BUTTON_MENU_OPTIONS, "OPTIONS", FONT_SIZE_BIG, 30, 15);
	buttons.paintButtonWithText(BUTTON_MENU_EXIT, "EXIT", FONT_SIZE_BIG, 63, 15);

	//Buttons highlights
	if (buttons.getHighlighted(BUTTON_MENU_PLAY) == true)
		buttons.paintButtonHighlight(BUTTON_MENU_PLAY, FONT_SIZE_BIG);
	else if (buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true)
		buttons.paintButtonHighlight(BUTTON_MENU_OPTIONS, FONT_SIZE_BIG);
	else if (buttons.getHighlighted(BUTTON_MENU_EXIT) == true)
		buttons.paintButtonHighlight(BUTTON_MENU_EXIT, FONT_SIZE_BIG);
	
		
}


