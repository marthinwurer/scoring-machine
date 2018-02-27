//
// Created by benjamin on 2/25/18.
//

#ifndef SCORING_MACHINE_CONFIG_H
#define SCORING_MACHINE_CONFIG_H

#define BUZZER_PIN 12
#define BUTTON_PIN 11
#define WAIT_TIME 200
#define ONE_SECOND 1000

#define NUM_TICKS (1000 / WAIT_TIME)

#define EPEE_LOCKOUT 40
// diveide by two because there are two sides
#define EPEE_LOCKOUT_TICKS (EPEE_LOCKOUT * NUM_TICKS / 2)
#define EPEE_DEBOUNCE 5
#define EPEE_DEBOUNCE_TICKS (EPEE_DEBOUNCE * NUM_TICKS / 2)

#endif //SCORING_MACHINE_CONFIG_H
