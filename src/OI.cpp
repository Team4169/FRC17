#include "OI.h"
#include "Commands/UpRope.h"
#include "Commands/DownRope.h"
#include "Commands/TestMotors.h"

OI::OI() : controller(std::make_shared<XboxController>(0)){
	//Define controller to the one in port 0

	//Assign buttons to their correct numbers
	a = std::make_shared<JoystickButton>(controller.get(), 1);
	b = std::make_shared<JoystickButton>(controller.get(), 2);
	x = std::make_shared<JoystickButton>(controller.get(), 3);
	y = std::make_shared<JoystickButton>(controller.get(), 4);
	bumper = std::make_shared<JoystickButton>(controller.get(), 5);
	bumper2 = std::make_shared<JoystickButton>(controller.get(), 6);

	a->WhenPressed(new TestMotors(1));
	b->WhenPressed(new TestMotors(2));
	x->WhenPressed(new TestMotors(3));
	y->WhenPressed(new TestMotors(4));
	bumper->WhenPressed(new TestMotors(5));
	bumper2->WhenPressed(new TestMotors(6));



}

std::shared_ptr<XboxController> OI::getController(){
	return controller;
}
