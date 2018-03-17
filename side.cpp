//
// Created by benjamin on 12/9/17.
//

#include "side.h"

void Side::setup_pins() {
    pinMode(a_pin, INPUT);
    pinMode(b_pin, OUTPUT);
    pinMode(c_pin, INPUT);
    pinMode(light, OUTPUT);
    pinMode(off_target, OUTPUT);
    pinMode(ground, OUTPUT);
    digitalWrite(a_pin, LOW);
    digitalWrite(light, LOW);
    digitalWrite(off_target, LOW);
    digitalWrite(ground, LOW);
}