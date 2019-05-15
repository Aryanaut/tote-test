#ifndef SERVOS_H
#define SERVOS_H

// Number of servos.
#define SERVOS 12

void servo_move(unsigned char servo, double rads);
void servo_setup(void);
void servo_shutdown(void);

#endif
