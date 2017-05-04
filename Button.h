//
// Created by Devon Mack on 4/4/2017.
//
#ifndef RPN_BUTTON_H
#define RPN_BUTTON_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

using namespace std;

class Button {
    public:
        enum b_event {
            ENTER,PLUSMINUS,DECIMAL,ADD,SUBTRACT,MULTIPLY,DIVIDE,RECIPROCAL,
            SQRT,CLEAR,ALLCLEAR,SIN,COS,TAN,EXPONENT,DELETE,POP,DEL
        };
        Button();
        Button(int x1_in, int y1_in, int width, int height, ALLEGRO_COLOR color_in, string text_in, b_event event_in);
        void draw();
        bool checkMouse(int x, int y);
        string getText();
        b_event getEvent();
        void setText(string text_in);
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
        b_event event;

};


#endif //RPN_BUTTON_H
