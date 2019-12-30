//1) ZROBIC FUNKCJE ROZSTAWIANIA DEFAULTOWYCH STATKOW
/*Statkom zostanie przydzielona ich aktualna ilosc w utilsach i bedzie sie zmniejszac przy rozstawieniu statku*/
/*Obliczenie koordynatow statku odbedzie sie po nacisnieciu klawisza, zostanie obliczony lewy gorny rog statku (wzgledem pozycji myszy i zaleznie od wielkosci statku).*/
/*Jezeli statek bedzie poza obrebem mapy, nie mozna go postawic*/
/*Jezeli lewy gorny rog statku bedzie w pierwszej cwiartce - daj go na prawe pole*/
/*... drugiej cwiartce - daj go w to miejsce gdzie jest*/
/*... trzeciej cwiartce - daj go na dol*/
/*... czwartej cwiartce - daj go na ukos w lewo i na dol*/

//2)WYPISAC WARTOSCI DOTYCZACE ILOSCI POZOSTALYCH DO ROZSTAWIENIA STATKOW (OPCJONALNIE POTEM INNE RZECZY)

//3) ZROBIC KLASE MENU I METODY PRZELACZEANIA POMIEDZY OKNAMI
/*W MAINIE USTAWIAMY STATYCZNIE NA POCZATKU MENU*/
/*JEZELI W MENU KLIKNIETO PRZYCISK WEJSCIA DO OPCJI BADZ GRY, WCHODZIMY TAM*/
/*JEZELI W OPCJACH BADZ GRZE KLIKNIEMY PRZYCISK POWROTU DO MENU, WTEDY WRACAMY DO MENU*/

//4) ZROBIC KLASE BUTTON I BUTTONS
/*BUTTON ZAWIERA TAKIE DANE JAK: KOORDYNATY LEWEJ GORNEJ KRAWEDZI, SZEROKOSC, WYSOKOSC, NAZWE(ID)*/
/*BUTTONSY ZAWIERAJA WEKTOR BUTTONOW W KOLEJNOSCI PO ID*/
/*BUTTONSY ZAWIERAJA ORYGINALY Z MAINA OBIEKTÓW: STATE, DEPLOYING, MENU, GAME (ABY MOC POROWNAC ADRESY)*/
/*INCLUDOWAC UTILS DO BUTTONOW I UZUPELNIC UTILSY O ID WSZYSTKICH BUTTONOW*/
/*NAPISAC METODY SPRAWDZAJACE WSZYSTKIE BUTONY W BUTTONSACH*/
/*WYKORZYSTUJE ONA POLE ACTUAL_WIDNOW Z KLASY UTILS*/
/*(CZY NAJECHANO NA TO POLE I CZY JEST AKTUALNIE WYSWIETLANE OKNO GDZIE TEN BUTTON SIE ZNAJDUJE) I ZWRACAJACE ZMIENNA BOOLOWSKA*/
/*W MAINIE SPRAWDZAC CZY KLIKNIETO DANY PRZYCISK - JEZELI KURSOR MYSZY JEST NA PRZYCISKU I NACISNIETO LEWY PRZYCISK MYSZY - WTEDY WCISNIETO BUTTON*/
/*ZROBIC PODSWIETLANIE PRZYCISKU PODOBNIE JAK WYZEJ W MAINIE*/

//5) WPROWADZIC LOSOWANIE GRACZA ZACZYNAJACEGO ROZGRYWKE PRZEZ EMITACJE RZUCANIA KOSTKA SZESCIENNA

//6) JAK ZOSTANIE CZAS, TO WPROAWDZIC OPCJE GRY W STATKI - SALVO(POCZYTAC W INTERNECIE O REGULACH TEJ GRY)


/*ZGODNE Z GITHUBEM*/
#pragma once
#include "Utils.h"
#include "Menu.h"
#include "Options.h"
#include "Deploying.h"
#include "Buttons.h"

void install_addons()
{
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
}

int main()
{
	al_init();
	install_addons();
	srand(time(NULL));

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	
	Utils u;
	Buttons buttons(u);
	Board b1(u, 80, 70);
	Board b2(u, 500, 70);
	State* s = NULL;
	Menu m(&s, u, buttons, b1, b2);
	Options o(&s, u, buttons);
	Deploying d(&s, u, buttons, b1, b2);
	//Game game(&s,u, buttons,b1,b2);
	//Player player1(&s, u, buttons, b1, b2);
	//Player player2(&s, u, buttons, b1, b2);

	m.setStates(&o, &d);
	o.setStates(&m);
	d.setStates(&m);	

	//USTAWIENIE POCZATKOWEJ FAZY (MA BYC NA POCZATKU MENU)
	s = &m;
	
	display = al_create_display(u.getDisplayX(), u.getDisplayY());
	queue = al_create_event_queue();
	timer = al_create_timer(u.getTimer());
		
	al_reserve_samples(u.getAudioSamples());//do zmiany ilosc uzytych dzwiekow
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	
	al_start_timer(timer);

	while (u.getRunning())
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			u.setRunning(false);

		/***MYSZ***/
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			u.setMouseX(event.mouse.x);
			u.setMouseY(event.mouse.y);
			cout << "X: " << u.getMouseX() << "\t" << "Y: " << u.getMouseY() << endl;
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button & 1 && u.getMouse1ClickGuard() == true)
		{
			u.setMouse1Clicked(true);
			u.setMouse1ClickGuard(false); //jezeli kliknieto przycisk myszy, nie mozna go kliknac drugi raz, do czasu, az puscimy przycisk - dlatego ustawiam ta flage na false
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button & 2 && u.getMouse2ClickGuard() == true)
		{
			u.setMouse2Clicked(true);
			u.setMouse2ClickGuard(false);
		}
		if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 1) //jezeli lewy przycisk myszy jest puszczony
		{
			u.setMouse1Clicked(false);
			u.setMouse1ClickGuard(true);

		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 2)
		{
			u.setMouse2Clicked(false);
			u.setMouse2ClickGuard(true);
		}

		/***KLAWIATURA***/
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
			u.setKeySpacePressed(true);
		else
			u.setKeySpacePressed(false);
		if (al_key_down(&keyState, ALLEGRO_KEY_UP))
			u.setKeyUpPressed(true);
		else
			u.setKeyUpPressed(false);
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
			u.setKeyDownPressed(true);
		else
			u.setKeyDownPressed(false);
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			u.setKeyRightPressed(true);
		else
			u.setKeyRightPressed(false);
		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
			u.setKeyLeftPressed(true);
		else
			u.setKeyLeftPressed(false);

		/***BUTTONY***/
		/*MENU*/
		if (s == &m)
		{
			/*RYSOWANIE BUTTONOW*/ //napisac w poszczegolnych klasach, w metodach render
			//BUTTONY Z OPCJI DAC DO KLASY OPCJI

			/*NAJECHANIE MYSZKA NA BUTTONA*/
			if (buttons.isMouseOnButton(BUTTON_MENU_PLAY) == true)
				buttons.setHighlighted(BUTTON_MENU_PLAY, true);
			else
				buttons.setHighlighted(BUTTON_MENU_PLAY, false);
			if (buttons.isMouseOnButton(BUTTON_MENU_OPTIONS) == true)
				buttons.setHighlighted(BUTTON_MENU_OPTIONS, true);
			else
				buttons.setHighlighted(BUTTON_MENU_OPTIONS, false);
			if (buttons.isMouseOnButton(BUTTON_MENU_EXIT) == true)
				buttons.setHighlighted(BUTTON_MENU_EXIT, true);
			else
				buttons.setHighlighted(BUTTON_MENU_EXIT, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_BACK) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_BACK, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_BACK, false);


			/*KLIKNIECIE PRZYCISKU NA BUTTONIE*/
			if (u.getMouse1Clicked() == true)
			{
				if (buttons.getHighlighted(BUTTON_MENU_PLAY) == true)
					buttons.setActivated(BUTTON_MENU_PLAY, true);
				else if (buttons.getHighlighted(BUTTON_MENU_OPTIONS) == true)
					buttons.setActivated(BUTTON_MENU_OPTIONS, true);
				else if (buttons.getHighlighted(BUTTON_MENU_EXIT) == true)
					buttons.setActivated(BUTTON_MENU_EXIT, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_BACK) == true)
					buttons.setActivated(BUTTON_OPTIONS_BACK, true);
				else
				{
					buttons.setActivated(BUTTON_MENU_PLAY, false);
					buttons.setActivated(BUTTON_MENU_OPTIONS, false);
					buttons.setActivated(BUTTON_MENU_EXIT, false);
					buttons.setActivated(BUTTON_OPTIONS_BACK, false);
				}
			}
			else
			{
				buttons.setActivated(BUTTON_MENU_PLAY, false);
				buttons.setActivated(BUTTON_MENU_OPTIONS, false);
				buttons.setActivated(BUTTON_MENU_EXIT, false);
				buttons.setActivated(BUTTON_OPTIONS_BACK, false);
			}
		}/*OPTIONS*/
		else if (s == &o)
		{
			/*NAJECHANIE MYSZKA NA BUTTONA*/
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_BACK) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_BACK, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_BACK, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_CLASSIC_GAME_MODE) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_CLASSIC_GAME_MODE, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_CLASSIC_GAME_MODE, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_ADVANCED_GAME_MODE) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_ADVANCED_GAME_MODE, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_ADVANCED_GAME_MODE, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_PVC_GAME_MODE) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_PVC_GAME_MODE, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_PVC_GAME_MODE, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_PVP_GAME_MODE) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_PVP_GAME_MODE, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_PVP_GAME_MODE, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_VOLUME_ON) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_VOLUME_ON, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_VOLUME_ON, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_VOLUME_OFF) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_VOLUME_OFF, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_VOLUME_OFF, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_MINUS_ONE) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_MINUS_ONE, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_MINUS_ONE, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_PLUS_ONE) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_PLUS_ONE, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_PLUS_ONE, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_MINUS_TWO) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_MINUS_TWO, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_MINUS_TWO, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_PLUS_TWO) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_PLUS_TWO, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_PLUS_TWO, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_MINUS_THREE) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_MINUS_THREE, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_MINUS_THREE, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_PLUS_THREE) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_PLUS_THREE, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_PLUS_THREE, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_MINUS_FOUR) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_MINUS_FOUR, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_MINUS_FOUR, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_PLUS_FOUR) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_PLUS_FOUR, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_PLUS_FOUR, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_HINTS_ON) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_HINTS_ON, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_HINTS_ON, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_HINTS_OFF) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_HINTS_OFF, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_HINTS_OFF, false);
			if (buttons.isMouseOnButton(BUTTON_OPTIONS_RESET) == true)
				buttons.setHighlighted(BUTTON_OPTIONS_RESET, true);
			else
				buttons.setHighlighted(BUTTON_OPTIONS_RESET, false);

			/*KLIKNIECIE PRZYCISKU NA BUTTONIE*/
			if (u.getMouse1Clicked() == true)
			{
				if (buttons.getHighlighted(BUTTON_OPTIONS_BACK) == true)
					buttons.setActivated(BUTTON_OPTIONS_BACK, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_CLASSIC_GAME_MODE) == true)
					buttons.setActivated(BUTTON_OPTIONS_CLASSIC_GAME_MODE, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_ADVANCED_GAME_MODE) == true)
					buttons.setActivated(BUTTON_OPTIONS_ADVANCED_GAME_MODE, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_PVC_GAME_MODE) == true)
					buttons.setActivated(BUTTON_OPTIONS_PVC_GAME_MODE, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_PVP_GAME_MODE) == true)
					buttons.setActivated(BUTTON_OPTIONS_PVP_GAME_MODE, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_VOLUME_ON) == true)
					buttons.setActivated(BUTTON_OPTIONS_VOLUME_ON, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_VOLUME_OFF) == true)
					buttons.setActivated(BUTTON_OPTIONS_VOLUME_OFF, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_MINUS_ONE) == true)
					buttons.setActivated(BUTTON_OPTIONS_MINUS_ONE, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_PLUS_ONE) == true)
					buttons.setActivated(BUTTON_OPTIONS_PLUS_ONE, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_MINUS_TWO) == true)
					buttons.setActivated(BUTTON_OPTIONS_MINUS_TWO, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_PLUS_TWO) == true)
					buttons.setActivated(BUTTON_OPTIONS_PLUS_TWO, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_MINUS_THREE) == true)
					buttons.setActivated(BUTTON_OPTIONS_MINUS_THREE, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_PLUS_THREE) == true)
					buttons.setActivated(BUTTON_OPTIONS_PLUS_THREE, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_MINUS_FOUR) == true)
					buttons.setActivated(BUTTON_OPTIONS_MINUS_FOUR, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_PLUS_FOUR) == true)
					buttons.setActivated(BUTTON_OPTIONS_PLUS_FOUR, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_HINTS_ON) == true)
					buttons.setActivated(BUTTON_OPTIONS_HINTS_ON, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_HINTS_OFF) == true)
					buttons.setActivated(BUTTON_OPTIONS_HINTS_OFF, true);
				else if (buttons.getHighlighted(BUTTON_OPTIONS_RESET) == true)
					buttons.setActivated(BUTTON_OPTIONS_RESET, true);
				else
				{
					buttons.setActivated(BUTTON_OPTIONS_BACK, false);
					buttons.setActivated(BUTTON_OPTIONS_CLASSIC_GAME_MODE, false);
					buttons.setActivated(BUTTON_OPTIONS_ADVANCED_GAME_MODE, false);
					buttons.setActivated(BUTTON_OPTIONS_PVC_GAME_MODE, false);
					buttons.setActivated(BUTTON_OPTIONS_PVP_GAME_MODE, false);
					buttons.setActivated(BUTTON_OPTIONS_VOLUME_ON, false);
					buttons.setActivated(BUTTON_OPTIONS_VOLUME_OFF, false);
					buttons.setActivated(BUTTON_OPTIONS_MINUS_ONE, false);
					buttons.setActivated(BUTTON_OPTIONS_PLUS_ONE, false);
					buttons.setActivated(BUTTON_OPTIONS_MINUS_TWO, false);
					buttons.setActivated(BUTTON_OPTIONS_PLUS_TWO, false);
					buttons.setActivated(BUTTON_OPTIONS_MINUS_THREE, false);
					buttons.setActivated(BUTTON_OPTIONS_PLUS_THREE, false);
					buttons.setActivated(BUTTON_OPTIONS_MINUS_FOUR, false);
					buttons.setActivated(BUTTON_OPTIONS_PLUS_FOUR, false);
					buttons.setActivated(BUTTON_OPTIONS_HINTS_ON, false);
					buttons.setActivated(BUTTON_OPTIONS_HINTS_OFF, false);
					buttons.setActivated(BUTTON_OPTIONS_RESET, false);
				}
			}
			else
			{
				buttons.setActivated(BUTTON_OPTIONS_BACK, false);
				buttons.setActivated(BUTTON_OPTIONS_CLASSIC_GAME_MODE, false);
				buttons.setActivated(BUTTON_OPTIONS_ADVANCED_GAME_MODE, false);
				buttons.setActivated(BUTTON_OPTIONS_PVC_GAME_MODE, false);
				buttons.setActivated(BUTTON_OPTIONS_PVP_GAME_MODE, false);
				buttons.setActivated(BUTTON_OPTIONS_VOLUME_ON, false);
				buttons.setActivated(BUTTON_OPTIONS_VOLUME_OFF, false);
				buttons.setActivated(BUTTON_OPTIONS_MINUS_ONE, false);
				buttons.setActivated(BUTTON_OPTIONS_PLUS_ONE, false);
				buttons.setActivated(BUTTON_OPTIONS_MINUS_TWO, false);
				buttons.setActivated(BUTTON_OPTIONS_PLUS_TWO, false);
				buttons.setActivated(BUTTON_OPTIONS_MINUS_THREE, false);
				buttons.setActivated(BUTTON_OPTIONS_PLUS_THREE, false);
				buttons.setActivated(BUTTON_OPTIONS_MINUS_FOUR, false);
				buttons.setActivated(BUTTON_OPTIONS_PLUS_FOUR, false);
				buttons.setActivated(BUTTON_OPTIONS_HINTS_ON, false);
				buttons.setActivated(BUTTON_OPTIONS_HINTS_OFF, false);
				buttons.setActivated(BUTTON_OPTIONS_RESET, false);
			}
		}/*DEPLOYING*/
		else if (s == &d)
		{
			
			/*NAJECHANIE MYSZKA NA BUTTONA*/
			if (buttons.isMouseOnButton(BUTTON_DEPLOYING_DONE) == true)
				buttons.setHighlighted(BUTTON_DEPLOYING_DONE, true);
			else
				buttons.setHighlighted(BUTTON_DEPLOYING_DONE, false);
			if (buttons.isMouseOnButton(BUTTON_DEPLOYING_BACK) == true)
				buttons.setHighlighted(BUTTON_DEPLOYING_BACK, true);
			else
				buttons.setHighlighted(BUTTON_DEPLOYING_BACK, false);
			if (buttons.isMouseOnButton(BUTTON_DEPLOYING_RESET) == true)
				buttons.setHighlighted(BUTTON_DEPLOYING_RESET, true);
			else
				buttons.setHighlighted(BUTTON_DEPLOYING_RESET, false);

			/*KLIKNIECIE PRZYCISKU NA BUTTONIE*/
			if (u.getMouse1Clicked() == true)
			{
				if (buttons.isMouseOnButton(BUTTON_DEPLOYING_DONE) == true)
					buttons.setActivated(BUTTON_DEPLOYING_DONE, true);
				else if (buttons.isMouseOnButton(BUTTON_DEPLOYING_BACK) == true)
					buttons.setActivated(BUTTON_DEPLOYING_BACK, true);
				else if (buttons.isMouseOnButton(BUTTON_DEPLOYING_RESET) == true)
					buttons.setActivated(BUTTON_DEPLOYING_RESET, true);
				else
				{
					buttons.setActivated(BUTTON_DEPLOYING_DONE, false);
					buttons.setActivated(BUTTON_DEPLOYING_BACK, false);
					buttons.setActivated(BUTTON_DEPLOYING_RESET, false);
				}
			}
			else
			{
				buttons.setActivated(BUTTON_DEPLOYING_DONE, false);
				buttons.setActivated(BUTTON_DEPLOYING_BACK, false);
				buttons.setActivated(BUTTON_DEPLOYING_RESET, false);
			}
		}
		

		/***GLOWNE WYWOLANIA METOD***/
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_clear_to_color(u.getColorOfBackground());
			s->tick();
			s->render();

			al_flip_display();

		}
	}

	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	//al_uninstall_audio(); jest w destruktorze klasy Utils zeby nie bylo odinstalowania audio kiedy nie sa usuniete wskazniki na audio

	return 0;
}