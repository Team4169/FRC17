#include "OI.h"
#include "Commands/UpRope.h"
#include "Commands/DownRope.h"

OI::OI() : controller(std::make_shared<XboxController>(0)){
	//Define controller to the one in port 0

	//Assign buttons to their correct numbers
	a = std::make_shared<JoystickButton>(controller.get(), 1);
	b = std::make_shared<JoystickButton>(controller.get(), 2);

	a->WhenPressed(new UpRope());
	b->WhenPressed(new DownRope());

}

std::shared_ptr<XboxController> OI::getController(){
	return controller;
}
