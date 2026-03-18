#include "libs/eadk.h"
#include "libs/storage.h"
#include "renderer.h"
#include "compute.h"
#include "tools.h"

#define SIM 1

const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Planet";
const uint32_t eadk_api_level  __attribute__((section(".rodata.eadk_api_level"))) = 0;

int main(void) {
    display_background();

    while (1) {
        // ===== INPUT =====
        eadk_keyboard_state_t state = eadk_keyboard_scan();
        if (eadk_keyboard_key_down(state, eadk_key_home)) {
            break;
        }
        if (eadk_keyboard_key_down(state, eadk_key_shift) && eadk_keyboard_key_down(state, eadk_key_backspace)) {
            volatile int *ptr = (int *)0xFFFFFFFF;
        	*ptr = 0;
        }

        // ===== UNDISPLAY =====
        for (int i = 0; i < PLANETS; i++) {
            undisplay_planet(planets[i].x, planets[i].y);
        }

        // ===== COMPUTE =====
        for (int i = 0; i < PLANETS; i++) {
            planets[i].ax = 0;
            planets[i].ay = 0;
        }

        for (int i = 0; i < PLANETS; i++) {
            for (int j = 0; j < PLANETS; j++) {
                if (i == j) continue;

                double dx = planets[j].x - planets[i].x;
                double dy = planets[j].y - planets[i].y;
                double distance = sqrt((double)(dx * dx + dy * dy));
                double force = compute_gravity_force(planets[i].mass, planets[j].mass, distance);

                planets[i].ax += force * dx / (distance * planets[i].mass);
                planets[i].ay += force * dy / (distance * planets[i].mass);
            }
        }

        for (int64_t i = 0; i < PLANETS; i++) {
            planets[i].vx += planets[i].ax * DT;
            planets[i].vy += planets[i].ay * DT;
            
            planets[i].x += planets[i].vx * DT;
            planets[i].y += planets[i].vy * DT;
        }

        // ===== DISPLAY =====
        for (int i = 0; i < PLANETS; i++) {
            if (planets[i].x * SCREEN_RATIO + 160 < 0 || planets[i].x * SCREEN_RATIO + 160 >= EADK_SCREEN_WIDTH || planets[i].y * SCREEN_RATIO + 120 < 0 || planets[i].y * SCREEN_RATIO + 120 >= EADK_SCREEN_HEIGHT) {
                continue; 
            }
            display_planet(planets[i].x, planets[i].y);
        }

        #if SIM
        eadk_keyboard_scan();
        #endif
        eadk_timing_msleep(1);
    }

    return 0;
}

