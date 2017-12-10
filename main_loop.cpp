#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include "side.h"

#define BUZZER_PIN 12
#define LED_PIN 13
#define WAIT_TIME 200
#define ONE_SECOND 1000

#define NUM_TICKS (1000 / WAIT_TIME)

#define EPEE_LOCKOUT 40
#define EPEE_LOCKOUT_TICKS (EPEE_LOCKOUT * NUM_TICKS)
#define EPEE_DEBOUNCE 5
#define EPEE_DEBOUNCE_TICKS (EPEE_DEBOUNCE * NUM_TICKS)

boolean hit;
int lockout;
Side left;
Side right;
Side * current_side;
Side * other_side;

void wait(){
    auto start = micros();
    auto time = start;
    do{
        time = micros();
    }
    while(time % WAIT_TIME || time == start);
}

void setup() {
    hit = false;
    lockout = 0;

    left.a_pin = 2;
    left.b_pin = 3;
    left.c_pin = 4;
    left.light = 5;
    left.off_target = 6;
    left.ticks = EPEE_DEBOUNCE_TICKS;

    right.a_pin = 7;
    right.b_pin = 8;
    right.c_pin = 9;
    right.light = 10;
    right.off_target = 11;
    right.ticks = EPEE_DEBOUNCE_TICKS;

    current_side = &left;
    other_side = &right;

    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // if there is a hit, test lockout
    if (hit){
        lockout++;
        if( lockout > EPEE_LOCKOUT_TICKS){
            hit = false;
            lockout = 0;
            digitalWrite(BUZZER_PIN, HIGH);
            delay(ONE_SECOND);
            digitalWrite(BUZZER_PIN, LOW);
            delay(ONE_SECOND);
            // turn off the lights
            digitalWrite(left.light, LOW);
            digitalWrite(right.light, LOW);
        }
    }
    // if lockout ticks > lockout time,
        // wait 1 second
        // reset the system (buzzers off, lights off)
    // test current side against other side

    // turn on current side, then wait, then test, then reset
    digitalWrite(current_side->a_pin, HIGH);
    wait();
    auto ground = digitalRead(other_side->c_pin);
    auto b_pin = digitalRead(current_side->b_pin);
    digitalWrite(current_side->a_pin, LOW);

    if( b_pin && !ground){
        current_side->ticks++;
        // check the debounce
        if (current_side->ticks >= EPEE_DEBOUNCE_TICKS){
            // we have a hit!
            hit = true;
            digitalWrite(BUZZER_PIN, HIGH);
            digitalWrite(current_side->light, HIGH);
        }
    }else{
        current_side->ticks = 0;
    }

    // switch sides
    auto temp = current_side;
    current_side = other_side;
    other_side = temp;
}
