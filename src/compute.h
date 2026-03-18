#ifndef COMPUTE_H
#define COMPUTE_H

#include "libs/eadk.h"

#define TARGET_FPS 600

// 6.67430e-11 / 1000^3
#define G 6.67430e-20
#define DEFAULT_DT 3600.0 * 24.0 // second per frame (1 day per frame)

#define PLANETS 9

typedef struct {
    double x; // position in km
    double y;
    double vx; // velocity in km per second
    double vy;
    double ax; // acceleration in km/s²
    double ay;
    double mass; // mass in kilograms
} planet_t;

extern uint32_t dt;

extern planet_t planets[PLANETS]; // Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune

double compute_gravity_force(double m1, double m2, double distance);

#endif