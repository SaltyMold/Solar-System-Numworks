#include "renderer.h"
#include "libs/eadk.h"
#include "compute.h"

double screen_ratio = DEFAULT_SCREEN_RATIO;

void display_background(void) {
    eadk_display_push_rect_uniform(eadk_screen_rect, eadk_color_black);
}

void display_planet(double x, double y) {
    int px = (int)(x * screen_ratio);
    int py = (int)(y * screen_ratio);

    eadk_display_push_rect_uniform((eadk_rect_t){160 + px, 120 + py, 1, 1}, eadk_color_white);
}

void undisplay_planet(double x, double y) {
    int px = (int)(x * screen_ratio);
    int py = (int)(y * screen_ratio);

    eadk_display_push_rect_uniform((eadk_rect_t){160 + px , 120 + py , 1, 1}, eadk_color_black);
}