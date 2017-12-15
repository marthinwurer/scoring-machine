#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include "side.h"

#define BUZZER_PIN 12
#define WAIT_TIME 200
#define ONE_SECOND 1000

#define NUM_TICKS (1000 / WAIT_TIME)

#define EPEE_LOCKOUT 40
#define EPEE_LOCKOUT_TICKS (EPEE_LOCKOUT * NUM_TICKS / 2)
#define EPEE_DEBOUNCE 5
#define EPEE_DEBOUNCE_TICKS (EPEE_DEBOUNCE * NUM_TICKS / 2)

boolean hit;
int lockout;
Side left;
Side right;
Side * current_side;
Side * other_side;

void wait(){
    unsigned long start = micros();
    unsigned long end = start + WAIT_TIME - (start % WAIT_TIME);
    unsigned long time;
    do{
        time = micros();
    }
    while(time < end);// || time < start + WAIT_TIME);
}

void setup() {
    hit = true;
    lockout = 0;

    left.a_pin = A0;
    left.b_pin = A1;
    left.c_pin = A2;
    left.light = 5;
    left.off_target = 6;
    left.ticks = EPEE_DEBOUNCE_TICKS;

    left.setup_pins();

    right.a_pin = A3;
    right.b_pin = A4;
    right.c_pin = A5;
    right.light = 10;
    right.off_target = 11;
    right.ticks = EPEE_DEBOUNCE_TICKS;

    right.setup_pins();

    current_side = &left;
    other_side = &right;

    pinMode(BUZZER_PIN, OUTPUT);

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
            delay(ONE_SECOND/2);
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

    if(b_pin){
        Serial.write('h');
        if(ground){
            Serial.write('g');
        }
    }

    if( b_pin && !ground){
        Serial.write('h');
        current_side->ticks++;
        if (current_side->hit_time == 0){
            current_side->hit_time = micros();
        }
        // check the debounce
        if (current_side->ticks >= EPEE_DEBOUNCE_TICKS){
            // we have a hit!
            hit = true;
            digitalWrite(BUZZER_PIN, HIGH);
            digitalWrite(current_side->light, HIGH);
            Serial.println(' ');
            Serial.println(micros() - current_side->hit_time);
        }
    }else{
        current_side->ticks = 0;
        current_side->hit_time = 0;
    }


    // switch sides
    auto temp = current_side;
    current_side = other_side;
    other_side = temp;
}
