#include "Options.h"
#include "Menu.h"

Options::Options(State** state, Utils& utils, Buttons& buttons):widnowID(WINDOW_OPTIONS),s(state),u(utils),buttons(buttons)
{
	m = NULL;
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
		if (buttons.getActivated(BUTTON_OPTIONS_BACK) == true)
		{
			*s = m;
			u.setMouseClickedBeforeStateSwitch(true);
			cout << "Przelaczenie z OPTIONS do MENU" << endl;
		}
		
		//DOKONCZYC
		/*if ((buttons.getHighlighted(BUTTON_MENU_PLAY) == true || buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true || buttons.getHighlighted(BUTTON_MENU_EXIT) == true) && audio_play_guard == true)
		{
			u.playSample(AUDIO_BUTTON_HIGHLIGHT);
			audio_play_guard = false;
		}
		else if ((buttons.getHighlighted(BUTTON_MENU_PLAY) == true || buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true || buttons.getHighlighted(BUTTON_MENU_EXIT) == true) == false)
			audio_play_guard = true;*/

	}

}

void Options::paintButtons()
{
	buttons.paintButtonWithText(BUTTON_OPTIONS_BACK, "BACK", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_CLASSIC_GAME_MODE, "Classic", FONT_SIZE_SMALL, 59, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ADVANCED_GAME_MODE, "Advanced", FONT_SIZE_SMALL, 30, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_PVC_GAME_MODE, "Computer", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_PVP_GAME_MODE, "Player", FONT_SIZE_SMALL, 63, 15);	
	buttons.paintButtonWithText(BUTTON_OPTIONS_VOLUME_ON, "ON", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_VOLUME_OFF, "OFF", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ARROW_DOWN_ONE, "\\/", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ARROW_UP_ONE, "/\\", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ARROW_DOWN_TWO, "\\/", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ARROW_UP_TWO, "/\\", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ARROW_DOWN_THREE, "\\/", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ARROW_UP_THREE, "/\\", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ARROW_DOWN_FOUR, "\\/", FONT_SIZE_SMALL, 63, 15);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ARROW_UP_FOUR, "/\\", FONT_SIZE_SMALL, 63, 15);

	//Buttons highlights


}

void Options::paintText()
{

}
