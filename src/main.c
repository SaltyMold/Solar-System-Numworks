#include "libs/eadk.h"
#include "libs/storage.h"
#include "renderer.h"
#include "compute.h"
#include "tools.h"

#define SIM 1

const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Planet";
const uint32_t eadk_api_level  __attribute__((section(".rodata.eadk_api_level"))) = 0;

int main(void) {
    uint32_t frame_count = 0;
    uint64_t first_frame_ts_ms = eadk_timing_millis();
    uint64_t start_frame_ts_ms;
    uint64_t end_frame_ts_ms;
    uint16_t frame_duration_ms;
    float average_frame_duration_ms = 0.0f;
    uint32_t sleep_us = 0;
    float fps = 0.0f;


    display_background();

    while (1) {
        start_frame_ts_ms = eadk_timing_millis();

        // ===== INPUT =====
        eadk_keyboard_state_t state = eadk_keyboard_scan();
        if (eadk_keyboard_key_down(state, eadk_key_home)) {
            break;
        }
        if (eadk_keyboard_key_down(state, eadk_key_shift) && eadk_keyboard_key_down(state, eadk_key_backspace)) {
            volatile int *ptr = (int *)0xFFFFFFFF;
        	*ptr = 0;
        }
        if (eadk_keyboard_key_down(state, eadk_key_ok)) {
            screen_ratio *= 1.03;
            display_background();
        }
        if (eadk_keyboard_key_down(state, eadk_key_back)) {
            screen_ratio /= 1.03;
            display_background();
        }
        if (eadk_keyboard_key_down(state, eadk_key_plus)) {
            dt += 60.0;
        }
        if (eadk_keyboard_key_down(state, eadk_key_minus)) {
            dt -= 60.0;
        }


        // ===== UNDISPLAY =====
        for (int i = 0; i < PLANETS; i++) {
            //undisplay_planet(planets[i].x, planets[i].y);
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
            planets[i].vx += planets[i].ax * dt;
            planets[i].vy += planets[i].ay * dt;
            
            planets[i].x += planets[i].vx * dt;
            planets[i].y += planets[i].vy * dt;
        }

        // ===== DISPLAY =====

        // display planets
        for (int i = 0; i < PLANETS; i++) {
            if (planets[i].x * screen_ratio + 160 < 0 || planets[i].x * screen_ratio + 160 >= EADK_SCREEN_WIDTH || planets[i].y * screen_ratio + 120 < 0 || planets[i].y * screen_ratio + 120 >= EADK_SCREEN_HEIGHT) {
                continue; 
            }
            display_planet(planets[i].x, planets[i].y);
        }

        // display banner
        char buffer[64];
        ftoa_3dec(fps, buffer, sizeof(buffer)); // fps
        eadk_display_draw_string(buffer, (eadk_point_t){0, 0}, false, eadk_color_white, eadk_color_black);
        ftoa_3dec(((float)dt) / 3600.0, buffer, sizeof(buffer)); // hours per frame
        eadk_display_draw_string(buffer, (eadk_point_t){0, 15}, false, eadk_color_white, eadk_color_black);
        ftoa_3dec((dt * (1000.0f / average_frame_duration_ms)) / 86400.0f, buffer, sizeof(buffer)); // days per second
        eadk_display_draw_string(buffer, (eadk_point_t){0, 30}, false, eadk_color_white, eadk_color_black);
        ftoa_3dec(average_frame_duration_ms, buffer, sizeof(buffer)); 
        eadk_display_draw_string(buffer, (eadk_point_t){0, 45}, false, eadk_color_white, eadk_color_black);
        

        // ===== COUNTS =====

        frame_count++;        
    
            



        // ===== TIMING =====
        #if SIM
        eadk_keyboard_scan();
        #endif
        
        

        // cap fps
        end_frame_ts_ms = eadk_timing_millis();
        frame_duration_ms = (uint16_t)(end_frame_ts_ms - start_frame_ts_ms);
        average_frame_duration_ms = ((float)(end_frame_ts_ms - first_frame_ts_ms)) / (float)frame_count;
        if (average_frame_duration_ms <= 0.0f) {
            fps = 0.0f;
        } else {
            fps = 1000.0f / average_frame_duration_ms;
        }
        float target_ms = 1000.0f / (float)TARGET_FPS;
        float sleep_ms_f = target_ms - (float)frame_duration_ms;
        if (sleep_ms_f < 0.0f) sleep_ms_f = 0.0f;
        sleep_us = (uint32_t)(sleep_ms_f * 1000.0f + 0.5f);
		
        eadk_timing_usleep(sleep_us);
    }

    return 0;
}

