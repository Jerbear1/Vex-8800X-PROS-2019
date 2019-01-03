#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Controller partner(pros::E_CONTROLLER_PARTNER);
	pros::Motor backRightDrive(3, true);
	pros::Motor frontRightDrive(4, true);
	pros::Motor frontLeftDrive(2);
	pros::Motor backLeftDrive(1);
	pros::Motor intake(5);
	pros::Motor shooter(6, true);
	pros::Motor lift(7);
	pros::Motor pancake(8);
	while (true) {
		/*pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);*/
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		bool intakeyswitch = false;
		backRightDrive = right;
		frontRightDrive = right;
		backLeftDrive = left;
		frontLeftDrive = left;

			if(master.get_digital(DIGITAL_R1)){
				intake = 127;
			} else if(master.get_digital(DIGITAL_R2)){
				intake = -127;
			} else {
				intake = 0;
			}

			if(partner.get_digital(DIGITAL_R1)){
				lift = 127;
			} else if(partner.get_digital(DIGITAL_R2)){
				lift = -127;
			} else {
				lift = 0;
			}

		if(master.get_digital(DIGITAL_L1)){
			shooter = 127;
		} else {
			shooter = 0;
		}

		pros::delay(20);
	}
}
