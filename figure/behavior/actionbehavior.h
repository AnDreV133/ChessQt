#ifndef ACTIONBEHAVIOR_H
#define ACTIONBEHAVIOR_H

#include <stdint.h>
#include <QtLogging>
#include <functional>

class ActionBehavior {
public:
    virtual uint64_t action(uint64_t bitboard, uint64_t blocking) {
        return 0ULL;
    }

protected:
    static const uint64_t RANK_8 = 0xFF00000000000000;
    static const uint64_t RANK_7 = 0x00FF000000000000;
    static const uint64_t RANK_6 = 0x0000FF0000000000;
    static const uint64_t RANK_5 = 0x000000FF00000000;
    static const uint64_t RANK_4 = 0x00000000FF000000;
    static const uint64_t RANK_3 = 0x0000000000FF0000;
    static const uint64_t RANK_2 = 0x000000000000FF00;
    static const uint64_t RANK_1 = 0x00000000000000FF;
    static const uint64_t FILE_A = 0x0101010101010101;
    static const uint64_t FILE_B = 0x0202020202020202;
    static const uint64_t FILE_H = 0x8080808080808080;
    static const uint64_t FILE_G = 0x7070707070707070;

    static const uint64_t EMPTY_MASK = 0ULL;

    static uint64_t genRay(
        std::function<uint64_t(uint64_t)> bitShift,
        uint64_t file,
        uint64_t bitboard,
        uint64_t blocking) {
        uint64_t flood = bitboard;
        uint64_t empty = ~blocking & ~file;
        flood |= bitboard = (bitShift(bitboard)) & empty;
        flood |= bitboard = (bitShift(bitboard)) & empty;
        flood |= bitboard = (bitShift(bitboard)) & empty;
        flood |= bitboard = (bitShift(bitboard)) & empty;
        flood |= bitboard = (bitShift(bitboard)) & empty;
        flood |=            (bitShift(bitboard)) & empty;
        return              (bitShift(flood)) & ~file;
    }
};

#endif // ACTIONBEHAVIOR_H
