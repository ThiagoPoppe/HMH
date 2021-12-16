#include <math.h>
#include "distances.h"

int euclid_2d(point_t u, point_t v) {
    double dx = u.x - v.x;
    double dy = u.y - v.y;

    return round(sqrt(dx*dx + dy*dy));
}

int pseudo_euclid_2d(point_t u, point_t v) {
    double dx = u.x - v.x;
    double dy = u.y - v.y;

    double real_distance = sqrt((dx*dx + dy*dy) / 10.0);
    double rounded_distance = round(real_distance);

    if (rounded_distance < real_distance)
        rounded_distance++;

    return rounded_distance;
}