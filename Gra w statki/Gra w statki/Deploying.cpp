#include "Deploying.h"
#include "Menu.h"

bool Deploying::checkIfShipCanBeChanged(vector <int> numbers_of_not_deployed_ships)
{
	for (int i = 0; i < numbers_of_not_deployed_ships.size(); i++)
	{
		if (numbers_of_not_deployed_ships[i] > 0)
			return true;	
	}
	return false;
}

void Deploying::fixShipSize()
{
	int size_of_vector = numbers_of_not_deployed_ships1.size();
	for (int i = 0; i < size_of_vector; i++)
	{
		if (numbers_of_not_deployed_ships1[i] != 0)
		{
			u.setShipSize(i + 1);
			break;
		}
	}
}

void Deploying::restoreDefaults()
{
	player1_deploy_flag = true;
	player2_deploy_flag = true;
	computer_deploy_flag = true;
	b1.clearVectors();
	b2.clearVectors();
	setNUmbersOfNotDeployedShips();

}

Deploying::Deploying(State **state, Utils& utils, Buttons& buttons, Board& board1, Board& board2):windowID(WINDOW_DEPLOYING), s(state), u(utils), buttons(buttons), b1(board1), b2(board2)
{
	m = NULL;
	audio_play_guard = true;
	warning_sample_play_flag = false;
	place_ship_sample_flag = false;
	resize_ship_guard = true;
	rotate_ship_guard = true;
	mouse_click_guard = true;
	player1_deploy_flag = true;
	player2_deploy_flag = true;
	computer_deploy_flag = true;

}

void Deploying::setStates(Menu* menu)
{
	m = menu;
}

void Deploying::setNUmbersOfNotDeployedShips()
{
	if (numbers_of_not_deployed_ships1.empty() == false)
	{
		numbers_of_not_deployed_ships1.clear();
		numbers_of_not_deployed_ships2.clear();
	}
	numbers_of_not_deployed_ships1.push_back(u.getNumberOfOneMastedShips()); //indeks 0
	numbers_of_not_deployed_ships1.push_back(u.getNumberOfTwoMastedShips()); //indeks 1
	numbers_of_not_deployed_ships1.push_back(u.getNumberOfThreeMastedShips()); //indeks 2
	numbers_of_not_deployed_ships1.push_back(u.getNumberOfFourMastedShips()); //indeks 3
	numbers_of_not_deployed_ships2 = numbers_of_not_deployed_ships1;
	fixShipSize();
}

void Deploying::tick()
{
	if (u.getClassicGameMode() == true)
	{
		classicKeyboardSwitches();
		
	}

	mouseSwitches();
	
}

void Deploying::render()
{
	playAudio();
	b1.paintBoard();
	b2.paintBoard();
	
	paintButtons();
	b1.paintClassicShip(u.getMouseX(), u.getMouseY());
	
}

int Deploying::getWindowID()
{
	return windowID;
}

void Deploying::classicKeyboardSwitches()
{
	//Sprawdzenie, czy mozna zmienic statek
	bool ship_can_be_changed_flag = checkIfShipCanBeChanged(numbers_of_not_deployed_ships1);
	
	if (ship_can_be_changed_flag == true)
	{
		if (u.getKeyUpPressed() == true && resize_ship_guard == true)
		{
			int actual_ship_size = u.getShipSize();
			int i = actual_ship_size - 1;
			i++; //pierwsze zwiekszenie indeksu petli
			int size_of_vector = numbers_of_not_deployed_ships1.size();
			bool running = true;

			while (running)
			{
				if (i >= size_of_vector)
				{
					i = 0;
					continue;
				}
				if (numbers_of_not_deployed_ships1[i] == 0)
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
			int size_of_vector = numbers_of_not_deployed_ships1.size();
			bool running = true;

			while (running)
			{
				if (i < 0)
				{
					i = size_of_vector - 1;
					continue;
				}
				if (numbers_of_not_deployed_ships1[i] == 0)
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
					setPlayer1DeployFlag();
					if (player1_deploy_flag == true) //plaer1 moze rozstawiac statki
					{
						cout << "Klikam myszka w classicu" << endl;
						int x = b1.deployClassicShip(u.getMouseX(), u.getMouseY(), numbers_of_not_deployed_ships1);
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
					//TODO DOKONCZYC ROZSTAWIANIE STATKOW
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

void Deploying::setPlayer1DeployFlag()
{
	int vector_size = numbers_of_not_deployed_ships1.size();
	for (int i = 0; i < vector_size; i++)
	{
		if (numbers_of_not_deployed_ships1[i] != 0)
		{
			player1_deploy_flag = true;
			return;
		}
	}
	player1_deploy_flag = false;
}

void Deploying::setPlayer2DeployFlag()
{
	int vector_size = numbers_of_not_deployed_ships2.size();
	for (int i = 0; i < vector_size; i++)
	{
		if (numbers_of_not_deployed_ships2[i] != 0)
		{
			player2_deploy_flag = true;
			return;
		}
	}
	player2_deploy_flag = false;
}

void Deploying::setComputerDeployFlag()
{

}


