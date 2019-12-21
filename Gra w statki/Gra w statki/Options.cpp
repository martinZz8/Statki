#include "Options.h"
#include "Menu.h"

Options::Options(State** state, Utils& utils, Buttons& buttons):widnowID(WINDOW_OPTIONS),s(state),u(utils),buttons(buttons)
{
	m = NULL;
}

Options::~Options()
{
	delete[]s;
	delete[]m;
}

void Options::setStates(Menu* menu)
{
	m = menu;
}

void Options::tick()
{
}

void Options::render()
{
}

int Options::getWindowID()
{
	return widnowID;
}

void Options::mouseSwitches()
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
			*s = m;
			u.setMouseClickedBeforeStateSwitch(true);
			cout << "Przelaczenie z OPTIONS do MENU" << endl;
		}
		
		//DOKONCZYC
		/*if ((buttons.getHighlighted(BUTTON_MENU_PLAY) == true || buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true || buttons.getHighlighted(BUTTON_MENU_EXIT) == true) && audio_play_guard == true)
		{
			u.playSample(AUDIO_MENU_CLICK);
			audio_play_guard = false;
		}
		else if ((buttons.getHighlighted(BUTTON_MENU_PLAY) == true || buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true || buttons.getHighlighted(BUTTON_MENU_EXIT) == true) == false)
			audio_play_guard = true;*/

	}

}
