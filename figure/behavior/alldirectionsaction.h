#ifndef ALLDIRECTIONSACTION_H
#define ALLDIRECTIONSACTION_H

#include "actionbehavior.h"

class AllDirectionsBehavior : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) override {
        return ((bitboard << 7) | (bitboard >> 9) | (bitboard >> 1)) & ~FILE_H
               | ((bitboard >> 7) | (bitboard << 9) | (bitboard << 1)) & ~FILE_A
               | (bitboard >> 8) | bitboard << 8;
    }
};

#endif // ALLDIRECTIONSACTION_H
