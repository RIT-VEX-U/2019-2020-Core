#ifndef _GYRO_
#define _GYRO_

#include <stdint.h>
#include "api.h"

class Gyro
{
private:

  const uint8_t port;
  const double multiplier;

  // Thread written variables
  double gyro_pos = 0;
  double gyro_vel = 0;
  double gyro_accel = 0;
  uint32_t last_time = 0;
  uint32_t thread_delay = 5;


  /**
  All the code that runs when the gyro thread is created
  */
  void gyro_task_fn(void* params)
  {
    last_time = pros::millis();
    while(true)
    {
      // Time difference between last loop and now
      uint32_t new_time = pros::millis();
      double time_diff = (new_time - last_time) / 1000.0;
      last_time = new_time;

      uint32_t analog_in = pros::c::adi_port_get_value(port) - 2048;

      gyro_accel = multiplier * analog_in;
      gyro_vel += multiplier * analog_in * time_diff;
      gyro_pos += (.5) * multiplier * analog_in * (time_diff * time_diff);

      pros::delay(thread_delay);
    }
  }

  pros::Task gyro_task(void (*gyro_task_fn));

public:
  static constexpr double VEX_GYRO_MULT = 1.0;

  double get_pos()
  {
    return gyro_pos;
  }

  double get_vel()
  {
    return gyro_vel;
  }

  double get_accel()
  {
    return gyro_accel;
  }

  /**
  Create a gyro object using the analog input through the legacy port.
  */
  Gyro(uint8_t legacy_port, double multiplier):
  port(legacy_port), multiplier(multiplier)
  {
    pros::c::adi_port_set_config(port, E_ADI_ANALOG_IN);
  }

};

#endif
