#pragma systemFile	// eliminate warning for "unreferenced" functions
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                        Copyright (c) James Pearman                          */
/*                                   2011                                      */
/*                            All Rights Reserved                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*        Module:     MultiTask.c                                              */
/*        Author:     James Pearman                                            */
/*        Created:    13 Oct 2011                                              */
/*                                                                             */
/*        Revisions:  V0.1                                                     */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*        Description:                                                         */
/*                                                                             */
/*        Demo for slew rate motor control                                     */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  definitions used by driver control                                         */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

#define     JOY_DRIVE_V     vexJSLeftV
#define     JOY_DRIVE_H     vexJSLeftH
#define     JOY_THRESHOLD   15

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  definitiona and variables for the motor slew rate controller.              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

#define MOTOR_NUM               kNumbOfTotalMotors
#define MOTOR_MAX_VALUE         100
#define MOTOR_MIN_VALUE         (-100)
#define MOTOR_DEFAULT_SLEW_RATE 10      // Default will cause 375mS from full fwd to rev
#define MOTOR_FAST_SLEW_RATE    256     // essentially off
#define MOTOR_TASK_DELAY        15      // task 1/frequency in mS (about 66Hz)
#define MOTOR_DEADBAND          10

#define MOTOR_NUM2               6/*kNumbOfTotalMotors*/
#define MOTOR_MAX_VALUE2         127
#define MOTOR_MIN_VALUE2         (-127)
#define MOTOR_DEFAULT_SLEW_RATE2 4      // Default will cause 375mS from full fwd to rev
#define MOTOR_FAST_SLEW_RATE2    256     // essentially off
#define MOTOR_TASK_DELAY2        15      // task 1/frequency in mS (about 66Hz)
#define MOTOR_DEADBAND2          10

// Array to hold requested speed for the motors
int motorReq[ MOTOR_NUM ];
int motorReq2[ MOTOR_NUM2 ];

// Array to hold "slew rate" for the motors, the maximum change every time the task
// runs checking current mootor speed.
int motorSlew[ MOTOR_NUM ];
int motorSlew2[ MOTOR_NUM2 ];

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  Task  - compares the requested speed of each motor to the current speed    */
/*          and increments or decrements to reduce the difference as nexessary */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task MotorSlewRateTask()
{
	int motorIndex;
	int motorTmp;

	int motorIndex2;
	int motorTmp2;

	// Initialize stuff
	for(motorIndex2=0;motorIndex2<MOTOR_NUM2;motorIndex2++)
	{
		motorReq2[motorIndex2] = 0;
		motorSlew2[motorIndex2] = MOTOR_DEFAULT_SLEW_RATE2;
		//writeDebugStreamLine("for 2");
	}

	// Initialize stuff
	for(motorIndex=0;motorIndex<MOTOR_NUM;motorIndex++)
	{
		motorReq[motorIndex] = 0;
		motorSlew[motorIndex] = MOTOR_DEFAULT_SLEW_RATE;
		//writeDebugStreamLine("for 1");
	}



	// run task until stopped
	while( true )
	{
		// run loop for every motor
		for( int motorIndex=5; motorIndex<MOTOR_NUM; motorIndex++)
		{

		// So we don't keep accessing the internal storage
			motorTmp = motor[ motorIndex ];

			// Do we need to change the motor value ?
			if( motorTmp != motorReq[motorIndex] )
			{
				// increasing motor value
				if( motorReq[motorIndex] > motorTmp )
				{
					motorTmp += motorSlew[motorIndex];
					// limit
					if( motorTmp > motorReq[motorIndex] )
					{
						motorTmp = motorReq[motorIndex];
					}
				}

				// decreasing motor value
				if( motorReq[motorIndex] < motorTmp )
				{
					motorTmp -= motorSlew[motorIndex];
					// limit
					if( motorTmp < motorReq[motorIndex] )
					{
						motorTmp = motorReq[motorIndex];
					}
				}

				// finally set motor
				motor[motorIndex] = motorTmp;

			}
		}

		for( int motorIndex2=1; motorIndex2<MOTOR_NUM2; motorIndex2++)
		{

			// So we don't keep accessing the internal storage
			motorTmp2 = motor[ motorIndex2 ];

			// Do we need to change the motor value ?
			if( motorTmp2 != motorReq2[motorIndex2] )
			{
				// increasing motor value
				if( motorReq2[motorIndex2] > motorTmp2 )
				{
					motorTmp2 += motorSlew2[motorIndex2];
					// limit
					if( motorTmp2 > motorReq2[motorIndex2] )
					{
						motorTmp2 = motorReq2[motorIndex2];
					}
				}

				// decreasing motor value
				if( motorReq2[motorIndex2] < motorTmp2 )
				{
					motorTmp2 -= motorSlew2[motorIndex2];
					// limit
					if( motorTmp2 < motorReq2[motorIndex2] )
					{
						motorTmp2 = motorReq2[motorIndex2];
					}
				}

				// finally set motor
				motor[motorIndex2] = motorTmp2;
				//writeDebugStreamLine("for 2 2");
			}
		}

		// Wait approx the speed of motor update over the spi bus
		wait1Msec( MOTOR_TASK_DELAY2 );
	}
}

/*task MotorSlewRateTask2()
{
int motorIndex2;
int motorTmp2;

// Initialize stuff
for(motorIndex2=0;motorIndex2<MOTOR_NUM2;motorIndex2++)
{
motorReq2[motorIndex2] = 0;
motorSlew2[motorIndex2] = MOTOR_DEFAULT_SLEW_RATE2;
}

// run task until stopped
while( true )
{
// run loop for every motor
for( motorIndex2=0; motorIndex2<MOTOR_NUM2; motorIndex2++)
{
// So we don't keep accessing the internal storage
motorTmp2 = motor[ motorIndex2 ];

// Do we need to change the motor value ?
if( motorTmp2 != motorReq2[motorIndex2] )
{
// increasing motor value
if( motorReq2[motorIndex2] > motorTmp2 )
{
motorTmp2 += motorSlew2[motorIndex2];
// limit
if( motorTmp2 > motorReq2[motorIndex2] )
motorTmp2 = motorReq2[motorIndex2];
}

// decreasing motor value
if( motorReq2[motorIndex2] < motorTmp2 )
{
motorTmp2 -= motorSlew2[motorIndex2];
// limit
if( motorTmp2 < motorReq2[motorIndex2] )
motorTmp2 = motorReq2[motorIndex2];
}

// finally set motor
motor[motorIndex2] = motorTmp2;
}
}

// Wait approx the speed of motor update over the spi bus
wait1Msec( MOTOR_TASK_DELAY2 );
}
}*/

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                                                                             */
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
