#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include "config.h"
#include "side.h"
#include "weapon_select.h"
#include "Epee.h"


//#define DEBUG

boolean hit;
int lockout;
Side left;
Side right;
Side * current_side;
Side * other_side;
Weapon * curr_weapon;
Epee epee;


void setup() {
    curr_weapon = &epee;
    hit = true;
    lockout = 0;

    left.a_pin = A0;
    left.b_pin = A1;
    left.c_pin = A2;
    left.light = 5;
    left.off_target = 6;
    left.ticks = curr_weapon->debounce_ticks();
    left.hit = false;

    left.setup_pins();

    right.a_pin = A3;
    right.b_pin = A4;
    right.c_pin = A5;
    right.light = 10;
    right.off_target = 11;
    right.ticks = EPEE_DEBOUNCE_TICKS;
    right.hit = false;

    right.setup_pins();

    current_side = &left;
    other_side = &right;

    pinMode(BUZZER_PIN, OUTPUT);

#ifdef DEBUG
    Serial.begin(9600);
//    Serial.println(NUM_TICKS);
//    delay(ONE_SECOND * 2);
//    auto start = micros();
//    wait();
//    auto end = micros();
//    Serial.println(end - start);
//    Serial.println(start);
//    Serial.println(end);
//    delay(ONE_SECOND * 2);
//    unsigned long times[256], sum;
//    times[0] = micros();
//    for (int ii = 1; ii < 256; ii++){
//        wait();
//        times[ii] = micros();
//    }
//    sum = 0;
//    for (int ii = 1; ii < 256; ii++){
//        times[ii] -= times[ii-1];
//        sum += times[ii];
//    }
//    sum /= 255;
//    Serial.println(sum);
#endif


}

void loop() {

    // if there is a hit, test lockout
    // if lockout ticks > lockout time,
    // wait 1 second
    // reset the system (buzzers off, lights off)
    if (hit) {
        lockout++;
        if (lockout > curr_weapon->lockout_ticks()) {
            hit = false;
            lockout = 0;
            digitalWrite(BUZZER_PIN, HIGH);
            delay(ONE_SECOND * 1.5);
            digitalWrite(BUZZER_PIN, LOW);
            delay(ONE_SECOND / 2);
            // turn off the lights
            digitalWrite(left.light, LOW);
            digitalWrite(left.off_target, LOW);
            digitalWrite(right.light, LOW);
            digitalWrite(right.off_target, LOW);
            delay(ONE_SECOND / 4);
        }
    }


    // test current side against other side
    WeaponState state = curr_weapon->main_loop(*current_side, *other_side);

    if ( state != IDLE) {
#ifdef DEBUG
        Serial.write('h');
#endif
        current_side->ticks++;
        if (current_side->hit_time == 0) {
            current_side->hit_time = micros();
        }
        // check the debounce
        if (current_side->ticks >= curr_weapon->debounce_ticks()) {
            // we have a hit!
            hit = true;
            digitalWrite(BUZZER_PIN, HIGH);
            digitalWrite(current_side->light, HIGH);
#ifdef DEBUG
            Serial.println(' ');
            Serial.println(micros() - current_side->hit_time);
#endif
        }
    } else {
        current_side->ticks = 0;
        current_side->hit_time = 0;
    }


    // switch sides
    auto temp = current_side;
    current_side = other_side;
    other_side = temp;
}
