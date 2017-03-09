/*
 * AHRSAccelerationSource.h
 *
 *  Created on: Mar 9, 2017
 *      Author: necrodrake101
 */

#ifndef SRC_AHRSACCELERATIONSOURCE_H_
#define SRC_AHRSACCELERATIONSOURCE_H_

#include <AHRS.h>
#include <PIDSource.h>

class AHRSAccelerationSource: public frc::PIDSource {
public:
	AHRSAccelerationSource(AHRS* ah);
	virtual ~AHRSAccelerationSource();
	double PIDGet();
private:
	AHRS* ahrs;
};

#endif /* SRC_AHRSACCELERATIONSOURCE_H_ */
