#ifndef RopeClimber_H
#define RopeClimber_H

#include <Commands/Subsystem.h>
#include <CANTalon.h>



class RopeClimber : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> motor;
public:
	RopeClimber();
	void InitDefaultCommand();
	void Up();
	void Down();
	void Stop();
};

#endif  // RopeClimber_H
