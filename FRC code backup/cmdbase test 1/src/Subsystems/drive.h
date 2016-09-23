#ifndef drive_H
#define drive_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class drive: public Subsystem
{
private:
	SpeedController *lmot,*rmot;
	RobotDrive* dtrain;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	drive();
	void InitDefaultCommand();
};

#endif
