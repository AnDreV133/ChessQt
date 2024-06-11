#ifndef STRAIGHTACTION_H
#define STRAIGHTACTION_H

#include "actionbehavior.h"

class StraightAction : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) {
        return genRay([](uint64_t x){return x << 1;},
                      FILE_A, bitboard, blocking)
               | genRay([](uint64_t x){return x >> 1;},
                      FILE_H, bitboard, blocking)
               | genRay([](uint64_t x){return x >> 8;},
                        EMPTY_MASK, bitboard, blocking)
               | genRay([](uint64_t x){return x << 8;},
                        EMPTY_MASK, bitboard, blocking);
    }
};

#endif // STRAIGHTACTION_H
