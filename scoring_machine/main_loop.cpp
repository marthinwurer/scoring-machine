#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include "config.h"
#include "side.h"
#include "weapon_select.h"
#include "Epee.h"
#include "Foil.h"
#include "Saber.h"

/**
 * Notes:
 * 220 ohm led resistors
 * 10000 ohm pull down
 */


//#define DEBUG

boolean hit;
int lockout;
Side left;
Side right;
Side * current_side;
Side * other_side;
Weapon * curr_weapon;
Epee epee;
Foil foil;
Saber saber;

int current_state = 0;
int button_debounce = 0;


void setup() {
    curr_weapon = &epee;
    hit = true;
    lockout = 0;

    left.a_pin = A0;
    left.b_pin = A1;
    left.c_pin = A2;
    left.light = 8;
    left.off_target = 9;
    left.ground = 10;
    left.ticks = curr_weapon->debounce_ticks();
    left.hit = false;

    left.setup_pins();

    right.a_pin = A3;
    right.b_pin = A4;
    right.c_pin = A5;
    right.light = 7;
    right.off_target = 6;
    right.ground = 5;
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

    // check the weapon select

    if ( digitalRead(BUTTON_PIN)) {

        button_debounce ++;

        if( button_debounce > 5 * NUM_TICKS) {
            current_state = (current_state + 1) % 3;

            if (current_state == 0) {
                curr_weapon = &epee;
            } else if (current_state == 1) {
                curr_weapon = &foil;
            } else {
                curr_weapon = &saber;
            }
            curr_weapon->setup(left);
            curr_weapon->setup(right);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(ONE_SECOND/10);
            digitalWrite(BUZZER_PIN, LOW);
            delay(ONE_SECOND);
        }
    } else {
        button_debounce = 0;
    }


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
            left.hit = false;
            right.hit = false;
        }
    }


    // test current side against other side
    WeaponState state = curr_weapon->main_loop(*current_side, *other_side);

    // TODO : when changing states reset debounce

    if ( state != IDLE && !current_side->hit) {
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
            current_side->hit = true;
            digitalWrite(BUZZER_PIN, HIGH);
            if( state == HIT){
                digitalWrite(current_side->light, HIGH);
            } else{
                digitalWrite(current_side->off_target, HIGH);
            }
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
