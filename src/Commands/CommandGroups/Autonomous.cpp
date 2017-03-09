#include "Autonomous.h"

#include "../../Robot.h"

#include "DriveForDistance.h"
#include "../TurnDegrees.h"
#include "../AlignRobot.h"

Autonomous::Autonomous(float drive_distance, float first_turn_angle, float second_turn_angle) : CommandGroup("Autonomous"){
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.
	AddSequential(new TurnDegrees(first_turn_angle));
	AddSequential(new DriveForDistance(drive_distance));
	AddSequential(new TurnDegrees(second_turn_angle));
	AddSequential(new AlignRobot());
	AddSequential(new DriveForDistance(kPlaceGearDistance));

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
