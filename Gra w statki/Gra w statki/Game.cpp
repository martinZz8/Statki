#include "Game.h"
#include "Menu.h"
#include "Deploying.h"

void Game::choose_who_starts()
{
	if (u.getPvPGameMode() == true)
	{
		int number = (rand() % 2) + 1; //losowanie od 1 do dwa
		if (number == 1)
			player1_turn_flag = true;
		else //number == 2
			player1_turn_flag = false;
	}
}

int Game::check_end_of_game()
{
	int size_of_vector_1 = b1.numbers_of_not_destroyed_ships.size();
	int size_of_vector_2 = b2.numbers_of_not_destroyed_ships.size();
	int numbers_1 = 0;
	int numbers_2 = 0;
	for (int i = 0; i < size_of_vector_1; i++)
	{
		if (b1.numbers_of_not_destroyed_ships[i] != 0)
			break;
		numbers_1++;
	}
	if (numbers_1 == size_of_vector_1) //wygral gracz spod boardu 2
	{
		end_of_game_flag = true;
		return 2;
	}
	for (int i = 0; i < size_of_vector_2; i++)
	{
		if (b2.numbers_of_not_destroyed_ships[i] != 0)
			break;
		numbers_2++;
	}
	if (numbers_2 == size_of_vector_2) //wygral gracz spod boardu 1
	{
		end_of_game_flag = true;
		return 1;
	}
	return 0; //nikt nie wygral
}

Game::Game(State** state, Utils& utils, Buttons& buttons, Board& board1, Board& board2):windowID(WINDOW_GAME), s(state), u(utils), buttons(buttons), b1(board1), b2(board2)
{
	m = NULL;
	d = NULL;
	player1_turn_flag = true;
	audio_play_guard = true;
	warning_sample_play_guard = true;
	warning_sample_play_flag = false;
	mouse_click_guard = true;
	ship_hitted_sample_play_flag = false;
	ship_missed_sample_play_flag = false;
	end_of_game_flag = false;
	who_won_game = 0;
	indeks_of_last_hitted_ship = -1;
}

void Game::setStates(Menu* menu, Deploying* deploying)
{
	m = menu;
	d = deploying;
}

void Game::tick()
{
	if (u.getPvCGameMode() == true && who_won_game == 0)
	{
		if (player1_turn_flag == false)
		{
			if (u.getClassicGameMode() == true)
			{
				Sleep(500);
				int result = classicComputerPvCShoot(b1);
				if (result == -1)
				{
					if (u.getVolumeOn() == true)
						u.playSample(AUDIO_MISSED_SHOT);
					player1_turn_flag = true;
				}
				else if (result == 0)
				{
					who_won_game = check_end_of_game();
					if (u.getVolumeOn() == true)
						u.playSample(AUDIO_HITTED_SHIP);
				}	
			}
			else if (u.getAdvancedGameMode() == true)
			{	
				Sleep(500);
				int result = advancedComputerPvCShoot(b1);
				if (result == -1)
				{
					if (u.getVolumeOn() == true)
						u.playSample(AUDIO_MISSED_SHOT);
					player1_turn_flag = true;
				}
				else if (result == 0)
				{
					who_won_game = check_end_of_game();
					if (u.getVolumeOn() == true)
						u.playSample(AUDIO_HITTED_SHIP);
				}	
			}
		}
	}
	mouseSwitches();
}

void Game::render()
{
	playAudio();
	paintBorders();
	paintButtons();
	if (end_of_game_flag == false)
	{
		b1.paintBoard(false, false);
		b2.paintBoard(false, false);
	}
	else //end_of_game_flag == true
	{
		b1.paintBoard(true, true);
		b2.paintBoard(true, true);
	}
	paintText();

}

int Game::getWindowID()
{
	return windowID;
}

int Game::playerShoot(Board& b)
{
	return b.setShipHitted(u.getMouseX(), u.getMouseY());
}

int Game::classicComputerPvCShoot(Board& b)
{
	int result = 2;
	float x = -1;
	float y = -1;
	do
	{
		if (indeks_of_last_hitted_ship != -1)
		{
			if (b.getShipsDestroyedFlag(indeks_of_last_hitted_ship) == false)
			{
				float field_size = b.getFieldSize();
				vector <float> coord_x;
				vector <float> coord_y;
				b.getCoordsOfShipHittedFields(indeks_of_last_hitted_ship, coord_x, coord_y);
				int number_of_hitted_fields = b.getNumbersOfShipHittedFields(indeks_of_last_hitted_ship);
				do
				{
					if (number_of_hitted_fields == 1) //losujemy fielda na lewo, prawo, w gore albo w dol
					{
						int number = (rand() % 4) + 1;
						if (number == 1) //w lewo
						{
							x = coord_x[0] - field_size;
							y = coord_y[0];
						}
						else if (number == 2) //w prawo
						{
							x = coord_x[0] + field_size;
							y = coord_y[0];
						}
						else if (number == 3) //w gore
						{
							x = coord_x[0];
							y = coord_y[0] - field_size;
						}
						else //number == 4 w dol
						{
							x = coord_x[0];
							y = coord_y[0] + field_size;
						}
					}
					else //number_of_hitted_fields >= 2
					{
						int random = (rand() % 2) + 1;
						float difference_x = coord_x[0] - coord_x[1];
						if (difference_x == 0) //pionowo
						{
							if (random == 1) //do gory
							{
								x = coord_x[0];
								y = coord_y[0] - field_size;
							}
							else //do dolu
							{
								x = coord_x[number_of_hitted_fields - 1];
								y = coord_y[number_of_hitted_fields - 1] + field_size;
							}
						}
						else //poziomo
						{
							if (random == 1) //w lewo
							{
								x = coord_x[0] - field_size;
								y = coord_y[0];
							}
							else //w prawo
							{
								x = coord_x[number_of_hitted_fields - 1] + field_size;
								y = coord_y[number_of_hitted_fields - 1];
							}
						}
					}
				} while ((x < b.getXOffset() || x >= b.getXOffset() + u.getBoardSize()) && (y < b.getYOffset() || y >= b.getYOffset() + u.getBoardSize()));
			}
			else //wylosowanie komputera po znisczonym statku
			{
				indeks_of_last_hitted_ship = -1;
				float l_x = b.getXOffset();
				float r_x = l_x + b.getWidth();
				float u_y = b.getYOffset();
				float d_y = u_y + b.getHeight();
				int mod_x = r_x - l_x + 1;
				int mod_y = d_y - u_y + 1;
				x = (rand() % mod_x) + l_x;
				y = (rand() % mod_y) + u_y;
			}
		}
		else //pierwsze wylosowanie komputera albo po zniszczonym statku i nie trafionym pierwszym strzale
		{
			float l_x = b.getXOffset();
			float r_x = l_x + b.getWidth();
			float u_y = b.getYOffset();
			float d_y = u_y + b.getHeight();
			int mod_x = r_x - l_x + 1;
			int mod_y = d_y - u_y + 1;
			x = (rand() % mod_x) + l_x;
			y = (rand() % mod_y) + u_y;
		}

		result = b.setShipHitted(x, y, indeks_of_last_hitted_ship);
	} while (result == 1);
	return result;
}

int Game::advancedComputerPvCShoot(Board& b)
{
	int result = 2;
	float x = -1;
	float y = -1;
	do
	{
		if (indeks_of_last_hitted_ship != -1)
		{
			if (b.getShipsDestroyedFlag(indeks_of_last_hitted_ship) == false)
			{
				float field_size = b.getFieldSize();
				vector <float> coord_x;
				vector <float> coord_y;
				b.getCoordsOfShipHittedFields(indeks_of_last_hitted_ship, coord_x, coord_y);
				int number_of_hitted_fields = b.getNumbersOfShipHittedFields(indeks_of_last_hitted_ship);
				do
				{
					int indeks = 0;
					if (number_of_hitted_fields != 1)
						indeks = rand() % number_of_hitted_fields;
					int random = (rand() % 4) + 1;

					if (random == 1) //w lewo
					{
						x = coord_x[indeks] - field_size;
						y = coord_y[indeks];
					}
					else if (random == 2) // w prawo
					{
						x = coord_x[indeks] + field_size;
						y = coord_y[indeks];
					}
					else if (random == 3) //w gore
					{
						x = coord_x[indeks];
						y = coord_y[indeks] - field_size;
					}
					else //random == 4 w dol
					{
						x = coord_x[indeks];
						y = coord_y[indeks] + field_size;
					}
				} while ((x < b.getXOffset() || x >= b.getXOffset() + u.getBoardSize()) && (y < b.getYOffset() || y >= b.getYOffset() + u.getBoardSize()));
			}
			else //wylosowanie komputera po znisczonym statku
			{
				indeks_of_last_hitted_ship = -1;
				float l_x = b.getXOffset();
				float r_x = l_x + b.getWidth();
				float u_y = b.getYOffset();
				float d_y = u_y + b.getHeight();
				int mod_x = r_x - l_x + 1;
				int mod_y = d_y - u_y + 1;
				x = (rand() % mod_x) + l_x;
				y = (rand() % mod_y) + u_y;
			}
		}
		else //pierwsze wylosowanie komputera albo po zniszczonym statku i nie trafionym pierwszym strzale
		{
			float l_x = b.getXOffset();
			float r_x = l_x + b.getWidth();
			float u_y = b.getYOffset();
			float d_y = u_y + b.getHeight();
			int mod_x = r_x - l_x + 1;
			int mod_y = d_y - u_y + 1;
			x = (rand() % mod_x) + l_x;
			y = (rand() % mod_y) + u_y;
		}

		result = b.setShipHitted(x, y, indeks_of_last_hitted_ship);
	} while (result == 1);
	return result;
}

void Game::mouseSwitches()
{
	if (u.getMouseClickedBeforeStateSwitch() == true)
	{
		u.setMouse1Clicked(false); //sztuczne ustawienie kliknietego lewego przycisku myszy na false po zmianie okna
		u.setMouseClickedBeforeStateSwitch(false);
	}
	else
	{
		if (u.getMouse1Clicked() == false)
		{
			mouse_click_guard = true;
			warning_sample_play_flag = false;
			ship_hitted_sample_play_flag = false;
			ship_missed_sample_play_flag = false;
		}

		if (buttons.getActivated(BUTTON_GAME_BACK) == true && mouse_click_guard == true)
		{
			*s = m;
			d->restoreDefaults();
			player1_turn_flag = true;
			mouse_click_guard = false;
			end_of_game_flag = false;
			who_won_game = 0;
			indeks_of_last_hitted_ship = -1;
			u.setMouseClickedBeforeStateSwitch(true);
			cout << "Przelaczenie z GAME do MENU" << endl;
		}
		else if (u.getMouse1Clicked() == true && mouse_click_guard == true && who_won_game == 0)
		{
			mouse_click_guard = false;
			if (u.getPvPGameMode() == true)
			{
				if (player1_turn_flag == true) //runda gracza nr 1
				{
					int result = playerShoot(b2);
					if (result == -1)
					{
						ship_missed_sample_play_flag = true;
						player1_turn_flag = false;
					}
					else if (result == 0)
					{
						who_won_game = check_end_of_game();
						ship_hitted_sample_play_flag = true;
					}
					else if (result == 1)
						warning_sample_play_flag = true;	
				}
				else //player1_turn_flag == false
				{
					int result = playerShoot(b1);
					if (result == -1)
					{
						ship_missed_sample_play_flag = true;
						player1_turn_flag = true;
					}
					else if (result == 0)
					{
						who_won_game = check_end_of_game();
						ship_hitted_sample_play_flag = true;
					}
					else if (result == 1)
						warning_sample_play_flag = true;
				}
			}
			else if (u.getPvCGameMode() == true)
			{
				if (player1_turn_flag == true)
				{
					int result = playerShoot(b2);
					if (result == -1)
					{
						ship_missed_sample_play_flag = true;
						player1_turn_flag = false;
					}
					else if (result == 0)
					{
						who_won_game = check_end_of_game();
						ship_hitted_sample_play_flag = true;
					}
					else if (result == 1)
						warning_sample_play_flag = true;
				}
			}
		}
	}
}

void Game::playAudio()
{
	if (u.getVolumeOn() == true)
	{
		/*Audio dotyczace highlightow*/
		bool highlighted = false;
		for (int indeks = BUTTON_GAME_BACK; indeks <= BUTTON_GAME_BACK; indeks++)
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

		/*Audio dotyczace trafienia statku*/
		if (ship_hitted_sample_play_flag == true && audio_play_guard == true)
		{
			u.playSample(AUDIO_HITTED_SHIP);
			audio_play_guard = false;
		}

		/*Audio dotyczace zmissowania statku*/
		if (ship_missed_sample_play_flag == true && audio_play_guard == true)
		{
			u.playSample(AUDIO_MISSED_SHOT);
			audio_play_guard = false;
		}

		if (highlighted == false && ship_hitted_sample_play_flag == false && ship_missed_sample_play_flag == false && audio_play_guard == false) //kiedy puscimy przycisk myszy mozna bedzie znowu odtworzyc sampla
			audio_play_guard = true;
		if (warning_sample_play_flag == false && warning_sample_play_guard == false)
			warning_sample_play_guard = true;
	}
}

void Game::paintText()
{
	/**Pod boardem nr 1**/
	u.drawText("4 MASZT", FONT_SIZE_SMALL, 183, 234, 243, 80, 500);
	u.drawText("3 MASZT", FONT_SIZE_SMALL, 183, 234, 243, 160, 500);
	u.drawText("2 MASZT", FONT_SIZE_SMALL, 183, 234, 243, 240, 500);
	u.drawText("1 MASZT", FONT_SIZE_SMALL, 183, 234, 243, 320, 500);
	u.drawText("POZOSTALE STATKI", FONT_SIZE_SMALL, 183, 234, 243, 80, 480);

	/*Wypisanie liczb na ekranie*/
	string number;
	number = to_string(b1.numbers_of_not_destroyed_ships[3]);
	u.drawText(number.c_str(), FONT_SIZE_SMALL, 183, 234, 243, 103, 520);
	number = to_string(b1.numbers_of_not_destroyed_ships[2]);
	u.drawText(number.c_str(), FONT_SIZE_SMALL, 183, 234, 243, 183, 520);
	number = to_string(b1.numbers_of_not_destroyed_ships[1]);
	u.drawText(number.c_str(), FONT_SIZE_SMALL, 183, 234, 243, 263, 520);
	number = to_string(b1.numbers_of_not_destroyed_ships[0]);
	u.drawText(number.c_str(), FONT_SIZE_SMALL, 183, 234, 243, 343, 520);

	/**Pod boardem nr 2**/
	u.drawText("4 MASZT", FONT_SIZE_SMALL, 183, 234, 243, 500, 500);
	u.drawText("3 MASZT", FONT_SIZE_SMALL, 183, 234, 243, 580, 500);
	u.drawText("2 MASZT", FONT_SIZE_SMALL, 183, 234, 243, 660, 500);
	u.drawText("1 MASZT", FONT_SIZE_SMALL, 183, 234, 243, 740, 500);
	u.drawText("POZOSTALE STATKI", FONT_SIZE_SMALL, 183, 234, 243, 500, 480);

	/*Wypisanie liczb na ekranie*/
	number = to_string(b2.numbers_of_not_destroyed_ships[3]);
	u.drawText(number.c_str(), FONT_SIZE_SMALL, 183, 234, 243, 523, 520);
	number = to_string(b2.numbers_of_not_destroyed_ships[2]);
	u.drawText(number.c_str(), FONT_SIZE_SMALL, 183, 234, 243, 603, 520);
	number = to_string(b2.numbers_of_not_destroyed_ships[1]);
	u.drawText(number.c_str(), FONT_SIZE_SMALL, 183, 234, 243, 683, 520);
	number = to_string(b2.numbers_of_not_destroyed_ships[0]);
	u.drawText(number.c_str(), FONT_SIZE_SMALL, 183, 234, 243, 763, 520);

	if (u.getPvCGameMode() == true)
	{
		if (player1_turn_flag == true)
		{
			u.drawText("GRACZ", FONT_SIZE_BIG, 255, 58, 37, 80, 25);
			u.drawText("KOMPUTER", FONT_SIZE_BIG, 183, 234, 243, 500, 25);
		}
		else //player1_turn_flag == false
		{
			u.drawText("GRACZ", FONT_SIZE_BIG, 183, 234, 243, 80, 25);
			u.drawText("KOMPUTER", FONT_SIZE_BIG, 255, 58, 37, 500, 25);
		}
	}
	else if (u.getPvPGameMode() == true)
	{
		if (player1_turn_flag == true)
		{
			u.drawText("GRACZ NR 1", FONT_SIZE_BIG, 255, 58, 37, 80, 25);
			u.drawText("GRACZ NR 2", FONT_SIZE_BIG, 183, 234, 243, 500, 25);
		}
		else //player1_turn_flag == false
		{
			u.drawText("GRACZ NR 1", FONT_SIZE_BIG, 183, 234, 243, 80, 25);
			u.drawText("GRACZ NR 2", FONT_SIZE_BIG, 255, 58, 37, 500, 25);
		}
	}

	//Wypisanie komunikatu, jesli ktos wygral gre
	if (u.getPvCGameMode() == true)
	{
		if (who_won_game == 1)
			u.drawText("WYGRAL GRACZ", FONT_SIZE_BIG, 255, 58, 37, 100, 545);
		else if (who_won_game == 2)
			u.drawText("WYGRAL KOMPUTER", FONT_SIZE_BIG, 255, 58, 37, 100, 545);
	}
	else //PvP_game_mode == true
	{
		if (who_won_game == 1)
			u.drawText("WYGRAL GRACZ NR 1", FONT_SIZE_BIG, 255, 58, 37, 100, 545);
		else if (who_won_game == 2)
			u.drawText("WYGRAL GRACZ NR 2", FONT_SIZE_BIG, 255, 58, 37, 100, 545);
	}
}

void Game::paintBorders()
{

}

void Game::paintButtons()
{
	buttons.paintButtonWithText(BUTTON_GAME_BACK, FONT_SIZE_SMALL);
	if (buttons.getHighlighted(BUTTON_GAME_BACK) == true)
		buttons.paintButtonHighlight(BUTTON_GAME_BACK, FONT_SIZE_SMALL);
}
