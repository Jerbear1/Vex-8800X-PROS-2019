#include "main.h"
#define _PROS_GLOBAL_H_

pros::Motor leftFrontMotor(1);
pros::Motor rightFrontMotor(2);
pros::Motor leftBackMotor(3);
pros::Motor rightBackMotor(4);
pros::Motor intakeMotor(5);
pros::Motor CATapultMotor(6);
pros::Motor liftMotor(7);
pros::Motor otherIntakeMotor(8);
pros::ADIAnalogIn otherIntakePotentiometer(1);
pros::ADIAnalogIn liftPotentiometer(2);


extern bool allianceColor; // true = red
extern bool startingSpot; // true = front
