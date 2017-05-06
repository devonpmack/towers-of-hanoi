#include <iostream>
//#include "Stack.cpp"
#include "Stack.h"
//#include "Button.cpp"
#include "Button.h"

#include "Block.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>

using namespace std;

bool initializeAllegro(ALLEGRO_DISPLAY *&display);
bool next_move();
void draw_all(Block* to_draw[]);
int ToH(Block* blocks[], int dskToMv, int cLocation, int tmpLocation, int fLocation);
int wait_and_draw(Block* blocks[]);

int ScreenWidth = 760;
int ScreenHeight = 480;
int numBlocks=7;

bool autorun = false;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

Stack pillar[3];
const int nButtons = 3;
Button *buttons[nButtons];

enum b_event {
    ADD_BLOCK,REMOVE_BLOCK,RESTART,AUTO_COMPLETE
};

int main(int argc, char **argv) {
	cout << "How many blocks would you like to solve?" << endl;
	cin >> numBlocks;
	
	if (numBlocks < 2) {
		cout << "Use at least 1 disk.";
		return 1;
	}
	srand(time(NULL));
	
	ALLEGRO_DISPLAY *display = NULL;
	
	if (!initializeAllegro(display)) {
		return false;
	}	
	
	Block *blocks[numBlocks];
	while (true) {
		// Reset everything (code restart)
		for (int i = 0; i < 3; i++) {
			while (pillar[i].getSize()) {
				pillar[i].pop();
			}
		}

        autorun = false;

        /* --- Main loop --- */
		int b_number = numBlocks;
		for (int i = 0; i < numBlocks; i++) {
			blocks[i] = new Block(pillar[0].getSize(), b_number--);
			pillar[0].push(blocks[i]);
		}

		// SECOND LINE C AC POP POW
		buttons[0] = new Button(20, 30, 150, 60, al_map_rgb(255, 255, 255), "Restart",
								ADD_BLOCK);
		buttons[1] = new Button(200, 30, 150, 60, al_map_rgb(255,255,255), "Auto",
                                AUTO_COMPLETE);

        /*buttons[2] = new Button(margin, margin+locationy, size-margin, size-margin, RED, "C",
                                RESTART);*/

		switch (wait_and_draw(blocks)) {
			case 1:
				return 1; // Exit
			case 2:
				continue; // Restart
			default:
				break;
		}
//		if (wait_and_draw(blocks) == 1) {
//
//		}
		switch (ToH(blocks, numBlocks, 0, 1, 2)) {
			case 1:
				return 1; // Exit
			case 2:
				cout << "case 2";
				continue; // Restart
			default:
				break;
		}

		bool stop = false;
		while (!stop) {
			switch (wait_and_draw(blocks)) {
				case 1:
					return 1; // Exit
				case 2:
					stop = true; // Restart
				default:
					break;
			}
		}

		// restarting
	}
}

int wait_and_draw(Block* blocks[]) {

    /* This function waits for input and will return based on the input */

    draw_all(blocks);
	al_flip_display();
	while(true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev); //Wait for event

        //If [x] is clicked then close game
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return 1;
        }
            //If keyboard pressed
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                return 1;
            } else {
                return 0;
            }
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (ev.mouse.button == 1) {
                // Find out if the user clicked the button
                if (buttons[0]->checkMouse(ev.mouse.x, ev.mouse.y)) {
                    return 2;
                }
                if (buttons[1]->checkMouse(ev.mouse.x, ev.mouse.y)) {
                    autorun = !autorun;
                    cout << autorun;
                    if (autorun) {
                        buttons[1]->setCol(al_map_rgb(255, 150, 150));
                    } else {
                        buttons[1]->setCol(al_map_rgb(255, 255, 255));
                    }
                    draw_all(blocks);
                }
            }
        } else if (ev.type == ALLEGRO_EVENT_TIMER && autorun) {
            return 0;
        }
    }
    return 0;
}

int ToH(Block* blocks[], int dskToMv, int cLocation, int tmpLocation, int fLocation) {
    /* This is a recursive algorithm to solve the Towers of Hanoi */

	if( dskToMv != 0 )
    {
		switch (ToH(blocks, dskToMv-1, cLocation, fLocation, tmpLocation)) {
			case 1:
				return 1; // Exit
			case 2:
				return 2; // Restart
			default:
				break;
		}
		Block* toMove = pillar[cLocation].pop();
		pillar[fLocation].push(toMove);
		toMove->setHeight(pillar[fLocation].getSize()-1);
		toMove->setPillar(fLocation);

		switch (wait_and_draw(blocks)) {
			case 1:
				return 1; // Exit
			case 2:
				return 2; // Restart
			default:
				break;
		}

		switch (ToH(blocks, dskToMv-1, tmpLocation, cLocation, fLocation)) {
			case 1:
				return 1; // Exit
			case 2:
				return 2; // Restart
			default:
				break;
		}
    }
    return 0;
}


void draw_all(Block* to_draw[]) {
    /* This function will draw all the blocks, buttons, and pillars */

    // Draw all the pillars
	al_clear_to_color(al_map_rgb(176,196,222));
	al_draw_filled_rectangle(100,ScreenHeight,150,ScreenHeight-250,al_map_rgb(210,105,30));
	al_draw_filled_rectangle(ScreenWidth/2-25,ScreenHeight,ScreenWidth/2+25,ScreenHeight-250,al_map_rgb(210,105,30));
	al_draw_filled_rectangle(ScreenWidth-150,ScreenHeight,ScreenWidth-100,ScreenHeight-250,al_map_rgb(210,105,30));
	al_draw_rectangle(100,ScreenHeight,150,ScreenHeight-250,al_map_rgb(0,0,0),3);
	al_draw_rectangle(ScreenWidth/2-25,ScreenHeight,ScreenWidth/2+25,ScreenHeight-250,al_map_rgb(0,0,0),3);
	al_draw_rectangle(ScreenWidth-150,ScreenHeight,ScreenWidth-100,ScreenHeight-250,al_map_rgb(0,0,0),3);
	
	int incHeight;
	int incWidth = (ScreenWidth/6-40)/numBlocks;
	
	if (numBlocks < 6) {
		incHeight = 32;
	} else {
		incHeight = 250/numBlocks;
	}
	
	for (int i = 0; i < numBlocks; i++) {
		to_draw[i]->draw(incWidth, incHeight);
	}
	//for (int i = 0; i < nButtons; i++) {
	//	buttons[i]->draw();
	//}
	buttons[0]->draw();

    buttons[1]->draw();
	al_flip_display();
}

bool initializeAllegro(ALLEGRO_DISPLAY *&display) {
    /* This function initializes Allegro 5 */

    if (!al_init()) {
        cerr << "failed to initialize allegro! "  << endl;
        return false;
    }
    cout << "Successfully Initialized Allegro" << endl;

    if (!al_init_primitives_addon())  {
        cerr << "failed to initialize primitives! "  << endl;
        return false;
    }
    cout << "Initialized Primitives" << endl;

    if (!al_init_font_addon())  {
        cerr << "failed to initialize primitives! "  << endl;
        return false;
    }
    cout << "Initialized font addon" << endl;

    if (!al_init_ttf_addon())  {
        cerr << "failed to initialize primitives! "  << endl;
        return false;
    }
    cout << "Initialized ttf addon" << endl;

    if (!al_install_keyboard()) {
        cerr << "failed to initialize the keyboard! "  << endl;
        return false;
    }
    cout << "Successfully Initialized keyboard" << endl;

    if(!al_install_mouse()) {
        cerr << "failed to initialize the mouse!" << endl;
        return false;
    }
    cout << "Successfully Initialized mouse" << endl;

    al_set_new_display_flags(ALLEGRO_WINDOWED); //| ALLEGRO_RESIZABLE);
    display = al_create_display(ScreenWidth, ScreenHeight);
    cout << "Successfully Initialized display" << endl;

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 300);
    if(!timer) {
        cerr << "failed to create timer!" << endl;
        return false;
    }

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_mouse_event_source()); //mouse clicks
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //keyboard presses
    al_register_event_source(event_queue, al_get_display_event_source(display)); //click x
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); //click x

    al_start_timer(timer);

    cout << "Successfully Initialized All of Allegro" << endl;
    return true;
}
