#include "Deploying.h"
#include "Menu.h"

void Deploying::fixShipSize()
{
	int size_of_vector = b1.numbers_of_not_deployed_ships.size();
	for (int i = 0; i < size_of_vector; i++)
	{
		if (b1.numbers_of_not_deployed_ships[i] > 0)
		{
			u.setShipSize(i + 1);
			break;
		}
	}
}

void Deploying::restoreDefaults()
{
	b1.clearVectors();
	b1.setFields();
	b2.clearVectors();
	b2.setFields();
	setNUmbersOfNotDeployedShips();

}

Deploying::Deploying(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2) :windowID(WINDOW_DEPLOYING), s(state), u(utils), buttons(buttons), b1(board1), b2(board2)
{
	m = NULL;
	audio_play_guard = true;
	warning_sample_play_flag = false;
	place_ship_sample_flag = false;
	resize_ship_guard = true;
	rotate_ship_guard = true;
	mouse_click_guard = true;

}

void Deploying::setStates(Menu* menu)
{
	m = menu;
}

void Deploying::setNUmbersOfNotDeployedShips()
{
	b1.setNumbersOfNotDeployedShips();
	b2.setNumbersOfNotDeployedShips();
	fixShipSize();
}

void Deploying::tick()
{
	b1.setDeployShipsFlag();
	b2.setDeployShipsFlag();
	if (u.getClassicGameMode() == true)
	{
		classicKeyboardSwitches();

	}

	mouseSwitches();

}

void Deploying::render()
{
	playAudio();
	paintText();
	paintBorders();
	b1.paintBoard(true, true);
	b2.paintBoard(false, true);

	if (b1.getDeployShipsFlag() == true)
		b1.paintClassicShip(u.getMouseX(), u.getMouseY());
	paintButtons();

}

int Deploying::getWindowID()
{
	return windowID;
}

void Deploying::classicKeyboardSwitches()
{

	bool ship_can_be_changed_flag = b1.getDeployShipsFlag(); //zmienna wskazujaca na to, czy mozna zmienic statek

	if (ship_can_be_changed_flag == true)
	{
		if (u.getKeyUpPressed() == true && resize_ship_guard == true)
		{
			int actual_ship_size = u.getShipSize();
			int i = actual_ship_size - 1;
			i++; //pierwsze zwiekszenie indeksu petli
			int size_of_vector = b1.numbers_of_not_deployed_ships.size();
			bool running = true;

			while (running)
			{
				if (i >= size_of_vector)
				{
					i = 0;
					continue;
				}
				if (b1.numbers_of_not_deployed_ships[i] == 0)
				{
					i++;
					continue;
				}

				u.setShipSize(i + 1);
				cout << "Rozmiar: " << u.getShipSize() << endl;
				resize_ship_guard = false;
				running = false;
			}
		}
		if (u.getKeyDownPressed() == true && resize_ship_guard == true)
		{
			int actual_ship_size = u.getShipSize();
			int i = actual_ship_size - 1;
			i--; //pierwsze zmniejszenie indeksu petli
			int size_of_vector = b1.numbers_of_not_deployed_ships.size();
			bool running = true;

			while (running)
			{
				if (i < 0)
				{
					i = size_of_vector - 1;
					continue;
				}
				if (b1.numbers_of_not_deployed_ships[i] == 0)
				{
					i--;
					continue;
				}

				u.setShipSize(i + 1);
				cout << "Rozmiar: " << u.getShipSize() << endl;
				resize_ship_guard = false;
				running = false;
			}
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
			restoreDefaults();
			u.setMouseClickedBeforeStateSwitch(true);
			cout << "Przelaczenie z DEPLOYING do MENU" << endl;
		}
		else if (buttons.getActivated(BUTTON_DEPLOYING_RESET) == true && mouse_click_guard == true)
		{
			restoreDefaults();
		}
		else if (u.getMouse1Clicked() == true && mouse_click_guard == true)
		{
			mouse_click_guard = false;
			if (u.getClassicGameMode() == true)
			{
				if (u.getPvCGameMode() == true)
				{
					if (b1.getDeployShipsFlag() == true) //plaer1 moze rozstawiac statki
					{
						cout << "Klikam myszka w classicu" << endl;
						int x = b1.deployClassicShip(u.getMouseX(), u.getMouseY());
						if (x == 0)
						{
							place_ship_sample_flag = true;
							warning_sample_play_flag = false;
							fixShipSize();
						}
						else
						{
							warning_sample_play_flag = true;
							place_ship_sample_flag = false;
						}

					}
					//TODO DOKONCZYC ROZSTAWIANIE STATKOW DLA KOLEJNEJ PLANSZY B2
				}
				else //PvP_game_mode == true
				{

				}
			}
			else //advanced_game_mode == true
			{
				if (u.getPvCGameMode() == true)
				{

				}
				else //PvP_game_mode == true
				{

				}
			}

		}
		else if (u.getMouse1Clicked() == false)
		{
			mouse_click_guard = true;
			place_ship_sample_flag = false;
			warning_sample_play_flag = false;
		}

	}
}

void Deploying::classicPlayerDeploy()
{

}

void Deploying::classicComputerDeploy()
{

}

void Deploying::classicBoardCopy()
{

}



void Deploying::paintButtons()
{
	buttons.paintButtonWithText(BUTTON_DEPLOYING_PLAY, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_DEPLOYING_BACK, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_DEPLOYING_RESET, FONT_SIZE_SMALL);

	if (buttons.getHighlighted(BUTTON_DEPLOYING_PLAY) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_PLAY, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_DEPLOYING_BACK) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_BACK, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_DEPLOYING_RESET) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_RESET, FONT_SIZE_SMALL);
}

void Deploying::paintText()
{

}

void Deploying::paintBorders()
{

}

void Deploying::playAudio()
{

	if (u.getVolumeOn() == true)
	{
		/*Audio dotyczace highlightow*/
		bool highlighted = false;
		for (int indeks = BUTTON_DEPLOYING_PLAY; indeks <= BUTTON_DEPLOYING_RESET; indeks++)
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

		/*Audio dotyczace warningow*/
		if (warning_sample_play_flag == true && audio_play_guard == true)
		{
			u.playSample(AUDIO_ERROR);
			audio_play_guard = false;
		}

		/*Audio dotyczace rozstawiania statkow*/
		if (place_ship_sample_flag == true && audio_play_guard == true)
		{
			u.playSample(AUDIO_PLACED_SHIP);
			audio_play_guard = false;
		}

		if (highlighted == false && warning_sample_play_flag == false && place_ship_sample_flag == false && audio_play_guard == false) //kiedy puscimy przycisk myszy mozna bedzie znowu odtworzyc sampla
			audio_play_guard = true;
	}
}