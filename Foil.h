//
// Created by benjamin on 2/26/18.
//

#ifndef SCORING_MACHINE_FOIL_H
#define SCORING_MACHINE_FOIL_H


#include "weapon_select.h"

class Foil : public Weapon {
    virtual WeaponState main_loop(Side &current_side, Side &other_side);
    virtual int lockout() {
        return 300;
    }

    virtual int debounce() {
        return 14;
    }

    virtual void setup(Side &side);
};


#endif //SCORING_MACHINE_FOIL_H
