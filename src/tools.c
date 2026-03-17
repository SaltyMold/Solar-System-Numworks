#include "tools.h"
#include "libs/eadk.h"

// convert a double to a string with 3 decimal places
void ftoa_3dec(double x, char *buffer, int bufsize) {
    int whole = (int)x;
    int frac = (int)round((x - whole) * 1000);
    if (frac < 0) frac = -frac;
    snprintf(buffer, bufsize, "%d.%03d", whole, frac);
}
