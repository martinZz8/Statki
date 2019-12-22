#include "Deploying.h"
#include "Menu.h"

Deploying::Deploying(State **state, Utils& utils, Buttons& buttons, Board& board1, Board& board2):windowID(WINDOW_DEPLOYING), s(state), u(utils), buttons(buttons), b1(board1), b2(board2)
{
	m = NULL;
	audio_play_guard = true;
	resize_ship_guard = true;
	rotate_ship_guard = true;
}

void Deploying::setStates(Menu* menu)
{
	m = menu;
}

void Deploying::tick()
{
	classicKeyboardSwitches();
	mouseSwitches();
}

void Deploying::render()
{
	b1.paintBoard();
	b2.paintBoard();
	paintButtons();
	b1.paintStandardShip(u.getMouseX(), u.getMouseY());
	
}

int Deploying::getWindowID()
{
	return windowID;
}

void Deploying::classicKeyboardSwitches()
{
	if (u.getKeyUpPressed() == true && resize_ship_guard == true)
	{
		u.setShipSize(u.getShipSize() + 1);
		if (u.getShipSize() > 4)
			u.setShipSize(1);
		cout << "Rozmiar: " << u.getShipSize() << endl;
		resize_ship_guard = false;
	}
	if (u.getKeyDownPressed() == true && resize_ship_guard == true)
	{
		u.setShipSize(u.getShipSize() - 1);
		if (u.getShipSize() < 1)
			u.setShipSize(4);
		cout << "Rozmiar: " << u.getShipSize() << endl;
		resize_ship_guard = false;
	}
	if (u.getKeyUpPressed() == false && u.getKeyDownPressed() == false)
		resize_ship_guard = true;
	if (u.getKeyRightPressed() == true && rotate_ship_guard == true)
	{
		u.setShipOrientation(u.getShipOrientation() + 1);
		if (u.getShipOrientation() > 2)
			u.setShipOrientation(1);
		cout << "Orientacja: " << u.getShipOrientation() << endl;
		rotate_ship_guard = false;
	}
	if (u.getKeyLeftPressed() == true && rotate_ship_guard == true)
	{
		u.setShipOrientation(u.getShipOrientation() - 1);
		if (u.getShipOrientation() < 1)
			u.setShipOrientation(2);
		cout << "Orientacja: " << u.getShipOrientation() << endl;
		rotate_ship_guard = false;
	}
	if (u.getKeyRightPressed() == false && u.getKeyLeftPressed() == false)
		rotate_ship_guard = true;
}

void Deploying::mouseSwitches()
{
	if (u.getMouseClickedBeforeStateSwitch() == true)
	{
		u.setMouse1Clicked(false); //sztuczne ustawienie kliknietego lewego przycisku myszy na false po zmianie okna
		u.setMouseClickedBeforeStateSwitch(false);
	}
	else
	{
		if (buttons.getActivated(BUTTON_DEPLOYING_BACK) == true)
		{
			*s = m;
			u.setMouseClickedBeforeStateSwitch(true);
			cout << "Przelaczenie z DEPLOYING do MENU" << endl;
		}

		if ((buttons.getHighlighted(BUTTON_DEPLOYING_PLAY) == true || buttons.getHighlighted(BUTTON_DEPLOYING_BACK) == true) && audio_play_guard == true)
		{
			u.playSample(AUDIO_BUTTON_HIGHLIGHT);
			audio_play_guard = false;
		}
		else if ((buttons.getHighlighted(BUTTON_DEPLOYING_PLAY) == true || buttons.getHighlighted(BUTTON_DEPLOYING_BACK) == true) == false) //kiedy puscimy przycisk myszy mozna bedzie znowu odtworzyc sampla
			audio_play_guard = true;
	}

	
	

}

void Deploying::paintButtons()
{
	buttons.paintButtonWithText(BUTTON_DEPLOYING_PLAY, "PLAY", FONT_SIZE_SMALL, 45, 12);
	buttons.paintButtonWithText(BUTTON_DEPLOYING_BACK, "BACK TO MENU", FONT_SIZE_SMALL, 6, 12);
	
	if (buttons.getHighlighted(BUTTON_DEPLOYING_PLAY) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_PLAY, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_DEPLOYING_BACK) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_BACK, FONT_SIZE_SMALL);
	
}
