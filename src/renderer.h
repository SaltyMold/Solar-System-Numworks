#ifndef RENDERER_H
#define RENDERER_H

#include "libs/eadk.h"

// 160/5_000_000_000 (max distance between Neptune and the Sun in km) = 3.2e-8
#define DEFAULT_SCREEN_RATIO 3.2e-8

extern double screen_ratio;

void display_background(void);

void display_planet(double x, double y);
void undisplay_planet(double x, double y);


#endif