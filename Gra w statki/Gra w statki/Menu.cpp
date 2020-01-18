#include "Menu.h"
#include "Options.h"
#include "Deploying.h"

Menu::Menu(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2) :windowID(WINDOW_MENU), s(state), u(utils), buttons(buttons), b1(board1), b2(board2)
{
	audio_play_guard = true;
	d = NULL;
	o = NULL;
}

void Menu::setStates(Options* options, Deploying* deploying)
{
	o = options;
	d = deploying;
}

void Menu::tick()
{
	mouseSwitches();

}

void Menu::render()
{
	playAudio();
	paintButtons();
	paintText();

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
			d->setNUmbersOfNotDeployedShips();
			u.setMouseClickedBeforeStateSwitch(true);
		}
		else if (buttons.getActivated(BUTTON_MENU_OPTIONS) == true)
		{
			*s = o;
			u.setMouseClickedBeforeStateSwitch(true);
		}
		else if (buttons.getActivated(BUTTON_MENU_EXIT) == true)
		{
			u.setRunning(false);
		}
	}
}

void Menu::paintButtons()
{
	buttons.paintButtonWithText(BUTTON_MENU_PLAY, FONT_SIZE_BIG);
	buttons.paintButtonWithText(BUTTON_MENU_OPTIONS, FONT_SIZE_BIG);
	buttons.paintButtonWithText(BUTTON_MENU_EXIT, FONT_SIZE_BIG);

	//Buttons highlights
	if (buttons.getHighlighted(BUTTON_MENU_PLAY) == true)
		buttons.paintButtonHighlight(BUTTON_MENU_PLAY, FONT_SIZE_BIG);
	else if (buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true)
		buttons.paintButtonHighlight(BUTTON_MENU_OPTIONS, FONT_SIZE_BIG);
	else if (buttons.getHighlighted(BUTTON_MENU_EXIT) == true)
		buttons.paintButtonHighlight(BUTTON_MENU_EXIT, FONT_SIZE_BIG);
}

void Menu::paintText()
{
	u.drawText("Statki", FONT_SIZE_HUGE, 183, 234, 243, 341, 40);
	u.drawText("Made by Maciej Harbuz", FONT_SIZE_SMALL, 183, 234, 243, 850, 580);
}

void Menu::playAudio()
{
	if (u.getVolumeOn() == true)
	{
		/*Audio dotyczace highlightow*/
		bool highlighted = false;
		for (int indeks = BUTTON_MENU_PLAY; indeks <= BUTTON_MENU_EXIT; indeks++)
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