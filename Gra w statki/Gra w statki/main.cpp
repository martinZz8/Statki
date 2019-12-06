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

/*ZGODNE Z GITHUBEM*/
#pragma once
#include "Utils.h"
#include "Deploying.h"
#include "Menu.h"

int main()
{
	al_init();
	
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	/*ALLEGRO_SAMPLE* audio_placed_ship = NULL;*/

	Utils u;
	Board b1(u, 80, 70);
	Board b2(u, 500, 70);
	State* s = NULL;
	Menu m(&s, u, b1, b2);
	Deploying d(&s, u, b1, b2);
	//Game game(&s,u,b1,b2);
	//Player player1(&s,u,b1,b2);
	//Player player2(&s,u,b1,b2);

	m.setStates(&d);
	d.setStates(&m);

	//USTAWIENIE POCZATKOWEJ FAZY (MA BYC NA POCZATKU MENU)
	s = &m;
	u.setActualWindow(WINDOW_DEPLOYING);

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
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button & 1)
			u.setMouse1Clicked(true);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button & 2)
			u.setMouse2Clicked(true);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 1)
			u.setMouse1Clicked(false);
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 2)
			u.setMouse2Clicked(false);

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
	al_uninstall_audio();
	al_uninstall_keyboard();

	return 0;
}

	
