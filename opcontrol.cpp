#include "main.h"
#include "global.h"

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

	bool intake = false;
	int capflip = 0;

	float target = 0;
	float current = 0;
	float error = 0;
	float lastError = 0;

	float P = 0;
	float I = 0;
	float D = 0;

	float integralLimit = 0;
	float integralZone = 0;

	float kp = 0;
	float ki = 0;
	float kd = 0;
	// tuning

	while (true) {

		int steer = master.get_analog(ANALOG_LEFT_X);
		int drive = master.get_analog(ANALOG_RIGHT_Y);

		bool intakeforwardm = master.get_digital(DIGITAL_R1);
		bool intakebackwardm = master.get_digital(DIGITAL_R2);
		bool intakeforwardp = partner.get_digital(DIGITAL_R1);
		bool intakebackwardp = partner.get_digital(DIGITAL_R2);
		bool intakestopp = partner.get_digital(DIGITAL_L2);
		bool intakestoppLeaingEdge = partner.get_digital_new_press(DIGITAL_L2);
		bool capfliptoggler = partner.get_digital_new_press(DIGITAL_L1);
		bool liftLowPost = partner.get_digital(DIGITAL_UP);
		bool liftHighpost = partner.get_digital(DIGITAL_LEFT);
		bool liftGroundLevel = partner.get_digital(DIGITAL_DOWN);

// all of the variables and inputs


		leftBackMotor = leftFrontMotor = drive + steer;
		rightBackMotor = rightFrontMotor = drive - steer;
// arcade drive

		if (intakestopp){
			intakeMotor = 0;
		}
		else if (intakeforwardp){
			intakeMotor = 127;
		}
		else if (intakebackwardp){
			intakeMotor = -127;
		}
		if (intakeforwardm){
			intakeMotor = 127;
		}
		else if (intakebackwardm){
			intakeMotor = -127;

		if ((intakestoppLeaingEdge && (intakeforwardm || intakebackwardm)) == true){
			master.rumble(".");
		}
// roller intake controls

		if(capfliptoggler && (capflip == 0)){
			capflip = 1;
		}

		if(capflip == 1){
			if(otherIntakePotentiometer.get_value() <= 1638){
				otherIntakeMotor = 127;
			}
			else{
				capflip = 2;
			}
		}
		if(capflip == 2){
			if(otherIntakePotentiometer.get_value() >= 50){
				otherIntakeMotor = -127;
			}
			else{
				capflip = 0;
			}
		}
		if(capflip == 0)
			otherIntakeMotor = 0;
// capflipper controls

	if(liftHighpost){
		target = 1638;
	}
	if(liftLowPost){
		target = 1200;
	}
	if(liftGroundLevel){
		target = 5;
	}

	if(partner.get_digital_new_press(DIGITAL_UP) || partner.get_digital_new_press(DIGITAL_LEFT) || partner.get_digital_new_press(DIGITAL_DOWN)){
		partner.rumble(".");
	}
		pros::delay(20);
	}

	while(true){
		current = liftPotentiometer.get_value();
		error = target - current;

		P = error * kp;

		if(fabs(error) <= integralZone){
			I = I + (error * ki);
			}
			if(I >= integralLimit){
				I = integralLimit;
				}
			if(I <= -(integralLimit)){
				I = -(integralLimit);
				}
		D = kd * (lastError - error);

		liftMotor = P + I + D;

		lastError = error;
	}
}
