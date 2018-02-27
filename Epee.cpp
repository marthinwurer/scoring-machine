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

void Epee::setup(Side &side) {
    pinMode(side.a_pin, OUTPUT);
    pinMode(side.b_pin, INPUT);
    pinMode(side.c_pin, INPUT);
    pinMode(side.light, OUTPUT);
    pinMode(side.off_target, OUTPUT);
    pinMode(side.ground, OUTPUT);
    digitalWrite(side.a_pin, LOW);
    digitalWrite(side.light, LOW);
    digitalWrite(side.off_target, LOW);
    digitalWrite(side.ground, LOW);
}
