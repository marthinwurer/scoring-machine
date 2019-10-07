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
Weapon * curr_weapon;
Epee epee;
Foil foil;
Saber saber;

uint8_t a_pin;
uint8_t b_pin;
uint8_t c_pin;
uint8_t light;
uint8_t buzzer;
int ticks;

int current_state = 0;
int button_debounce = 0;


void setup() {
    curr_weapon = &epee;
    hit = true;
    lockout = 0;

    a_pin = A3;
    b_pin = A4;
    c_pin = A5;
    light = A2;
    buzzer = A0;
    ticks = curr_weapon->debounce_ticks();

    pinMode(a_pin, INPUT);
    pinMode(b_pin, OUTPUT);
    pinMode(c_pin, INPUT);
    pinMode(light, OUTPUT);
    digitalWrite(b_pin, HIGH);
    digitalWrite(light, LOW);


    pinMode(buzzer, OUTPUT);

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


    // to make this more modular, make a list of teams, then go until all all players on a team are dead
    // Then go until there is only one team remaining.


    // test current side against other side
    // this is a buzzbox, if we pull B high and A is high for the debounce, then we increment the debounce counter
    digitalWrite(b_pin, HIGH);
    wait::wait();
    auto pin_state = digitalRead(a_pin);
    WeaponState state = pin_state ? WeaponState::HIT : WeaponState::IDLE;


//    WeaponState state = curr_weapon->main_loop(*current_side, *other_side);

    if (state != IDLE) {
        ticks++;
        if (ticks >= curr_weapon->debounce_ticks()) {
            digitalWrite(light, HIGH);
            digitalWrite(buzzer, HIGH);
            delay(ONE_SECOND * 1.5);
            digitalWrite(buzzer, LOW);
            delay(ONE_SECOND / 2);
            digitalWrite(light, LOW);
        }
    }

}
