#ifndef NOACTION_H
#define NOACTION_H

#include "actionbehavior.h"

class NoAction : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) override {
        return 0;
    }
};

#endif // NOACTION_H
