#ifndef BEEP_H
#define BEEP_H

extern bool beep_mute;

void beep_setup(void);
void beep(int frequency, int duration);

#endif
