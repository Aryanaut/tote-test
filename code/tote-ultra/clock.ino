#include "clock.h"

void tick(unsigned int ms) {
    // Wait remaining time to delay ms milliseconds since last call.
    static unsigned long last = 0;
    unsigned long now = millis();
    long wait = last + ms - now;
    if (wait > 0) {
        delay(wait);
    } else {
        // Somehow engage a time machine here to go back in time.
    }
    last = now;
}
