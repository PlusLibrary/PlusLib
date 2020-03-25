#include "random.h"
#include <math.h>
#include <limits.h>
#include <time.h>

void seed() {
    srand(time(NULL));
}

int Random::getInteger() {
    seed();
    return rand();
}

int Random::getInteger(int max) {
    seed();
    return rand() % max;
}

double Random::getDouble() {
    seed();
    return rand() / (double) INT_MAX;
}