#define BEEP_PIN 13

bool beep_mute = false;


void beep_setup() {
    pinMode(BEEP_PIN, OUTPUT);
    beep(1760, 50);
    delay(100);
    beep(1975, 50);
    delay(50);
    beep(1760, 50);
}

void beep(int frequency, int duration) {
    if (beep_mute) {
        return;
    }
    tone(BEEP_PIN, frequency, duration);
}
