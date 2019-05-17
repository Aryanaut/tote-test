#include "misc.h"
#include "servos.h"
#include <Servo.h>

// Range of the servos.
#define SERVO_FREQ_MIN 600
#define SERVO_FREQ_MAX 2400

static const unsigned char SERVO_PINS[SERVOS] = {
// ankle, knee, hip

/* For Pro Micro
    14, 16, 10,     // front left
    A0, A1, A2,     // hind left
*/

    12, 11, 10,     // front left
    14, 15, 16,     // hind left
    6, 5, 4,        // hind right
    7, 8, 9         // front right
};
static const signed char SERVO_REVERSE[SERVOS] = {
// ankle, knee, hip
    -1, 1, 1,    // front left
    1, -1, -1,   // hind left
    -1, 1, 1,    // hind right
    1, -1, -1    // front right
};
static const signed char SERVO_TRIM[SERVOS] = {
// ankle, knee, hip
    0, 5, -10,    // front left
    10, -5, -10,    // hind left
    0, 0, 10,    // hind right
    0, 0, 10     // front right
};
static Servo servos[SERVOS];

static const double HOME_POSITION[SERVOS] = {
// ankle, knee, hip
    0, 0, 0,    // front left
    0, 0, 0,    // hind left
    0, 0, 0,    // hind right
    0, 0, 0     // front right
};

static const double FOLD_POSITION[SERVOS] = {
// ankle, knee, hip
    -PI2,  PI2, -PI4,    // front left
    -PI2,  PI2, -PI4,    // hind left
    -PI2,  PI2, -PI4,    // hind right
    -PI2,  PI2, -PI4     // front right
};

void servo_move(unsigned char servo, double rads) {
    // Move a servo to a position in radians between -PI/2 and PI/2.
    if (servo >= SERVOS) {
        return;
    }
    rads = rads * SERVO_REVERSE[servo] + PI2;
    while (rads > TAU) {
        rads -= TAU;
    }
    while (rads < 0) {
        rads += TAU;
    }
    int freq = (SERVO_FREQ_MAX -
                SERVO_FREQ_MIN) * rads / PI + SERVO_FREQ_MIN;
    freq = min(SERVO_FREQ_MAX,
               max(SERVO_FREQ_MIN,
                   freq + SERVO_TRIM[servo] * 10));
    servos[servo].writeMicroseconds(freq);
}

void servo_setup() {
    // Initialize all servos.
    // Start with hips.
    for (unsigned char servo = 2; servo < SERVOS; servo += 3) {
        servos[servo].attach(SERVO_PINS[servo],
                             SERVO_FREQ_MIN, SERVO_FREQ_MAX);
        servo_move(servo, HOME_POSITION[servo]);
        delay(150);
    }
    // Then ankles.
    for (unsigned char servo = 0; servo < SERVOS; servo += 3) {
        servos[servo].attach(SERVO_PINS[servo],
                             SERVO_FREQ_MIN, SERVO_FREQ_MAX);
        servo_move(servo, HOME_POSITION[servo]);
        delay(150);
    }
    // Finally knees.
    for (unsigned char servo = 1; servo < SERVOS; servo += 3) {
        servos[servo].attach(SERVO_PINS[servo],
                             SERVO_FREQ_MIN, SERVO_FREQ_MAX);
        servo_move(servo, HOME_POSITION[servo]);
        delay(150);
    }
}

void servo_shutdown() {
    // Power down all servos.
    for (unsigned char servo = 0; servo < SERVOS; ++servo) {
        servo_move(servo, FOLD_POSITION[servo]);
    }
    delay(500);
    for (unsigned char servo = 0; servo < SERVOS; ++servo) {
        servos[servo].detach();
    }
}
