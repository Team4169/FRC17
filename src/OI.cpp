#include "OI.h"

#include <WPILib.h>

OI::OI() {
	// Process operator interface input here.
	controller = new XboxController(0);
}
