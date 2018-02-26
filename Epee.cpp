//
// Created by benjamin on 2/25/18.
//

#include "Epee.h"

WeaponState Epee::main_loop(Side &current_side, Side &other_side) {
    // turn on current side, then wait, then test, then reset
    digitalWrite(current_side.a_pin, HIGH);
    wait::wait();
    auto ground = digitalRead(other_side.c_pin);
    auto b_pin = digitalRead(current_side.b_pin);
    digitalWrite(current_side.a_pin, LOW);

#ifdef DEBUG
    if(b_pin){
        Serial.write('h');
        if(ground){
            Serial.write('g');
        }
    }
#endif

    // check if hit
    if (b_pin && !ground) {
        return WeaponState ::HIT;
    }

    return WeaponState ::IDLE;
}
