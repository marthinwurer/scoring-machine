//
// Created by benjamin on 2/26/18.
//

#ifndef SCORING_MACHINE_SABER_H
#define SCORING_MACHINE_SABER_H

#include "side.h"
#include "weapon_select.h"

class Saber: public Weapon {
public:
    virtual WeaponState main_loop(Side &current_side, Side &other_side);

    virtual int debounce() {
        return 1;
    }

    virtual int lockout(){
        return 40;
    }

    virtual void setup(Side &side);
};


#endif //SCORING_MACHINE_SABER_H
