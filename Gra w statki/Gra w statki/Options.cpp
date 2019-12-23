#include "Options.h"
#include "Menu.h"

Options::Options(State** state, Utils& utils, Buttons& buttons):widnowID(WINDOW_OPTIONS),s(state),u(utils),buttons(buttons)
{
	audio_play_guard = false;
	m = NULL;
}

void Options::setStates(Menu* menu)
{
	m = menu;
}

void Options::tick()
{
	mouseSwitches();
}

void Options::render()
{
	
	paintButtons();
	paintText();

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
		//dokonczyc ify
		
		bool highlighted = false;
		for (int indeks = BUTTON_OPTIONS_BACK; indeks <= BUTTON_OPTIONS_MINUS_ONE; indeks++)
		{
			if (buttons.getHighlighted(indeks) == true)
			{
				highlighted = true;
				break;
			}
		}
		if (highlighted == true && audio_play_guard == true)
		{
			u.playSample(AUDIO_BUTTON_HIGHLIGHT);
			audio_play_guard = false;
		}
		else if (highlighted == false)
			audio_play_guard = true;

	}

}

void Options::paintButtons()
{
	buttons.paintButtonWithText(BUTTON_OPTIONS_BACK, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_CLASSIC_GAME_MODE, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_ADVANCED_GAME_MODE, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_PVP_GAME_MODE, FONT_SIZE_BIG);
	buttons.paintButtonWithText(BUTTON_OPTIONS_PVC_GAME_MODE, FONT_SIZE_BIG);	
	buttons.paintButtonWithText(BUTTON_OPTIONS_VOLUME_ON, FONT_SIZE_BIG);
	buttons.paintButtonWithText(BUTTON_OPTIONS_VOLUME_OFF, FONT_SIZE_BIG);
	buttons.paintButtonWithText(BUTTON_OPTIONS_MINUS_ONE, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_PLUS_ONE, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_MINUS_TWO, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_PLUS_TWO, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_MINUS_THREE, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_PLUS_THREE, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_MINUS_FOUR, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_OPTIONS_PLUS_FOUR, FONT_SIZE_SMALL);

	//Buttons highlights
	if (buttons.getHighlighted(BUTTON_OPTIONS_BACK) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_BACK, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_CLASSIC_GAME_MODE) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_CLASSIC_GAME_MODE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_ADVANCED_GAME_MODE) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_ADVANCED_GAME_MODE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_PVP_GAME_MODE) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_PVP_GAME_MODE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_PVC_GAME_MODE) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_PVC_GAME_MODE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_VOLUME_ON) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_VOLUME_ON, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_VOLUME_OFF) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_VOLUME_OFF, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_MINUS_ONE) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_MINUS_ONE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_PLUS_ONE) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_PLUS_ONE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_MINUS_TWO) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_MINUS_TWO, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_PLUS_TWO) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_PLUS_TWO, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_MINUS_THREE) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_MINUS_THREE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_PLUS_THREE) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_PLUS_THREE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_MINUS_FOUR) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_MINUS_FOUR, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_OPTIONS_PLUS_FOUR) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_PLUS_FOUR, FONT_SIZE_SMALL);
}

void Options::paintText()
{
	u.drawText("TRYB STAWIANIA", FONT_SIZE_BIG, 183, 234, 240, 372, 43);
	u.drawText("STATKOW", FONT_SIZE_BIG, 183, 234, 243, 422, 80);
	u.drawText("TRYB GRY", FONT_SIZE_BIG, 183, 234, 243, 424, 220);
	u.drawText("MUZYKA", FONT_SIZE_BIG, 183, 234, 243, 433, 360);
		

}
