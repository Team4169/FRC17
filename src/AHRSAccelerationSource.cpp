/*
 * AHRSAccelerationSource.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: necrodrake101
 */

#include <AHRSAccelerationSource.h>

AHRSAccelerationSource::AHRSAccelerationSource(AHRS* ah) {
	// TODO Auto-generated constructor stub
	ahrs = ah;
	SetPIDSourceType(frc::PIDSourceType::kRate);
}

AHRSAccelerationSource::~AHRSAccelerationSource() {
	// TODO Auto-generated destructor stub
}

double AHRSAccelerationSource::PIDGet() {
	return ahrs->GetWorldLinearAccelY();
}
