#ifndef PAWNACTION_H
#define PAWNACTION_H

#include "actionbehavior.h"

class PawnWhiteMove : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) override {
        return (bitboard << 8) | (((bitboard & RANK_2) << 16));
                                  // & ~(blocking | (blocking & ~RANK_2)<< 8));
    }
};

class PawnWhiteAttack : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) override {
        return ((bitboard << 9) & ~FILE_A | (bitboard << 7) & (~FILE_H)) & blocking;
    }
};

class PawnBlackMove : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) override {
        return ((bitboard >> 8) | (bitboard & RANK_7) >> 16);
               // & ~(blocking | (blocking & ~RANK_7) >> 8);;
    }
};

class PawnBlackAttack : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) override {
        return ((bitboard >> 9) & ~FILE_H | (bitboard >> 7) & (~FILE_A)) & blocking;
    }
};

#endif // PAWNACTION_H
