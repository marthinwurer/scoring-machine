#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define LED_PIN 13
#define WAIT_TIME 200

#define NUM_TICKS (1000 / WAIT_TIME)

#define EPEE_LOCKOUT 40
#define EPEE_LOCKOUT_TICKS (EPEE_LOCKOUT * NUM_TICKS)
#define EPEE_DEBOUNCE 5
#define EPEE_DEBOUNCE_TICKS (EPEE_DEBOUNCE * NUM_TICKS)

boolean hit;

void wait(){
    auto start = micros();
    auto time;
    do{
        time = micros();
    }
    while(time == start || time % WAIT_TIME);
}

void setup() {
    hit = true;
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // if there is a hit, test lockout
    // if lockout ticks > lockout time,
        // wait 1 second
        // reset the system (buzzers off, lights off)
    // test current side against other side
    // if circuit is connected, then
    // if hit, set locked out and lockout start, and set light and buzzer on
    wait();

    digitalWrite(LED_PIN, HIGH);   // set the LED on
    delay(WAIT_TIME);           // wait for a second
    digitalWrite(LED_PIN, LOW);    // set the LED off
    delay(WAIT_TIME);           // wait for a second
}
