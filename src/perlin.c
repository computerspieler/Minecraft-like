/* Stolen from the wikipedia page on Perlin noise */

#include <math.h>

#include "vector.h"

float interpolate(float a0, float a1, float w) {
    return (a1 - a0) * w + a0;
}

/* Create pseudorandom direction vector
 */
Vec2f randomGradient(int ix, int iy) {
    /* No precomputed gradients mean this works for any number of grid coordinates */
    float random;
    Vec2f v;
    unsigned int a, b;

    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; /* rotation width */
    a = ix;
    b = iy;
    a *= 3284157443; b ^= a << s | a >> (w-s);
    b *= 1911520717; a ^= b << s | b >> (w-s);
    a *= 2048419325;
    random = a * (3.14159265 / ~(~0u >> 1)); /* in [0, 2*Pi] */
    v.x = cos(random);
    v.y = sin(random);
    return v;
}

/* Computes the dot product of the distance and gradient vectors. */
float dotGridGradient(int ix, int iy, float x, float y) {
    float dx, dy;

    /* Get gradient from integer coordinates */
    Vec2f gradient = randomGradient(ix, iy);

    /* Compute the distance vector */
    dx = x - (float)ix;
    dy = y - (float)iy;

    /* Compute the dot-product */
    return (dx*gradient.x + dy*gradient.y);
}

/* Compute Perlin noise at coordinates x, y */
float perlin(float x, float y) {
    float n0, n1, ix0, ix1, value;
    float sx, sy;
    int x0, x1, y0, y1;

    /* Determine grid cell coordinates */
    x0 = (int)floor(x);
    x1 = x0 + 1;
    y0 = (int)floor(y);
    y1 = y0 + 1;

    /*
     * Determine interpolation weights
     * Could also use higher order polynomial/s-curve here
     */
    sx = x - (float)x0;
    sy = y - (float)y0;

    /* Interpolate between grid point gradients */
    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);
    return value;
}

