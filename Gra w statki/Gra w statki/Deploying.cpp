#include "Deploying.h"
#include "Menu.h"

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
	setNUmbersOfNotDeployedShips();
	done_deploying_b1 = false;
	done_deploying_b2 = false;
	done_copy_b1_to_b2 = false;
	done_fix_ship_size_after_p1 = false;

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
	done_deploying_b1 = false;
	done_deploying_b2 = false;
	done_copy_b1_to_b2 = false;
	done_fix_ship_size_after_p1 = false;

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

	if (u.getPvCGameMode() == true)
	{
		if (done_deploying_b1 == true && b2.getDeployShipsFlag() == true) //&& done_copy_b1_to_b2 == false - jako drugi warunek
		{
			//done_copy_b1_to_b2 = true;
			//copyShips(b1, b2);
			//cout << "Skopiowalem ships z b1 do b2" << endl;
			classicComputerDeploy();
			cout << "Komputer zakonczyl rozstawianie bourdu b2" << endl;
		}
		if (b2.getDeployShipsFlag() == false)
		{
			done_deploying_b2 = true;
			//cout << "Mozna kliknac button play" << endl;
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
		b2.paintBoard(true, true); //PIERWSZY I DRUGI ARGUMENT METODY OBOK MAJA BYC NA FALSE; JEST TRUE TYLKO DLA TESTU!

		if(u.getClassicGameMode() == true && b1.getDeployShipsFlag() == true)
			b1.paintClassicShip(u.getMouseX(), u.getMouseY());
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
			if (b1.getDeployShipsFlag() == true)
				b1.paintClassicShip(u.getMouseX(), u.getMouseY());
			else if (b2.getDeployShipsFlag() == true && done_deploying_b1 == true)
				b2.paintClassicShip(u.getMouseX(), u.getMouseY());
		}
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

void Deploying::classicKeyboardSwitches()
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
		else if (buttons.getActivated(BUTTON_DEPLOYING_DONE) == true && mouse_click_guard == true)
		{
			mouse_click_guard = false;
			if (b1.getDeployShipsFlag() == false)
				done_deploying_b1 = true;
			if (b2.getDeployShipsFlag() == false)
				done_deploying_b2 = true;

		}
		else if (u.getMouse1Clicked() == true && mouse_click_guard == true)
		{
			mouse_click_guard = false;
			//TODO DODAC NOWE OPCJE DZIALANIA LEWEJ MYSZY
			if (u.getClassicGameMode() == true)
			{
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
						if (done_fix_ship_size_after_p1 == false)
						{
							done_fix_ship_size_after_p1 = true;
							fixShipSize();
						}
						cout << "Gracz 2 klika myszka w classicu" << endl;
						classicPlayer2Deploy();
					}
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

void Deploying::classicComputerDeploy()
{
	for (int indeks = b2.numbers_of_not_deployed_ships.size() - 1; indeks >= 0; indeks--)
	{
		while (b2.numbers_of_not_deployed_ships[indeks] > 0)
		{
			int warunek;
			do
			{
				int orientation = (rand() % 2) + 1; //losowanie od 1 do 2
				float l_x = b2.getXOffset();
				float r_x = l_x + b2.getWidth();
				float u_y = b2.getYOffset();
				float d_y = u_y + b2.getHeight();
				int mod_x = r_x - l_x + 1;
				int mod_y = d_y - u_y + 1;
				
				float x = (rand() % mod_x) + l_x;
				float y = (rand() % mod_y) + u_y;
				cout << "wylosowane x wynosi: " << x << ", natomiast wylosowane y: " << y << endl;
				warunek = b2.deployClassicShip(x, y, orientation, indeks + 1);
			} while (warunek == -1);
		}
	}
}

void Deploying::paintButtons()
{
	buttons.paintButtonWithText(BUTTON_DEPLOYING_DONE, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_DEPLOYING_BACK, FONT_SIZE_SMALL);
	buttons.paintButtonWithText(BUTTON_DEPLOYING_RESET, FONT_SIZE_SMALL);

	if (buttons.getHighlighted(BUTTON_DEPLOYING_DONE) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_DONE, FONT_SIZE_SMALL);
	else if (buttons.getHighlighted(BUTTON_DEPLOYING_BACK) == true)
		buttons.paintButtonHighlight(BUTTON_DEPLOYING_BACK, FONT_SIZE_SMALL);
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
}

void Deploying::paintBorders()
{
	if(u.getPvCGameMode() == true && done_deploying_b1 == false)
		u.drawBorders(167, 480, 530, 103, 3, 159, 58, 37);
	else if (u.getPvPGameMode() == true && (done_deploying_b1 == false || done_deploying_b2 == false))
		u.drawBorders(167, 480, 530, 103, 3, 159, 58, 37);
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

void Deploying::copyShips(Board& from, Board& to)
{
	vector <Ship> ships(from.getShips());
	to.setShips(ships);
}
