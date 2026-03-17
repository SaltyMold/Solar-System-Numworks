#ifndef COMPUTE_H
#define COMPUTE_H

#define G 6.67430e-11

typedef struct {
    double x; // position in km
    double y;
    double vx; // velocity in km per second
    double vy;
    double mass; // mass in kilograms
} planet_t;

extern planet_t planets[10]; // Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune

#endif