#include "Options.h"
#include "Menu.h"

Options::Options(State** state, Utils& utils, Buttons& buttons):widnowID(WINDOW_OPTIONS),s(state),u(utils),buttons(buttons)
{
	audio_play_guard = true;
	audio_error_play_guard = true;
	warning_sample_play_flag = false;
	mouse_click_guard = true;
	back_to_menu_guard = true;
	warning_ship_remove_flag = false;
	warning_ship_remove_timer = 0;
	warning_ship_add_flag = false;
	warning_ship_add_timer = 0;
	number_of_left_fields = 0;
	m = NULL;
}

void Options::setStates(Menu* menu)
{
	m = menu;
}

void Options::tick()
{
	/*warning_ship_remove_flag = false;
	warning_ship_add_flag = false;
	warning_sample_play_flag = false;*/
	mouseSwitches();
	setBackToMenuGuard();
	calculateNumberOfLeftFields();

}

void Options::render()
{
	playAudio();
	paintButtons();
	paintBorders();
	paintText();

}

int Options::getWindowID()
{
	return widnowID;
}

void Options::setBackToMenuGuard()
{
	if (u.getNumberOfFourMastedShips() == 0 && u.getNumberOfThreeMastedShips() == 0 && u.getNumberOfTwoMastedShips() == 0 && u.getNumberOfOneMastedShips() == 0)
		back_to_menu_guard = false;
	else if (back_to_menu_guard == false)
		back_to_menu_guard = true;
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
		if (buttons.getActivated(BUTTON_OPTIONS_BACK) == true && mouse_click_guard == true)
		{
			if (back_to_menu_guard == true)
			{
				*s = m;
				u.setMouseClickedBeforeStateSwitch(true);
				cout << "Przelaczenie z OPTIONS do MENU" << endl;
			}
			else
				warning_sample_play_flag = true;
			mouse_click_guard = false;
	
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_CLASSIC_GAME_MODE) == true && mouse_click_guard == true)
		{
			u.setClassicGameMode(true);
			buttons.setChoosed(BUTTON_OPTIONS_CLASSIC_GAME_MODE, true);
			u.setAdvancedGameMode(false);
			buttons.setChoosed(BUTTON_OPTIONS_ADVANCED_GAME_MODE, false);
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_ADVANCED_GAME_MODE) == true && mouse_click_guard == true)
		{
			u.setAdvancedGameMode(true);
			buttons.setChoosed(BUTTON_OPTIONS_ADVANCED_GAME_MODE, true);
			u.setClassicGameMode(false);
			buttons.setChoosed(BUTTON_OPTIONS_CLASSIC_GAME_MODE, false);
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_PVC_GAME_MODE) == true && mouse_click_guard == true)
		{
			u.setPvCGameMode(true);
			buttons.setChoosed(BUTTON_OPTIONS_PVC_GAME_MODE, true);
			u.setPvPGameMode(false);
			buttons.setChoosed(BUTTON_OPTIONS_PVP_GAME_MODE, false);
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_PVP_GAME_MODE) == true && mouse_click_guard == true)
		{
			u.setPvPGameMode(true);
			buttons.setChoosed(BUTTON_OPTIONS_PVP_GAME_MODE, true);
			u.setPvCGameMode(false);
			buttons.setChoosed(BUTTON_OPTIONS_PVC_GAME_MODE, false);
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_VOLUME_ON) == true && mouse_click_guard == true)
		{
			u.setVolumeOn(true);
			buttons.setChoosed(BUTTON_OPTIONS_VOLUME_ON, true);
			buttons.setChoosed(BUTTON_OPTIONS_VOLUME_OFF, false);
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_VOLUME_OFF) == true && mouse_click_guard == true)
		{
			buttons.setChoosed(BUTTON_OPTIONS_VOLUME_OFF, true);
			u.setVolumeOn(false);
			buttons.setChoosed(BUTTON_OPTIONS_VOLUME_ON, false);
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_PLUS_FOUR) == true && mouse_click_guard == true)
		{
			if (number_of_left_fields >= 4)
				u.setNumberOfFourMastedShips(u.getNumberOfFourMastedShips() + 1);
			else
			{
				warning_sample_play_flag = true;
				warning_ship_add_flag = true;
			}
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_MINUS_FOUR) == true && mouse_click_guard == true)
		{
			int number_of_ships = u.getNumberOfFourMastedShips();
			if (number_of_ships > 0)
				u.setNumberOfFourMastedShips(number_of_ships -1);
			else
			{
				warning_sample_play_flag = true;
				warning_ship_remove_flag = true;
			}
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_PLUS_THREE) == true && mouse_click_guard == true)
		{
			if (number_of_left_fields >= 3)
				u.setNumberOfThreeMastedShips(u.getNumberOfThreeMastedShips() + 1);
			else
			{
				warning_sample_play_flag = true;
				warning_ship_add_flag = true;
			}
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_MINUS_THREE) == true && mouse_click_guard == true)
		{
			int number_of_ships = u.getNumberOfThreeMastedShips();
			if (number_of_ships > 0)
				u.setNumberOfThreeMastedShips(number_of_ships - 1);
			else
			{
				warning_sample_play_flag = true;
				warning_ship_remove_flag = true;
			}
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_PLUS_TWO) == true && mouse_click_guard == true)
		{
			if (number_of_left_fields >= 2)
				u.setNumberOfTwoMastedShips(u.getNumberOfTwoMastedShips() + 1);
			else
			{
				warning_sample_play_flag = true;
				warning_ship_add_flag = true;
			}
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_MINUS_TWO) == true && mouse_click_guard == true)
		{
			int number_of_ships = u.getNumberOfTwoMastedShips();
			if (number_of_ships > 0)
				u.setNumberOfTwoMastedShips(number_of_ships - 1);
			else
			{
				warning_sample_play_flag = true;
				warning_ship_remove_flag = true;
			}
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_PLUS_ONE) == true && mouse_click_guard == true)
		{
			int number_of_ships = u.getNumberOfOneMastedShips();
			if (number_of_left_fields >= 1 && number_of_ships < 8)
				u.setNumberOfOneMastedShips(number_of_ships + 1);
			else
			{
				warning_sample_play_flag = true;
				warning_ship_add_flag = true;
			}
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_MINUS_ONE) == true && mouse_click_guard == true)
		{
			int number_of_ships = u.getNumberOfOneMastedShips();
			if (number_of_ships > 0)
				u.setNumberOfOneMastedShips(number_of_ships - 1);
			else
			{
				warning_sample_play_flag = true;
				warning_ship_remove_flag = true;
			}
			mouse_click_guard = false;
		}
		else if (buttons.getActivated(BUTTON_OPTIONS_RESET) == true && mouse_click_guard == true)
		{
			u.restoreDefaults();
			buttons.setChoosed(BUTTON_OPTIONS_CLASSIC_GAME_MODE, true);
			buttons.setChoosed(BUTTON_OPTIONS_ADVANCED_GAME_MODE, false);
			buttons.setChoosed(BUTTON_OPTIONS_PVC_GAME_MODE, true);
			buttons.setChoosed(BUTTON_OPTIONS_PVP_GAME_MODE, false);
			buttons.setChoosed(BUTTON_OPTIONS_VOLUME_ON, true);
			buttons.setChoosed(BUTTON_OPTIONS_VOLUME_OFF, false);
			mouse_click_guard = false;
		}
		else if (u.getMouse1Clicked() == false)
		{
			warning_sample_play_flag = false;
			warning_ship_add_flag = false;
			warning_ship_remove_flag = false;
			mouse_click_guard = true;
		}

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
	buttons.paintButtonWithText(BUTTON_OPTIONS_RESET, FONT_SIZE_SMALL);

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
	else if (buttons.getHighlighted(BUTTON_OPTIONS_RESET) == true)
		buttons.paintButtonHighlight(BUTTON_OPTIONS_RESET, FONT_SIZE_SMALL);
}

void Options::paintText()
{
	u.drawText("POZOSTALE POLA", FONT_SIZE_SMALL, 183, 234, 243, 90, 8);
	u.drawText("TRYB STAWIANIA", FONT_SIZE_BIG, 183, 234, 240, 372, 43);
	u.drawText("STATKOW", FONT_SIZE_BIG, 183, 234, 243, 422, 80);
	u.drawText("TRYB GRY", FONT_SIZE_BIG, 183, 234, 243, 424, 220);
	u.drawText("MUZYKA", FONT_SIZE_BIG, 183, 234, 243, 433, 360);
	u.drawText("4 MASZTOWIEC", FONT_SIZE_SMALL, 183, 234, 243, 90, 77);
	u.drawText("3 MASZTOWIEC", FONT_SIZE_SMALL, 183, 234, 243, 90, 178);
	u.drawText("2 MASZTOWIEC", FONT_SIZE_SMALL, 183, 234, 243, 90, 279);
	u.drawText("1 MASZTOWIEC", FONT_SIZE_SMALL, 183, 234, 243, 90, 380);

	/*Wypisanie liczb na ekranie*/
	string number;
	number = to_string(u.getNumberOfFourMastedShips());
	u.drawText(number.c_str(), FONT_SIZE_BIG, 183, 234, 243, 138, 111);
	number = to_string(u.getNumberOfThreeMastedShips());
	u.drawText(number.c_str(), FONT_SIZE_BIG, 183, 234, 243, 138, 213);
	number = to_string(u.getNumberOfTwoMastedShips());
	u.drawText(number.c_str(), FONT_SIZE_BIG, 183, 234, 243, 138, 313);
	number = to_string(u.getNumberOfOneMastedShips());
	u.drawText(number.c_str(), FONT_SIZE_BIG, 183, 234, 243, 138, 413);
	number = to_string(number_of_left_fields);
	u.drawText(number.c_str(), FONT_SIZE_BIG, 183, 234, 243, 140, 23);

	/*Wypisanie warningow*/
	paintWarnings();
}

void Options::paintWarnings()
{
	if (back_to_menu_guard == false)
		u.drawText("UWAGA Musi byc wybrany co najmniej jeden statek do gry", FONT_SIZE_BIG, 168, 0, 0, 2, 497);
	else if (u.getNumberOfOneMastedShips() >= 8)
		u.drawText("UWAGA Osiagnieta maksymalna ilosc jednomasztowcow", FONT_SIZE_BIG, 168, 0, 0, 2, 497);
	
	if (warning_ship_remove_flag == true || warning_ship_remove_timer > 0)
	{
		if (warning_ship_remove_flag == true)
			warning_ship_remove_timer = 200;
		warning_ship_remove_timer -= 1;
		u.drawText("UWAGA Nie mozna usunac statku", FONT_SIZE_SMALL, 168, 0, 0, 218, 488);
	}
	if (warning_ship_add_flag == true || warning_ship_add_timer > 0)
	{
		if (warning_ship_add_flag == true)
			warning_ship_add_timer = 200;
		warning_ship_add_timer -= 1;
		u.drawText("UWAGA Nie mozna dodac statku", FONT_SIZE_SMALL, 168, 0, 0, 2, 488);
	}
		
}

void Options::paintBorders()
{
	u.drawBorders(100, 100, 90, 70, 3, 81, 75, 201);
	u.drawBorders(100, 202, 90, 70, 3, 81, 75, 201);
	u.drawBorders(100, 302, 90, 70, 3, 81, 75, 201);
	u.drawBorders(100, 402, 90, 70, 3, 81, 75, 201);
	u.drawBorders(363, 42, 300, 140, 4, 81, 75, 201);
	u.drawBorders(390, 220, 230, 100, 4, 81, 75, 201);
	u.drawBorders(390, 360, 230, 100, 4, 81, 75, 201);

}

void Options::calculateNumberOfLeftFields()
{
	number_of_left_fields = 20 - (4 * u.getNumberOfFourMastedShips()) - (3 * u.getNumberOfThreeMastedShips()) - (2 * u.getNumberOfTwoMastedShips()) - u.getNumberOfOneMastedShips();
}

void Options::playAudio()
{
	
	if (u.getVolumeOn() == true)
	{
		/*Audio dotyczace highlightow*/
		bool highlighted = false;
		for (int indeks = BUTTON_OPTIONS_BACK; indeks <= BUTTON_OPTIONS_RESET; indeks++)
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
		if (warning_sample_play_flag == true && audio_error_play_guard == true)
		{
			u.playSample(AUDIO_ERROR);
			audio_error_play_guard = false;
		}
		else if (warning_sample_play_flag == false && audio_error_play_guard == false)
			audio_error_play_guard = true;

		if (highlighted == false && audio_play_guard == false)
			audio_play_guard = true;
			
	}

	

}
