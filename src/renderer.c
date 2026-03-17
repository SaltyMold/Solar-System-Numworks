#include "renderer.h"
#include "libs/eadk.h"
#include "compute.h"

void display_background(void) {
    eadk_display_push_rect_uniform(eadk_screen_rect, eadk_color_black);
}

// 160/5_000_000_000 (max distance between Neptune and the Sun in km) = 3.2e-8
void display_planet(double x, double y) {
    int px = (int)(x * 3.2e-8);
    int py = (int)(y * 3.2e-8);

    eadk_display_push_rect_uniform((eadk_rect_t){160 + px - 4, 120 + py - 4, 8, 8}, eadk_color_white);
}

void undisplay_planet(double x, double y) {
    int px = (int)(x * 3.2e-8);
    int py = (int)(y * 3.2e-8);

    eadk_display_push_rect_uniform((eadk_rect_t){160 + px - 4, 120 + py - 4, 8, 8}, eadk_color_black);
}