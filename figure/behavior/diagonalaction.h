#ifndef DIAGONALACTION_H
#define DIAGONALACTION_H

#include "actionbehavior.h"

class DiagonalAction : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) {
        return genRay([](uint64_t x){return x << 7;},
                      FILE_H, bitboard, blocking)
               | genRay([](uint64_t x){return x >> 7;},
                        FILE_A, bitboard, blocking)
               | genRay([](uint64_t x){return x >> 9;},
                        FILE_H, bitboard, blocking)
               | genRay([](uint64_t x){return x << 9;},
                        FILE_A, bitboard, blocking);
    }
};

#endif // DIAGONALACTION_H
