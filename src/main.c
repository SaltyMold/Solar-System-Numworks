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
        for (int i = 0; i < 9; i++) {
            undisplay_planet(planets[i].x, planets[i].y);
        }

        // ===== COMPUTE =====

        
        

        // ===== DISPLAY =====
        for (int i = 0; i < 9; i++) {
            display_planet(planets[i].x, planets[i].y);
        }

        #if SIM
        eadk_keyboard_scan();
        #endif
        eadk_timing_msleep(10);
    }

    return 0;
}

