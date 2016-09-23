#include "WPILib.h"

/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{

	/*
	 * config.quoththemotor.rar
	 * 2	1
	 * 3	0
	 */
    // Channels for the wheels
    const static int frontLeftChannel	= 2;
    const static int rearLeftChannel	= 3;
    const static int frontRightChannel	= 1;
    const static int rearRightChannel	= 0;
    //oh what joy(stick)
    const static int joystickChannel	= 0;

	RobotDrive vroomer;	// robot drive system
	Joystick ifyouknowwhatimean;

public:
	Robot() :
			vroomer(frontLeftChannel, rearLeftChannel,frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			ifyouknowwhatimean(joystickChannel)								// as they are declared above.
	{
		vroomer.SetExpiration(0.1);
		vroomer.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);	// invert the left side motors
		vroomer.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);	// you may need to change or remove this to match your robot
	}
	/**
	 * Runs the motors with Mecanum drive.
	 */
	void OperatorControl()
	{
		vroomer.SetSafetyEnabled(false);
		while (IsOperatorControl() && IsEnabled())
		{
        	// Use the joystick X axis for lateral movement, Y axis for forward movement, and Z axis for rotation.
        	// This sample does not use field-oriented drive, so the gyro input is set to zero.
			vroomer.MecanumDrive_Cartesian(ifyouknowwhatimean.GetX(), ifyouknowwhatimean.GetY(), ifyouknowwhatimean.GetZ());
			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
};

START_ROBOT_CLASS(Robot);
