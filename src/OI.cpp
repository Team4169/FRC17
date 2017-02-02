#include "OI.h"

OI::OI() : controller(std::make_shared<XboxController>(0)){
	//Define controller to the one in port 0

	//Assign buttons to their correct numbers
	a = new JoystickButton(controller.get(), 1);
	b = new JoystickButton(controller.get(), 2);

	a->WhenPressed(new UpRope());
	b->WhenPressed(new DownRope());

}

std::shared_ptr<XboxController> OI::getController(){
	return controller;
}
