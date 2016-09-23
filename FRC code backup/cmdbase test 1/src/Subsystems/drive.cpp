#include "drive.h"
#include "../RobotMap.h"

drive::drive() :
		Subsystem("ExampleSubsystem")
{//ctor
	lmot = new Talon(1);
	rmot = new Talon(2);
	dtrain = new RobotDrive(lmot,rmot);
}

void drive::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
