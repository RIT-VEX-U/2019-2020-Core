#ifndef _PID_
#define _PID_

#include "pros/rtos.h"
#include <cmath>

class PID
{
public:
// Configuration of the PID loop
struct config_t
{
    double p = 0;
    double i = 0;
    double d = 0;
    double feedforward = 0;
    double deadband = 0;
    double on_target_time = 0;
};

private:

config_t *config;

double last_error = 0;
double last_time = 0;
double on_target_last_time = 0;
bool is_checking_on_target = false;

double lower_limit = 0, upper_limit = 0;
double target = 0, sensorVal = 0, out = 0;
double accum_error = 0;

public:

/**
 * Update the PID loop by taking the time difference from last update,
 * and running the PID formula with the new sensor data
 */
void update(double sensorVal);

/**
 * Reset the PID loop by resetting time since 0 and accumulated error.
 */
void reset();

/**
 * Gets the current PID out value, from when update() was last run
 */
double get();

/**
 * Get the delta between the current sensor data and the target
 */
double get_error();

/**
 * Set the target for the PID loop, where the robot is trying to end up
 */
void set_target(double target);

/**
 * Set the limits on the PID out. The PID out will "clip" itself to be 
 * between the limits.
 */
void set_limits(double lower, double upper);

/**
 * Returns true if the loop is within [deadband] for [on_target_time]
 * seconds
 */
bool is_on_target();

/**
 * Create the PID object with a configuration.
 */
PID(config_t *config) :
config(config)
{

}
};

#endif