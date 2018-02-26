//
// Created by benjamin on 2/25/18.
//

#ifndef SCORING_MACHINE_EPEE_H
#define SCORING_MACHINE_EPEE_H


#include "side.h"
#include "weapon_select.h"

class Epee: public Weapon {
public:
    virtual int main_loop(Side &current_side, Side &other_side);


    static int lockout(){
        return 40;
    }

};


#endif //SCORING_MACHINE_EPEE_H
