#include "OI.h"

#include <WPILib.h>

OI::OI() {
	//Define controller to the one in port 0
	controller = new XboxController(0);

}
