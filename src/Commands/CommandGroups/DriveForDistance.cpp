#include "DriveForDistance.h"
#include "../AccelerateToSpeed.h"
#include "../AutoDrive.h"
#include "../SlowDown.h"

#include "../../Robot.h"

static std::shared_ptr<DriveTrain> getDriveTrain() {
	return Robot::GetInstance()->getDriveTrain();
}


DriveForDistance::DriveForDistance(float dist, float angle) : CommandGroup("DriveForDistance") {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	getDriveTrain()->setAutoDistance(dist);
	getDriveTrain()->getAHRS()->ResetDisplacement();

	if (dist < kMinDistance) {
		AddSequential(new AccelerateToSpeed(angle, kAccelerationRate));
		AddSequential(new SlowDown(angle, kAccelerationRate));
	} else {
		AddSequential(new AccelerateToSpeed(kSpeed, angle, kAccelerationRate));
		AddSequential(new AutoDrive(kSpeed, angle));
		AddSequential(new SlowDown(kSpeed, angle, kAccelerationRate));
	}

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
