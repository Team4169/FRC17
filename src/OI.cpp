#include "OI.h"
#include "Commands/UpRope.h"
#include "Commands/DownRope.h"
#include "Commands/TestMotors.h"

OI::OI() : controller(std::make_shared<XboxController>(0)){
	//Define controller to the one in port 0

	//Assign buttons to their correct numbers
	a = std::make_shared<JoystickButton>(controller.get(), A_Button);
	b = std::make_shared<JoystickButton>(controller.get(), B_Button);

}

std::shared_ptr<XboxController> OI::getController(){
	return controller;
}
