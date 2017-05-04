#include <iostream>
#include <stdio.h>
#include "stack.cpp"
#include "stack.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <cstdlib>
#include <time.h>
#include <queue>
using namespace std;


bool initializeAllegro(ALLEGRO_DISPLAY *&display);
bool next_move();
void draw_all(Block* to_draw[]);
int ToH(Block* blocks[], int dskToMv, int cLocation, int tmpLocation, int fLocation);
int wait_and_draw(Block* blocks[]);

int ScreenWidth = 760;
int ScreenHeight = 480;
const int numBlocks = 8;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

Stack pillar[3];

int main(int argc, char **argv) {
	
	srand(time(NULL));
	
	ALLEGRO_DISPLAY *display = NULL;
	
	if (!initializeAllegro(display)) {
		return false;
	}	
	
	Block *blocks[numBlocks];
	int b_number = numBlocks;
	for (int i = 0; i < numBlocks; i++) {
		blocks[i] = new Block(pillar[0].getSize(), b_number--);
		pillar[0].push(blocks[i]);
	}
	
//	draw_all(blocks);
	if (wait_and_draw(blocks) == 1) {
		return 1;
	}
	if (ToH(blocks, numBlocks,0,1,2) == 1) {
		return 1;
	}
	while(wait_and_draw(blocks) == 0) {
		//press esc to exit
	}
	
}

int wait_and_draw(Block* blocks[]) {
	draw_all(blocks);
	al_flip_display();
	while(true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev); //Wait for event
		
		//If [x] is clicked then close game
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return 1;
		}
		//If keyboard pressed
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				return 1;
			}
			else {
				return 0;
			}
		}
    }
    
    return 0;
}

int ToH(Block* blocks[], int dskToMv, int cLocation, int tmpLocation, int fLocation) {
	if( dskToMv != 0 ) 
    {
		
        if (ToH(blocks, dskToMv-1, cLocation, fLocation, tmpLocation ) == 1) {
			return 1;
		}
		Block* toMove = pillar[cLocation].pop();
		pillar[fLocation].push(toMove);
		toMove->setHeight(pillar[fLocation].getSize()-1);
		toMove->setPillar(fLocation);
		
    	if (wait_and_draw(blocks) == 1) {
			return 1;
		}
        if (ToH(blocks, dskToMv-1, tmpLocation, cLocation, fLocation ) == 1) {
        	return 1;
		}
    }
    return 0;
}


void draw_all(Block* to_draw[]) {
	int pillar1x = 125;
	
	int pillar2x = ScreenWidth/2;
	
	int pillar3x = ScreenWidth-25;
	
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
	
	for (int i = 0; i <= numBlocks; i++) {
		to_draw[i]->draw(incWidth, incHeight);
	}
	al_flip_display();
}

bool initializeAllegro(ALLEGRO_DISPLAY *&display) {
    if (!al_init()) {
        cerr << "failed to initialize allegro! "  << endl;
        return false;
    }
    cout << "Successfully Initialized Allegro, part 1" << endl;
    
    if (!al_init_primitives_addon())  {
        cerr << "failed to initialize primitives! "  << endl;
        return false;
    }
    cout << "Initialized Primitives" << endl;
    
	if (!al_install_keyboard()) {
        cerr << "failed to initialize the keyboard! "  << endl;
        return false;
    }
    cout << "Successfully Initialized Allegro, part 2" << endl;
    
    al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(ScreenWidth, ScreenHeight);
    cout << "Successfully Initialized Allegro, part 3" << endl;
    
    event_queue = al_create_event_queue();
    
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //keyboard presses
	al_register_event_source(event_queue, al_get_display_event_source(display)); //click x
    cout << "Successfully Initialized Allegro, part 5" << endl;
    return true;
}
