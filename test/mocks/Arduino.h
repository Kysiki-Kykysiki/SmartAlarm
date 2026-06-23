#pragma once
#include <cstdint>
#include <cstdlib>

typedef uint8_t byte;

// random(max): [0, max)  — как в Arduino
inline long random(long howbig) {
    if (howbig == 0) return 0;
    return rand() % howbig;
}

// random(min, max): [min, max) — как в Arduino
inline long random(long howsmall, long howbig) {
    if (howsmall >= howbig) return howsmall;
    long diff = howbig - howsmall;
    return random(diff) + howsmall;
}

inline void randomSeed(unsigned long seed) {
    if (seed != 0) srand((unsigned int)seed);
}
