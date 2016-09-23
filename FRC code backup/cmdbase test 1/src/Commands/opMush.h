#ifndef opMush_H
#define opMush_H

#include "../CommandBase.h"
#include "WPILib.h"

class opMush: public CommandBase
{
public:
	opMush();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
