#include "Robot.h"

#include <thread>
#include <chrono>
#include "GripPipeline.h"
#include "Commands/TurnDegrees.h"

static Robot *mRobotPointer = NULL;


Robot::Robot(){
	if(mRobotPointer == NULL){
		mRobotPointer = this;
	}
	table = NetworkTable::GetTable("Vision_Info");
}

void Robot::VisionThread(){

    cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
	camera.SetResolution(CAMERA_IMG_WIDTH, CAMERA_IMG_HEIGHT);
	camera.SetExposureManual(15);
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();

	cs::CvSource outputStream = CameraServer::GetInstance()->
						PutVideo("Rectangle", CAMERA_IMG_WIDTH, CAMERA_IMG_HEIGHT);
	cv::Mat mat;
	grip::GripPipeline* visionPipeline = new grip::GripPipeline();
	while(true){
		camera.SetExposureManual((int)SmartDashboard::GetNumber("CameraExposure", 15));
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	        if (cvSink.GrabFrame(mat) == 0) {
		        // Send the output the error.
		        outputStream.NotifyError(cvSink.GetError());
			// skip the rest of the current iteration
			continue;
		}
		visionPipeline->Process(mat);
		outputStream.PutFrame(*(visionPipeline->getRectanglesMat()));
	}


}


void Robot::RobotInit() {

	driveTrain = std::make_shared<DriveTrain>();
	ropeClimber = std::make_shared<RopeClimber>();
	oi = std::make_shared<OI>();

	//chooser.AddDefault("90 Degrees", new TurnDegrees(90));
	//chooser.AddObject("45 Degrees", new TurnDegrees(45));
	frc::SmartDashboard::PutData(Scheduler::GetInstance());
	frc::SmartDashboard::PutData(driveTrain.get());
	frc::SmartDashboard::PutData(ropeClimber.get());
	frc::SmartDashboard::PutBoolean("Gyro Connected?", driveTrain->getAHRS()->IsConnected());
	frc::SmartDashboard::PutBoolean("Gyro Calibrating?", driveTrain->getAHRS()->IsCalibrating());
	frc::SmartDashboard::PutNumber("CameraExposure", 15);

	driveTrain->Reset();
	driveTrain->getAHRS()->Reset();
	ropeClimber->Stop();

	chooser.AddDefault("90 degrees", new TurnDegrees(90));
	chooser.AddObject("45 degrees", new TurnDegrees(45));
	chooser.AddObject("-45 degrees", new TurnDegrees(-45));
	chooser.AddObject("-90 degrees", new TurnDegrees(-90));


	//std::thread visionThread(VisionThread);
	//visionThread.detach();

}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	frc::SmartDashboard::PutNumber("Angle", driveTrain->getAHRS()->GetAngle());
	frc::SmartDashboard::PutNumber("X Displacement", driveTrain->getAHRS()->GetDisplacementX());
	frc::SmartDashboard::PutNumber("Y Displacement", driveTrain->getAHRS()->GetDisplacementY());
	frc::SmartDashboard::PutData("Gyro", driveTrain->getAHRS());
}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to the
	 * chooser code above (like the commented example) or additional comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
void Robot::AutonomousInit() {
	/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
	if (autoSelected == "My Auto") {
		autonomousCommand.reset(new MyAutoCommand());
	}
	else {
		autonomousCommand.reset(new ExampleCommand());
	} */
	/*autonomousCommand.reset(chooser.GetSelected());
	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Start();
	}*/
	autonomousCommand.reset(new TurnDegrees(90));
	autonomousCommand->Start();
}
void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
  
	frc::SmartDashboard::PutBoolean("Gyro Connected?", driveTrain->getAHRS()->IsConnected());
	frc::SmartDashboard::PutNumber("Angle", driveTrain->getAHRS()->GetAngle());
	frc::SmartDashboard::PutNumber("X Displacement", driveTrain->getAHRS()->GetDisplacementX());
	frc::SmartDashboard::PutNumber("Y Displacement", driveTrain->getAHRS()->GetDisplacementY());
}
void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Cancel();
	}
	frc::SmartDashboard::PutBoolean("Gyro Connected?", driveTrain->getAHRS()->IsConnected());
}
void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	frc::SmartDashboard::PutBoolean("Gyro Connected?", driveTrain->getAHRS()->IsConnected());
	frc::SmartDashboard::PutNumber("Angle", driveTrain->getAHRS()->GetAngle());
	frc::SmartDashboard::PutNumber("X Displacement", driveTrain->getAHRS()->GetDisplacementX());
	frc::SmartDashboard::PutNumber("Y Displacement", driveTrain->getAHRS()->GetDisplacementY());
	frc::SmartDashboard::PutString("DirectionString", table->GetString("Direction", ""));
	frc::SmartDashboard::PutNumber("Distance", table->GetNumber("Distance", 0));
	frc::SmartDashboard::PutBoolean("A Button", GetInstance()->getOI()->getController()->GetAButton());
	frc::SmartDashboard::PutBoolean("B Button", GetInstance()->getOI()->getController()->GetBButton());
	frc::SmartDashboard::PutNumber("Right Trigger", GetInstance()->getOI()->getController()->GetTriggerAxis(GenericHID::kRightHand));
	frc::SmartDashboard::PutNumber("Left Trigger", GetInstance()->getOI()->getController()->GetTriggerAxis(GenericHID::kLeftHand));
	frc::SmartDashboard::PutNumber("X", GetInstance()->getOI()->getController()->GetX(GenericHID::kLeftHand));
	frc::SmartDashboard::PutNumber("Y", GetInstance()->getOI()->getController()->GetY(GenericHID::kLeftHand));
	frc::SmartDashboard::PutBoolean("X Button", oi->getController()->GetXButton());
	frc::SmartDashboard::PutBoolean("Y Button", oi->getController()->GetYButton());
}
void Robot::TestPeriodic() {
	frc::LiveWindow::GetInstance()->Run();
}

std::shared_ptr<ExampleSubsystem> Robot::getExampleSubsystem() {
	return exampleSubsystem;
}

std::shared_ptr<DriveTrain> Robot::getDriveTrain() {
	return driveTrain;
}

std::shared_ptr<RopeClimber> Robot::getRopeClimber() {
	return ropeClimber;
}

std::shared_ptr<OI> Robot::getOI() {
	return oi;
}

Robot *Robot::GetInstance() {
	return mRobotPointer;
}

START_ROBOT_CLASS(Robot)
