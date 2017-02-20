#include "Autonomous.h"

#include "../../Robot.h"

#include "DriveForDistance.h"
#include "../TurnDegrees.h"
#include "../AlignRobot.h"

Autonomous::Autonomous(float drive_distance, float drive_angle, float turn_angle) : CommandGroup("Autonomous"){
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	AddSequential(new DriveForDistance(drive_distance, drive_angle));
	AddSequential(new TurnDegrees(turn_angle));
	AddSequential(new AlignRobot());
	AddSequential(new DriveForDistance(kPlaceGearDistance, 0));

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
