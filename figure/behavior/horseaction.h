#ifndef HORSEACTION_H
#define HORSEACTION_H

#include "actionbehavior.h"

class HorseAction : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) override {
        const uint64_t notAFile = ~FILE_A;
        const uint64_t notABFile = notAFile & ~FILE_B;
        const uint64_t notHFile = ~FILE_H;
        const uint64_t notGHFile = notHFile & ~FILE_G;
        return (bitboard << 17) & notAFile | (bitboard << 10) & notABFile | (bitboard >> 6) & notABFile | (bitboard >> 15) & notAFile |
               (bitboard << 15) & notHFile | (bitboard << 6) & notGHFile | (bitboard >> 10) & notGHFile | (bitboard >> 17) & notHFile;
    }
};

#endif // HORSEACTION_H
