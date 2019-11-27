//ZROBIC FUNKCJE PRZYPORZADKOWUJACA STATKOWI POLA
//ZROBIC FUNKCJE ROZSTAWIANIA STATKOW
/*Statkom zostanie przydzielona ich aktualna ilosc w utilsach i bedzie sie zmniejszac przy rozstawieniu statku*/
/*Obliczenie koordynatow statku odbedzie sie po nacisnieciu klawisza, zostanie obliczony lewy gorny rog statku (wzgledem pozycji myszy i zaleznie od wielkosci statku).*/
/*Jezeli statek bedzie poza obrebem mapy, nie mozna go postawic*/
/*Jezeli lewy gorny rog statku bedzie w pierwszej cwiartce - daj go na prawe pole*/
/*... drugiej cwiartce - daj go w to miejsce gdzie jest*/
/*... trzeciej cwiartce - daj go na dol*/
/*... czwartej cwiartce - daj go na ukos w lewo i na dol*/
//WGRAC CZCIONKE I WYPISAC WARTOSCI DOTYCZACE ILOSCI POZOSTALYCH DO ROZSTAWIENIA STATKOW (OPCJONALNIE POTEM INNE RZECZY)
//ZROBIC KLASE BUTTON I INCLUDOWAC JA W UTILSACH
//ZROBIC KLASE MENU I PRZELACZEANIE POMIEDZY OKNAMI


#pragma once
#include "Utils.h"
#include "Deploying.h"

int main()
{
	al_init();

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	/*ALLEGRO_SAMPLE* audio_placed_ship = NULL;*/

	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();

	Utils u;
	Board b1(u, 80, 70);
	Board b2(u, 500, 70);
	//Player player1(u,b1,b2);
	//Player player2(u,b1,b2);
	//Menu menu(u);
	//Game game(u);
	Deploying d(u, b1, b2);
	State* s = NULL;

	//USTAWIENIE POCZATKOWEJ FAZY (ZMIANA)
	s = &d;

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

	
