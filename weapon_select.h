//
// Created by benjamin on 2/25/18.
//

#ifndef SCORING_MACHINE_WEAPON_SELECT_H
#define SCORING_MACHINE_WEAPON_SELECT_H

#include "side.h"
#include "config.h"

namespace wait{
    void wait();

}

enum WeaponState {
    IDLE, HIT, OFF_TARGET
};

class Weapon
{
public:
    virtual WeaponState main_loop(Side &current_side, Side &other_side) = 0;
    virtual int lockout() = 0;
    virtual int debounce() = 0;
    virtual int debounce_ticks(){
        // divide by two to get both sides
        return debounce() * NUM_TICKS / 2;
    }
    virtual int lockout_ticks(){
        // don't need to divide because it's checked on both
        return lockout() * NUM_TICKS;
    }

};

#endif //SCORING_MACHINE_WEAPON_SELECT_H
