//
// Created by Devon Mack on 4/4/2017.
//

#include "Block.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#define SCREENHEIGHT 480
#define SCREENWIDTH 760
using namespace std;

Block::Block() {

}

Block::Block(int height_in, int num_in) {
		pillar = 0;
		PILLAR_X[0] = 125;
		PILLAR_X[1] = SCREENWIDTH/2;
		PILLAR_X[2] = SCREENWIDTH-125;
		
		num = num_in;
		height = height_in;
		colour = al_map_rgb(rand() % 256, rand() % 256, rand() % 256);
}

void Block::setPillar(int pillar_in) {
	pillar = pillar_in;
}

void Block::setHeight(int height_in) {
	height = height_in;
}

void Block::draw(int incWidth, int incHeight) {
		int minRadius = 25;
		al_draw_filled_rectangle(PILLAR_X[pillar]- incWidth*num - minRadius,
								 SCREENHEIGHT-height*incHeight,
								 PILLAR_X[pillar]+incWidth*num + minRadius,
								 SCREENHEIGHT-height*incHeight-incHeight,
								 colour);
		al_draw_rectangle(PILLAR_X[pillar]- incWidth*num - minRadius,
								 SCREENHEIGHT-height*incHeight,
								 PILLAR_X[pillar]+incWidth*num + minRadius,
								 SCREENHEIGHT-height*incHeight-incHeight,
								 al_map_rgb(0,0,0),3);
}

