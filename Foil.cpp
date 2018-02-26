//
// Created by benjamin on 2/26/18.
//

#include "Foil.h"

WeaponState Foil::main_loop(Side &current_side, Side &other_side) {
    digitalWrite(current_side.b_pin, HIGH);
    wait::wait();
    auto their_ground = digitalRead(other_side.c_pin);
    auto their_lame = digitalRead(other_side.a_pin);
    auto my_lame = digitalRead(current_side.a_pin);
    auto my_ground = digitalRead(current_side.c_pin);
    digitalWrite(current_side.b_pin, LOW);

    auto retval = IDLE;

    if (!my_ground){ // circuit is broken, button is pressed

        if( their_lame){ // connected to their lame, hit
            retval = HIT;
        } else if (their_ground ){ // hit their weapon
            retval = IDLE;
        } else { // not their lame or their ground, must be off target
            retval = OFF_TARGET;
        }
    }

    return retval;
}
