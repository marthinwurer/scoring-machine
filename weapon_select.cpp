//
// Created by benjamin on 2/25/18.
//

#include "weapon_select.h"
void wait::wait(){
    unsigned long start = micros();
    unsigned long end = start + WAIT_TIME - (start % WAIT_TIME);
    unsigned long time;
    do{
        time = micros();
    }
    while(time < end);// || time < start + WAIT_TIME);
}
