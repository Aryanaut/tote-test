#include "creep.h"
#include "leg.h"
#include "servos.h"
#include "misc.h"
#include "beep.h"
#include "IRLremote.h"


#define IR_INTERRUPT 0 // Sensor on PIN 2
#define IR_PROTOCOL IR_NEC
#define IR_ADDRESS 0xFF00

#define KEY_UP      0xBF40 // Up arrow.
#define KEY_DOWN    0xE619 // Down arrow.
#define KEY_LEFT    0xF807 // Left arrow.
#define KEY_RIGHT   0xF609 // Right arrow.
#define KEY_REV     0xF30C // Rewind.
#define KEY_PLAY    0xE718 // Play/pause.
#define KEY_FF      0xA15E // Fast forward.
#define KEY_CHMINUS 0xF708 // Channel minus.
#define KEY_CHPLUS  0xA55A // Channel plus.
#define KEY_CHLEVEL 0xE31C
#define KEY_VOLDOWN 0xBD42 // Volume down.
#define KEY_MUTE    0xAD52 // Mute.
#define KEY_VOLUP   0xB54A // Volume up.
#define KEY_POWER   0xBA45 // Power.
#define KEY_POWER2  0xAF50 // Power.
#define KEY_SEARCH  0xBB44 // Search.
#define KEY_HOME    0xB847 // Home.
#define KEY_OK      0xEA15 // OK.


extern int robot_mode;


void ir_setup() {
    IRLbegin<IR_ALL>(IR_INTERRUPT);
    pinMode(3, OUTPUT);
}

void ir_loop() {
    static uint32_t last=0;
    uint32_t IRcommand = 0;

    if (!IRLavailable()) {
        return;
    }

    IRcommand = IRLgetCommand();

    if (IRcommand == 0xFFFF) {
        IRcommand = last;
    } else if (IRLgetAddress() != IR_ADDRESS) {
        IRLreset();
        return; // React only to my remote.
    }
    last = IRcommand;

    beep(1319, 50);

    switch (IRcommand) {
        case KEY_UP:    // Up arrow.
            creep_dy = min(3, creep_dy + 0.25);
            break;
        case KEY_DOWN:    // Down arrow.
            creep_dy = max(-3, creep_dy - 0.25);
            break;
        case KEY_LEFT:    // Left arrow.
            creep_rotation = min(PI/90, creep_rotation + PI/360);
            break;
        case KEY_RIGHT:    // Right arrow.
            creep_rotation = max(-PI/90, creep_rotation - PI/360);
            break;
        case KEY_REV:    // Rewind.
            creep_spread = max(-10.0, creep_spread - 1);
            break;
        case KEY_PLAY:    // Play/pause.
            creep_spread = 0.0;
            break;
        case KEY_FF:    // Fast forward.
            creep_spread = min(10.0, creep_spread + 1);
            break;
        case KEY_CHMINUS:    // Channel minus.
            creep_height = max(TIBIA * 0.25, creep_height - 1);
            break;
        case KEY_CHPLUS:    // Channel plus.
            creep_height = min(TIBIA * 1.25, creep_height + 1);
            break;
        case KEY_CHLEVEL:
            creep_height = TIBIA * 0.80;
            break;
        case KEY_VOLDOWN:    // Volume down.
            creep_dx = max(-1.0, creep_dx - 0.25);
            break;
        case KEY_MUTE:    // Mute.
            beep_mute = !beep_mute;
            break;
        case KEY_VOLUP:    // Volume up.
            creep_dx = min(1.0, creep_dx + 0.25);
            break;
        case KEY_POWER:    // Power.
        case KEY_POWER2:    // Power.
            robot_mode = 0;
            break;
        case KEY_SEARCH:    // Search.
            digitalWrite(3, !digitalRead(3));
            break;
        case KEY_HOME:    // Home.
            for (unsigned char leg=0; leg < 4; ++leg) {
                move_leg(leg, HOME, HOME, TIBIA);
            }
            break;
        case KEY_OK:    // OK.
            creep_dx = 0.0;
            creep_dy = 0.0;
            creep_rotation = 0.0;
            break;
    }
    IRLreset();
}
