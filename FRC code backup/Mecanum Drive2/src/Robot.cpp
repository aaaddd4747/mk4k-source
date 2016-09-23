#include "WPILib.h"
#include <iostream>
using namespace std;
/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{

    // Channels for the wheels
    const static int frontLeftChannel	= 2;
    const static int rearLeftChannel	= 3;
    const static int frontRightChannel	= 1;
    const static int rearRightChannel	= 0;

    const static int joystickChannel	= 0;

	RobotDrive robotDrive;	// robot drive system
	Joystick stick;			// only joystick
float ctrlCurve(float a,float kil)//control curve and deadzone
{
	a = -a;//account for stupidity
	bool mienNEG = false;
	//kil = 0.20;//deadzone control var
	if(a<0)//negative handling
	{
		a = -a;
		mienNEG = true;
	}
	if(a<kil)//deadzone implementation
	{
		a = 0;
	}
	else
	{
		a = (a-kil)/(1-kil);
	}
	//TODO implement curve
	if(mienNEG)//return to negatives
	{
		a = -a;
	}
	a = a*(-(stick.GetThrottle()-1)/2);//TODO make a better throttle implementation
	return a;//return to return
}
public:
	Robot() :
			robotDrive(frontLeftChannel, rearLeftChannel,
					   frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			stick(joystickChannel)								// as they are declared above.
	{
		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);	// invert the left side motors
		robotDrive.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);	// you may need to change or remove this to match your robot
	}

	/**
	 * Runs the motors with Mecanum drive.
	 */
	void Autonomous()//auto-nom, yum!
	{//placeholder test thingy
		robotDrive.SetExpiration(10);
		for(float i = 0;i<=1;i = i+0.01)
		{
			robotDrive.MecanumDrive_Cartesian(0,i,0);
			Wait(0.1);
		}
		/*for(float i = 0;i<=1;i = i+0.01)
		{
			robotDrive.MecanumDrive_Cartesian(0,1-i,0);
			Wait(0.1);
		}//*/
		Wait(3);
		robotDrive.MecanumDrive_Cartesian(0,0,0);
		robotDrive.SetExpiration(0.1);
	}
	void OperatorControl()
	{
		int POVerty;
		float mX,mY,mZ;//rawr.quothethemotor.rar
		robotDrive.SetSafetyEnabled(false);
		while (IsOperatorControl() && IsEnabled())
		{
			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
        	//read stick for user input
			mX = ctrlCurve(stick.GetX(),0.15);
			mY = ctrlCurve(stick.GetY(),0.10);
			mZ = 0.5*(ctrlCurve(stick.GetZ()-0.10,0.35));

			//POV hat test thingy
			POVerty = stick.GetPOV();
			cout << "POV: "<<POVerty<<endl;
			//handbrake (MUST BE LAST!!!1!1)
			if(stick.GetTrigger())
			{
				//robotDrive.MecanumDrive_Cartesian(0,0,0);
				mX = 0;
				mY = 0;
				mZ = 0;
			}

			//finally, send command to the motors
			robotDrive.MecanumDrive_Cartesian(mX,mY,mZ);
		}
	}

};

START_ROBOT_CLASS(Robot);
