#pragma once
#include "Utils.h"
#include "Deploying.h"

int main()
{
	al_init();

	Utils u;
	Board b1(u, 80, 70);
	Board b2(u, 500, 70);
	//Player player1(u,b1,b2);
	//Player player2(u,b1,b2);
	//Menu menu(u);
	//Game game(u);
	Deploying d(u,b1,b2); //ZROBIC DZIALNIE NA ORYGINALE
	State* s=NULL;

	//USTAWIENIE POCZATKOWEJ FAZY (ZMIANA)
	s = &d;
	
	
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_SAMPLE* audio_placed_ship = NULL;

	display = al_create_display(u.getDisplayX(), u.getDisplayY());
	queue = al_create_event_queue();
	timer = al_create_timer(u.getTimer());

	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_reserve_samples(u.getAudioSamples());//do zmiany ilosc uzytych dzwiekow

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	
	


	bool running = true;
	float mouse_x = 0, mouse_y = 0;
	audio_placed_ship = al_load_sample("placed_ship.wav");
	assert(audio_placed_ship != NULL); //sprawdzenie, czy dzwiek zostal poprawnie wgrany
	al_start_timer(timer);

	while (running)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;

		/***MYSZ***/
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouse_x = event.mouse.x;
			mouse_y = event.mouse.y;
			cout << "X: " << mouse_x << "\t" << "Y: " << mouse_y << endl;
		}
		// GDY MAMY OKNO DEPLOYING
		if (s->getWindowID() == WINDOW_DEPLOYING)
		{
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				al_play_sample(audio_placed_ship, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				cout << b1.whichField(mouse_x, mouse_y) << endl;
			}
		}

		/***KLAWIATURA***/
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		// GDY MAMY OKNO DEPLOYING
		if (s->getWindowID() == WINDOW_DEPLOYING)
		{
			if (event.type == ALLEGRO_EVENT_KEY_CHAR)
			{
				if (al_key_down(&keyState, ALLEGRO_KEY_UP))
				{
					u.ship_size++;
					if (u.ship_size > 4)
						u.ship_size = 1;
					cout << "Rozmiar: " << u.ship_size << endl;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
				{
					u.ship_size--;
					if (u.ship_size < 1)
						u.ship_size = 4;
					cout << "Rozmiar: " << u.ship_size << endl;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
				{
					u.ship_orientation++;
					if (u.ship_orientation > 2)
						u.ship_orientation = 1;
					cout << "Orientacja: " << u.ship_orientation << endl;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
				{
					u.ship_orientation--;
					if (u.ship_orientation < 1)
						u.ship_orientation = 2;
					cout << "Orientacja: " << u.ship_orientation << endl;
				}
			}
		}

		/***GLOWNE WYWOLANIA METOD***/
		if (event.type == ALLEGRO_EVENT_TIMER)
		{

			/*al_clear_to_color(u.getColorOfBackground());
			A.setOffset(A.getXOffset(), A.getYOffset());
			A.setFields();
			A.paintBoard();
			A.paintShip(mouse_x, mouse_y, ship_size, ship_orientation);


			B.setOffset(B.getXOffset(), B.getYOffset());
			B.setFields();
			B.paintBoard();*/

			al_clear_to_color(u.getColorOfBackground());
			s->tick();
			s->render(mouse_x, mouse_y);

			al_flip_display();

		}
	}

	al_destroy_display(display);
	al_destroy_sample(audio_placed_ship);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_uninstall_mouse();
	al_uninstall_audio();
	al_uninstall_keyboard();

	return 0;
}

	
