#ifndef ALLSLIDEDIRECTIONACTION_H
#define ALLSLIDEDIRECTIONACTION_H

#include "actionbehavior.h"
#include "diagonalaction.h"
#include "straightaction.h"

class AllSlideDirectionAction : public ActionBehavior {
public:
    uint64_t action(uint64_t bitboard, uint64_t blocking) {
        return DiagonalAction().action(bitboard, blocking)
               | StraightAction().action(bitboard, blocking);
    }
};

#endif // ALLSLIDEDIRECTIONACTION_H
