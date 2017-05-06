//
// Created by Devon Mack on 4/4/2017.
//

#ifndef BLOCK_H
#define BLOCK_H

#include <allegro5/allegro.h>
#include <iostream>


class Block {
    private:
		int num;
		int pillar;
		int height;
		int PILLAR_X[3];
		ALLEGRO_COLOR colour;
    public:
    	void setPillar(int pillar_in);
    	void setHeight(int height_in);
    	Block();
		Block(int height_in, int num_in);
		void draw(int incWidth, int incHeight);
};


#endif //BLOCK_H
