#ifndef CREEP_H
#define CREEP_H

/* Walking speed. */
extern double creep_dx; // Sideways.
extern double creep_dy; // Forward.
extern double creep_spread;
extern double creep_rotation;
extern double creep_height;

/* Perform one step of the creep gait with the current speed. */
void walk();

#endif
