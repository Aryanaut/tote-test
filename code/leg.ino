#include "misc.h"
#include "leg.h"

const unsigned char LEG_JOINT[4][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {9, 10, 11},
};

double leg_position[4][3] = {
    {HOME, LEG_Y[0] * HOME, -TIBIA},
    {HOME, LEG_Y[0] * HOME, -TIBIA},
    {HOME, LEG_Y[0] * HOME, -TIBIA},
    {HOME, LEG_Y[0] * HOME, -TIBIA},
};


double _solve_triangle(double a, double b, double c) {
    // Calculate the angle between a and b, opposite to c.
    a = abs(a);
    b = abs(b);
    c = abs(c);
    c = min(c, a + b);
    b = min(b, a + c);
    a = min(a, b + c);
    return acos((a * a + b * b - c * c) / (2 * a * b));
}

double _norm(double a, double b) {
    // Calculate the norm of a vector.
    return sqrt(a * a + b * b);
}

bool _inverse_kinematics(double x, double y, double z,
                         double *ankle, double *knee, double *hip) {
    // Calculate angles for knee and ankle, and put them in those variables.
    // Return true on success, and false if x and y are out of range.
    double f = _norm(x, y) - COXA;
    double d = _norm(f, z);
    d = min(d, FEMUR + TIBIA);
    *hip = atan2(y, x);
    if (isnan(*hip)) { return false; }
    *knee = _solve_triangle(FEMUR, d, TIBIA) - atan2(-z, f);
    if (isnan(*knee)) { return false; }
    *ankle = _solve_triangle(FEMUR, TIBIA, d) - PI2;
    if (isnan(*ankle)) { return false; }
    return true;
}

bool move_leg(unsigned char leg, double x, double y, double z) {
    // Move the tip of the leg to x, y. Return false when out of range.
    double ankle = NAN;
    double knee = NAN;
    double hip = NAN;
    leg_position[leg][0] = x;
    leg_position[leg][1] = y;
    leg_position[leg][2] = z;
    if (!_inverse_kinematics(x, y, z, &ankle, &knee, &hip)) {
        return false;
    }
    hip -= PI4;
    servo_move(LEG_JOINT[leg][0], ankle);
    servo_move(LEG_JOINT[leg][1], knee);
    servo_move(LEG_JOINT[leg][2], hip);
    return true;
}

bool move_leg_by(unsigned char leg, double dx, double dy, double dz) {
    // Move the tip of the leg by dx, dy. Return false when out of range.
    return move_leg(leg,
                    leg_position[leg][0] + dx,
                    leg_position[leg][1] + dy,
                    leg_position[leg][2] + dz);
}

bool rotate_leg_by(unsigned char leg, double angle) {
    // Rotate the tip of the leg around the center of robot's body.
    double x = leg_position[leg][0] + BASE;
    double y = leg_position[leg][1] + BASE;
    double nx = x * cos(angle) - y * sin(angle) - BASE;
    double ny = x * sin(angle) + y * cos(angle) - BASE;
    return move_leg(leg, nx, ny, leg_position[leg][2]);
}
