#include "misc.h"
#include "servos.h"
#include "beep.h"
#include "battery.h"
#include "creep.h"
#include "leg.h"

#include <avr/sleep.h>

// 0 -- Power off
// 1 -- Walk
// 2 -- Nothing
int robot_mode = 1;
const int trigPin = A4;
const int echo = A5;

long duration;
int distance;
void setup() {
    //battery_setup();
    servo_setup();
    //beep_setup();
    //ir_setup();
    pinMode(trigPin, OUTPUT);
    pinMode(echo, INPUT);
    Serial.begin(9600);
}

void loop() {
    switch (robot_mode) {
        case 0: // Power off
            servo_shutdown();
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();
            while (1) {
                delay(100);
            }
            break;
        case 1:
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
          
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
          
            duration = pulseIn(echo, HIGH);
            
            distance = duration*0.034/2;
            Serial.println(distance);
            if (distance > 10) {
              walk();      
            }
            //walk();
            break;
        case 2: // Nothing
            delay(100);
            break;
    }
    //ir_loop();
    //battery_loop();
}
