#ifndef CLOCK_H
#define CLOCK_H

#define FPS 25

const unsigned char TICK = 1000 / FPS;
void tick(unsigned int ms);

#endif
