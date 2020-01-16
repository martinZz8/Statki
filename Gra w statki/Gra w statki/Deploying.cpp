#include "Deploying.h"
#include "Menu.h"
#include "Game.h"

void Deploying::fixShipSize()
{
	if (done_deploying_b1 == false)
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
	else if (done_deploying_b2 == false && u.getPvPGameMode() == true)
	{
		int size_of_vector = b2.numbers_of_not_deployed_ships.size();
		for (int i = 0; i < size_of_vector; i++)
		{
			if (b2.numbers_of_not_deployed_ships[i] > 0)
			{
				u.setShipSize(i + 1);
				break;
			}
		}
	}
}

void Deploying::restoreDefaults()
{
	b1.clearVectors();
	b1.setFields();
	b2.clearVectors();
	b2.setFields();
	done_deploying_b1 = false;
	done_deploying_b2 = false;
	setNUmbersOfNotDeployedShips();
	moving_ship_mode_on = false;
	indeks_of_coppied_ship = -1;
	choosed_for_move_ship_guard = false;
	if (created_advanced_ship.empty() == false)
		created_advanced_ship.clear();
	if (fields_of_temporary_ship.empty() == false)
		fields_of_temporary_ship.clear();
	if (difference_x.empty() == false)
		difference_x.clear();
	if (difference_y.empty() == false)
		difference_y.clear();
	coppied_ship.clearShipFields();
	coppied_ship.clearSurroundingFields();
}

void Deploying::clearBoard1()
{
	b1.clearVectors();
	b1.setFields();
	done_deploying_b1 = false;
	b1.setNumbersOfNotDeployedShips();
	fixShipSize();
	moving_ship_mode_on = false;
	indeks_of_coppied_ship = -1;
	choosed_for_move_ship_guard = false;
	if (created_advanced_ship.empty() == false)
		created_advanced_ship.clear();
	if (fields_of_temporary_ship.empty() == false)
		fields_of_temporary_ship.clear();
	if (difference_x.empty() == false)
		difference_x.clear();
	if (difference_y.empty() == false)
		difference_y.clear();
	coppied_ship.clearShipFields();
	coppied_ship.clearSurroundingFields();
}

void Deploying::clearBoard2()
{
	b2.clearVectors();
	b2.setFields();
	done_deploying_b2 = false;
	b2.setNumbersOfNotDeployedShips();
	fixShipSize();
	moving_ship_mode_on = false;
	indeks_of_coppied_ship = -1;
	choosed_for_move_ship_guard = false;
	if (created_advanced_ship.empty() == false)
		created_advanced_ship.clear();
	if (fields_of_temporary_ship.empty() == false)
		fields_of_temporary_ship.clear();
	if (difference_x.empty() == false)
		difference_x.clear();
	if (difference_y.empty() == false)
		difference_y.clear();
	coppied_ship.clearShipFields();
	coppied_ship.clearSurroundingFields();
}

Deploying::Deploying(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2) :coppied_ship(u),windowID(WINDOW_DEPLOYING), s(state), u(utils), buttons(buttons), b1(board1), b2(board2)
{
	m = NULL;
	g = NULL;
	indeks_of_coppied_ship = -1;
	choosed_for_move_ship_guard = false;
	audio_play_guard = true;
	warning_sample_play_guard = true;
	warning_sample_play_flag = false;
	place_ship_sample_flag = false;
	add_advanced_ship_field_sample_flag = false;
	add_advanced_ship_field_sample_guard = true;
	resize_ship_guard = true;
	reorientate_ship_guard = true;
	mouse_click_guard = true;
	done_deploying_b1 = false;
	done_deploying_b2 = false;
	moving_ship_mode_on = false;

}

void Deploying::setStates(Menu* menu, Game* game)
{
	m = menu;
	g = game;
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

	if (u.getClassicGameMode() == true)
	{
		if (u.getPvCGameMode() == true)
		{
			if (done_deploying_b1 == true && b2.getDeployShipsFlag() == true)
			{
				classicComputerDeploy(b2, false);
				cout << "Komputer zakonczyl rozstawianie boardu b2" << endl;
			}
			if (b2.getDeployShipsFlag() == false)
				done_deploying_b2 = true;
		}
	}
	else //advanced_game_mode == true
	{
		if (u.getPvCGameMode() == true)
		{
			if (done_deploying_b1 == true && b2.getDeployShipsFlag() == true)
			{
				advancedComputerDeploy(b2, false);
				cout << "Komputer zakonczyl rozstawianie boardu b2" << endl;
			}
			if (b2.getDeployShipsFlag() == false)
				done_deploying_b2 = true;
		}
	}

	mouseSwitches();
}

void Deploying::render()
{
	playAudio();
	paintText();
	paintBorders();
	if (u.getPvCGameMode() == true)
	{
		b1.paintBoard(true, true);
		b2.paintBoard(false, false); //PIERWSZY I DRUGI ARGUMENT METODY OBOK MAJA BYC NA FALSE; JEST TRUE TYLKO DLA TESTU!

		if (b1.getDeployShipsFlag() == true)
		{
			if (u.getClassicGameMode() == true && moving_ship_mode_on == false)
				b1.paintClassicShip(u.getMouseX(), u.getMouseY());
			else if (u.getAdvancedGameMode() == true && moving_ship_mode_on == false)
				paintCreatedAdvancedShip();
		}
		if (done_deploying_b1 == false && moving_ship_mode_on == true)
			paintTemporaryShip();
	}
	else if (u.getPvPGameMode() == true)
	{
		if (done_deploying_b1 == false) //roztsawianie gracza nr 1
		{
			b1.paintBoard(true, true); 
			b2.paintBoard(false, false);
		}
		else if (done_deploying_b2 == false) //rozstawianie gracza nr 2
		{
			b1.paintBoard(false, false);
			b2.paintBoard(true, true);
		}
		else //koniec rozstawiania
		{
			b1.paintBoard(false, false);
			b2.paintBoard(false, false);
		}

		if (u.getClassicGameMode() == true)
		{
			if (b1.getDeployShipsFlag() == true && moving_ship_mode_on == false)
				b1.paintClassicShip(u.getMouseX(), u.getMouseY());
			else if (b2.getDeployShipsFlag() == true && done_deploying_b1 == true && moving_ship_mode_on == false)
				b2.paintClassicShip(u.getMouseX(), u.getMouseY());
		}
		else if (u.getAdvancedGameMode() == true)
		{
			if (b1.getDeployShipsFlag() == true && moving_ship_mode_on == false)
				paintCreatedAdvancedShip();
			else if (b2.getDeployShipsFlag() == true && done_deploying_b1 == true && moving_ship_mode_on == false)
				paintCreatedAdvancedShip();
		}
		if ((done_deploying_b1 == false || (done_deploying_b1 == true && done_deploying_b2 == false)) && moving_ship_mode_on == true)
			paintTemporaryShip();
	}
	paintButtons();

}

int Deploying::getWindowID()
{
	return windowID;
}

void Deploying::classicShipSwitch(vector <int>& numbers_of_not_deployed_ships)
{
	if (u.getKeyUpPressed() == true && resize_ship_guard == true)
	{
		int actual_ship_size = u.getShipSize();
		int i = actual_ship_size - 1;
		i++; //pierwsze zwiekszenie indeksu petli
		int size_of_vector = numbers_of_not_deployed_ships.size();

		while (true)
		{
			if (i >= size_of_vector)
			{
				i = 0;
				continue;
			}
			if (numbers_of_not_deployed_ships[i] == 0)
			{
				i++;
				continue;
			}

			break;
		}
		u.setShipSize(i + 1);
		cout << "Rozmiar: " << u.getShipSize() << endl;
		resize_ship_guard = false;
	}
	if (u.getKeyDownPressed() == true && resize_ship_guard == true)
	{
		int actual_ship_size = u.getShipSize();
		int i = actual_ship_size - 1;
		i--; //pierwsze zmniejszenie indeksu petli
		int size_of_vector = numbers_of_not_deployed_ships.size();

		while (true)
		{
			if (i < 0)
			{
				i = size_of_vector - 1;
				continue;
			}
			if (numbers_of_not_deployed_ships[i] == 0)
			{
				i--;
				continue;
			}

			break;
		}
		u.setShipSize(i + 1);
		cout << "Rozmiar: " << u.getShipSize() << endl;
		resize_ship_guard = false;
	}
	if (u.getKeyUpPressed() == false && u.getKeyDownPressed() == false)
		resize_ship_guard = true;
	if (u.getKeyRightPressed() == true && reorientate_ship_guard == true)
	{
		u.setShipOrientation(u.getShipOrientation() + 1);
		if (u.getShipOrientation() > 2)
			u.setShipOrientation(1);
		cout << "Orientacja: " << u.getShipOrientation() << endl;
		reorientate_ship_guard = false;
	}
	if (u.getKeyLeftPressed() == true && reorientate_ship_guard == true)
	{
		u.setShipOrientation(u.getShipOrientation() - 1);
		if (u.getShipOrientation() < 1)
			u.setShipOrientation(2);
		cout << "Orientacja: " << u.getShipOrientation() << endl;
		reorientate_ship_guard = false;
	}
	if (u.getKeyRightPressed() == false && u.getKeyLeftPressed() == false)
		reorientate_ship_guard = true;
}

void Deploying::classicKeyboardSwitches()
{
	if (moving_ship_mode_on == false)
	{
		if (b1.getDeployShipsFlag() == true)
		{
			classicShipSwitch(b1.numbers_of_not_deployed_ships);
		}
		else if (b2.getDeployShipsFlag() == true && done_deploying_b1 == true)
		{
			classicShipSwitch(b2.numbers_of_not_deployed_ships);
		}
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
		if (u.getMouse1Clicked() == false && u.getMouse2Clicked() == false)
		{
			mouse_click_guard = true;
			place_ship_sample_flag = false;
			add_advanced_ship_field_sample_flag = false;
			warning_sample_play_flag = false;
		}

		if (u.getMouse2Clicked() == true && u.getMouse1Clicked() == false && mouse_click_guard == true && (done_deploying_b1 == false || (done_deploying_b1 == true && done_deploying_b2 == false))) //przelaczanie moving_ship_mode_on
		{
			mouse_click_guard = false;
			if (moving_ship_mode_on == false)
				moving_ship_mode_on = true;
			else //moving_ship_mode_on == true
				moving_ship_mode_on = false;
		}
		else if (buttons.getActivated(BUTTON_DEPLOYING_BACK) == true && mouse_click_guard == true)
		{
			*s = m;
			mouse_click_guard = false;
			restoreDefaults();
			u.setMouseClickedBeforeStateSwitch(true);
			cout << "Przelaczenie z DEPLOYING do MENU" << endl;
		}
		else if (buttons.getActivated(BUTTON_DEPLOYING_AUTO) == true && mouse_click_guard == true)
		{
			mouse_click_guard = false;
			if (u.getClassicGameMode() == true)
			{
				if (u.getPvCGameMode() == true)
				{
					if (b1.getDeployShipsFlag() == true && done_deploying_b1 == false)
						classicComputerDeploy(b1, true);
					else
						warning_sample_play_flag = true;
				}
				else //PvP_game_mode == true
				{
					if (b1.getDeployShipsFlag() == true && done_deploying_b1 == false)
						classicComputerDeploy(b1, true);
					else if (b2.getDeployShipsFlag() == true && done_deploying_b2 == false && done_deploying_b1 == true)
						classicComputerDeploy(b2, true);
					else
						warning_sample_play_flag = true;
				}
			}
			else //advanced_game_mode == true
			{
				if (u.getPvCGameMode() == true)
				{
					if (b1.getDeployShipsFlag() == true && done_deploying_b1 == false)
						advancedComputerDeploy(b1, true);
					else
						warning_sample_play_flag = true;
				}
				else //PvP_game_mode == true
				{
					if (b1.getDeployShipsFlag() == true && done_deploying_b1 == false)
						advancedComputerDeploy(b1, true);
					else if (b2.getDeployShipsFlag() == true && done_deploying_b2 == false && done_deploying_b1 == true)
						advancedComputerDeploy(b2, true);
					else
						warning_sample_play_flag = true;
				}
			}
		}
		else if (buttons.getActivated(BUTTON_DEPLOYING_RESET) == true && mouse_click_guard == true)
		{
			mouse_click_guard = false;
			if (u.getPvPGameMode() == true)
			{
				if (done_deploying_b1 == false)
					clearBoard1();
				else if (done_deploying_b2 == false)
					clearBoard2();
				else
					warning_sample_play_flag = true;
			}
			else //PvC_game_mode == true
			{
				if (done_deploying_b1 == false)
					clearBoard1();
				else
					warning_sample_play_flag = true;
			}
		}
		else if (buttons.getActivated(BUTTON_DEPLOYING_DONE) == true && mouse_click_guard == true)
		{
			mouse_click_guard = false;
			if (b2.getDeployShipsFlag() == false && done_deploying_b2 == false)
			{
				done_deploying_b2 = true;
				moving_ship_mode_on = false;
			}
			else if (b2.getDeployShipsFlag() == true && done_deploying_b1 == true)
			{
				cout << "Blad roztawiania b2" << endl;
				warning_sample_play_flag = true;
			}

			if (b1.getDeployShipsFlag() == false && done_deploying_b1 == false)
			{
				done_deploying_b1 = true;
				fixShipSize();
				moving_ship_mode_on = false;
			}
			else if (b1.getDeployShipsFlag() == true)
			{
				cout << "Blad rozstawiania b1" << endl;
				warning_sample_play_flag = true;
			}
		}
		else if (buttons.getActivated(BUTTON_DEPLOYING_PLAY) == true && mouse_click_guard == true)
		{
			mouse_click_guard = false;
			if (done_deploying_b1 == true && done_deploying_b2 == true)
			{
				*s = g;
				g->choose_who_starts();
				moving_ship_mode_on = false;
				b1.setNumbersOfNotDestroyedShips();
				b2.setNumbersOfNotDestroyedShips();
				u.setMouseClickedBeforeStateSwitch(true);
				cout << "Przelaczanie okna z DEPLOYING do GAME" << endl;
			}
			else
				warning_sample_play_flag = true;
		}
		else if (u.getClassicGameMode() == true)
		{
			if (u.getMouse1Clicked() == true && mouse_click_guard == true && moving_ship_mode_on == false)
			{
				mouse_click_guard = false;
				if (u.getPvCGameMode() == true)
				{
					if (b1.getDeployShipsFlag() == true) //plaer1 moze rozstawiac statki
					{
						cout << "Gracz klika myszka w classicu" << endl;
						classicPlayer1Deploy();
					}
					//ROZTSAWIANIE PLANSZY KOMPUTERA JEST W TICKU
				}
				else //PvP_game_mode == true
				{
					if (b1.getDeployShipsFlag() == true) //player1 moze rozstawiac statki
					{
						cout << "Gracz 1 klika myszka w classicu" << endl;
						classicPlayer1Deploy();
					}
					else if (b2.getDeployShipsFlag() == true && done_deploying_b1 == true) //player2 moze rozstawiac statki
					{
						cout << "Gracz 2 klika myszka w classicu" << endl;
						classicPlayer2Deploy();
					}
				}
			}
			else if (u.getMouse1Clicked() == true && moving_ship_mode_on == true)
			{
				if(u.getPvCGameMode() == true)
					movePlayerShip(b1);
				else //PvP_game_mode == true
				{
					if(done_deploying_b1 == false)
						movePlayerShip(b1);
					else if (done_deploying_b2 == false)
						movePlayerShip(b2);
				}
			}
			else if (u.getMouse1Clicked() == false && moving_ship_mode_on == true && indeks_of_coppied_ship != -1)
			{
				if (u.getPvCGameMode() == true)
				{
					int result = placeMovedPlayerShip(b1);
					if (result == 0)
						place_ship_sample_flag = true;
					else if (result == -1)
						warning_sample_play_flag = true;
					choosed_for_move_ship_guard = false;
				}
				else //PvP_game_mode == true
				{
					if (done_deploying_b1 == false)
					{
						int result = placeMovedPlayerShip(b1);
						if (result == 0)
							place_ship_sample_flag = true;
						else if (result == -1)
							warning_sample_play_flag = true;
						choosed_for_move_ship_guard = false;
					}
					else if (done_deploying_b2 == false)
					{
						int result = placeMovedPlayerShip(b2);
						if (result == 0)
							place_ship_sample_flag = true;
						else if (result == -1)
							warning_sample_play_flag = true;
						choosed_for_move_ship_guard = false;
					}
				}
			}
		}
		else if (u.getAdvancedGameMode() == true) //tutaj byl sam if
		{
			if (u.getMouse1Clicked() == true && moving_ship_mode_on == false)
			{
				if (u.getPvCGameMode() == true)
				{
					if (b1.getDeployShipsFlag() == true) //plaer1 moze rozstawiac statki
					{
						advancedPlayer1Deploy();
					}
					//ROZTSAWIANIE PLANSZY KOMPUTERA JEST W TICKU
				}
				else //PvP_game_mode == true
				{
					if (b1.getDeployShipsFlag() == true) //player1 moze rozstawiac statki
						advancedPlayer1Deploy();
					else if (b2.getDeployShipsFlag() == true && done_deploying_b1 == true) //player2 moze rozstawiac statki
						advancedPlayer2Deploy();
				}
			}
			else if (u.getMouse1Clicked() == false && moving_ship_mode_on == false)
			{
				if (u.getPvCGameMode() == true)
				{
					if (b1.getDeployShipsFlag() == true) //plaer1 moze rozstawiac statki
					{
						int ship_size = created_advanced_ship.size();
						if (ship_size == 1 || ship_size == 2 || ship_size == 3 || ship_size == 4) //dowzwolone rozmiary statku
						{
							if (b1.numbers_of_not_deployed_ships[ship_size - 1] > 0)
							{
								b1.addAdvancedShip(created_advanced_ship);
								place_ship_sample_flag = true;
								created_advanced_ship.clear();
							}
							else
							{
								warning_sample_play_flag = true;
								created_advanced_ship.clear();
							}
						}
						else if (ship_size > 4) //niedozwolony rozmiar statku
						{
							created_advanced_ship.clear();
							warning_sample_play_flag = true;
						}
					}	
				}
				else //PvP_game_mode == true
				{
					if (b1.getDeployShipsFlag() == true) //plaer1 moze rozstawiac statki
					{
						int ship_size = created_advanced_ship.size();
						if (ship_size == 1 || ship_size == 2 || ship_size == 3 || ship_size == 4) //dowzwolone rozmiary statku
						{
							if (b1.numbers_of_not_deployed_ships[ship_size - 1] > 0)
							{
								b1.addAdvancedShip(created_advanced_ship);
								place_ship_sample_flag = true;
								created_advanced_ship.clear();
							}
							else
							{
								warning_sample_play_flag = true;
								created_advanced_ship.clear();
							}
						}
						else if (ship_size > 4) //niedozwolony rozmiar statku
						{
							created_advanced_ship.clear();
							warning_sample_play_flag = true;
						}
					}
					else if (b2.getDeployShipsFlag() == true && done_deploying_b1 == true) //plaer2 moze rozstawiac statki
					{
						int ship_size = created_advanced_ship.size();
						if (ship_size == 1 || ship_size == 2 || ship_size == 3 || ship_size == 4) //dowzwolone rozmiary statku
						{
							if (b2.numbers_of_not_deployed_ships[ship_size - 1] > 0)
							{
								b2.addAdvancedShip(created_advanced_ship);
								place_ship_sample_flag = true;
								created_advanced_ship.clear();
							}
							else
							{
								warning_sample_play_flag = true;
								created_advanced_ship.clear();
							}
						}
						else if (ship_size > 4) //niedozwolony rozmiar statku
						{
							created_advanced_ship.clear();
							warning_sample_play_flag = true;
						}
					}
				}
			}
			else if (u.getMouse1Clicked() == true && moving_ship_mode_on == true)
			{
				if (u.getPvCGameMode() == true)
					movePlayerShip(b1);
				else //PvP_game_mode == true
				{
					if (done_deploying_b1 == false)
						movePlayerShip(b1);
					else if (done_deploying_b2 == false)
						movePlayerShip(b2);
				}
		
			}
			else if (u.getMouse1Clicked() == false && moving_ship_mode_on == true && indeks_of_coppied_ship != -1)
			{
				if (u.getPvCGameMode() == true)
				{
					int result = placeMovedPlayerShip(b1);
					if (result == 0)
						place_ship_sample_flag = true;
					else if (result == -1)
						warning_sample_play_flag = true;
					choosed_for_move_ship_guard = false;
				}
				else //PvP_game_mode == true
				{
					if (done_deploying_b1 == false)
					{
						int result = placeMovedPlayerShip(b1);
						if (result == 0)
							place_ship_sample_flag = true;
						else if (result == -1)
							warning_sample_play_flag = true;
						choosed_for_move_ship_guard = false;
					}
					else if (done_deploying_b2 == false)
					{
						int result = placeMovedPlayerShip(b2);
						if (result == 0)
							place_ship_sample_flag = true;
						else if (result == -1)
							warning_sample_play_flag = true;
						choosed_for_move_ship_guard = false;
					}
				}
			}
		}
	}
}

void Deploying::classicPlayer1Deploy()
{
	int x = b1.deployClassicShip(u.getMouseX(), u.getMouseY(), u.getShipOrientation(), u.getShipSize());
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

void Deploying::classicPlayer2Deploy()
{
	int x = b2.deployClassicShip(u.getMouseX(), u.getMouseY(), u.getShipOrientation(), u.getShipSize());
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

void Deploying::classicComputerDeploy(Board& b, bool deploy_for_player)
{
	float l_x = b.getXOffset();
	float r_x = l_x + b.getWidth();
	float u_y = b.getYOffset();
	float d_y = u_y + b.getHeight();
	int mod_x = r_x - l_x + 1;
	int mod_y = d_y - u_y + 1;

	for (int indeks = b.numbers_of_not_deployed_ships.size() - 1; indeks >= 0; indeks--)
	{
		while (b.numbers_of_not_deployed_ships[indeks] > 0)
		{
			int iteration = 0;
			int condition;
			do
			{
				int orientation = (rand() % 2) + 1; //losowanie od 1 do 2
				float x = (rand() % mod_x) + l_x;
				float y = (rand() % mod_y) + u_y;
				cout << "wylosowane x wynosi: " << x << ", natomiast wylosowane y: " << y << endl;
				condition = b.deployClassicShip(x, y, orientation, indeks + 1);
				iteration++;
				if (deploy_for_player == true && iteration > 300) //zakleszczenie, nie mozna znalezc odpowiedniego fielda
				{
					warning_sample_play_flag = true;
					return;
				}	
			} while (condition == -1);
		}
	}
}

void Deploying::advancedPlayer1Deploy()
{
	int x = b1.deployAdvancedShip(u.getMouseX(), u.getMouseY(), created_advanced_ship, true);
	if (x == 0) //dodano fielda
	{
		add_advanced_ship_field_sample_flag = true;
		warning_sample_play_flag = false;
	}
	else if (x == -1) //nie dodano fielda, bo kliknieto w zabrionione miejsce
	{
		if (created_advanced_ship.empty() == false)
			created_advanced_ship.clear();
		add_advanced_ship_field_sample_flag = false;
		if (buttons.getActivated(BUTTON_DEPLOYING_DONE) == false && buttons.getActivated(BUTTON_DEPLOYING_PLAY) == false && buttons.getActivated(BUTTON_DEPLOYING_AUTO) == false && buttons.getActivated(BUTTON_DEPLOYING_RESET) == false && buttons.getActivated(BUTTON_DEPLOYING_BACK) == false)
			warning_sample_play_flag = true;	
	}
}

void Deploying::advancedPlayer2Deploy()
{
	int x = b2.deployAdvancedShip(u.getMouseX(), u.getMouseY(), created_advanced_ship, true);
	if (x == 0) //dodano fielda
	{
		add_advanced_ship_field_sample_flag = true;
		warning_sample_play_flag = false;
	}
	else if (x == -1) //nie dodano fielda, bo kliknieto w zabrionione miejsce
	{
		if (created_advanced_ship.empty() == false)
			created_advanced_ship.clear();
		add_advanced_ship_field_sample_flag = false;
		if (buttons.getActivated(BUTTON_DEPLOYING_DONE) == false && buttons.getActivated(BUTTON_DEPLOYING_PLAY) == false && buttons.getActivated(BUTTON_DEPLOYING_AUTO) == false && buttons.getActivated(BUTTON_DEPLOYING_RESET) == false && buttons.getActivated(BUTTON_DEPLOYING_BACK) == false)
			warning_sample_play_flag = true;
	}
}

void Deploying::advancedComputerDeploy(Board& b, bool deploy_for_player)
{
	float l_x = b.getXOffset();
	float r_x = l_x + b.getWidth();
	float u_y = b.getYOffset();
	float d_y = u_y + b.getHeight();
	int mod_x = r_x - l_x + 1;
	int mod_y = d_y - u_y + 1;

	for (int indeks = b.numbers_of_not_deployed_ships.size() - 1; indeks >= 0; indeks--)
	{
		int clearing = 0;
		while (b.numbers_of_not_deployed_ships[indeks] > 0)
		{
			int iteration = 0;
			clearing = 0;
			int condition;
			do
			{
				float x;
				float y;
				if (created_advanced_ship.size() > 0)
				{
					float field_size = created_advanced_ship[created_advanced_ship.size() - 1].getWidth();
					float new_l_x = created_advanced_ship[created_advanced_ship.size() - 1].getCoordX() - field_size;
					float new_r_x = new_l_x + (3 * field_size);
					float new_u_y = created_advanced_ship[created_advanced_ship.size() - 1].getCoordY() - field_size;
					float new_d_y = new_u_y + (3 * field_size);
					int new_mod_x = new_r_x - new_l_x + 1;
					int new_mod_y = new_d_y - new_u_y + 1;
					x = (rand() % new_mod_x) + new_l_x;
					y = (rand() % new_mod_y) + new_u_y;
				}
				else
				{
					x = (rand() % mod_x) + l_x;
					y = (rand() % mod_y) + u_y;
				}
				cout << "wylosowane x wynosi: " << x << ", natomiast wylosowane y: " << y << endl;
				condition = b.deployAdvancedShip(x, y, created_advanced_ship, false);
				iteration++;
				if (condition == -1 && created_advanced_ship.empty() == false)
					created_advanced_ship.clear();
				if (deploy_for_player == true && iteration > 100) //zakleszczenie, nie mozna znalezc odpowiedniego fielda
				{
					cout << "Czyszczenie" << endl;
					iteration = 0;
					clearing++;
					if(created_advanced_ship.empty() == false)
						created_advanced_ship.clear();
					if (clearing == 15)
					{
						warning_sample_play_flag = true;
						return;
					}
				}
			} while (created_advanced_ship.size() < (indeks + 1));
			b.addAdvancedShip(created_advanced_ship);
			created_advanced_ship.clear();
		}
	}
}

void Deploying::movePlayerShip(Board& b)
{
	if (choosed_for_move_ship_guard == false)
	{
		indeks_of_coppied_ship = b.whichShip(u.getMouseX(), u.getMouseY());
		if (indeks_of_coppied_ship != -1)
		{
			b.copyShip(coppied_ship, indeks_of_coppied_ship);
			b.copyFieldsOfShip(coppied_ship, fields_of_temporary_ship);
			b.clearVectorsOfShip(indeks_of_coppied_ship);
			float mouse_x = u.getMouseX();
			float mouse_y = u.getMouseY();
			int size_of_vector = fields_of_temporary_ship.size();
			for (int i = 0; i < size_of_vector; i++)
			{
				difference_x.push_back(fields_of_temporary_ship[i].getCoordX() - mouse_x);
				difference_y.push_back(fields_of_temporary_ship[i].getCoordY() - mouse_y);
			}
			choosed_for_move_ship_guard = true;
		}
		else
			warning_sample_play_flag = true;
	}
	else if (indeks_of_coppied_ship != -1) //choosed_for_move_ship_guard == true
	{
		float mouse_x = u.getMouseX();
		float mouse_y = u.getMouseY();
		int size_of_vector = fields_of_temporary_ship.size();
		for (int i = 0; i < size_of_vector; i++)
		{
			fields_of_temporary_ship[i].setCoordX(mouse_x + difference_x[i]);
			fields_of_temporary_ship[i].setCoordY(mouse_y + difference_y[i]);
		}
	}
}

int Deploying::placeMovedPlayerShip(Board& b)
{
	int result = b.placeShip(coppied_ship, indeks_of_coppied_ship, fields_of_temporary_ship);
	indeks_of_coppied_ship = -1;
	fields_of_temporary_ship.clear();
	difference_x.clear();
	difference_y.clear();
	coppied_ship.clearShipFields();
	coppied_ship.clearSurroundingFields();
	return result;
}

void Deploying::paintButtons()
{
	buttons.paintButtonWithText(BUTTON_DEPLOYING_DONE, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_DEPLOYING_PLAY, FONT_SIZE_BIG);
	buttons.paintButtonWithText(BUTTON_DEPLOYING_BACK, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_DEPLOYING_AUTO, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_DEPLOYING_RESET, FONT_SIZE_SMALL);

	if (buttons.getHighlighted(BUTTON_DEPLOYING_DONE) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_DONE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_DEPLOYING_PLAY) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_PLAY, FONT_SIZE_BIG);
	else if (buttons.getHighlighted(BUTTON_DEPLOYING_BACK) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_BACK, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_DEPLOYING_AUTO) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_AUTO, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_DEPLOYING_RESET) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_RESET, FONT_SIZE_SMALL);
}

void Deploying::paintText()
{
	if (u.getPvCGameMode() == true)
	{
		if (done_deploying_b1 == false) //wybiera gracz
		{
			u.drawText("GRACZ", FONT_SIZE_BIG, 255, 58, 37, 80, 25);
			u.drawText("KOMPUTER", FONT_SIZE_BIG, 183, 234, 243, 500, 25);
			u.drawText("4 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 177, 520);
			u.drawText("3 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 328, 520);
			u.drawText("2 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 477, 520);
			u.drawText("1 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 629, 520);
			u.drawText("POZOSTALE STATKI", FONT_SIZE_BIG, 255, 58, 37, 275, 477);

			/*Wypisanie liczb na ekranie*/
			string number;
			number = to_string(b1.numbers_of_not_deployed_ships[3]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 200, 540);
			number = to_string(b1.numbers_of_not_deployed_ships[2]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 350, 540);
			number = to_string(b1.numbers_of_not_deployed_ships[1]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 500, 540);
			number = to_string(b1.numbers_of_not_deployed_ships[0]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 650, 540);
			
		}
		else if (done_deploying_b2 == false) //wybiera komputer
		{
			u.drawText("GRACZ", FONT_SIZE_BIG, 183, 234, 243, 80, 25); 
			u.drawText("KOMPUTER", FONT_SIZE_BIG, 255, 58, 37, 500, 25);
		}
		else //wszyscy juz wybrali
		{
			u.drawText("GRACZ", FONT_SIZE_BIG, 183, 234, 243, 80, 25);
			u.drawText("KOMPUTER", FONT_SIZE_BIG, 183, 234, 243, 500, 25);
		}
	}
	else if (u.getPvPGameMode() == true)
	{
		if (done_deploying_b1 == false) //wybiera gracz nr 1
		{
			u.drawText("GRACZ NR 1", FONT_SIZE_BIG, 255, 58, 37, 80, 25);
			u.drawText("GRACZ NR 2", FONT_SIZE_BIG, 183, 234, 243, 500, 25);
			u.drawText("4 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 177, 520);
			u.drawText("3 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 328, 520);
			u.drawText("2 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 477, 520);
			u.drawText("1 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 629, 520);
			u.drawText("POZOSTALE STATKI", FONT_SIZE_BIG, 255, 58, 37, 275, 477);

			/*Wypisanie liczb na ekranie*/
			string number;
			number = to_string(b1.numbers_of_not_deployed_ships[3]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 200, 540);
			number = to_string(b1.numbers_of_not_deployed_ships[2]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 350, 540);
			number = to_string(b1.numbers_of_not_deployed_ships[1]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 500, 540);
			number = to_string(b1.numbers_of_not_deployed_ships[0]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 650, 540);
		}
		else if (done_deploying_b2 == false) //wybiera gracz nr 2
		{
			u.drawText("GRACZ NR 1", FONT_SIZE_BIG, 183, 234, 243, 80, 25);
			u.drawText("GRACZ NR 2", FONT_SIZE_BIG, 255, 58, 37, 500, 25);
			u.drawText("4 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 177, 520);
			u.drawText("3 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 328, 520);
			u.drawText("2 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 477, 520);
			u.drawText("1 MASZT", FONT_SIZE_SMALL, 206, 97, 37, 629, 520);
			u.drawText("POZOSTALE STATKI", FONT_SIZE_BIG, 255, 58, 37, 275, 477);

			/*Wypisanie liczb na ekranie*/
			string number;
			number = to_string(b2.numbers_of_not_deployed_ships[3]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 200, 540);
			number = to_string(b2.numbers_of_not_deployed_ships[2]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 350, 540);
			number = to_string(b2.numbers_of_not_deployed_ships[1]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 500, 540);
			number = to_string(b2.numbers_of_not_deployed_ships[0]);
			u.drawText(number.c_str(), FONT_SIZE_BIG, 206, 97, 37, 650, 540);
		}
		else //wszyscy juz wybrali
		{
			u.drawText("GRACZ NR 1", FONT_SIZE_BIG, 183, 234, 243, 80, 25);
			u.drawText("GRACZ NR 2", FONT_SIZE_BIG, 183, 234, 243, 500, 25);
		}
	}

	if (done_deploying_b1 == false || (done_deploying_b1 == true && done_deploying_b2 == false))
	{
		u.drawText("Tryb", FONT_SIZE_SMALL, 183, 234, 243, 740, 475);
		if (moving_ship_mode_on == false)
			u.drawText("rozstawiania", FONT_SIZE_SMALL, 206, 97, 37, 780, 475);
		else //moving_ship_mode_on == true
			u.drawText("przestawiania", FONT_SIZE_SMALL, 101, 226, 49, 780, 475);
	}
}

void Deploying::paintBorders()
{
	if(u.getPvCGameMode() == true && done_deploying_b1 == false)
		u.drawBorders(167, 480, 530, 103, 3, 159, 58, 37);
	else if (u.getPvPGameMode() == true && (done_deploying_b1 == false || done_deploying_b2 == false))
		u.drawBorders(167, 480, 530, 103, 3, 159, 58, 37);
}

void Deploying::paintCreatedAdvancedShip()
{
	if (created_advanced_ship.empty() == false)
	{
		for (Field f : created_advanced_ship)
		{
			float c_x = f.getCoordX();
			float c_y = f.getCoordY();
			float width = f.getWidth();
			al_draw_filled_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfShip());
		}
	}
}

void Deploying::paintTemporaryShip()
{
	if (fields_of_temporary_ship.empty() == false)
	{
		for (Field f : fields_of_temporary_ship)
		{
			float c_x = f.getCoordX();
			float c_y = f.getCoordY();
			float width = f.getWidth();
			al_draw_filled_rectangle(c_x, c_y, c_x + width, c_y + width, u.getColorOfShip());
		}
	}
}

void Deploying::playAudio()
{
	if (u.getVolumeOn() == true)
	{
		/*Audio dotyczace highlightow*/
		bool highlighted = false;
		for (int indeks = BUTTON_DEPLOYING_DONE; indeks <= BUTTON_DEPLOYING_RESET; indeks++)
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
		if (warning_sample_play_flag == true && warning_sample_play_guard == true)
		{
			u.playSample(AUDIO_ERROR);
			warning_sample_play_guard = false;
		}

		/*Audio dotyczace rozstawiania statkow*/
		if (place_ship_sample_flag == true && audio_play_guard == true)
		{
			u.playSample(AUDIO_PLACED_SHIP);
			audio_play_guard = false;
		}


		/*Audio dotyczace dodawania fielda do statku advanced*/
		if (add_advanced_ship_field_sample_flag == true && add_advanced_ship_field_sample_guard == true)
		{
			u.playSample(AUDIO_MOUSE_CLICK);
			add_advanced_ship_field_sample_flag = false;
			add_advanced_ship_field_sample_guard = false;
		}

		if (highlighted == false && place_ship_sample_flag == false  && audio_play_guard == false) //kiedy puscimy przycisk myszy mozna bedzie znowu odtworzyc sampla
			audio_play_guard = true;
		if (warning_sample_play_flag == false && warning_sample_play_guard == false)
			warning_sample_play_guard = true;
		if (add_advanced_ship_field_sample_flag == false && add_advanced_ship_field_sample_guard == false)
			add_advanced_ship_field_sample_guard = true;
	}
}