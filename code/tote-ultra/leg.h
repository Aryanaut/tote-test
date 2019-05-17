#ifndef LEG_H
#define LEG_H

#ifdef TOTE2
// For version 2:
#define COXA    12.0
#define FEMUR   42.0
#define TIBIA   38.5
#define BASE    21.0
#else
// For version 1:
#define COXA    8.0
#define FEMUR   20.5
#define TIBIA   28.5
#define BASE    18.5
#endif

const signed char LEG_X[4] = {-1, -1, 1, 1};
const signed char LEG_Y[4] = {1, -1, -1, 1};
extern double leg_position[4][3];
const double HOME = (COXA + FEMUR) / SQRT2;

bool move_leg(unsigned char leg, double x, double y, double z);
bool move_leg_by(unsigned char leg, double dx, double dy, double dz);
bool rotate_leg_by(unsigned char leg, double angle);

#endif
