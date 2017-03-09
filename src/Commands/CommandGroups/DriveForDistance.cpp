#include "DriveForDistance.h"
#include "../AccelerateToSpeed.h"
#include "../AutoDrive.h"
#include "../SlowDown.h"

#include "../../Robot.h"

static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}


DriveForDistance::DriveForDistance(float dist) : CommandGroup("DriveForDistance") {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	getDriveTrain()->getAHRS()->Reset();
	getDriveTrain()->getAutoTimer()->Start();
	AddSequential(new AccelerateToSpeed(kSpeed, kAccelerationRate));
	if ((kSpeed*kSpeed)/kAccelerationRate <= dist) AddSequential(new AutoDrive(dist, kSpeed));
	AddSequential(new SlowDown(kAccelerationRate));


	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
