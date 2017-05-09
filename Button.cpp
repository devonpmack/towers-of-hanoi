//
// Created by Devon Mack on 4/4/2017.
//

#include <iostream>
#include "Button.h"


using namespace std;

Button::Button() {
    //throw invalid_argument("You can't initialize a button with no arguments!");
}

Button::Button(int x1_in, int y1_in, int width, int height, ALLEGRO_COLOR color_in, string text_in, int event_in) {
    x1 = x1_in;
    y1 = y1_in;
    w = width;
    h = height;
    text = text_in;
    color = color_in;
    pressing = false;
    hovering = false;
    margin = 2;
    event = event_in;
    font = al_load_font("font.ttf",30,0);
    //font = al_load_font("C:\\Users\\Devon Mack\\CLionProjects\\towers-of-hanoi\\font.ttf", 30, 0);
    if (!font) {
        throw invalid_argument("Error loading font!");
    }
}

void Button::draw() {
    //cout << "Drawing: " << x1 << " " << y1 << " " << x1+w << " " << y1+w << endl;
    al_draw_filled_rectangle(x1+margin, y1+margin, x1+w-margin, y1+h-margin, color);
    al_draw_text(font, al_map_rgb(0, 0, 0), x1 + w/2, y1 + h/2-20, ALLEGRO_ALIGN_CENTRE, text.c_str());
}

string Button::getText() {
    return text;
}

bool Button::checkMouse(int x, int y) {
    if (x >= x1 && x <= x1+w && y >= y1 && y <= y1+h) {
        return true;
    } else {
        return false;
    }
}

int Button::getEvent() {
    return event;
}

void Button::setCol(ALLEGRO_COLOR color_in) {
    color = color_in;
}

void Button::setText(string text_in) {
    text = text_in;
}
