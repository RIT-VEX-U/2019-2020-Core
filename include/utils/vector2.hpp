#ifndef _VECTOR2_
#define _VECTOR2_

#include <cmath>

class Vector2
{
public:

  float x = 0, y = 0;

  float get_length()
  {
    return sqrt((x*x) + (y*y));
  }

  float get_angle_rad()
  {
    return atan2(y, x);
  }

  float get_angle_deg()
  {
    return get_angle_rad() * (180.0/3.141592654);
  }

  void normalize(float max_val)
  {
    x /= max_val;
    y /= max_val;
  }

  const Vector2 operator+(const Vector2& rhs)
  {
    Vector2 rval;
    rval.setxy(x+rhs.x, y+rhs.y);
    return rval;
  }

  const Vector2 operator-(const Vector2& rhs)
  {
    Vector2 rval;
    rval.setxy(x-rhs.x, y-rhs.y);
    return rval;
  }

  bool operator==(const Vector2& rhs)
  {
    return (x==rhs.x) && (y==rhs.y);
  }

  bool operator!=(const Vector2& rhs)
  {
    return !(*this==rhs);
  }

  void setxy(float x, float y)
  {
    this->x = x;
    this->y = y;
  }

  void set_length_dir(float length, float dir)
  {
    x = length * cos(dir);
    y = length * sin(dir);
  }
};

#endif
