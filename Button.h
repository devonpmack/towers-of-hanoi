//
// Created by Devon Mack on 4/4/2017.
// Modified 5/4/2017
//
#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

using namespace std;

class Button {
    public:
        int b_event;
        Button();
        Button(int x1_in, int y1_in, int width, int height, ALLEGRO_COLOR color_in, string text_in, int event_in);
        void draw();
        bool checkMouse(int x, int y);
        string getText();
        int getEvent();
        void setText(string text_in);
        void setCol(ALLEGRO_COLOR color_in);
        //~Stack();
    protected:
        int x1;
        int w;
        int y1;
        int h;
        int margin;
        ALLEGRO_COLOR color;
        string text;
        bool hovering;
        bool pressing;
        ALLEGRO_FONT *font;
        int event;

};


#endif //BUTTON_H
