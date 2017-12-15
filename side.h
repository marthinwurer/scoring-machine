//
// Created by benjamin on 12/9/17.
//

#ifndef SCORING_MACHINE_SIDE_H
#define SCORING_MACHINE_SIDE_H
#include <Arduino.h>


class Side {
private:

public:
    // Pins
    uint8_t a_pin;
    uint8_t b_pin;
    uint8_t c_pin;
    uint8_t light;
    uint8_t off_target;

    int ticks;
    unsigned long hit_time;

//    Side(int a, int b, int c, int light, int off, int ticks);

    void setup_pins();

};


#endif //SCORING_MACHINE_SIDE_H
