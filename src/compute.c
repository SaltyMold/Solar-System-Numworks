#include "compute.h"

planet_t planets[10] = {
    {0, 0, 0, 0, 1.989e30}, // Sun
    {57.9e6, 0, 0, 47.4, 3.285e23}, // Mercury
    {108.2e6, 0, 0, 35.0, 4.867e24}, // Venus
    {149.6e6, 0, 0, 29.8, 5.972e24}, // Earth
    {227.9e6, 0, 0, 24.1, 6.39e23}, // Mars
    {778.5e6, 0, 0, 13.1, 1.898e27}, // Jupiter
    {1433.5e6, 0, 0, 9.7, 5.683e26}, // Saturn
    {2872.5e6, 0, 0, 6.8, 8.681e25}, // Uranus
    {4495.1e6, 0, 0, 5.4, 1.024e26}, // Neptune
};

double compute_gravity_force(double m1, double m2, double distance) {
    return G * (m1 * m2) / (distance * distance);
}