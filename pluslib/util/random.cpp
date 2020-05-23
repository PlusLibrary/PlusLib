#include "random.h"
#include <math.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>

void seed() {
    srand(time(NULL));
}

int Random::getInteger() {
    return rand();
}

int Random::getInteger(int max) {
    return rand() % max;
}

double Random::getDouble() {
    return rand() / (double) INT_MAX;
}