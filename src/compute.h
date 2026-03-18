#ifndef COMPUTE_H
#define COMPUTE_H

// 6.67430e-11 / 1000^3
#define G 6.67430e-20
#define DT 86400.0 * 7

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

extern planet_t planets[PLANETS]; // Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune

double compute_gravity_force(double m1, double m2, double distance);

#endif