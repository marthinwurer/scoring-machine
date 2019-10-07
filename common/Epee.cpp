//
// Created by benjamin on 2/25/18.
//

#include "Epee.h"

WeaponState Epee::main_loop(Side &current_side, Side &other_side) {
    // turn on current side, then wait, then test, then reset
    digitalWrite(current_side.b_pin, HIGH);
    wait::wait();
    auto ground = digitalRead(other_side.c_pin);
    auto a_pin = digitalRead(current_side.a_pin);
    digitalWrite(current_side.a_pin, LOW);

#ifdef DEBUG
    if(b_pin){
        Serial.write('h');
        if(ground){
            Serial.write('g');
        }
    }
#endif

    // do ground light logic
    if ( ground ){
        digitalWrite(current_side.ground, HIGH);
    } else {
        digitalWrite(current_side.ground, LOW);
    }

    // check if hit
    if (a_pin && !ground) {
        return WeaponState ::HIT;
    }

    return WeaponState ::IDLE;
}

void Epee::setup(Side &side) {
    pinMode(side.a_pin, INPUT);
    pinMode(side.b_pin, OUTPUT);
    pinMode(side.c_pin, INPUT);
    pinMode(side.light, OUTPUT);
    pinMode(side.off_target, OUTPUT);
    pinMode(side.ground, OUTPUT);
    digitalWrite(side.b_pin, LOW);
    digitalWrite(side.light, LOW);
    digitalWrite(side.off_target, LOW);
    digitalWrite(side.ground, LOW);
}
