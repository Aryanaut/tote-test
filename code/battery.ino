#include "beep.h"

#define BATTERY_PIN A3
// #define MIN_BATTERY 557  // About 3.59V.
#define MIN_BATTERY 367  // About 3.59V.

extern int robot_mode;

void battery_setup() {
    pinMode(BATTERY_PIN, INPUT);
}

int get_battery() {
    return analogRead(BATTERY_PIN);
}

void battery_loop() {
    static int battery_fail = 0;
    int reading = get_battery();

    if (reading < MIN_BATTERY) {
        battery_fail += 1;
        beep(reading, 200);
    } else {
        battery_fail = 0;
    }
    if (battery_fail > 40) {
        /* If it stays bad for 4s, shut down. */
        robot_mode = 0;
    }
}
