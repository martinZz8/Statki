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

	choose_who_starts();
}

void Game::setStates(Menu* menu, Deploying* deploying)
{
	m = menu;
	d = deploying;
}

void Game::tick()
{
	mouseSwitches();
}

void Game::render()
{
	playAudio();
	paintText();
	paintBorders();
	paintButtons();
	b1.paintBoard(false, false);
	b2.paintBoard(false, false);

}

int Game::getWindowID()
{
	return windowID;
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
			u.setMouseClickedBeforeStateSwitch(true);
			cout << "Przelaczenie z GAME do MENU" << endl;
		}
	}
}

void Game::playAudio()
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

void Game::paintText()
{
	/*Pod boardem nr 1*/
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

	/*Pod boardem nr 2*/
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
